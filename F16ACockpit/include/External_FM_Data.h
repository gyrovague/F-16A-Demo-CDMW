/**
	copied as-is from Export.lua
*/

#ifndef  _EXTERNAL_FM_DATA_H
#define  _EXTERNAL_FM_DATA_H

struct external_FM_data  
{
	double orientation_X[3];
	double orientation_Y[3];
	double orientation_Z[3];
	double pos[3];

	//

	double velocity[3];
	double acceleration[3];
	double omega[3];
};

#endif  // _EXTERNAL_FM_DATA_H
