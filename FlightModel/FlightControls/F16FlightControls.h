#ifndef _F16FLIGHTCONTROLS_H_
#define _F16FLIGHTCONTROLS_H_

#include "../stdafx.h"
#include <memory.h>
#include "../UtilityFunctions.h"
#include <Windows.h>
//#include "../include/general_filter.h"

#include "DummyFilter.h"

namespace F16
{
	// TODO! real actuator support

	class F16FcsController
	{
	public:
		F16FcsController() {}
		~F16FcsController() {}
	};


	class F16FlightControls
	{
	public:
		bool		simInitialized;
		int         Speedlevel; // LJQC: add speedlevel
		int         autopilot = 0; // LJQC: add autopilot/pull-up when overspeed
		int         ALTflaps = 0; // LJQC: ALT Flaps Switch to control the automatic flaps on F-16
		int         directmode = 0; //LJQC: Direct control mode just like in Su-27

		double		leadingEdgeFlap_PCT;	// Leading edge flap as a percent of maximum (0 to 1)
		double      blank = 0; //LJQC: add 0 value
		double      overspeed = 10; //LJQC: Deal with overspeed
	//protected:
		double		leading_edge_flap_integral;
		double		leading_edge_flap_integrated;
		double		leading_edge_flap_rate;
		double		leading_edge_flap_integrated_gained;
		double		leading_edge_flap_integrated_gained_biased;

		// TODO: just use as boolean or use this as angle?
		//double airbrake; // 0 = off
		bool airbrakeExtended;

		// Pitch controller variables
		double		longStickInput; // pitch normalized
		double		latStickInput; // bank normalized
		double		longStickInputRaw; // pitch orig
		double		latStickInputRaw; // bank orig
		
		double		stickCommandPosFiltered;
		double		azFiltered;
		double		alphaFiltered;
		double		longStickForce;

		double		pedInput;		// Pedal input command normalized (-1 to 1)
		double		pedInputRaw;	// yaw orig

		// Control filters (general filters to easily code up when compared to report block diagrams)
		DummyFilter	pitchRateWashout;
		DummyFilter	pitchIntegrator;
		DummyFilter	pitchPreActuatorFilter;
		DummyFilter	pitchActuatorDynamicsFilter;
		DummyFilter	accelFilter;
		DummyFilter	latStickForceFilter;
		DummyFilter	rollCommandFilter;
		DummyFilter	rollActuatorDynamicsFilter;
		DummyFilter	rollRateFilter1;
		DummyFilter	rollRateFilter2;
		DummyFilter	rudderCommandFilter;
		DummyFilter	yawRateWashout;
		DummyFilter	yawRateFilter;
		DummyFilter	yawServoFilter;

	public:
		F16FlightControls() 
			: simInitialized(false)
			, leadingEdgeFlap_PCT(0)
			, leading_edge_flap_integral(0)
			, leading_edge_flap_integrated(0)
			, leading_edge_flap_rate(0)
			, leading_edge_flap_integrated_gained(0)
			, leading_edge_flap_integrated_gained_biased(0)
			//, airbrake(0)
			, airbrakeExtended(false)
			, longStickInput(0)
			, latStickInput(0)
			, longStickInputRaw(0)
			, latStickInputRaw(0)
			, stickCommandPosFiltered(0)
			, azFiltered(0)
			, alphaFiltered(0)
			, longStickForce(0)
			, pedInput(0)
			, pedInputRaw(0)
			, pitchRateWashout()
			, pitchIntegrator()
			, pitchPreActuatorFilter()
			, pitchActuatorDynamicsFilter()
			, accelFilter()
			, latStickForceFilter()
			, rollCommandFilter()
			, rollActuatorDynamicsFilter()
			, rollRateFilter1()
			, rollRateFilter2()
			, rudderCommandFilter()
			, yawRateWashout()
			, yawRateFilter()
			, yawServoFilter()
		{}
		~F16FlightControls() {}

		void setPedInput(double value)
		{
			pedInput = value;
		}
		void setLatStickInput(double value) 
		{
			latStickInput = value;
		}
		void setLongStickInput(double value) 
		{
			longStickInput = value;
		}
		void setAirbrakeON()
		{
			//airbrake = value;
			airbrakeExtended = true;
		}
		void setAirbrakeOFF()
		{
			//airbrake = value;
			airbrakeExtended = false;
		}
		void switchAirbrake()
		{
			airbrakeExtended = !airbrakeExtended;
		}

