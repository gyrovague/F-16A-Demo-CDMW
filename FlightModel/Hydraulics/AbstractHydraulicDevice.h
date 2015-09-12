#ifndef _ABSTRACTHYDRAULICDEVICE_H_
#define _ABSTRACTHYDRAULICDEVICE_H_

#include "../stdafx.h"

// base class for hydraulic device:
// each device (actuator, sensor etc.) inherits from this 
// to provide unified interface for the system
//
class AbstractHydraulicDevice
{
public:
	// TODO: replace with correct type
	void *parentSystem;

	AbstractHydraulicDevice(void *_parentSystem) 
		: parentSystem(_parentSystem)
	{}
	~AbstractHydraulicDevice() {}

	/*
	void updateFrame(const double frameTime)
	{
	}
	*/

	void updateFrame(const double force, const double command, const double frameTime)
	{
	}
};

#endif // ifndef _ABSTRACTHYDRAULICDEVICE_H_



