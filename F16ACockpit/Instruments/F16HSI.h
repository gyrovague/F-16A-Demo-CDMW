#ifndef _F16HSI_H_
#define _F16HSI_H_

#include "../stdafx.h"
#include "BaseInstrument.h"

class F16HSI : public BaseInstrument
{
public:
	F16HSI() 
		: BaseInstrument() 
	{}
	~F16HSI() {}

	void updateFrame(double frametime) {}
};

#endif 
