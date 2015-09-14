#ifndef _F16LIQUIDOXYGENQUANTITY_H_
#define _F16LIQUIDOXYGENQUANTITY_H_

#include "../stdafx.h"
#include "BaseInstrument.h"

class F16LiquidOxygenQuantity : public BaseInstrument
{
public:
	F16LiquidOxygenQuantity() 
		: BaseInstrument() 
	{}
	~F16LiquidOxygenQuantity() {}

	void updateFrame(double frametime) {}
};

#endif 
