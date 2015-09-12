#ifndef _DUMMYFILTER_H_
#define _DUMMYFILTER_H_

#include "../stdafx.h"
#include <memory.h>
#include "../UtilityFunctions.h"
//#include "../include/general_filter.h"

class DummyFilter
{
public:
	DummyFilter(double *pdNumerators   = NULL,
                double *pdDenominators = NULL,
                int     nOrder         = 0,
                double  dFrameTime_SEC = 0 )
	{
		InitFilter(pdNumerators, pdDenominators, nOrder, dFrameTime_SEC);
	}
	~DummyFilter() {}

    void InitFilter( double *pdNumerators,
                        double *pdDenominators,
                        int     nOrder,       
                        double  dFrameTime_SEC = 0 )
	{
		SetCoefficients(pdNumerators, pdDenominators);
		m_nOrder = nOrder;
		m_dFrameTime_SEC = dFrameTime_SEC;
	}
    void SetCoefficients(double *pdNumerator, double *pdDenominator)
	{
	}
    double Filter(bool bResetFlag, double dFrameTime_SEC, double dInput)
	{
		SetFrameTime(dFrameTime_SEC);
		return dInput;
	}
    void SetFrameTime(double dFrameTime_SEC)
	{
		m_dFrameTime_SEC = dFrameTime_SEC;
	}

    double      m_dOutput;

protected:
    int                     m_nOrder;  
    int                     m_nOrder1;
    double                  m_dFrameTime_SEC;  
    double                  m_dZDenomNormal;
    double                 *m_pdInputs;
    double                 *m_pdOutputs;
    double                 *m_pdSNumerator;
    double                 *m_pdSDenominator;
    double                 *m_pdZNumerator;
    double                 *m_pdZDenominator;
    double                 *m_pdPDt;
};

#endif // ifndef _DUMMYFILTER_H_
