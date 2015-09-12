#ifndef _F16FUELFLOWINDICATOR_H_
#define _F16FUELFLOWINDICATOR_H_

#include "../stdafx.h"
#include "BaseInstrument.h"

class F16FuelFlowIndicator : public BaseInstrument
{
public:
	F16FuelFlowIndicator() 
		: BaseInstrument() 
	{}
	~F16FuelFlowIndicator() {}

	void updateFrame(double frametime) {}
};

#endif 
