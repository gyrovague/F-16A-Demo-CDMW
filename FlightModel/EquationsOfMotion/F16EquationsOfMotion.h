/*
	physics integrator
*/

#ifndef _F16EQUATIONSOFMOTION_H_
#define _F16EQUATIONSOFMOTION_H_

#include "../stdafx.h"
#include <math.h>

#include "include/ED_FM_Utility.h"		// Provided utility functions that were in the initial EFM example
#include "include/F16Constants.h"		// Common constants used throughout this DLL

namespace F16
{
	class F16Motion
	{
	protected:
		//-----------------------------------------------------------------
		// This variable is very important.  Make sure you set this
		// to 0 at the beginning of each frame time or else the moments
		// will accumulate.  For each frame time, add up all the moments
		// acting on the air vehicle with this variable using th
		//
		// Units = Newton * meter
		//-----------------------------------------------------------------
		Vec3	common_moment;							
		//-----------------------------------------------------------------
		// This variable is also very important.  This defines all the forces
		// acting on the air vehicle.  This also needs to be reset to 0 at the
		// beginning of each frame time.  
		//
		// Units = Newton
		//-----------------------------------------------------------------
		Vec3	common_force;
		//-----------------------------------------------------------------
		// Center of gravity of the air vehicle as calculated from the 
		// DCS simulation, I don't believe this is utilized within this 
		// EFM.
		//
		// Units = meter
		//-----------------------------------------------------------------
		Vec3    center_of_gravity;
		//-----------------------------------------------------------------
		// The moments of inertia for the air vehicle as calculated from the
		// DCS Simulation.  This is not used within this EFM as there is a bug
		// when trying to manipulate weight or moment of inertia from within
		// the EFM.  The inertia is currently set from entry.lua
		//
		// Units: Newton * meter^2
		//-----------------------------------------------------------------
		Vec3	inertia;

		// current total mass (including fuel)
		//double mass;

		// mass times speed
		//double kinetic_energy;

		double fuel_mass_delta; // change in fuel mass since last frame

		double weight_N; // Weight force of aircraft (N)

	public:
		F16Motion() 
			: common_moment()
			, common_force()
			, center_of_gravity()
			, inertia()
			, fuel_mass_delta(0)
			, weight_N(0)
		{}
		~F16Motion() {}

		// Very important! This function sum up all the forces acting on
		// the aircraft for this run frame.  It currently assume the force
		// is acting at the CG
		void add_local_force(const Vec3 & Force, const Vec3 & Force_pos)
		{
			common_force.x += Force.x;
			common_force.y += Force.y;
			common_force.z += Force.z;

			Vec3 delta_pos(Force_pos.x - center_of_gravity.x,
						   Force_pos.y - center_of_gravity.y,
						   Force_pos.z - center_of_gravity.z);

			Vec3 delta_moment = cross(delta_pos, Force);

			common_moment.x += delta_moment.x;
			common_moment.y += delta_moment.y;
			common_moment.z += delta_moment.z;
		}
		void add_local_force_cg(const Vec3 & Force)
		{
			// old plain sum for comparison
			//sum_vec3(common_force, Force);

			Vec3 force_pos(0,0,0); // cg
			add_local_force(Force, force_pos);
		}

		/*
		void dec_local_force(const Vec3 & Force, const Vec3 & Force_pos)
		{
			// TODO:! force position

			dec_vec3(common_force, Force);
		}
		void dec_local_force_cg(const Vec3 & Force)
		{
			// TODO:! force position
			Vec3 force_pos(0,0,0);
			dec_local_force(Force, force_pos);
			//dec_vec3(common_force, Force);
		}
		*/

		// Very important! This function sums up all the moments acting
		// on the aircraft for this run frame.  It currently assumes the
		// moment is acting at the CG
		void add_local_moment(const Vec3 & Moment)
		{
			sum_vec3(common_moment, Moment);
		}

		void clear()
		{
			// Very important! clear out the forces and moments before you start calculated
			// a new set for this run frame
			clear_vec3(common_force);
			clear_vec3(common_moment);
			fuel_mass_delta = 0;
		}

		/*
		void setMassChange(double delta_mass)
		{
			mass += delta_mass;
		}
		*/

		void setMassState(double mass,
						double center_of_mass_x,
						double center_of_mass_y,
						double center_of_mass_z,
						double moment_of_inertia_x,
						double moment_of_inertia_y,
						double moment_of_inertia_z)
		{
			weight_N = mass * 9.80665002864;

			center_of_gravity.x  = center_of_mass_x;
			center_of_gravity.y  = center_of_mass_y;
			center_of_gravity.z  = center_of_mass_z;

			inertia.x = moment_of_inertia_x;
			inertia.y = moment_of_inertia_y;
			inertia.z = moment_of_inertia_z;
		}

