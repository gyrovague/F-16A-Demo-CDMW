#ifndef _F16FUELSYSTEM_H_
#define _F16FUELSYSTEM_H_

#include "../stdafx.h"

namespace F16
{
	// we need fuel usage curve for the used engine here
	// also calculation for the mass of the fuel and position of it

	// F100-PW-229
	//Specific fuel consumption: Military thrust: 77.5 kg/(kN·h) (0.76 lb/(lbf·h)) Full afterburner: 197.8 kg/(kN·h) (1.94 lb/(lbf·h))

	/*
	For example: 
	49,000 PPH would be 7,000 gal/hr, 117 gal/min or 3 gal/sec 'roughly'. (Using 7 lbs/gal) 
	49,000 PPH would be 7,368 gal/hr, 123 gal/min or 2 gal/sec 'roughly'. (Using 6.65 lbs/gal) 
	*/

	// three externals: wings and centerline station
	// five internals: left and right wing tanks, two forward (F-1, F-2) and one aft (A-1) fuselage tank.
	// fwd & aft reservoir
	// total internal: [A] 6950 +- 300 (JP-4), 7290 +- 300 (JP-5/8) [B] 5650 +- 300, 5930 +- 300

	// JP8 weight 6.65lbs/gal ?

	// main fuel pump or AB fuel pump
	class F16FuelPump
	{
		// gearbox mounted on engine -> torque from engine to power fuel feeding?
	public:

		double fuel_flow;

		F16FuelPump() 
			: fuel_flow(0)
		{}
		~F16FuelPump() {}
	};


	// add:
	// - currently used (selected) station
	// - support for internal tanks and external (pylons)
	class F16FuelTank
	{
	public:
		int station; // do we need this here or not?

		double volume; // capacity of tank
		double fuel; // amount of fuel in tank

		double x;
		double y;
		double z;

		F16FuelTank(double _volume = 0, double _fuel = 0)
			: station(0)
			, volume(_volume)
			, fuel(_fuel)
			, x(0)
			, y(0)
			, z(0)
		{}
		~F16FuelTank() {}

		// add what is possible, return remaining if full
		double addFuel(const double addition)
		{
			double space = volume - fuel;
			if (space < addition)
			{
				fuel = volume; // set to max
				return (addition - space); // overflow
			}
			fuel += addition;
			return 0;
		}

		double decFuel(const double decrement)
		{
			if (fuel < decrement)
			{
				double tmp = decrement - fuel;
				fuel = 0; // set to min
				return tmp; // remaining
			}
			fuel -= decrement;
			return 0;
		}

		double getSpace() const
		{
			return (volume - fuel);
		}
	};

	// TODO: fuel transfer between internal tanks etc.

	class F16FuelSystem
	{
	protected:

		bool is_unlimited_fuel;
		double previous_usage;

		// Internal fuel as calculated by the EFM fuel system modeling
		//F16FuelTank FwdFus1; // foward fuselage 1
		//F16FuelTank FwdFus2; // forward fuselage 2
		//F16FuelTank FwdRes; // forward reservoir
		//F16FuelTank AftFus1; // aft fuselage
		//F16FuelTank AftRes; // aft reservoir

		F16FuelTank FwdFus; // forward combined
		F16FuelTank AftFus; // aft combined

		F16FuelTank LeftWing; // wing internal
		F16FuelTank RightWing; // wing internal

		// externals: one per wing plus centerline (if equipped)
		F16FuelTank ext_Center;
		F16FuelTank ext_LWing;
		F16FuelTank ext_RWing;

	public:
		// TODO: check units !! (pounds)
		// 0.45359237 (1/2.2046)

		F16FuelSystem() 
			: is_unlimited_fuel(false)
			, previous_usage(0)
			, FwdFus(3100 / 2.2046) // lb to kg
			, AftFus(2800 / 2.2046) 
			, LeftWing(525 / 2.2046)
			, RightWing(525 / 2.2046)
			, ext_Center(1800 / 2.2046)
			, ext_LWing(2300 / 2.2046)
			, ext_RWing(2300 / 2.2046)
		{}
		~F16FuelSystem() {}

		/* 
		// for weight-balance calculation,
		// we need amount of fuel in each tank and position
		double getFuelMass()
		{
			// JP8 weight 6.65lbs/gal ?
			//return getInternalFuel() * weightconstant;
			return 0;
		}
		*/

		// is low fuel indication
		bool isLowFuel() const
		{
			// check remining fuel
			if (getInternalFuel() <= 500)
			{
				return true;
			}
			return false;
		}

		// called on initialization and on refueling
		void setInternalFuel(const double fuel) // <- in kg
		{
			// distribute fuel to each tank for weight balance
			double addition = fuel;

			// TODO: transfer of fuel

			addition = AftFus.addFuel(addition);
			addition = FwdFus.addFuel(addition);

			addition = LeftWing.addFuel(addition);
			addition = RightWing.addFuel(addition);
		}
		double getInternalFuel() const
		{
			return (FwdFus.fuel + AftFus.fuel + LeftWing.fuel + RightWing.fuel);
		}

		// not ready yet
		void setExternalFuel(int station, double fuel, double x, double y, double z)
		{
		}
		// not ready yet
		double getExternalFuel() const
		{
			return 0;
		}

		void refuelAdd(const double fuel) // <- in kg
		{
			// TODO: transfer of fuel

			// aerial refuel support: add given amount of fuel
			setInternalFuel(fuel);
		}

		void dumpFuel(const double frameTime)
		{
			// TODO: transfer of fuel

			// amount of fuel dumped from tanks within frame,
			// decrement from tanks
		}

		void setUnlimitedFuel(bool status)
		{
			is_unlimited_fuel = status;
		}

		double getUsageSinceLastFrame() const
		{
			return previous_usage;
		}
		void clearUsageSinceLastFrame()
		{
			previous_usage = 0;
		}

		void updateFrame(const double fuelPerFrame, const double frameTime)
		{
			// TODO: decrement from tanks by order of usage
			// TODO: usage by throttle setting / altitude?

			if (is_unlimited_fuel == true)
			{
				return;
			}
			if (getInternalFuel() == 0 && is_unlimited_fuel == false)
			{
				return;
			}

			previous_usage += fuelPerFrame; // add to usage since last time updated

			double fueltmp = fuelPerFrame;

			// TODO: transfer of fuel between tanks

			fueltmp = RightWing.decFuel(fueltmp);
			fueltmp = LeftWing.decFuel(fueltmp);

			fueltmp = FwdFus.decFuel(fueltmp);
			fueltmp = AftFus.decFuel(fueltmp);
		}

		// internal fuel transfer
		void transferFuel()
		{
			// transfer from external tanks to wings and fuselage tanks when consuming

			// transfer from wings to fuselage tanks when consuming
		}
	};
}

#endif // ifndef _F16FUELSYSTEM_H_
