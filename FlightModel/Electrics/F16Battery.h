#ifndef _F16BATTERY_H_
#define _F16BATTERY_H_

#include "../stdafx.h"

#include "Electrics/AbstractElectricDevice.h"

namespace F16
{
	class F16Battery : public AbstractElectricDevice
	{
	public:
		F16Battery(void *_parentSystem) 
			: AbstractElectricDevice(_parentSystem)
		{}
		~F16Battery() {}

		void updateFrame(const double frameTime)
		{
		}
	};
}

#endif // ifndef _F16BATTERY_H_

