#ifndef _F16ADI_H_
#define _F16ADI_H_

#include "../stdafx.h"
#include "BaseInstrument.h"

class F16ADI : public BaseInstrument
{
public:
	F16ADI() 
		: BaseInstrument() 
	{}
	~F16ADI() {}

	void updateFrame(double frametime) {}
};

#endif 
