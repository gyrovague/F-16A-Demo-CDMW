#ifndef _F16COMPASS_H_
#define _F16COMPASS_H_

#include "../stdafx.h"
#include "BaseInstrument.h"

class F16Compass : public BaseInstrument
{
public:
	F16Compass() 
		: BaseInstrument() 
	{}
	~F16Compass() {}

	void updateFrame(double frametime) {}
};

#endif 
