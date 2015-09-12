#ifndef _F16HYDRAULICPUMP_H_
#define _F16HYDRAULICPUMP_H_

#include "../stdafx.h"
#include "AbstractHydraulicDevice.h"

namespace F16
{
	// pump provides pressure to hydraulic system so that other devices can operate

	// TODO: need engine power to operate and generate pressure (ADG)

	// also reservoir?
	// maintain positive pressure at pump
	class F16HydraulicReservoir
	{
	public:
		F16HydraulicReservoir() {}
		~F16HydraulicReservoir() {}
	};

	class F16HydraulicPump : public AbstractHydraulicDevice
	{
	public:
		// pressure provided for devices
		// 3000 psi max?
		double pressure;

		F16HydraulicReservoir reservoir;

		F16HydraulicPump(void *_parentSystem) 
			: AbstractHydraulicDevice(_parentSystem)
			, pressure(0)
			, reservoir()
		{}
		~F16HydraulicPump() {}

		bool isWarning() const
		{
			if (pressure < 1000)
			{
				return true;
			}
			return false;
		}

		// engine RPM or torque here?
		void updateFrame(const double engineRpm, const double frameTime)
		{
			if (engineRpm > 0)
			{
				pressure = 3000;
			}
			else
			{
				pressure = 0;
			}
		}
	};
}

#endif // ifndef _F16HYDRAULICPUMP_H_


