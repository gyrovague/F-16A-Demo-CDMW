#ifndef _F16EPU_H_
#define _F16EPU_H_

#include "../stdafx.h"

#include "Electrics/AbstractElectricDevice.h"

/*
EPU = emergency power unit
*/

namespace F16
{
	class F16EPU : public AbstractElectricDevice
	{
	public:
		F16EPU(void *_parentSystem) 
			: AbstractElectricDevice(_parentSystem)
		{}
		~F16EPU() {}

		void updateFrame(const double frameTime)
		{
		}

	};
}

#endif // ifndef _F16EPU_H_

