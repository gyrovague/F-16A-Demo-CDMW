#ifndef _F16THREATINDICATOR_H_
#define _F16THREATINDICATOR_H_

#include "../stdafx.h"
#include "BaseInstrument.h"

class F16ThreatIndicator : public BaseInstrument
{
public:
	F16ThreatIndicator() 
		: BaseInstrument() 
	{}
	~F16ThreatIndicator() {}

	void updateFrame(double frametime) {}
};

#endif 
