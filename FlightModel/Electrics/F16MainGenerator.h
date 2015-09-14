#ifndef _F16MAINGENERATOR_H_
#define _F16MAINGENERATOR_H_

#include "../stdafx.h"

#include "Electrics/AbstractElectricDevice.h"

namespace F16
{
	// alternator
	class F16MainGenerator : public AbstractElectricDevice
	{
	public:
		F16MainGenerator(void *_parentSystem) 
			: AbstractElectricDevice(_parentSystem)
		{}
		~F16MainGenerator() {}

		void updateFrame(const double frameTime)
		{
		}

	};
}

#endif // ifndef _F16MAINGENERATOR_H_