		float getAirbrake()
		{
			if (airbrakeExtended == true)
			{
				return 1.0;
			}
			return 0.0;
		}

	//protected:

		// Controller for the leading edge flaps
		double leading_edge_flap_controller(double alpha_DEG, double dynamicPressure_FTLB, double staticPressure_FTLB, double frameTime)
		{
			double qbarOverPs = dynamicPressure_FTLB/staticPressure_FTLB;

			if(!(simInitialized))
			{
				leading_edge_flap_integral = -alpha_DEG;
				leading_edge_flap_integrated = leading_edge_flap_integral + 2*alpha_DEG;
				return leading_edge_flap_integral;
			}

			leading_edge_flap_rate = (alpha_DEG - leading_edge_flap_integrated) * 7.25;
			leading_edge_flap_integral += (leading_edge_flap_rate * frameTime);

			leading_edge_flap_integrated = leading_edge_flap_integral + alpha_DEG * 2.0;
			leading_edge_flap_integrated_gained = leading_edge_flap_integrated * 1.38;
			leading_edge_flap_integrated_gained_biased = leading_edge_flap_integrated_gained + 1.45 - (9.05 * qbarOverPs);	

			return leading_edge_flap_integrated_gained_biased; 
		}

		// Controller for yaw
		double fcs_yaw_controller(double pedInput, double pedTrim, double yaw_rate, double roll_rate, double aoa_filtered, double aileron_commanded, double ay, double dt)
		{
			if(!(simInitialized))
			{
				double numerators[2] = {0.0,4.0};
				double denominators[2] = {1.0,4.0};
				rudderCommandFilter.InitFilter(numerators,denominators,1,dt);

				double numerators1[2] = {1.0,0.0};
				double denominators1[2] = {1.0,1.0};
				yawRateWashout.InitFilter(numerators1,denominators1,1,dt);

				double numerators2[2] = {3.0,15.0};
				double denominators2[2] = {1.0,15.0};
				yawRateFilter.InitFilter(numerators2,denominators2,1,dt);

				double numerators3[3] = { 0.0, 0.0, pow(52.0,2.0)};
				double denomiantors3[3] = { 1.0, 2.0*0.7*52.0, pow(52.0,2.0)};
				yawServoFilter.InitFilter(numerators3,denomiantors3,2,dt);
			}

			double rudderForceCommand = pedInput * 450.0;

			double rudderCommand = 0.0;
			/*if(abs(rudderForceCommand) < 44.0)
			{
				rudderCommand = 0.0;
			}
			else if(rudderForceCommand >= 44.0)
			{
				rudderCommand = -0.0739 * rudderForceCommand + 3.2512;
			}
			else if(rudderForceCommand <= -44.0)
			{
				rudderCommand = -0.0739 * rudderForceCommand - 3.2512;
			}*/

			rudderCommand = limit(rudderCommand, -30.0, 30.0);
			double rudderCommandFiltered = rudderCommandFilter.Filter(!(simInitialized),dt,rudderCommand);
			double rudderCommandFilteredWTrim = pedTrim - rudderCommandFiltered;

			double alphaGained = aoa_filtered * (1.0/57.3);
			double rollRateWithAlpha = roll_rate * alphaGained;
			double yawRateWithRoll = yaw_rate - rollRateWithAlpha;

			double yawRateWithRollWashedOut = yawRateWashout.Filter(!(simInitialized),dt,yawRateWithRoll);
			double yawRateWithRollFiltered = yawRateFilter.Filter(!(simInitialized),dt,yawRateWithRollWashedOut);

			double yawRateFilteredWithSideAccel = yawRateWithRollFiltered;// + (ay * 19.3);

			double aileronGained = 0; //LJQC: make ARI only works at 0~25deg AOA=================================================================
			if (aoa_filtered < 25 && aoa_filtered > 0) aileronGained = limit(0.05 * aoa_filtered, 0.0, 1.5) * aileron_commanded;

			double finalRudderCommand = aileronGained + yawRateFilteredWithSideAccel + rudderCommandFilteredWTrim;

			if (Speedlevel !=4) return finalRudderCommand;
			else return blank;

			//TODO: Figure out why there is a ton of flutter at high speed due to these servo dynamics
			//double yawServoCommand = yawServoFilter.Filter(!(simInitialized),dt,finalRudderCommand);
			//return yawServoCommand;
		}

