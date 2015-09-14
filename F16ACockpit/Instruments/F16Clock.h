#ifndef _F16CLOCK_H_
#define _F16CLOCK_H_

#include "../stdafx.h"
#include "BaseInstrument.h"

class F16Clock : public BaseInstrument
{
public:
	F16Clock() 
		: BaseInstrument() 
	{}
	~F16Clock() {}

	void updateFrame(double frametime) {}
};

#endif 
