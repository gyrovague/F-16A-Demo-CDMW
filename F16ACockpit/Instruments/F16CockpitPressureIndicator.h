#ifndef _F16COCKPITPRESSUREINDICATOR_H_
#define _F16COCKPITPRESSUREINDICATOR_H_

#include "../stdafx.h"
#include "BaseInstrument.h"

class F16CockpitPressureIndicator : public BaseInstrument
{
public:
	F16CockpitPressureIndicator() 
		: BaseInstrument() 
	{}
	~F16CockpitPressureIndicator() {}

	void updateFrame(double frametime) {}
};

#endif 