		double fcs_flap_controller(double airspeed_FPS) //LJQC: FLAPS will deploy when ALT Flaps Switch is ON.=====================================
		{
			double airspeed_KTS = 0.5924838012958964 * airspeed_FPS;
			double trailing_edge_flap_deflection = 0.0;

			if (airspeed_KTS < 240.0)
			{
				Speedlevel = 1;
				if (ALTflaps == 1) trailing_edge_flap_deflection = 20.0;
				else trailing_edge_flap_deflection = 0;
			}
			else if ((airspeed_KTS >= 240.0) && (airspeed_KTS <= 370.0))
			{
				Speedlevel = 2;
				if (ALTflaps == 1) trailing_edge_flap_deflection = (1.0 - ((airspeed_KTS - 240.0) / (370.0 - 240.0))) * 20.0;
				else trailing_edge_flap_deflection = 0;
			}
			else if ((airspeed_KTS > 370.0) && (airspeed_KTS <= 650.0))
			{
				Speedlevel = 3;
				trailing_edge_flap_deflection = 0.0;
			}
			else
			{
				Speedlevel = 4;
				trailing_edge_flap_deflection = 0.0;
			}

			trailing_edge_flap_deflection = limit(trailing_edge_flap_deflection, 0.0, 20.0);

			return trailing_edge_flap_deflection;
		}
		// Stick force schedule for pitch control
		double fcs_pitch_controller_force_command(double longStickInput, double pitchTrim, double dt)
		{
			double longStickInputForce = 0.0;
			if(longStickInput > 0.0)
			{
				longStickInputForce = longStickInput * 80.0;
			}
			else
			{
				longStickInputForce = longStickInput * 180.0;
			}
			longStickInputForce = limit(longStickInputForce,-180.0,80.0);
			longStickForce = longStickInputForce;

			double longStickCommand_G = 0.0;
			if(abs(longStickInputForce) <=  8.0)
			{
				longStickCommand_G = 0.0;
			}
			else if((longStickInputForce < -8) && (longStickInputForce > -33.0))
			{
				//if (pedInput > 0.8 || pedInput < -0.8) longStickCommand_G = 0.2*longStickInputForce + 1.6;
				longStickCommand_G = (0.016 * longStickInputForce) + 0.128;
			}
			else if(longStickInputForce <= -33.0)
			{
				//if (pedInput > 0.8 || pedInput < -0.8) longStickCommand_G = 0.2*longStickInputForce + 1.6;
				longStickCommand_G = (0.067 * longStickInputForce) + 1.8112;
			}
			else if((longStickInputForce > 8.0) && (longStickInputForce < 33.0))
			{
				longStickCommand_G = (0.032 * longStickInputForce) - 0.256;
			}
			else if(longStickInputForce >= 33.0)
			{
				longStickCommand_G = 0.0681*longStickInputForce - 1.4468;
			}

			double longStickCommandWithTrim_G = pitchTrim - longStickCommand_G;

			//LJQC: Pedal G-limit Override===============================================================================================
			double longStickCommandWithTrimLimited_G;
			if (pedInput < -0.8) longStickCommandWithTrimLimited_G = limit(longStickCommandWithTrim_G, -4.0, 50.0);
			else longStickCommandWithTrimLimited_G = limit(longStickCommandWithTrim_G, -4.0, 11.0);

			double longStickCommandWithTrimLimited_G_Rate = 6.0 * (longStickCommandWithTrimLimited_G - stickCommandPosFiltered);
			stickCommandPosFiltered += (longStickCommandWithTrimLimited_G_Rate * dt);

			return stickCommandPosFiltered;
		}

		// Schedule gain component due to dynamic pressure
		double dynamic_pressure_schedule(double dynPressure_LBFT2)
		{
			double dynamicPressure_kNM2 = dynPressure_LBFT2 * 1.4881639/1000.0; //for kN/m^2
			double scheduleOutput = 0.0;

			if(dynamicPressure_kNM2 < 9.576)
			{
				scheduleOutput = 1.0;
			}
			else if((dynamicPressure_kNM2 >= 9.576) && (dynamicPressure_kNM2 <= 43.0))
			{
				scheduleOutput =  (-0.018 * dynamicPressure_kNM2) + 1.1719;
				//scheduleOutput =  (-0.0239 * dynamicPressure_kNM2) + 1.2292;
			}
			else if(dynamicPressure_kNM2 > 43.0)
			{
				scheduleOutput = -0.003 * dynamicPressure_kNM2 + 0.5277;
				//scheduleOutput = -0.001 * dynamicPressure_kNM2 + 0.2422;
			}

			scheduleOutput = limit(scheduleOutput,0.05,1.0);

			return scheduleOutput;
		}

