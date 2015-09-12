#ifndef _F16EPUFUELQUANTITY_H_
#define _F16EPUFUELQUANTITY_H_

#include "../stdafx.h"
#include "BaseInstrument.h"

class F16EPUFuelQuantity : public BaseInstrument
{
public:
	F16EPUFuelQuantity() 
		: BaseInstrument() 
	{}
	~F16EPUFuelQuantity() {}

	void updateFrame(double frametime) {}
};

#endif 
