#ifndef _F16GEARBOX_H_
#define _F16GEARBOX_H_

#include "../stdafx.h"

/*
main engine is connected to gearbox which powers 
hydraulic pumps, fuel pumps and has some torque resistance on engine.

also JFS is connected to gearbox for rotating engine, especially during startup.
*/

namespace F16
{
	class F16Gearbox
	{
	public:
		F16Gearbox() {}
		~F16Gearbox() {}

		// update with engine/APU rpm/torque
		// and power consumption
		void updateFrame(const double engineRPM, const double frameTime)
		{
		}

	};
}

#endif // ifndef _F16GEARBOX_H_

