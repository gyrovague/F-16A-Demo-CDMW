#ifndef _F16MFD_H_
#define _F16MFD_H_

#include "../stdafx.h"
#include "BaseDisplay.h"

class F16MFD : public BaseDisplay
{
public:
	F16MFD() 
		: BaseDisplay()
	{}
	~F16MFD() {}

	void updateFrame(double frametime) {}
};

#endif 
