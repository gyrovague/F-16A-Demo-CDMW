#ifndef _F16HUD_H_
#define _F16HUD_H_

#include "../stdafx.h"
#include "BaseDisplay.h"

class F16HUD : public BaseDisplay
{
public:
	F16HUD() 
		: BaseDisplay()
	{}
	~F16HUD() {}

	void updateFrame(double frametime) {}
};

#endif 
