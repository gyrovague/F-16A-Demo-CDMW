--local cockpit = folder.."../../../Cockpit/Scripts/"
--dofile(cockpit.."devices.lua")
--dofile(cockpit.."command_defs.lua")

local res = external_profile("Config/Input/Aircrafts/base_keyboard_binding.lua")
join(res.keyCommands,{

--return {
--keyCommands = {

-- example
--{down = 3010, up = 3011, cockpit_device_id = 49, value_down = 1.0,	value_up = -1.0, name = _('Anti-Collision Lights switch'), category = _('Lighting Panel')},
--{down = 3010, up = 3011, value_down = 1.0,	value_up = -1.0, name = _('Anti-Collision Lights switch'), category = _('Lighting Panel')},

-- Autopilot
{combos = {{key = 'A'}, {key = '1', reformers = {'LAlt'}}}, down = iCommandPlaneAutopilot, name = _('Autopilot - Attitude Hold'), category = _('Autopilot')},
{combos = {{key = 'H'}, {key = '2', reformers = {'LAlt'}}}, down = iCommandPlaneStabHbar, name = _('Autopilot - Altitude Hold'), category = _('Autopilot')},
{combos = {{key = '9', reformers = {'LAlt'}}}, down = iCommandPlaneStabCancel, name = _('Autopilot Disengage'), category = _('Autopilot')},

--Flight Control
{combos = {{key = 'T', reformers = {'LAlt'}}}, down = iCommandPlaneTrimOn, up = iCommandPlaneTrimOff, name = _('T/O Trim'), category = _('Flight Control')},

--Engine control
{down = iCommandPlane_APU_Start														, name = _('APU Start')							, category = _('Engine Control Panel')},
{down = iCommandPlane_APU_Off														, name = _('APU Off')								, category = _('Engine Control Panel')},
{down = iCommandAPUGeneratorPower								, name = _('APU generator power'), category = _('Electrical power control panel')},
{down = iCommandBatteryPower									, name = _('Battery power'), category = _('Electrical power control panel')},
--{down = iCommandPowerGeneratorLeft								, name = _('AC generator power left'), category = _('Electrical power control panel')},
--{down = iCommandPowerGeneratorRight								, name = _('AC generator power right'), category = _('Electrical power control panel')},

--Landing gear panel
{combos = {{key = 'G'}},						 		 down = iCommandPlaneGear, name = _('Landing Gear Up/Down'), category = _('Landing gear panel')},
{combos = {{key = 'G', reformers = {'LCtrl'}}} , 		 down = iCommandPlaneGearUp, name = _('Landing Gear Up'), category = _('Landing gear panel')},
{combos = {{key = 'G', reformers = {'LShift'}}}, down = iCommandPlaneGearDown, name = _('Landing Gear Down'), category = _('Landing gear panel')},
--{combos = {{key = 'G', reformers = {'RAlt'}}}, 			 down = iCommandEmergencyGear, name = _('Auxiliary gear handle'), category = _('Landing gear panel')},
--{down = iCommandEmergencyGearCover, 							name = _('Auxiliary gear handle lock button'), category = _('Landing gear panel')},
--{down = iCommandPlaneLGPAntiSkid, 								name = _('Anti-Skid ON/OFF'), category = _('Landing gear panel')},

-- Systems
--[[
{combos = {{key = 'R', reformers = {'LCtrl'}}}, down = iCommandPlaneAirRefuel, name = _('Refueling Boom'), category = _('Systems')},
{combos = {{key = 'R', reformers = {'LAlt'}}}, down = iCommandPlaneJettisonFuelTanks, name = _('Jettison Fuel Tanks'), category = _('Systems')},
{combos = {{key = 'S'}}, down = iCommandPlane_HOTAS_NoseWheelSteeringButton, up = iCommandPlane_HOTAS_NoseWheelSteeringButton, name = _('Nose Gear Maneuvering Range'), category = _('Systems')},
{combos = {{key = 'Q', reformers = {'LAlt'}}}, down = iCommandPlane_HOTAS_NoseWheelSteeringButtonOff, up = iCommandPlane_HOTAS_NoseWheelSteeringButtonOff, name = _('Nose Gear Steering Disengage'), category = _('Systems')},
{combos = {{key = 'A', reformers = {'LCtrl'}}}, down = iCommandPlaneWheelBrakeLeftOn, up = iCommandPlaneWheelBrakeLeftOff, name = _('Wheel Brake Left On/Off'), category = _('Systems')},
{combos = {{key = 'A', reformers = {'LAlt'}}}, down = iCommandPlaneWheelBrakeRightOn, up = iCommandPlaneWheelBrakeRightOff, name = _('Wheel Brake Right On/Off'), category = _('Systems')},
{combos = {{key = 'T', reformers = {'LShift'}}}, down = iCommandClockElapsedTimeReset, name = _('Elapsed Time Clock Start/Stop/Reset'), category = _('Systems')},
{combos = {{key = 'D', reformers = {'LShift'}}}, down = iCommandPlaneFSQuantityIndicatorSelectorMAIN, name = _('Fuel Quantity Selector'), category = _('Systems')},
{combos = {{key = 'D', reformers = {'LCtrl'}}}, down = iCommandPlaneFSQuantityIndicatorTest, up = iCommandPlaneFSQuantityIndicatorSelectorINT, name = _('Fuel Quantity Test'), category = _('Systems')},
--]]
{combos = {{key = 'L', reformers = {'RShift'}}}, down = iCommandPowerOnOff, name = _('Electric Power Switch'), category = _('Systems')},
{combos = {{key = 'B'}}, down = iCommandPlaneAirBrake, name = _('Airbrake'), category = _('Systems')},
{combos = {{key = 'B', reformers = {'LShift'}}}, down = iCommandPlaneAirBrakeOn, name = _('Airbrake On'), category = _('Systems')},
{combos = {{key = 'B', reformers = {'LCtrl'}}}, down = iCommandPlaneAirBrakeOff, name = _('Airbrake Off'), category = _('Systems')},
{combos = {{key = 'T'}}, down = iCommandPlaneWingtipSmokeOnOff, name = _('Smoke'), category = _('Systems')},
{combos = {{key = 'L'}}, down = iCommandPlaneCockpitIllumination, name = _('Illumination Cockpit'), category = _('Systems')},
{combos = {{key = 'L', reformers = {'RCtrl'}}}, down = iCommandPlaneLightsOnOff, name = _('Navigation lights'), category = _('Systems')},
{combos = {{key = 'L', reformers = {'RAlt'}}}, down = iCommandPlaneHeadLightOnOff, name = _('Gear Light Near/Far/Off'), category = _('Systems')},
--{combos = {{key = 'F'}}, down = iCommandPlaneFlaps, name = _('Flaps Up/Down'), category = _('Systems')},
--{combos = {{key = 'F', reformers = {'LShift'}}}, down = iCommandPlaneFlapsOn, name = _('Flaps Landing Position'), category = _('Systems')},
--{combos = {{key = 'F', reformers = {'LCtrl'}}}, down = iCommandPlaneFlapsOff, name = _('Flaps Up'), category = _('Systems')},
{combos = {{key = 'W'}}, down = iCommandPlaneWheelBrakeOn, up = iCommandPlaneWheelBrakeOff, name = _('Wheel Brake On'), category = _('Systems')},
{combos = {{key = 'C', reformers = {'LCtrl'}}}, down = iCommandPlaneFonar, name = _('Canopy Open/Close'), category = _('Systems')},
{combos = {{key = 'P'}}, down = iCommandPlaneParachute, name = _('Dragging Chute'), category = _('Systems')},
{combos = {{key = 'N', reformers = {'RShift'}}}, down = iCommandPlaneResetMasterWarning, name = _('Audible Warning Reset'), category = _('Systems')},
{combos = {{key = 'W', reformers = {'LCtrl'}}}, down = iCommandPlaneJettisonWeapons,up = iCommandPlaneJettisonWeaponsUp, name = _('Weapons Jettison'), category = _('Systems')},
{combos = {{key = 'E', reformers = {'LCtrl'}}}, down = iCommandPlaneEject, name = _('Eject (3 times)'), category = _('Systems')},
{combos = {{key = 'C', reformers = {'RShift'}}}, down = iCommandFlightClockReset, name = _('Flight Clock Start/Stop/Reset'), category = _('Systems')},
{down = iCommandClockElapsedTimeReset, name = _('Elapsed Time Clock Start/Stop/Reset'), category = _('Systems')},
{combos = {{key = 'Home', reformers = {'RShift'}}}, down = iCommandEnginesStart, name = _('Engines Start'), category = _('Systems')},
{combos = {{key = 'End', reformers = {'RShift'}}}, down = iCommandEnginesStop, name = _('Engines Stop'), category = _('Systems')},
--{combos = {{key = 'Home', reformers = {'RAlt'}}}, down = iCommandLeftEngineStart, name = _('Engine Left Start'), category = _('Systems')},
--{combos = {{key = 'End', reformers = {'RAlt'}}}, down = iCommandLeftEngineStop, name = _('Engine Left Stop'), category = _('Systems')},
--{combos = {{key = 'Home', reformers = {'RCtrl'}}}, down = iCommandRightEngineStart, name = _('Engine Right Start'), category = _('Systems')},
--{combos = {{key = 'End', reformers = {'RCtrl'}}}, down = iCommandRightEngineStop, name = _('Engine Right Stop'), category = _('Systems')},
{combos = {{key = 'H', reformers = {'RCtrl'}}}, down = iCommandBrightnessILS, name = _('HUD Color'), category = _('Systems')},
{combos = {{key = 'H', reformers = {'RCtrl','RShift'}}}, pressed = iCommandHUDBrightnessUp, name = _('HUD Brightness up'), category = _('Systems')},
{combos = {{key = 'H', reformers = {'RShift','RAlt'}}}, pressed = iCommandHUDBrightnessDown, name = _('HUD Brightness down'), category = _('Systems')},
{combos = {{key = 'R'}}, down = iCommandPlaneFuelOn, up = iCommandPlaneFuelOff, name = _('Fuel Dump'), category = _('Systems')},

-- Modes
{combos = {{key = '2'}}, down = iCommandPlaneModeBVR, name = _('(2) Beyond Visual Range Mode'), category = _('Modes')},
{combos = {{key = '3'}}, down = iCommandPlaneModeVS, name = _('(3) Close Air Combat Vertical Scan Mode'), category = _('Modes')},
{combos = {{key = '4'}}, down = iCommandPlaneModeBore, name = _('(4) Close Air Combat Bore Mode'), category = _('Modes')},
--{combos = {{key = '5'}}, down = iCommandPlaneModeHelmet, name = _('(5) Close Air Combat HMD Helmet Mode'), category = _('Modes')},
{combos = {{key = '6'}}, down = iCommandPlaneModeFI0, name = _('(6) Longitudinal Missile Aiming Mode/FLOOD mode'), category = _('Modes')},
--{combos = {{key = '7'}}, down = iCommandPlaneModeGround, name = _('(7) Air-To-Ground Mode'), category = _('Modes')},
--{combos = {{key = '8'}}, down = iCommandPlaneModeGrid, name = _('(8) Gunsight Reticle Switch'), category = _('Modes')},

-- Sensors
{combos = {{key = 'Enter'}}, down = iCommandPlaneChangeLock, up = iCommandPlaneChangeLockUp, name = _('Target Lock'), category = _('Sensors')},
{combos = {{key = 'Back'}}, down = iCommandSensorReset, name = _('Radar - Return To Search/NDTWS'), category = _('Sensors')},
{down = iCommandRefusalTWS, name = _('Unlock TWS Target'), category = _('Sensors')},
{combos = {{key = 'I'}}, down = iCommandPlaneRadarOnOff, name = _('Radar On/Off'), category = _('Sensors')},
{combos = {{key = 'I', reformers = {'RAlt'}}}, down = iCommandPlaneRadarChangeMode, name = _('Radar RWS/TWS Mode Select'), category = _('Sensors')},
{combos = {{key = 'I', reformers = {'RCtrl'}}}, down = iCommandPlaneRadarCenter, name = _('Target Designator To Center'), category = _('Sensors')},
{combos = {{key = 'I', reformers = {'RShift'}}}, down = iCommandPlaneChangeRadarPRF, name = _('Radar Pulse Repeat Frequency Select'), category = _('Sensors')},
--{combos = {{key = 'O'}}, down = iCommandPlaneEOSOnOff, name = _('Electro-Optical System On/Off'), category = _('Sensors')},
--{combos = {{key = 'O', reformers = {'RShift'}}}, down = iCommandPlaneLaserRangerOnOff, name = _('Laser Ranger On/Off'), category = _('Sensors')},
--{combos = {{key = 'O', reformers = {'RCtrl'}}}, down = iCommandPlaneNightTVOnOff, name = _('Night Vision (FLIR or LLTV) On/Off'), category = _('Sensors')},
{combos = {{key = ';'}}, pressed = iCommandPlaneRadarUp, up = iCommandPlaneRadarStop, name = _('Target Designator Up'), category = _('Sensors')},
{combos = {{key = '.'}}, pressed = iCommandPlaneRadarDown, up = iCommandPlaneRadarStop, name = _('Target Designator Down'), category = _('Sensors')},
{combos = {{key = ','}}, pressed = iCommandPlaneRadarLeft, up = iCommandPlaneRadarStop, name = _('Target Designator Left'), category = _('Sensors')},
{combos = {{key = '/'}}, pressed = iCommandPlaneRadarRight, up = iCommandPlaneRadarStop, name = _('Target Designator Right'), category = _('Sensors')},
{combos = {{key = ';', reformers = {'RShift'}}}, pressed = iCommandSelecterUp, up = iCommandSelecterStop, name = _('Scan Zone Up'), category = _('Sensors')},
{combos = {{key = '.', reformers = {'RShift'}}}, pressed = iCommandSelecterDown, up = iCommandSelecterStop, name = _('Scan Zone Down'), category = _('Sensors')},
{combos = {{key = ',', reformers = {'RShift'}}}, pressed = iCommandSelecterLeft, up = iCommandSelecterStop, name = _('Scan Zone Left'), category = _('Sensors')},
{combos = {{key = '/', reformers = {'RShift'}}}, pressed = iCommandSelecterRight, up = iCommandSelecterStop, name = _('Scan Zone Right'), category = _('Sensors')},
{combos = {{key = '='}}, down = iCommandPlaneZoomIn, name = _('Display Zoom In'), category = _('Sensors')},
{combos = {{key = '-'}}, down = iCommandPlaneZoomOut, name = _('Display Zoom Out'), category = _('Sensors')},
{combos = {{key = '-', reformers = {'RCtrl'}}}, down = iCommandDecreaseRadarScanArea, name = _('Radar Scan Zone Decrease'), category = _('Sensors')},
{combos = {{key = '=', reformers = {'RCtrl'}}}, down = iCommandIncreaseRadarScanArea, name = _('Radar Scan Zone Increase'), category = _('Sensors')},
--{combos = {{key = '=', reformers = {'RAlt'}}}, pressed = iCommandPlaneIncreaseBase_Distance, up = iCommandPlaneStopBase_Distance, name = _('Target Specified Size Increase'), category = _('Sensors')},
--{combos = {{key = '-', reformers = {'RAlt'}}}, pressed = iCommandPlaneDecreaseBase_Distance, up = iCommandPlaneStopBase_Distance, name = _('Target Specified Size Decrease'), category = _('Sensors')},
{combos = {{key = 'R', reformers = {'RShift'}}}, down = iCommandChangeRWRMode, name = _('RWR/SPO Mode Select'), category = _('Sensors')},
{combos = {{key = ',', reformers = {'RAlt'}}}, down = iCommandPlaneThreatWarnSoundVolumeDown, name = _('RWR/SPO Sound Signals Volume Down'), category = _('Sensors')},
{combos = {{key = '.', reformers = {'RAlt'}}}, down = iCommandPlaneThreatWarnSoundVolumeUp, name = _('RWR/SPO Sound Signals Volume Up'), category = _('Sensors')},

-- Weapons                                                                        
{combos = {{key = 'V', reformers = {'LCtrl'}}}, down = iCommandPlaneSalvoOnOff, name = _('Salvo Mode'), category = _('Weapons')},
{combos = {{key = 'Space', reformers = {'RAlt'}}}, down = iCommandPlanePickleOn,	up = iCommandPlanePickleOff, name = _('Weapon Release'), category = _('Weapons')},
--{combos = {{key = 'C', reformers = {'LShift'}}}, down = iCommandChangeGunRateOfFire, name = _('Cannon Rate Of Fire / Cut Of Burst select'), category = _('Weapons')},
})

--}}
return res
