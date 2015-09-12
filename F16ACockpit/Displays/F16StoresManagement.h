#ifndef _F16STORESMANAGEMENT_H_
#define _F16STORESMANAGEMENT_H_

#include "../stdafx.h"
#include "BaseDisplay.h"

class F16StoresManagement : public BaseDisplay
{
public:
	F16StoresManagement() 
		: BaseDisplay()
	{}
	~F16StoresManagement() {}

	void updateFrame(double frametime) {}
};

#endif 
