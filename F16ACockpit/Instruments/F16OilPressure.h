#ifndef _F16OILPRESSURE_H_
#define _F16OILPRESSURE_H_

#include "../stdafx.h"
#include "BaseInstrument.h"

class F16OilPressure : public BaseInstrument
{
public:
	F16OilPressure() 
		: BaseInstrument() 
	{}
	~F16OilPressure() {}

	void updateFrame(double frametime) {}
};

#endif 
