#ifndef _F16LANDINGGEAR_H_
#define _F16LANDINGGEAR_H_

#include "../stdafx.h"

#include "F16LandingWheel.h"
#include <Windows.h>

namespace F16
{
	// nosewheel steering (NWS) limited to 32 degrees in each direction

	// gears up/down status
	// weight-on-wheels
	// actuator movement
	// aerodynamic drag
	// wheelbrake deceleration
	// parking brake

	// anti-skid system

	// TODO: different friction coefficient on each surface?
	// (tarmac, concrete, grass, mud...)

	class F16LandingGear
	{
	protected:
		// precalculate some things
		const double gearZsin = sin(F16::degtorad);
		const double gearYcos = cos(F16::degtorad);

	public:
		double gearDownAngle;	// Is the gear currently down? (If not, what angle is it?)
		bool   geardownornot;
		bool nosewheelSteering; // is active/not
		double noseGearTurnAngle; // steering angle {-1=CW max;1=CCW max}

		// aerodynamic drag when gears are not fully up
		double CDGearAero;
		double CzGearAero;
		double CxGearAero;

		// free-rolling friction of all wheels combined
		// TODO: need to fix per-wheel friction and nose-wheel steering angle handling
		double CxRollingFriction;
		double CyRollingFriction;

		F16LandingWheel wheelNose;
		F16LandingWheel wheelLeft;
		F16LandingWheel wheelRight;

		bool parkingBreakOn;

		int geardownn = 0;

		F16LandingGear() 
			: gearDownAngle(0)
			, nosewheelSteering(true) // <- enable by default until button mapping works
			, noseGearTurnAngle(0)
			, CDGearAero(0)
			, CzGearAero(0)
			, CxGearAero(0)
			, CxRollingFriction(0)
			, CyRollingFriction(0)
			, wheelNose(0.479)
			, wheelLeft(0.68)
			, wheelRight(0.68)
			, parkingBreakOn(false)
		{
		}
		~F16LandingGear() {}

		bool isWoW()
		{
			if (wheelNose.isWoW()
				|| wheelLeft.isWoW()
				|| wheelRight.isWoW())
			{
				return true;
			}
			return false;
		}

		void setParkingBreak(bool OnOff)
		{
			parkingBreakOn = OnOff;
		}

		// joystick axis
		void setWheelBrakeLeft(double value)
		{
			// 0..1 from input
			if (GetAsyncKeyState(0x57) & 0x8000) wheelLeft.brakeInput = 1;
			else wheelLeft.brakeInput = 0;
		}
		// joystick axis
		void setWheelBrakeRight(double value)
		{
			// 0..1 from input
			if (GetAsyncKeyState(0x57) & 0x8000) wheelRight.brakeInput = 1;
			else  wheelRight.brakeInput = 0;
		}

		// key press DOWN
		void setWheelBrakesON()
		{
			wheelLeft.brakeInput = 1;
			wheelRight.brakeInput = 1;
		}
		// key press UP
		void setWheelBrakesOFF()
		{
			wheelLeft.brakeInput = 0;
			wheelRight.brakeInput = 0;
		}

		void setNosewheelSteeringON()
		{
				nosewheelSteering = true;
		}
		void setNosewheelSteeringOFF()
		{
				nosewheelSteering = false;
		}

		// TODO: joystick input is usually -100..100
		// and we have limit of 32 degrees each way
		// -> calculate correct nosewheel angle by input amount
		// or just "cut" out excess input?
		void nosewheelTurn(const double value)
		{
			// skip for now until button mapping works for it
			//if (nosewheelSteering == false)
			//{
				//return;
			//}
			
			/*if (isWoW() == false)
			{
				return;
			}*/
			// TODO: check value
			noseGearTurnAngle = value * 32.0;

			// for now, just cut input to allowed range in degrees
			//noseGearTurnAngle = limit(value, -32, 32);
		}

