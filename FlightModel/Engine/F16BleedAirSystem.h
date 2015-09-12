#ifndef _F16BLEEDAIRSYSTEM_H_
#define _F16BLEEDAIRSYSTEM_H_

#include "../stdafx.h"

namespace F16
{
	class F16BleedAirSystem
	{
	public:
		F16BleedAirSystem() {}
		~F16ElectricSystem() {}

		// update with engine/APU rpm/torque
		// and power consumption
		void updateFrame(const double frameTime)
		{
		}

	};
}

#endif // ifndef _F16BLEEDAIRSYSTEM_H_

