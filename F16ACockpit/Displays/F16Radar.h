#ifndef _F16RADAR_H_
#define _F16RADAR_H_

#include "../stdafx.h"
#include "BaseDisplay.h"

class F16Radar : public BaseDisplay
{
public:
	F16Radar() 
		: BaseDisplay()
	{}
	~F16Radar() {}

	void updateFrame(double frametime) {}
};

#endif 
