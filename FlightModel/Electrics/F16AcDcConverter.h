#ifndef _F16ACDCCONVERTER_H_
#define _F16ACDCCONVERTER_H_

#include "../stdafx.h"

#include "Electrics/AbstractElectricDevice.h"

// also inverter/regulator?

namespace F16
{
	class F16AcDcConverter : public AbstractElectricDevice
	{
	public:
		F16AcDcConverter(void *_parentSystem) 
			: AbstractElectricDevice(_parentSystem)
		{}
		~F16AcDcConverter() {}

		void updateFrame(const double frameTime)
		{
		}

	};
}

#endif // ifndef _F16ACDCCONVERTER_H_