		// Angle of attack limiter logic
		double angle_of_attack_limiter(double alphaFiltered, double pitchRateCommand)
		{
			double topLimit = limit((alphaFiltered - 179.4) * 0.56, 0.0, 99999.0); //LJQC: increase AOA limits
			double bottomLimit = limit((alphaFiltered - 170.0 + pitchRateCommand) * 0.322, 0.0, 99999.0);
			
			return (topLimit + bottomLimit);
		}

		// Controller for pitch
		double fcs_pitch_controller(double longStickInput, double pitchTrim, double angle_of_attack_ind, double pitch_rate, double az, double differentialCommand, double dynPressure_LBFT2, double dt)
		{
			if(!(simInitialized))
			{
				double numerators[2] = {1.0,0.0};
				double denominators[2] = {1.0,1.0};
				pitchRateWashout.InitFilter(numerators,denominators,1,dt);

				numerators[0] = 0.0; numerators[1] = 2.5;
				denominators[0] = 1.0; denominators[1] = 0.0;
				pitchIntegrator.InitFilter(numerators,denominators,1,dt);

				numerators[0] = 3.0; numerators[1] = 15;
				denominators[0] = 1.0; denominators[1] = 15.0;
				pitchPreActuatorFilter.InitFilter(numerators,denominators,1,dt);

				double numerators2[3] = { 0.0, 0.0, pow(52.0,2.0)};
				double denomiantors2[3] = { 1.0, 2.0*0.7*52.0, pow(52.0,2.0)};
				pitchActuatorDynamicsFilter.InitFilter(numerators2,denomiantors2,2,dt);

				numerators[0] = 0.0; numerators[1] = 15.0;
				denominators[0] = 1.0; denominators[1] = 15.0;
				accelFilter.InitFilter(numerators,denominators,1,dt);
			}

			double stickCommandPos =  fcs_pitch_controller_force_command(longStickInput, pitchTrim, dt);

			double dynamicPressureScheduled = dynamic_pressure_schedule(dynPressure_LBFT2);	

			azFiltered = accelFilter.Filter(!(simInitialized),dt,az-1.0);

			double alphaLimited = limit(angle_of_attack_ind,-15.0, 179.0);
			double alphaLimitedRate = 10.0 * (alphaLimited - alphaFiltered); //10.0
			alphaFiltered += (alphaLimitedRate * dt);

			double pitchRateWashedOut = pitchRateWashout.Filter(!(simInitialized),dt,pitch_rate);



			//LJQC: Adjust Gains according to speed.=====================================================================================
			double pitchRateCommand; 
			if (Speedlevel == 1 && pedInput <= 0.8 && pedInput >= -0.8)
			{
				pitchRateCommand = pitchRateWashedOut * 0.4 * dynamicPressureScheduled; 
			}
			else if (Speedlevel == 2 && pedInput <= 0.8 && pedInput >= -0.8)
			{
				pitchRateCommand = pitchRateWashedOut * 0.55 * dynamicPressureScheduled;
			}
			else if (Speedlevel == 3 && pedInput <= 0.8 && pedInput >= -0.8)
			{
				pitchRateCommand = pitchRateWashedOut * 0.7 * dynamicPressureScheduled;
			}
			else if (Speedlevel == 4 && pedInput <= 0.8 && pedInput >= -0.8)
			{
				pitchRateCommand = pitchRateWashedOut * 0.1 * dynamicPressureScheduled;
			}
			else if (pedInput < -0.8) pitchRateCommand = pitchRateWashedOut * 0.8 * dynamicPressureScheduled;

			double limiterCommand = angle_of_attack_limiter(-alphaFiltered, pitchRateCommand);

			double gLimiterCommand;
			if (Speedlevel == 1 && pedInput <= 0.8 && pedInput >= -0.8)
			{
				gLimiterCommand = -(azFiltered + (pitchRateWashedOut * 0.2));	//0.2
			}
			else if (Speedlevel == 2 && pedInput <= 0.8 && pedInput >= -0.8)
			{
				gLimiterCommand = -(azFiltered + (pitchRateWashedOut * 0.15));	//0.2
			}
			else if (Speedlevel == 3 && pedInput <= 0.8 && pedInput >= -0.8)
			{
				gLimiterCommand = -(azFiltered + (pitchRateWashedOut * 0.1));	//0.2
			}
			else if (Speedlevel == 4 && pedInput <= 0.8 && pedInput >= -0.8)
			{
				gLimiterCommand = -(azFiltered + (pitchRateWashedOut * 0.7));	//0.2
			}
			else if (pedInput < -0.8) gLimiterCommand = -azFiltered;
			

			double finalCombinedCommand = dynamicPressureScheduled * (2.5 * (stickCommandPos + limiterCommand + gLimiterCommand));

			double finalCombinedCommandFilteredLimited = limit(pitchIntegrator.Filter(!(simInitialized),dt,finalCombinedCommand),-25.0,25.0);
			finalCombinedCommandFilteredLimited = finalCombinedCommandFilteredLimited + finalCombinedCommand;

			double finalPitchCommandTotal;
			if (Speedlevel == 1 && pedInput <= 0.8 && pedInput >= -0.8)
			{
				finalPitchCommandTotal = pitchPreActuatorFilter.Filter(!(simInitialized), dt, finalCombinedCommandFilteredLimited);
				finalPitchCommandTotal += (0.5 * alphaFiltered);
			}
			else if (Speedlevel == 2 && pedInput <= 0.8 && pedInput >= -0.8)
			{
				finalPitchCommandTotal = pitchPreActuatorFilter.Filter(!(simInitialized), dt, finalCombinedCommandFilteredLimited);
				finalPitchCommandTotal += (0.6 * alphaFiltered);
			}
			else if (Speedlevel == 3 && pedInput <= 0.8 && pedInput >= -0.8)
			{
				finalPitchCommandTotal = pitchPreActuatorFilter.Filter(!(simInitialized), dt, finalCombinedCommandFilteredLimited);
				finalPitchCommandTotal += (0.7 * alphaFiltered);
			}
			else if (Speedlevel == 4 && pedInput <= 0.8 && pedInput >= -0.8)
			{
				finalPitchCommandTotal = pitchPreActuatorFilter.Filter(!(simInitialized), dt, finalCombinedCommandFilteredLimited);
				finalPitchCommandTotal += (0.1 * alphaFiltered);
			}
			else if (pedInput < -0.8)
			{
				finalPitchCommandTotal = pitchPreActuatorFilter.Filter(!(simInitialized), dt, finalCombinedCommandFilteredLimited);
				finalPitchCommandTotal += (0.7 * alphaFiltered);
			}

			double longStickInputForce2;
			if (longStickInput > 0.0)
			{
				longStickInputForce2 = longStickInput * 80.0;
			}
			else
			{
				longStickInputForce2 = longStickInput * 180.0;
			}

			//LJQC: Key functions here:===================================================================================================
			if (GetAsyncKeyState(0x44) & 1)
			{
				autopilot = autopilot + 1;
				if (autopilot > 1) autopilot = 0;
			}

			if (GetAsyncKeyState(0x46) & 1) //ALT Flaps Switch: Press "F"
			{
				ALTflaps = ALTflaps + 1;
				if (ALTflaps > 1) ALTflaps = 0;
			}

			if (GetAsyncKeyState(0x53) & 1) //Direct Control Mode: press "S"
			{
				directmode = directmode + 1;
				if (directmode > 1) directmode = 0;
			}
			

			//LJQC: MPO fuctions here:=====================================================================================================
			if (directmode == 0)
			{

				if (pedInput <= 0.8 && autopilot == 0)
				{

					if (Speedlevel == 1)
					{
						if (longStickInputForce2 >= -8 && longStickInputForce2 <= 8 && alphaFiltered <= 10 && alphaFiltered > -179)
						{
							return finalPitchCommandTotal;
						}
						else if (longStickInputForce2 < -8 && alphaFiltered < 40) return finalPitchCommandTotal;
						else return stickCommandPos;
					}
					else if (Speedlevel == 2)
					{
						if (longStickInputForce2 < -8 && alphaFiltered > 40) return stickCommandPos;
						else return finalPitchCommandTotal;
					}
					else if (Speedlevel == 3)
					{
						return finalPitchCommandTotal;
					}
					else if (Speedlevel == 4)
					{
						directmode = 1;
					}
					else return finalPitchCommandTotal;

				}
				else if (pedInput > 0.8 || autopilot == 1) return overspeed;
				else return overspeed;
			}
			else 
			{ 
				stickCommandPos = stickCommandPos + 5;
				return stickCommandPos; 
			}

			// TODO: There are problems with flutter with the servo dynamics...needs to be nailed down!
			//double actuatorDynamicsResult = pitchActuatorDynamicsFilter.Filter(!(simInitialized),dt,finalPitchCommandTotal);
			//return actuatorDynamicsResult;	
		}

