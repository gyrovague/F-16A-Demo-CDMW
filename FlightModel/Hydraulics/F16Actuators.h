#ifndef _F16ACTUATORS_H_
#define _F16ACTUATORS_H_

#include "../stdafx.h"
#include <memory.h>
#include "../UtilityFunctions.h"

#include "AbstractHydraulicDevice.h"

namespace F16
{
	// TODO: speed brake handling..

	class Actuator
	{
	public:
		bool working; // in working order
		bool simInitialized;

		double max_position_DEG;
		double max_rate_DEGPERSEC;

		double position_DEG;
		double rate_DEGPERSEC;

		Actuator(const double max_pos_DEG, const double max_rate_DEGPERSEC) 
			: working(true)
			, simInitialized(false)
			, max_position_DEG(max_pos_DEG)
			, max_rate_DEGPERSEC(max_rate_DEGPERSEC)
			, position_DEG(0)
			, rate_DEGPERSEC(0)
		{}
		~Actuator() {}

		double command(const double commanded_DEG, const double frameTime)
		{
			if(!simInitialized)
			{
				simInitialized = true;
				position_DEG = commanded_DEG;
				return position_DEG;		
			}

			rate_DEGPERSEC = 20.2 * (commanded_DEG - position_DEG);
			rate_DEGPERSEC = limit(rate_DEGPERSEC, -max_rate_DEGPERSEC, max_rate_DEGPERSEC);

			position_DEG += (rate_DEGPERSEC * frameTime);
			position_DEG = limit(position_DEG, -max_position_DEG, max_position_DEG);

			return position_DEG;
		}
	};


	class F16Actuators
	{
	public:
		//Actuator leading_edge;
		Actuator elevator;
		Actuator aileron;
		Actuator rudder;
		//Actuator speedbrake;

		//Actuator landing_gear;

		F16Actuators() 
			: elevator(25.0, 60.0)
			, aileron(21.5, 56.0)
			, rudder(30.0, 120.0)
			//, speedbrake()
		{}
		~F16Actuators() {}

		double elevator_actuator(const double elevatorCommanded_DEG, const double frameTime)
		{
			return elevator.command(elevatorCommanded_DEG, frameTime);
		}

		double aileron_actuator(const double aileronCommanded_DEG, const double frameTime)
		{
			return aileron.command(aileronCommanded_DEG, frameTime);
		}

		double rudder_actuator(const double rudderCommanded_DEG, const double frameTime)
		{
			return rudder.command(rudderCommanded_DEG, frameTime);
		}
	};
}

#endif // ifndef _F16ACTUATORS_H_