		void getLocalForce(double &x,double &y,double &z,double &pos_x,double &pos_y,double &pos_z)
		{
			x = common_force.x;
			y = common_force.y;
			z = common_force.z;
			pos_x = center_of_gravity.x;
			pos_y = center_of_gravity.y;
			pos_z = center_of_gravity.z;
		}

		void getLocalMoment(double &x,double &y,double &z)
		{
			x = common_moment.x;
			y = common_moment.y;
			z = common_moment.z;
		}

		bool isMassChanged() const
		{
			if (fuel_mass_delta != 0)
			{
				return true;
			}
			if (inertia.x != F16::inertia_Ix_KGM2 
				|| inertia.y != F16::inertia_Iz_KGM2 
				|| inertia.z != F16::inertia_Iy_KGM2)
			{
				return true;
			}
			return false;
		}

		void getMassMomentInertiaChange(double & delta_mass,
										double & delta_mass_pos_x,
										double & delta_mass_pos_y,
										double & delta_mass_pos_z,
										double & delta_mass_moment_of_inertia_x,
										double & delta_mass_moment_of_inertia_y,
										double & delta_mass_moment_of_inertia_z)
		{
			// TODO: change in amount of fuel -> change in mass -> set here

			delta_mass -= fuel_mass_delta;
			//delta_mass = 0;
			delta_mass_pos_x = 0.0;
			delta_mass_pos_y = 0.0;
			delta_mass_pos_z = 0.0;

			//delta_mass_pos_x = -1.0;
			//delta_mass_pos_y =  1.0;
			//delta_mass_pos_z =  0;

			delta_mass_moment_of_inertia_x = F16::inertia_Ix_KGM2 - inertia.x;
			delta_mass_moment_of_inertia_y = F16::inertia_Iy_KGM2 - inertia.y;
			delta_mass_moment_of_inertia_z = F16::inertia_Iz_KGM2 - inertia.z;

			// TODO: decrement this delta from inertia now?
			fuel_mass_delta = -1000;
		}

		//----------------------------------------------------------------
		// All prior forces calculated in lbs, needs to be converted
		// to units.  All prior forces calculated in lb*ft, needs
		// to be converted into N*m
		//----------------------------------------------------------------
		void updateAeroForces(const double Cy_total, const double Cx_total, const double Cz_total, const double Cl_total, const double Cm_total, const double Cn_total, const double dynamicPressure_LBFT2)
		{
			// precalculate some terms
			const double wingPressureN = F16::wingArea_FT2 * dynamicPressure_LBFT2 * 4.44822162825;
			const double wingPressureNm = F16::wingArea_FT2 * dynamicPressure_LBFT2 * 1.35581795;

			// Cy	(force out the right wing)
			Vec3 cy_force(0.0, 0.0, Cy_total * wingPressureN);		// Output force in Newtons
			Vec3 cy_force_pos(0.0,0,0); //0.01437
			add_local_force_cg(cy_force /*,cy_force_pos*/);	

			// Cx (force out the nose)
			Vec3 cx_force(Cx_total * wingPressureN, 0, 0 );		// Output force in Newtons
			Vec3 cx_force_pos(0, 0.0,0.0);
			add_local_force_cg(cx_force /*,cx_force_pos*/);

			// Cz (force down the bottom of the aircraft)
			Vec3 cz_force(0.0,  -Cz_total * wingPressureN, 0.0 );	// Output force in Newtons
			Vec3 cz_force_pos(0,0,0);
			add_local_force_cg(cz_force /*,cz_force_pos*/);

			// Cl	(Output force in N/m)
			Vec3 cl_moment(Cl_total * wingPressureNm * F16::wingSpan_FT, 0.0,  0.0);
			add_local_moment(cl_moment);

			// Cm	(Output force in N/m)
			Vec3 cm_moment(0.0, 0.0,  Cm_total * wingPressureNm * F16::meanChord_FT);
			add_local_moment(cm_moment);

			// Cn	(Output force in N/m)
			Vec3 cn_moment(0.0, -Cn_total * wingPressureNm * F16::wingSpan_FT,  0.0);
			add_local_moment(cn_moment);	
		}

		void updateEngineForces(double thrust_N)
		{
			// Thrust	
			Vec3 thrust_force(thrust_N , 0.0, 0.0);	// Output force in Newtons
			Vec3 thrust_force_pos(0,0,0);
			add_local_force_cg(thrust_force /*, thrust_force_pos*/);	
			//add_local_force(thrust_force, thrust_force_pos);	
		}

