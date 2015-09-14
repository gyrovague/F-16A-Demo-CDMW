dofile(LockOn_Options.script_path.."HUD/Indicator/definitions.lua")

PitchLineClipRadius = 163

function AddElement(object)
    object.use_mipfilter    = true
	object.additive_alpha   = true
	object.h_clip_relation  = h_clip_relations.COMPARE
	object.level			= HUD_DEFAULT_LEVEL
    Add(object)
end

local BASE_COLOR  = {255,0  ,0,255}
local BASE_COLOR2 = {0  ,255,0,255} --128,165,0,120

local BASE_COLOR_MAT    = MakeMaterial(nil,BASE_COLOR)

--local IndicationTexturesPath = LockOn_Options.script_path.."../Textures/"
--local GRID_MAT   			= MakeMaterial(IndicationTexturesPath.."HUD_grid.tga",BASE_COLOR2) -- image of the fixed net
--local GRID_MAT   			= MakeMaterial(IndicationTexturesPath.."F-16HUD.tga",BASE_COLOR2) -- image of the fixed net
local GRID_MAT   			= MakeMaterial("HUD_grid.tga",BASE_COLOR2) -- image of the fixed net

local shape_rotation = 0

shape_rotation = math.tan(shape_rotation/57.3) * 1000 -- to mils -- NOTE: this does nothing currently, returns 0


local full_radius =  108 -- is this the radius of "HUD/net view field"? Units (pixels or angular units)?
local grid_shift  = -35 -- explain shift?
local grid_radius =  full_radius + grid_shift

local grid_origin	         = CreateElement "ceSimple"
grid_origin.name 		     = create_guid_string() -- no such function in this script. Not in definitions.lua either. Could be in elements_defs.lua
grid_origin.collimated 		 = true
AddElement(grid_origin)

local gridpoly	    = CreateElement "ceTexPoly" --this could be the text area on HUD
gridpoly.name 		= create_guid_string() -- this must be external function call.
gridpoly.vertices   = {{-grid_radius, grid_radius},
				   { grid_radius, grid_radius},
				   { grid_radius,-grid_radius},
				   {-grid_radius,-grid_radius}}
gridpoly.indices	= {0,1,2,2,3,0}
gridpoly.tex_coords = {{0,0},{1,0},{1,1},{0,1}}
gridpoly.material   = GRID_MAT
gridpoly.init_pos   = {0,grid_shift + shape_rotation} 
gridpoly.collimated = true
gridpoly.parent_element = grid_origin.name
AddElement(gridpoly)

--this is font object declaration. 
local FONT_MAT = MakeFont({used_DXUnicodeFontData = "FUI/Fonts/font_cockpit_usa"},BASE_COLOR,40,"test_font") 

local indicated_airspeed           = CreateElement "ceStringPoly"
indicated_airspeed.name            = create_guid_string()
indicated_airspeed.material        = FONT_MAT
indicated_airspeed.init_pos        = {-65,-10}
indicated_airspeed.alignment       = "RightCenter"
indicated_airspeed.stringdefs      = {0.01,0.75 * 0.01, 0, 0}
indicated_airspeed.formats         = {"%4.0f","%s"} 
indicated_airspeed.element_params  = {"INDICATED_AIRSPEED"}
indicated_airspeed.controllers     = {{"text_using_parameter",0,0}} --first index is for element_params (starting with 0) , second for formats ( starting with 0)
indicated_airspeed.additive_alpha  = true
indicated_airspeed.collimated      = true
AddElement(indicated_airspeed)

local mach_number                  = CreateElement "ceStringPoly"
mach_number.name                   = create_guid_string()
mach_number.material               = FONT_MAT
mach_number.init_pos               = {-65,-21}
mach_number.alignment       = "RightCenter"
mach_number.stringdefs      = {0.01,0.75 * 0.01, 0, 0}
mach_number.formats         = {"%4.2fM","%s"} 
mach_number.element_params  = {"MACH_NUMBER"}
mach_number.controllers     = {{"text_using_parameter",0,0}} --first index is for element_params (starting with 0) , second for formats ( starting with 0)
mach_number.additive_alpha  = true
mach_number.collimated      = true
AddElement(mach_number)

local magnetic_heading           = CreateElement "ceStringPoly"
magnetic_heading.name            = create_guid_string()
magnetic_heading.material        = FONT_MAT
magnetic_heading.init_pos        = {0,50}
magnetic_heading.alignment       = "CenterCenter"
magnetic_heading.stringdefs      = {0.01,0.75 * 0.01, 0, 0}
magnetic_heading.formats         = {"%4.0f","%s"} 
magnetic_heading.element_params  = {"MAGNETIC_HEADING"}
magnetic_heading.controllers     = {{"text_using_parameter",0,0}} --first index is for element_params (starting with 0) , second for formats ( starting with 0)
magnetic_heading.additive_alpha  = true
magnetic_heading.collimated     = true
AddElement(magnetic_heading)

