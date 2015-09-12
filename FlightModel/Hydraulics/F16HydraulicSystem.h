#ifndef _F16HYDRAULICSYSTEM_H_
#define _F16HYDRAULICSYSTEM_H_

#include "../stdafx.h"

#include "Hydraulics/F16Actuators.h"				//Actuators model functions

#include "Hydraulics/F16HydraulicPump.h"

namespace F16
{
	//class F16HydraulicReservoir

	// amount of hydraulic fluid in system
	// pressure
	// pump

	class F16HydraulicSystem
	{
	public:
		//AbstractHydraulicDevice devices[];

		// two pumps: system A and system B
		// operated from ADG by engine
		F16HydraulicPump *pumpA;
		F16HydraulicPump *pumpB;

		//F16Actuator *leading_edge;
		//F16Actuator *aileron;
		//F16Actuator *elevator;
		//F16Actuator *rudder;
		//F16Actuator *speedbrake;

		//F16Actuator *landing_gear;

		F16HydraulicSystem() 
		{
			pumpA = new F16HydraulicPump(this);
			pumpB = new F16HydraulicPump(this);
		}
		~F16HydraulicSystem() 
		{
			delete pumpB;
			delete pumpA;
		}

		bool isWarning() const
		{
			if (pumpA->isWarning()
				|| pumpB->isWarning())
			{
				return true;
			}
			return false;
		}

		// need either engine torque or RPM here for pump operating information,
		// use RPM for now, also add power usage in actuators
		void updateFrame(const double engineRPM, const double frameTime)
		{
			pumpA->updateFrame(engineRPM, frameTime);
			pumpB->updateFrame(engineRPM, frameTime);
		}

	};
}

#endif // ifndef _F16HYDRAULICSYSTEM_H_