		// TODO: left, right and nose wheel forces
		// TODO: nose-wheel steering angle, braking forces
		void updateWheelForces(double leftWheelXFriction, double leftWheelYFriction, double rightWheelXFriction, double rightWheelYFriction, double noseWheelXFriction, double noseWheelYFriction)
		{
			// TODO: offset pos of each wheel,
			// how much is it in the coordinate system?

			// TODO: nose wheel turn

			// TODO: debug: check force direction!
			// check reduction in kinetic energy per wheel
			// and check that we don't underflow..
			//add_local_force_cg(Vec3(leftWheelXFriction, 0.0,0.0) /*, Vec3(0.0,0.0,0.0)*/);
			//add_local_force_cg(Vec3(0.0, 0.0, leftWheelYFriction) /*, Vec3(0.0,0.0,0.0)*/);
			//add_local_force_cg(Vec3(rightWheelXFriction, 0.0,0.0) /*, Vec3(0.0,0.0,0.0)*/);
			//add_local_force_cg(Vec3(0.0, 0.0, rightWheelYFriction) /*, Vec3(0.0,0.0,0.0)*/);
		}

		/* TODO: handling for skidding friction? (maybe sliding sideways..)
		void updateSlippingFriction()
		{}
		*/

		// free-rolling friction
		void updateRollingFriction(const double CxWheelFriction, const double CyWheelFriction)
		{
			// TODO: must have support for static friction: engine power needed to overcome and transfer to rolling

			//Vec3 cx_wheel_friction_force(CxWheelFriction, 0.0,0.0);
			//Vec3 cx_wheel_friction_pos(0.0,0.0,0.0);
			//add_local_force_cg(cx_wheel_friction_force, cx_wheel_friction_pos);

			// test, skip some things for now
			//sum_vec3(common_force, Vec3(CxWheelFriction, 0.0,0.0));
			// -> actually need to reduce this from _moment_ not add opposite force?


			// note: applying this causes "steering" while rolling, is the axis now correct ?
			// -> if not turning this should be zero since the angle is same as rolling direction
			// -> skip this if cx vector is aligned with direction of traveling?
			//
			//Vec3 cy_wheel_friction_force(0.0, 0.0,CyWheelFriction);
			//Vec3 cy_wheel_friction_pos(0.0,0.0,0.0);
			//add_local_force_cg(cy_wheel_friction_force /*,cy_wheel_friction_pos*/);
			// test, skip some things for now
			//sum_vec3(common_force, cy_wheel_friction_force);
		}

		// handle brake input (differential support)
		void updateBrakingFriction(const double leftCxWheelFriction, const double rightCxWheelFriction)
		{
			// TODO: lua has this definition, check our values in calculations 
			//wheel_brake_moment_max = 15000.0, -- maximum value of braking moment  , N*m 

			// TODO: verify values are negative now?
			// TODO: should decrement from moment or verify that brake force does not exceed forward force (or we would go backwards..)

			/*
			// both sides equal amount -> just reduce it in cg?
			if (leftCxWheelFriction == rightCxWheelFriction)
			{
			}
			else
			{
				// differential -> separate moment vectoring
			}
			*/

			//Vec3 cxr_wheel_friction_force(-rightCxWheelFriction, 0.0,0.0);
			//Vec3 cxl_wheel_friction_force(-leftCxWheelFriction, 0.0,0.0);

			// TODO: check wheel offset from cg!
			// reversed axis? 
			// in DCS Zbody out of right wing?
			// Xbody out of nose -> force must be negative here

			// TODO: find better limiter here! we can't exceed forward force
			// -> we should decrement from momentum instead and note the cg there!

			/*
			if (common_force.x < rightCxWheelFriction)
			{
				// silly hack, remove this
				cxr_wheel_friction_force.x = -common_force.x;
			}

			Vec3 cxr_wheel_friction_pos(0.0,0.0,-5.0); // TODO: check offset!
			add_local_force(cxr_wheel_friction_force, cxr_wheel_friction_pos);

			if (common_force.x < leftCxWheelFriction)
			{
				// silly hack, remove this
				cxl_wheel_friction_force.x = -common_force.x;
			}

			Vec3 cxl_wheel_friction_pos(0.0,0.0,5.0); // TODO: check offset!
			add_local_force(cxl_wheel_friction_force, cxl_wheel_friction_pos);
			*/
		}

		// something like this to handle when nosewheel is turned?
		void updateNoseWheelTurn(const Vec3 &nosewheelDirection, const double turnAngle)
		{
			Vec3 cx_wheel_pos(5.0,0.0,0.0); // TODO: check offset!
			add_local_force(nosewheelDirection, cx_wheel_pos);
		}

		// 
		void updateFuelUsageMass(double mass_delta, double posX, double posY, double posZ)
		{
			fuel_mass_delta = mass_delta;
		}

		double getWeightN() const
		{
			return weight_N;
		}
	};
}

#endif // ifndef _F16EQUATIONSOFMOTION_H_
