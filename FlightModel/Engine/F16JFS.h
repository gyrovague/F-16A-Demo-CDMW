#ifndef _F16JFS_H_
#define _F16JFS_H_

#include "../stdafx.h"

/*
JFS = Jet Fuel Starter,
gas turbine -> auxiliary drive gearbox -> clutch -> engine starter and maintains rpm
*/

namespace F16
{
	// two batteries "accumulators",
	// charged by hydraulic system
	//class F16JFSAccu

	// torque to main engine via ADG+clutch,
	// if engine "seized" clutch slippage
	// ..
	class F16JFS
	{
	public:
		F16JFS() {}
		~F16JFS() {}

		double getRpm() const
		{
			return 0;
		}
		double getRelatedRpm() const
		{
			return 0;
		}

		double getTemperature() const
		{
			return 0;
		}
		double getOilPressure() const
		{
			return 0;
		}
		double getFuelFlow() const
		{
			return 0;
		}

		void start()
		{
		}
		void stop()
		{
		}

		void updateFrame(const double frameTime)
		{
		}

	};
}

#endif // ifndef _F16JFS_H_