local vertical_acceleration           = CreateElement "ceStringPoly"
vertical_acceleration.name            = create_guid_string()
vertical_acceleration.material        = FONT_MAT
vertical_acceleration.init_pos        = {0,-93}
vertical_acceleration.alignment       = "CenterCenter"
vertical_acceleration.stringdefs      = {0.01,0.75 * 0.01, 0, 0}
vertical_acceleration.formats         = {"%4.2fG","%s"} 
vertical_acceleration.element_params  = {"VERTICAL_ACCELERATION"}
vertical_acceleration.controllers     = {{"text_using_parameter",0,0}} --first index is for element_params (starting with 0) , second for formats ( starting with 0)
vertical_acceleration.additive_alpha  = true
vertical_acceleration.collimated     = true
AddElement(vertical_acceleration)

local altitude_source           = CreateElement "ceStringPoly"
altitude_source.name            = create_guid_string()
altitude_source.material        = FONT_MAT
altitude_source.init_pos        = {90,1}
altitude_source.alignment       = "RightCenter"
altitude_source.stringdefs      = {0.01,0.75 * 0.01, 0, 0}
altitude_source.formats         = {"%s","%s"} 
altitude_source.element_params  = {"ALTITUDE_SOURCE"}
altitude_source.controllers     = {{"text_using_parameter",0,0}} --first index is for element_params (starting with 0) , second for formats ( starting with 0)
altitude_source.additive_alpha  = true
altitude_source.collimated     = true
AddElement(altitude_source)

local altitude           = CreateElement "ceStringPoly"
altitude.name            = create_guid_string()
altitude.material        = FONT_MAT
altitude.init_pos        = {90,-10}
altitude.alignment       = "RightCenter"
altitude.stringdefs      = {0.01,0.75 * 0.01, 0, 0}
altitude.formats         = {"%6.0f","%s"} 
altitude.element_params  = {"ALTITUDE"}
altitude.controllers     = {{"text_using_parameter",0,0}} --first index is for element_params (starting with 0) , second for formats ( starting with 0)
altitude.additive_alpha  = true
altitude.collimated     = true
AddElement(altitude)

local vertical_velocity           = CreateElement "ceStringPoly"
vertical_velocity.name            = create_guid_string()
vertical_velocity.material        = FONT_MAT
vertical_velocity.init_pos        = {90,-21}
vertical_velocity.alignment       = "RightCenter"
vertical_velocity.stringdefs      = {0.01,0.75 * 0.01, 0, 0}
vertical_velocity.formats         = {"%6.0f","%s"} 
vertical_velocity.element_params  = {"VERTICAL_VELOCITY"}
vertical_velocity.controllers     = {{"text_using_parameter",0,0}} --first index is for element_params (starting with 0) , second for formats ( starting with 0)
vertical_velocity.additive_alpha  = true
vertical_velocity.collimated     = true
AddElement(vertical_velocity)

function texture_box (UL_X,UL_Y,W,H) --this is texture box function. Receives some coordinates and dimensions, returns 4 pairs of values. Nothing is calling this function inside script.
local texture_size_x = 128
local texture_size_y = 128
local ux = UL_X / texture_size_x
local uy = UL_Y / texture_size_y
local w  = W / texture_size_x
local h  = W / texture_size_y

return {{ux	    ,uy},
		{ux + w ,uy},
		{ux + w ,uy + h},
		{ux	 	,uy + h}}
end

function create_textured_box(UL_X,UL_Y,DR_X,DR_Y) -- function that creates textured square. This function is called 2 times in below code.

local size_per_pixel = 1/8
local texture_size_x = 128
local texture_size_y = 128
local W = DR_X - UL_X
local H = DR_Y - UL_Y

local half_x = 0.5 * W * size_per_pixel
local half_y = 0.5 * H * size_per_pixel
local ux 	 = UL_X / texture_size_x
local uy 	 = UL_Y / texture_size_y
local w  	 = W / texture_size_x
local h 	 = H / texture_size_y

local object = CreateElement "ceTexPoly"
object.vertices =  {{-half_x, half_y},
				    { half_x, half_y},
				    { half_x,-half_y},
				    {-half_x,-half_y}}
object.indices	  = {0,1,2,2,3,0}
object.tex_coords = {{ux     ,uy},
					 {ux + w ,uy},
					 {ux + w ,uy + h},
				     {ux 	 ,uy + h}}	 
				 
return object

end

gun_sight_mark 					= create_textured_box(7,7,25,25) -- this is create_textured_box function call with parameters
gun_sight_mark.material       	= PIPER_	
gun_sight_mark.name 			= BASE_COLOR_MAT
gun_sight_mark.collimated	  	= true
gun_sight_mark.element_params   = {"WS_GUN_PIPER_AVAILABLE",
								   "WS_GUN_PIPER_AZIMUTH",
								   "WS_GUN_PIPER_ELEVATION"} 
								   
gun_sight_mark.controllers 	   = {{"parameter_in_range"				,0,0.9,1.1},--check that piper available using WS_GUN_PIPER_AVAILABLE
								  {"move_left_right_using_parameter",1, 0.73 },	--azimuth move by WS_GUN_PIPER_AZIMUTH , 0.73 is default collimator distance (from eye to HUD plane)
								  {"move_up_down_using_parameter"   ,2, 0.73 }, --elevation move by WS_GUN_PIPER_ELEVATION
								 }
AddElement(gun_sight_mark)
