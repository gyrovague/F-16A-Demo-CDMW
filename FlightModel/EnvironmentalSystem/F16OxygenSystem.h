#ifndef _F16OXYGENSYSTEM_H_
#define _F16OXYGENSYSTEM_H_

#include "../stdafx.h"

namespace F16
{
	// amount of bleed air from engine (oxygen generator)
	// oxygen tanks
	// valve open/not
	// pressurization

	// 5-liter liquid oxygen -> diluter (0..100 percent O2)

	class F16OxygenSystem
	{
	protected:
		const double tank_volume; // whole volume of tank
		double tank_usage; // amount used
		double diluter_setting; // normal/100% ?

		double pressure; // pressure provided (pascals), used over ambient pressure

		// sensors? (for cockpit?)
		// valves?

	public:
		F16OxygenSystem() 
			: tank_volume(5.0)
			, tank_usage(5.0)
			, diluter_setting(0) // <- off
			, pressure(0)
		{}
		~F16OxygenSystem() {}

		double getPressure() const
		{
			return pressure;
		}

		void updateFrame(const double ambientPressure, const double altitude, const double frameTime)
		{
			// very rough usage
			double use = 0;//frameTime * diluter_setting;
			tank_usage = 0;//-=use
			//tanks += o2_gen;

			// pressure provided depends on diluter setting
			// and ambient pressure ?
			//pressure
		}
	};
}

#endif // ifndef _F16OXYGENSYSTEM_H_
