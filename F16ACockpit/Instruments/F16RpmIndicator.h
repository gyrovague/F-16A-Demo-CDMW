#ifndef _F16RPMINDICATOR_H_
#define _F16RPMINDICATOR_H_

#include "../stdafx.h"
#include "BaseInstrument.h"

class F16RpmIndicator : public BaseInstrument
{
public:
	F16RpmIndicator() 
		: BaseInstrument() 
	{}
	~F16RpmIndicator() {}

	void updateFrame(double frametime) {}
};

#endif 
