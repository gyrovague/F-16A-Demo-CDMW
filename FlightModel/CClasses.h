#ifndef CLASSES
#define CLASSES

#include "stdafx.h"
//using namespace F16;
//using F16::F16FlightControls;


class CWorld;

class CArmaMain
{
public:
	CWorld* m_pWorld; //0x0000 
	static CArmaMain* GetInstance()
	{
		return 0;
	}
};

class CWorld
{
public:
	double readaoa(double alphaFiltered)
	{
		return alphaFiltered;
	}
	double readspeed(double airspeed_FPS)
	{
		double airspeed_KTS = 0.5924838012958964 * airspeed_FPS;
		return airspeed_KTS;
	}

};//Size=0x1590

extern CArmaMain* g_pArmaMain;

#endif