		// Controller for roll
		double fcs_roll_controller(double latStickInput, double longStickForce, double ay, double roll_rate, double roll_rate_trim,double dynPressure_LBFT2, double dt)
		{
			if(!(simInitialized))
			{
				double numerators[2] = {0.0,60.0};
				double denominators[2] = {1.0,60.0};
				latStickForceFilter.InitFilter(numerators,denominators,1,dt);

				double numerators1[2] = {0.0,10.0};
				double denominators1[2] = {1.0,10.0};
				rollCommandFilter.InitFilter(numerators1,denominators1,1,dt);

				double numerators2[3] = { 0.0, 0.0, pow(52.0,2.0)};
				double denomiantors2[3] = { 1.0, 2.0*0.7*52.0, pow(52.0,2.0)};
				rollActuatorDynamicsFilter.InitFilter(numerators2,denomiantors2,2,dt);

				double numerators3[2] = {0.0,50.0};
				double denominators3[2] = {1.0,50.0};
				rollRateFilter1.InitFilter(numerators3,denominators3,1,dt);

				double numerators4[3] = { 4.0, 64.0, 6400.0};
				double denomiantors4[3] = { 1.0, 80.0, 6400.0};
				rollRateFilter2.InitFilter(numerators4,denomiantors4,2,dt);
			}

			double latStickForceCmd = latStickInput * 75.0;
			double latStickForce = latStickForceFilter.Filter(!(simInitialized),dt,latStickForceCmd);

			double latStickForceBiased = latStickForce - (ay * 8.9);  // CJS: remove side acceleration bias?

			double longStickForceGained = longStickForce * 0.0667;
			double rollFeelGain = 0.0;
			if(abs(longStickForce) > 25.0)
			{
				rollFeelGain = 0.7;
			}
			else if(longStickForce >= 0.0)
			{
				rollFeelGain = -0.012 * longStickForceGained + 1.0;
			}
			else if(longStickForce < 0.0)
			{
				rollFeelGain = 0.012 * longStickForceGained + 1.0;
			}

			double latStickForceFinal = latStickForceBiased * rollFeelGain;

			double rollRateCommand = 0.0;
			if(abs(latStickForceFinal) < 3.0)
			{
				rollRateCommand = 0.0;
			}
			else if((latStickForceFinal >= 3.0) && (latStickForceFinal <= 25.0))
			{
				rollRateCommand = 0.9091 * latStickForceFinal - 2.7273;
			}
			else if((latStickForceFinal > 25.0) && (latStickForceFinal <= 46.0))
			{
				rollRateCommand = 2.8571 * latStickForceFinal - 51.429;
			}
			else if((latStickForceFinal > 46.0))
			{
				rollRateCommand = 7.5862 * latStickForceFinal - 268.97;
			}
			else if((latStickForceFinal <= -3.0) && (latStickForceFinal >= -25.0))
			{
				rollRateCommand = 0.9091 * latStickForceFinal + 2.7273;
			}
			else if((latStickForceFinal < -25.0) && (latStickForceFinal >= -46.0))
			{
				rollRateCommand = 2.8571 * latStickForceFinal + 51.429;
			}
			else if((latStickForceFinal < -46.0))
			{
				rollRateCommand = 7.5862 * latStickForceFinal + 268.97;
			}

			double rollRateCommandFilterd = rollCommandFilter.Filter(!(simInitialized),dt,rollRateCommand);

			double rollRateFiltered1 = rollRateFilter1.Filter(!(simInitialized),dt,roll_rate);

			double rollRateFiltered2 = (rollRateFilter2.Filter(!(simInitialized),dt,rollRateFiltered1));

			double rollRateCommandCombined = rollRateFiltered2 - rollRateCommandFilterd - roll_rate_trim;

			double dynamicPressure_NM2 = dynPressure_LBFT2 * 47.880258889;

			double pressureGain = 0.0;
			if(dynamicPressure_NM2 < 19153.0)
			{
				pressureGain = 0.2;
			}
			else if((dynamicPressure_NM2 >= 19153.0) && (dynamicPressure_NM2 <= 23941.0))
			{
				pressureGain = -0.00002089 * dynamicPressure_NM2 + 0.6;
			}
			else
			{
				pressureGain = 0.1;
			}

			double rollCommandGained = limit(rollRateCommandCombined * pressureGain, -21.5, 21.5);

			// Mechanical servo dynamics
			double rollActuatorCommand = rollActuatorDynamicsFilter.Filter(!(simInitialized),dt,rollCommandGained);	
			return rollActuatorCommand;
		}		

