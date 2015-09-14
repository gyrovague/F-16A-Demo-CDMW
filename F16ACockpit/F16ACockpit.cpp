// F16ACockpit.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <windows.h>

// create handlers for controls (stick, throttle, pedals)

// create handlers for "passive" instruments (clock, ADI, engine RPM)

// create handlers for displays (active instruments)

// bind handlers to inputs, animation items

/*
void * ed_cockpit_get_parameter_handle			  (const char * name)
{
}

void   ed_cockpit_update_parameter_with_string    (void		  * handle	,const char * string_value)
{
}

void   ed_cockpit_update_parameter_with_number    (void		  * handle	,double   number_value)
{
}

bool   ed_cockpit_parameter_value_to_number       (const void * handle	,double & res	,bool interpolated)
{
}

bool   ed_cockpit_parameter_value_to_string       (const void * handle	,char * buffer	,unsigned buffer_size)
{
}

//return 0 if equal , -1 if first less than second 1 otherwise
int    ed_cockpit_compare_parameters			  (void		  * handle_1,void * handle_2)
{
	return 0;
}
*/

double test(double in)
{
	return in*10.0;
}
