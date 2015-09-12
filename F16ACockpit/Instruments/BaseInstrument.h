/*
 Instrument is anything "passive" display that requires animating.
 Usually a thing like heading needle, ADI, clock.
*/

#ifndef _BASEINSTRUMENT_H_
#define _BASEINSTRUMENT_H_

#include "../stdafx.h"

class BaseInstrument
{
public:
	BaseInstrument() {}
	~BaseInstrument() {}

	void updateFrame(double frametime) {}
};

#endif // ifndef _BASEINSTRUMENT_H_

