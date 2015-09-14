--shape_name   	   = "Cockpit-Wunderluft"
shape_name   	   = "Cockpit-Viper"
is_EDM			   = true
new_model_format   = true
ambient_light    = {255,255,255}
ambient_color_day_texture    = {72, 100, 160}
ambient_color_night_texture  = {40, 60 ,150}
ambient_color_from_devices   = {50, 50, 40}
ambient_color_from_panels	 = {35, 25, 25}

dusk_border					 = 0.4
draw_pilot					 = false

external_model_canopy_arg	 = 38

use_external_views = false 
cockpit_local_point = {4.15, 1.15, 0.0} --F-16 New Model {4.8, 0.78, 0.0} -- 1.57 for Y

day_texture_set_value   = 0.0
night_texture_set_value = 0.1

local controllers = LoRegisterPanelControls()

mirrors_data = 
{
    center_point 	= {0.6,0.40,0.00},
    width 		 	= 0.3,
    aspect 		 	= 1.7, 
	rotation 	 	= math.rad(-20);
	animation_speed = 2.0;
	near_clip 		= 0.1;
	middle_clip		= 10;
	far_clip		= 60000;
}

mirrors_draw                    = CreateGauge()
mirrors_draw.arg_number    		= 16
mirrors_draw.input   			= {0,1}
mirrors_draw.output   			= {1,0}
mirrors_draw.controller         = controllers.mirrors_draw

-- not animated in edm?
Canopy      = CreateGauge()
Canopy.arg_number = 1
Canopy.input   = {0,1}
Canopy.output  = {0,1}
Canopy.controller = controllers.base_gauge_CanopyPos

-- stick arg 2 and 3 match args in cockpit edm, anim should work with proper input binding
StickPitch						= CreateGauge()
StickPitch.arg_number			= 2
StickPitch.input				= {-100, 100}
StickPitch.output				= {-1, 1}
StickPitch.controller			= controllers.base_gauge_StickPitchPosition

-- stick arg 2 and 3 match args in cockpit edm, anim should work with proper input binding
StickBank						= CreateGauge()
StickBank.arg_number			= 3
StickBank.input					= {-100, 100}
StickBank.output				= {-1, 1}
StickBank.controller			= controllers.base_gauge_StickRollPosition


need_to_be_closed = true -- close lua state after initialization 


Z_test =
{
	near = 0.05,
	far  = 4.0,
}

--[[ available functions 

 --base_gauge_RadarAltitude
 --base_gauge_BarometricAltitude
 --base_gauge_AngleOfAttack
 --base_gauge_AngleOfSlide
 --base_gauge_VerticalVelocity
 --base_gauge_TrueAirSpeed
 --base_gauge_IndicatedAirSpeed
 --base_gauge_MachNumber
 --base_gauge_VerticalAcceleration --Ny
 --base_gauge_HorizontalAcceleration --Nx
 --base_gauge_LateralAcceleration --Nz
 --base_gauge_RateOfRoll
 --base_gauge_RateOfYaw
 --base_gauge_RateOfPitch
 --base_gauge_Roll
 --base_gauge_MagneticHeading
 --base_gauge_Pitch
 --base_gauge_Heading
 --base_gauge_EngineLeftFuelConsumption
 --base_gauge_EngineRightFuelConsumption
 --base_gauge_EngineLeftTemperatureBeforeTurbine
 --base_gauge_EngineRightTemperatureBeforeTurbine
 --base_gauge_EngineLeftRPM
 --base_gauge_EngineRightRPM
 --base_gauge_WOW_RightMainLandingGear
 --base_gauge_WOW_LeftMainLandingGear
 --base_gauge_WOW_NoseLandingGear
 --base_gauge_RightMainLandingGearDown
 --base_gauge_LeftMainLandingGearDown
 --base_gauge_NoseLandingGearDown
 --base_gauge_RightMainLandingGearUp
 --base_gauge_LeftMainLandingGearUp
 --base_gauge_NoseLandingGearUp
 --base_gauge_LandingGearHandlePos
 --base_gauge_StickRollPosition
 --base_gauge_StickPitchPosition
 --base_gauge_RudderPosition
 --base_gauge_ThrottleLeftPosition
 --base_gauge_ThrottleRightPosition
 --base_gauge_HelicopterCollective
 --base_gauge_HelicopterCorrection
 --base_gauge_CanopyPos
 --base_gauge_CanopyState
 --base_gauge_FlapsRetracted
 --base_gauge_SpeedBrakePos
 --base_gauge_FlapsPos
 --base_gauge_TotalFuelWeight

--]]
