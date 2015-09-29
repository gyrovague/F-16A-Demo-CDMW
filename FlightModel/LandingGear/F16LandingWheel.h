#ifndef _F16LANDINGWHEEL_H_
#define _F16LANDINGWHEEL_H_

#include "../stdafx.h"

namespace F16
{
	// nosewheel steering (NWS) limited to 32 degrees in each direction

	// gears up/down status
	// weight-on-wheels
	// actuator movement
	// aerodynamic drag
	// wheelbrake deceleration
	// parking brake

	// TODO: different friction coefficient on each surface?
	// (tarmac, concrete, grass, mud...)


	class F16LandingWheel
	{
	protected:
		//const double rolling_friction;		// Rolling friction amount (constant now)
		//double slip_friction;		// TODO: Slip friction amount? (depends on surface as well..)
		//double forcefriction // <- direction and combined forces to calculate if maximum friction is exceeded?

		const double wheel_radius; //					  = 0.479,
		const double wheel_static_friction_factor; //  = 0.65 , --Static friction when wheel is not moving (fully braked)
		const double wheel_side_friction_factor; //    = 0.65 ,
		const double wheel_roll_friction_factor; //    = 0.025, --Rolling friction factor when wheel moving
		const double wheel_glide_friction_factor; //   = 0.28 , --Sliding aircraft
		const double wheel_damage_force_factor; //     = 250.0, -- Tire is explosing due to hard landing
		const double wheel_damage_speed; //			   = 150.0, -- Tire burst due to excessive speed
		const double wheel_moment_of_inertia; //		= 3.6, --wheel moi as rotation body
		const double wheel_brake_moment_max; //		= 15000.0, -- maximum value of braking moment  , N*m 

	public:
		double strutCompression;

		// current frictions applied on wheel
		double CxWheelFriction;
		double CyWheelFriction; // side-ways friction (should be Zbody axis)

		double brakeInput; // braking command/input from user
		double brakeForce; // result force

		// from DCS, see ed_fm_suspension_feedback()
		Vec3 actingForce;
		Vec3 actingForcePoint;
		double integrityFactor;
		bool Gearr = FALSE;

		F16LandingWheel(const double wheelRadius) 
			//: rolling_friction(0.03)
			: wheel_radius(wheelRadius) // all other same on each wheel? (check)
			, wheel_static_friction_factor(0.65)
			, wheel_side_friction_factor(0.65)
			, wheel_roll_friction_factor(0.025)
			, wheel_glide_friction_factor(0.28)
			, wheel_damage_force_factor(250.0)
			, wheel_damage_speed(150.0)
			, wheel_moment_of_inertia(3.6) // <- should be different for nose wheel? (smaller wheel)
			, wheel_brake_moment_max(15000.0)
			, strutCompression(0)
			, CxWheelFriction(0)
			, CyWheelFriction(0)
			, brakeInput(0)
			, brakeForce(0)
			, actingForce()
			, actingForcePoint()
			, integrityFactor(0)
		{}
		~F16LandingWheel() {}


		bool isWoW() const
		{
			if (Gearr == TRUE)
			{
				return true;
			}
			else return false;
		}

		

		void wheelBrake()
		{
			if (Gearr == FALSE)
			{
				// no weight on wheels?
				brakeForce = 0;
				return;
			}
			else
			{

				/*
				if (brakeInput <= 0)
				{
				return;
				}
				*/

				// TODO: find out some reasonable values,
				// do we need to have brake fading support as well?
				// TODO: also switch calculation to reduction in kinectic energy in motion handling
				// -> should calculate proper moment here
				brakeForce = 9000; // guess, find out reasonable value for this!!
				brakeForce = limit(brakeForce, 0, wheel_brake_moment_max);

				// just add it to rolling friction
				//CxWheelFriction += (wheel_roll_friction_factor * brakeFriction * weightN);
				//CyWheelFriction = 0.18 * weightN;
			}
		}

		void setActingForce(double x, double y, double z)
		{
			actingForce.x = x;
			actingForce.y = y;
			actingForce.z = z;
		}
		void setActingForcePoint(double x, double y, double z)
		{
			actingForcePoint.x = x;
			actingForcePoint.y = y;
			actingForcePoint.z = z;
		}
		void setIntegrityFactor(double d)
		{
			integrityFactor = d;
		}

		double getStrutCompression() const
		{
			return strutCompression;
		}

		// we might get this directly at initialization so set here
		void setStrutCompression(const double compression)
		{
			strutCompression = compression;
		}

		// calculate new direction of force and if it exceeds friction (begins sliding)
		// TODO: need ground speed here for rolling/static friction
		void updateForceFriction(const double groundSpeed, const double weightN)
		{
			// TODO: also if wheel rotation is slower than speed relative to ground
			// -> apply sliding friction factor
			if (GetAsyncKeyState(0x51) & 0x8000) Gearr = TRUE;
			else Gearr = FALSE;

			if (Gearr == TRUE)//groundSpeed > 0
			{
				// TODO: amount of weight per wheel instead?
				// also weight balance? wheel size?
				// TODO: nose-gear steering angle etc.
				
				CxWheelFriction = (-wheel_roll_friction_factor * weightN);

				// should have wheel_side_friction_factor ?
				//CyWheelFriction = 0.18 * weightN;
				//CyWheelFriction = wheel_side_friction_factor;
			}
			/*
			else if (isWoW() == true && groundSpeed == 0)
			{
				CxWheelFriction = wheel_static_friction_factor;
				CyWheelFriction = wheel_side_friction_factor;
			}
			*/
			else
			{
				// no weight on wheels
				CxWheelFriction = 0;
				CyWheelFriction = 0;
			}
		}
	};

}

#endif // ifndef _F16LANDINGWHEEL_H_