		/*
		// Passive flap schedule for the F-16...nominal for now from flight manual comments
		double fcs_flap_controller(double airspeed_FPS)
		{
			double airspeed_KTS = 0.5924838012958964 * airspeed_FPS;
			double trailing_edge_flap_deflection = 0.0;

			if(airspeed_KTS < 240.0)
			{
				trailing_edge_flap_deflection = 20.0;
			}
			else if((airspeed_KTS >= 240.0) && (airspeed_KTS <= 370.0))
			{
				trailing_edge_flap_deflection = (1.0 - ((airspeed_KTS - 240.0)/(370.0-240.0))) * 20.0;
			}
			else
			{
				trailing_edge_flap_deflection = (1.0 - ((airspeed_KTS - 240.0)/(370.0-240.0))) * 20.0;
			}

			trailing_edge_flap_deflection = limit(trailing_edge_flap_deflection,0.0,20.0);

			return trailing_edge_flap_deflection;
		}*/

	public:

		//---------------------------------------------
		//-----CONTROL DYNAMICS------------------------
		//---------------------------------------------
		void updateFrame(double totalVelocity_FPS, double dynamicPressure_LBFT2, double ps_LBFT2, double dt)
		{
			/*
			// Call the leading edge flap dynamics controller, this controller is based on dynamic pressure and angle of attack
			// and is completely automatic
			double leadingEdgeFlap_DEG = leading_edge_flap_controller(F16::alpha_DEG, dynamicPressure_LBFT2, ps_LBFT2, dt);	
			leadingEdgeFlap_PCT = limit(leadingEdgeFlap_DEG / 25.0, 0.0, 1.0);	

			// Call the longitudinal (pitch) controller.  Takes the following inputs:
			// -Normalize long stick input
			// -Trimmed G offset
			// -Angle of attack (deg)
			// -Pitch rate (rad/sec)
			// -Differential command (from roll controller, not quite implemented yet)
			elevator_DEG_commanded   = -(fcs_pitch_controller(longStickInput, -0.3, F16::alpha_DEG, F16::pitchRate_RPS * F16::radiansToDegrees, (F16::accz/9.81), 0.0, dynamicPressure_LBFT2, dt));

			// Call the servo dynamics model (not used as it causes high flutter in high speed situations, related to filtering and dt rate)
			elevator_DEG	= F16::elevator_DEG_commanded; //F16::ACTUATORS::elevator_actuator(F16::elevator_DEG_commanded,dt);
			elevator_DEG = limit(F16::elevator_DEG,-25.0,25.0);
	
			aileron_DEG_commanded = (fcs_roll_controller(latStickInput, longStickForce, F16::accy/9.81, F16::rollRate_RPS* F16::radiansToDegrees, 0.0, dynamicPressure_LBFT2, dt));
			aileron_DEG	= F16::aileron_DEG_commanded; //F16::ACTUATORS::aileron_actuator(F16::aileron_DEG_commanded,dt);
			aileron_DEG = limit(F16::aileron_DEG,-21.5,21.5);

			rudder_DEG_commanded = fcs_yaw_controller(	pedInput, 0.0, F16::yawRate_RPS * (180.0/3.14159), F16::rollRate_RPS* F16::radiansToDegrees,
															alphaFiltered, F16::aileron_DEG_commanded, F16::accy/9.81, dt);
			rudder_DEG		= rudder_DEG_commanded; //F16::ACTUATORS::rudder_actuator(F16::rudder_DEG_commanded,dt);
			rudder_DEG = limit(rudder_DEG,-30.0,30.0);

			flap_DEG = fcs_flap_controller(totalVelocity_FPS);
			*/
		}

	};
}

#endif // ifndef _F16FLIGHTCONTROLS_H_
