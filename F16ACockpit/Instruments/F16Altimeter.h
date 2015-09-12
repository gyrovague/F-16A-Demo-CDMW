#ifndef _F16ALTIMETER_H_
#define _F16ALTIMETER_H_

#include "../stdafx.h"
#include "BaseInstrument.h"

class F16Altimeter : public BaseInstrument
{
public:
	F16Altimeter() 
		: BaseInstrument() 
	{}
	~F16Altimeter() {}

	void updateFrame(double frametime) {}
};

#endif 