		// in case of nose wheel: 
		// calculate direction vector based on the turn angle
		// (polar to cartesian coordinates)
		Vec3 getNoseTurnDirection()
		{
			// in DCS body coordinates, (x,z) plane vector instead of (x,y) ?
			double x = cos(noseGearTurnAngle);
			double z = cos(noseGearTurnAngle);

			return Vec3(x, 0, z); // test!

			//Vec3 direction(1, 0, 0); // <- start with aligned to body direction
			// ..vector multiply by radians?
			// translation matrix?
			//return direction;
		}

		// nosegear turn -1..1 for drawargs
		float getNosegearTurn()
		{
			/*
			if (isWoW() == false)
			{
				return 0;
			}
			*/
			return (float)limit(noseGearTurnAngle, -1, 1);
		}

		// actual nosegear turn angle
		double getNosegearAngle()
		{
			/*
			if (isWoW() == false)
			{
				return 0;
			}
			*/
			return noseGearTurnAngle;
		}

		double getNoseGearDown()
		{
			return limit(gearDownAngle, 0, 1);
		}
		double getLeftGearDown()
		{
			
			return limit(gearDownAngle, 0, 1);
		}
		double getRightGearDown()
		{
			return limit(gearDownAngle, 0, 1);
		}

		void switchGearUpDown()
		{

			if (geardownn == 0)
			{
				// down -> up
				setGearUp();
			}
			else if (geardownn == 1)
			{
				// up -> down
				setGearDown();
			}
		}
		
		void setGearDown()
		{
			gearDownAngle = 1.0;

			// !! disabled for now
			//weight_on_wheels = 1;
		}
		void setGearUp()
		{
			gearDownAngle = 0;

			// !! disabled for now
			//weight_on_wheels = 0;
		}

		// need current weight of the whole aircraft
		// and speed relative to ground (static, sliding or rolling friction of each wheel)
		void updateFrame(const double groundSpeed, const double weightN, double frameTime)
		{
			gearAeroDrag();

			wheelNose.updateForceFriction(groundSpeed, weightN);
			wheelLeft.updateForceFriction(groundSpeed, weightN);
			wheelRight.updateForceFriction(groundSpeed, weightN);

			wheelFriction();

			wheelBrakeEffect(weightN);
		}

	protected:

		void gearAeroDrag(/*double airspeed?*/)
		{
			// TODO Gear aero (from JBSim F16.xml config)
			CDGearAero = 0.0270 * gearDownAngle; 
			CzGearAero = - (CDGearAero * gearZsin);
			CxGearAero = - (CDGearAero * gearYcos);
		}

		void wheelFriction()
		{
			// TODO: can we just add together like this?

			CxRollingFriction += wheelNose.CxWheelFriction;
			CxRollingFriction += wheelLeft.CxWheelFriction;
			CxRollingFriction += wheelRight.CxWheelFriction;

			CyRollingFriction += wheelNose.CyWheelFriction;
			CyRollingFriction += wheelLeft.CyWheelFriction;
			CyRollingFriction += wheelRight.CyWheelFriction;
		}

		void wheelBrakeEffect(const double weightN)
		{
			// TODO: also anti-skid system, wheel locking without it etc.

			// also include hydraulic system pressure for effective braking force (not just indicated)

			//wheelNose.wheelBrake();
			wheelLeft.wheelBrake();
			wheelRight.wheelBrake();
		}

		void brakeFluidUsage(double frameTime)
		{
			// TODO: there's fluid for approx. 75s (toe brakes)
			// parking brake usage does not deplete fluid
		}

		/*
		void updateStrutCompression()
		{
			// TODO: actual calculations of weight on each wheel,
			// especially force when landing unevenly etc.

			if (gearDownAngle == 0)
			{
				// retracted
				wheelNose.setStrutRetracted();
				wheelLeft.setStrutRetracted();
				wheelRight.setStrutRetracted();
			}
			else if (isWoW() == true)
			{
				// parking
				wheelNose.setStrutParking();
				wheelLeft.setStrutParking();
				wheelRight.setStrutParking();
			}
			else
			{
				// extended
				wheelNose.setStrutExtended();
				wheelLeft.setStrutExtended();
				wheelRight.setStrutExtended();
			}
		}
		*/
	};
}

#endif // ifndef _F16LANDINGGEAR_H_
