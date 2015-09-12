#ifndef _F16NOZZLEPOSITION_H_
#define _F16NOZZLEPOSITION_H_

#include "../stdafx.h"
#include "BaseInstrument.h"

class F16NozzlePosition : public BaseInstrument
{
public:
	F16NozzlePosition() 
		: BaseInstrument() 
	{}
	~F16NozzlePosition() {}

	void updateFrame(double frametime) {}
};

#endif 
