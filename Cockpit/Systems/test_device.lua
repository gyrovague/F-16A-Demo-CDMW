local dev 	    = GetSelf()

local altitude = get_param_handle("ALTITUDE")
local indicated_airspeed = get_param_handle("INDICATED_AIRSPEED")
local mach_number = get_param_handle("MACH_NUMBER")
local magnetic_heading = get_param_handle("MAGNETIC_HEADING")
local vertical_acceleration = get_param_handle("VERTICAL_ACCELERATION")
local vertical_velocity = get_param_handle("VERTICAL_VELOCITY")
local altitude_source = get_param_handle("ALTITUDE_SOURCE")

local update_time_step = 0.1

make_default_activity(update_time_step)
--update will be called 10 times per second

local sensor_data = get_base_data()


local DC_BUS_V  = get_param_handle("DC_BUS_V")
DC_BUS_V:set(0)

function post_initialize()
	electric_system = GetDevice(3) --devices["ELECTRIC_SYSTEM"]
	--print("post_initialize called")
end

function update()
	--my_param4:set(sensor_data.getStickPitchPosition())
	altitude:set(sensor_data.getRadarAltitude()*3.28084)
	local barometric_altitude = sensor_data.getBarometricAltitude()*3.28084
	local radar_altitude = sensor_data.getRadarAltitude()*3.28084
	if radar_altitude > 3000 then
	  altitude:set(barometric_altitude)
	  altitude_source:set("B")
	else
	  altitude:set(radar_altitude)
	  altitude_source:set("R")
	end
	indicated_airspeed:set(sensor_data.getIndicatedAirSpeed()*1.943)
	magnetic_heading:set(sensor_data.getMagneticHeading()*(180/math.pi))
	mach_number:set(sensor_data.getMachNumber())
	vertical_acceleration:set(sensor_data.getVerticalAcceleration())
    vertical_velocity:set(sensor_data.getVerticalVelocity())
	
	if electric_system ~= nil then
	   local DC_V     =  electric_system:get_DC_Bus_1_voltage()
	   local prev_val =  DC_BUS_V:get()
	   -- add some dynamic: 
	   DC_V = prev_val + (DC_V - prev_val) * update_time_step   
	   DC_BUS_V:set(DC_V)
	end	
end
