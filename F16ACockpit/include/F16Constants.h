#ifndef _F16CONSTANTS_H_
#define _F16CONSTANTS_H_

//-------------------------------------------------------
// Start of F-16 Simulation Variables
// Probably doesn't need it's own namespace or anything
// I just quickly did this to organize my F-16 specific
// variables, needs to be done better eventually
//-------------------------------------------------------
namespace F16
{
	const double		wingSpan_FT				= 32.667;		// F-16 wing-span (ft)
	const double		wingArea_FT2			= 300.0;		// F-16 wing area (ft^2)
	const double		meanChord_FT			= 11.32;		// F-16 mean aerodynamic chord (ft)
	const double		referenceCG_PCT			= 0.35;			// Reference CG as a % of wing chord
	const double		actualCG_PCT			= 0.30;			// Actual CG as a % of wing chord
	const double		pi						= M_PI;			// Pi (3.14159....) - use value from math.h
	const double		radiansToDegrees		= 180.0/M_PI;		// Conversion factor from radians to degrees - use value from math.h
	const double		inertia_Ix_KGM2			= 12874.0;		// Reference moment of inertia (kg/m^2)
	const double		inertia_Iy_KGM2			= 75673.6;		// Reference moment of inertia (kg/m^2)
	const double		inertia_Iz_KGM2			= 85552.1;		// Reference moment of inertia (kg/m^2)
	const double		meterToFoot				= 3.28084;		// Meter to foot conversion factor
}

#endif // ifndef _F16CONSTANTS_H_

