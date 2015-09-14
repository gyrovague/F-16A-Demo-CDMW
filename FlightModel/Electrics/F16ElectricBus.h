#ifndef _F16ELECTRICBUS_H_
#define _F16ELECTRICBUS_H_

#include "../stdafx.h"

//#include "Electrics/AbstractElectricDevice.h"

namespace F16
{
	class F16ElectricBus
	{
	protected:
		// type: AC no 1, AC no 2, DC "battery" bus
		// voltage
		// on/off
		// battery/generator status?

		//AbstractElectricDevice devices[];

	public:
		F16ElectricBus() {}
		~F16ElectricBus() {}

	
		void updateFrame(const double frameTime)
		{
		}

	};
}

#endif // ifndef _F16ELECTRICBUS_H_

