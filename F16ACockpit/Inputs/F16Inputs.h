/*
	Keep input enum in separate file: this can get potentially long list
	so don't define it in .cpp source directly.
*/

#ifndef _F16INPUTS_H_
#define _F16INPUTS_H_

// These are taken from Export.lua
// See also: http://www.digitalcombatsimulator.com/en/dev_journal/lua-export/
//
// Used in ed_fm_set_command() and ed_fm_get_param()
//
enum F16InputCommands
{
	//{down = iCommandPlaneGear, name = _('Landing Gear Up/Down'), category = _('Systems')},
	//{down = iCommandPlaneGearUp, name = _('Landing Gear Up'), category = _('Systems')},
	//{down = iCommandPlaneGearDown, name = _('Landing Gear Down'), category = _('Systems')},
	Gear				= 68, // Gear (toggle)		(doesn't work) 

	//{down = iCommandPlaneFonar, name = _('Canopy Open/Close'), category = _('Systems')},
	//{combos = {{key = 'C', reformers = {'LCtrl'}}}, down = iCommandPlaneFonar, name = _('Canopy Open/Close'), category = _('Systems')},
	Canopy				= 71, // Canopy				(doesn't work)

	//{combos = {{key = 'F'}}, down = iCommandPlaneFlaps, name = _('Flaps Up/Down'), category = _('Systems')},
	//{combos = {{key = 'F', reformers = {'LShift'}}}, down = iCommandPlaneFlapsOn, name = _('Flaps Landing Position'), category = _('Systems')},
	//{combos = {{key = 'F', reformers = {'LCtrl'}}}, down = iCommandPlaneFlapsOff, name = _('Flaps Up'), category = _('Systems')},
	Flaps				= 72, // Flaps up/down (toggle)		(doesn't work)
	AirBrake			= 73, // Air brake (toggle)	(doesn't work)

	//{down = iCommandPlaneWheelBrakeOn, up = iCommandPlaneWheelBrakeOff, name = _('Wheel Brake On'), category = _('Systems')},
	//{combos = {{key = 'W'}}, down = iCommandPlaneWheelBrakeOn, up = iCommandPlaneWheelBrakeOff, name = _('Wheel Brake On'), category = _('Systems')},
	WheelBrakesOn		= 74, // Wheel brakes on	(doesn't work)
	WheelBrakesOff		= 75, // Wheel brakes off	(doesn't work)

	//{down = iCommandPlaneFlaps, name = _('Flaps Up/Down'), category = _('Systems')},
	//{down = iCommandPlaneFlapsOn, name = _('Flaps Landing Position'), category = _('Systems')},
	//{down = iCommandPlaneFlapsOff, name = _('Flaps Up'), category = _('Systems')},
	FlapsOn				= 145, // Flaps on			(doesn't work)
	FlapsOff			= 146, // Flaps off			(doesn't work)

	//{combos = {{key = 'B', reformers = {'LShift'}}}, down = iCommandPlaneAirBrakeOn, name = _('Airbrake On'), category = _('Systems')},
	//{combos = {{key = 'B', reformers = {'LCtrl'}}}, down = iCommandPlaneAirBrakeOff, name = _('Airbrake Off'), category = _('Systems')},
	AirBrakeOn			= 147, // Air brake on		(doesn't work)
	AirBrakeOff			= 148, // Air brake off		(doesn't work)

	LandingGearUp		= 430, // Gear up			(doesn't work)	
	LandingGearDown		= 431, // Gear down			(doesn't work)

	//{down = iCommandEnginesStart, name = _('Engines Start'), category = _('Systems')},
	//{down = iCommandEnginesStop, name = _('Engines Stop'), category = _('Systems')},
	//{combos = {{key = 'Home', reformers = {'RShift'}}}, down = iCommandEnginesStart, name = _('Engines Start'), category = _('Systems')},
	//{combos = {{key = 'End', reformers = {'RShift'}}}, down = iCommandEnginesStop, name = _('Engines Stop'), category = _('Systems')},
	EnginesStart		= 309, // Engines start // iCommandEnginesStart
	EnginesStop			= 310, // Engines stop 	// iCommandEnginesStop

	//{combos = {{key = 'L', reformers = {'RShift'}}}, down = iCommandPowerOnOff, name = _('Electric Power Switch'), category = _('Systems')},
	PowerOnOff			= 315, // Electric power switch

	// joystick axis commands
	//{action = iCommandWheelBrake,		name = _('Wheel Brake')},
	//{action = iCommandLeftWheelBrake,	name = _('Wheel Brake Left')},
	//{action = iCommandRightWheelBrake,	name = _('Wheel Brake Right')},
	//WheelBrake = ; // iCommandWheelBrake
	WheelBrakeLeft = 2112, // iCommandLeftWheelBrake
	WheelBrakeRight = 2113, // iCommandRightWheelBrake

	//GearHandleRelease
	//AltGearHandle

	//NoseWheelSteering
	//RefuelingBoom 

	//{down = iCommandPlaneParachute, name = _('Dragging Chute'), category = _('Systems')},
	//DraggingChute // iCommandPlaneParachute

	JoystickPitch		= 2001,	
	JoystickRoll		= 2002,
	JoystickYaw			= 2003,
	JoystickThrottle	= 2004,
	JoystickLeftEngineThrottle = 2005,
	JoystickRightEngineThrottle = 2006,

	Reserved // placeholder
};

// TODO: trivial container for values or hard-coded for efficiency?
//std::map<F16InputCommands,double>

#endif // ifndef _F16INPUTS_H_
