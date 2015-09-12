#ifndef _F16OXYGENFLOWINDICATOR_H_
#define _F16OXYGENFLOWINDICATOR_H_

#include "../stdafx.h"
#include "BaseInstrument.h"

class F16OxygenFlowIndicator : public BaseInstrument
{
public:
	F16OxygenFlowIndicator() 
		: BaseInstrument() 
	{}
	~F16OxygenFlowIndicator() {}

	void updateFrame(double frametime) {}
};

#endif 
