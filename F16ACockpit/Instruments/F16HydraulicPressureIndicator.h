#ifndef _F16HYDRAULICPRESSUREINDICATOR_H_
#define _F16HYDRAULICPRESSUREINDICATOR_H_

#include "../stdafx.h"
#include "BaseInstrument.h"

class F16HydraulicPressureIndicator : public BaseInstrument
{
public:
	F16HydraulicPressureIndicator() 
		: BaseInstrument() 
	{}
	~F16HydraulicPressureIndicator() {}

	void updateFrame(double frametime) {}
};

#endif 
