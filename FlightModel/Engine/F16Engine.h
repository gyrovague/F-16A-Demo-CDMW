#ifndef _F16ENGINE_H_
#define _F16ENGINE_H_

#include "../stdafx.h"

/*
		engine = 
		{
			Nmg	=	62, -- RPM at idle
			MinRUD	=	0, -- Min state of the throttle
			MaxRUD	=	1, -- Max state of the throttle
			MaksRUD	=	0.85, -- Military power state of the throttle
			ForsRUD	=	0.91, -- Afterburner state of the throttle
			typeng	=	E_TURBOJET_AB,
			
			hMaxEng	=	19, -- Max altitude for safe engine operation in km
			dcx_eng	=	0.0124, -- Engine drag coeficient
			cemax	=	1.24, -- not used for fuel calulation , only for AI routines to check flight time ( fuel calculation algorithm is built in )
			cefor	=	2.56, -- not used for fuel calulation , only for AI routines to check flight time ( fuel calculation algorithm is built in )
			dpdh_m	=	2000, --  altitude coefficient for max thrust
			dpdh_f	=	4200,  --  altitude coefficient for AB thrust

			-- M - Mach number
			-- Pmax - Engine thrust at military power
			-- Pfor - Engine thrust at AFB
			table_data = 
			{		--   M		Pmax		 Pfor	
				[1] = 	{0,	88000,	141000},
				[2] = 	{0.2,	80000,	143000},
				[3] = 	{0.4,	79000,	150000},
				[4] = 	{0.6,	82000,	165000},
				[5] = 	{0.7,	90000,	177000},
				[6] = 	{0.8,	94000,	193000},
				[7] = 	{0.9,	96000,	200000},
				[8] = 	{1,	100000,	205000},
				[9] = 	{1.1,	100000,	214000},
				[10] = 	{1.2,	98000,	222000},
				[11] = 	{1.3,	100000,	235000},
				[12] = 	{1.5,	98000,	258000},
				[13] = 	{1.8,	94000,	276000},
				[14] = 	{2,	88000,	283000},
				[15] = 	{2.2,	82000,	285000},
				[16] = 	{2.5,	80000,	287000},
				[17] = 	{3.9,	50000,	200000},
			}, -- end of table_data
		}, -- end of engine
*/

namespace F16
{
	// Engine: Pratt & Whitney F100-PW-129 or General Electric F110-GE-129
	// Thrust: Pratt & Whitney: 65 kN, AB 106 kN; General Electric: 76 kN, AB 129 kN
	// -> adapt to support either one?
	// Turbine inlet temperature: 1,350 °C (2,460 °F)

	double thrustTmp = 0.0;
	double Tmil;
	double Tmax;
	double Tidle;
	bool UFO = FALSE; //LJQC: Speed Brake Hack
	bool CATI2;
	double Speeeeeeeeed;

	class F16Engine
	{
	protected:
		double m_power3;

	public:
		double	thrust_N; // Engine thrust (N)
		double	throttleInput;	// Throttle input command normalized (-1 to 1)

		double percentPower;
		double afterburner;
		
		

		// amount of fuel used in this engine setting in current flight conditions (temperature, airspeed..)
		double fuelPerFrame;

		

		// fuel flow: LEAN - RICH
		// -> 100pph increase?
		// range 0 - 80,000pph (instruments)

		// oil pressure: 0-100 psi
		double oilPressure;

		// temperatures, overheat

		// which part of engine we need? 
		// likely we need calculation of each section separately?
		// cockpit gauge: 300..900 range
		double engineTemperature;

		//double engineRPM; // rounds per minute: non-zero if shutdown in air?
		//double drag; // amount of drag if not running while in air?

		bool starting; // "spooling up"
		bool stopping; // "spooling down"

		bool isIgnited; // if it is really running or just rotating from airflow? (out of fuel mid-air?)
		bool Cstate;

		F16Engine() 
			: m_power3(0)
			, thrust_N(0)
			, throttleInput(0)
			, percentPower(0)
			, afterburner(0)
			, fuelPerFrame(0)
			, oilPressure(100)
			, engineTemperature(900)
			//, engineRPM(0)
			, starting(false)
			, stopping(false)
			, isIgnited(true) // currently, have it as started always (check initial status handling etc.)
		{}
		~F16Engine() {}

		void setThrottleInput(double value)
		{
			throttleInput = value;
		}
		double getThrottleInput() const
		{
			return throttleInput;
		}

		double getOilPressure() const
		{
			return oilPressure;
		}
		double getEngineTemperature() const
		{
			return engineTemperature;
		}
		double getFuelFlow() const
		{
			return fuelPerFrame;
		}

		double getEngineRpm() const
		{
			if (isIgnited == false) // ignore throttle setting if engine is not running
			{
				return 0;
			}

			// ED_FM_ENGINE_1_RPM:
			return (throttleInput/100.0) * 3000;
		}
		double getEngineRelatedRpm() const
		{
			if (isIgnited == false)
			{
				return 0;
			}

			// ED_FM_ENGINE_1_RELATED_RPM:
			return (throttleInput/100.0);
		}
		double getEngineThrust() const
		{
			if (isIgnited == false)
			{
				return 0;
			}

			// ED_FM_ENGINE_1_THRUST:
			return (throttleInput/100.0) * 9000 * 9.81;
		}
		double getEngineRelatedThrust() const
		{
			if (isIgnited == false)
			{
				return 0;
			}

			// ED_FM_ENGINE_1_RELATED_THRUST:
			return (throttleInput/100.0);
		}
		int getUFOstate() const
		{
			if (UFO == FALSE)
			{
				return 0;
			}
			else if (UFO == TRUE)
			{
				return 1;
			}
		}

		bool getCATI(bool CAT)
		{
			CATI2 = CAT;
			return CATI2;
		}

		double getSpeeeed(double bb)
		{
			Speeeeeeeeed = bb;
			return Speeeeeeeeed;

		}

		bool getCstate(bool a)
		{
			Cstate = a;
			return Cstate; //LJQC: Canopy Open/Close State
		}

		void startEngine()
		{
			starting = true;
			stopping = false;

			// temporary for testing
			isIgnited = true;
		}
		void stopEngine()
		{
			stopping = true;
			starting = false;

			// temporary for testing
			isIgnited = false;
			fuelPerFrame = 0;
		}

		double getLowPressureBleedAir() const
		{
			// just a function of engine RPM?
			return 0;
		}
		double getHighPressureBleedAir() const
		{
			// just a function of engine RPM?
			return 0;
		}

		// fuel use per frame in current conditions
		double getFuelPerFrame() const
		{
			return fuelPerFrame;
		}
		double getThrustN() const
		{
			return thrust_N;
		}

		void updateFrame(const double mach, double alt, double frameTime);
	};

	// Coded from the simulator study document
	void F16Engine::updateFrame(const double mach, double alt, double frameTime)
	{
		/*
		if (starting == true)
		{
			// TODO: update according to frametime

			// just skip to final result now..
			starting = false;
			isIgnited = true;
		}
		else if (stopping == true)
		{
			// TODO: update according to frametime

			// just skip to final result now..
			stopping = false;
			isIgnited = false;
		}

		if (isIgnited == false)
		{
			engineRPM = 0;
			afterburner = 0;
			percentPower = 0;
			thrust_N = 0;
			m_power3 = 0;
			return;
		}
		*/
		if (GetAsyncKeyState(0x42) & 1) UFO = !UFO; //LJQC: Toggle Speed Brakes Open/Close

		afterburner = (throttleInput - 80.0) / 20.0;
		if(throttleInput < 78.0)
		{
			percentPower = throttleInput * 0.6923;
		}
		else
		{
			percentPower = 54.0 + throttleInput *4.5455 - 354.55;//LJQC: Fix for power curve
		}
		percentPower = limit(percentPower,0.0,100.0);

		double power1 = percentPower;
		double power2 = 0.0;
		double power3rate = 0.0;

		//if(!(F16::simInitialized))
		//{
		//	m_power3 = power1;
		//}

		if(power1 < 50.0)
		{
			if(m_power3 < 50.0)
			{
				power2 = power1;
				if((power2-m_power3) < 40.0)
				{
					power3rate = 1.0 * (power2 - m_power3);
				}
				else
				{
					power3rate = 0.1 * (power2 - m_power3);
				}
			}
			else
			{
				power2 = 40.0;
				power3rate = 5.0 * (power2 - m_power3);
			}
		}
		else
		{
			if(m_power3 < 50.0)
			{
				power2 = 60.0;
				if((power2-m_power3) < 40.0)
				{
					power3rate = 1.0 * (power2 - m_power3);
				}
				else
				{
					power3rate = 0.1 * (power2 - m_power3);
				}
			}
			else
			{
				power2 = power1;
				power3rate = 5.0 * (power2 - m_power3);
			}
		}

		m_power3 += (power3rate * frameTime);
		m_power3 = limit(m_power3,0.0,100.0);

		//From Simulator Study document (use 0 altitude values for now)
		//TODO: This should really be a look-up table per the document reference but this is sufficient for now...
		double altTemp;
		double altTemp2;

		
		//if (UFO == FALSE)
		//{
			altTemp = (alt/55000.0);
			altTemp2 = (alt/50000.0);
		//}
		/*
		else if (UFO == TRUE)
		{
			altTemp = 0.0;
			altTemp2 = 0.0;
		}
		*/

		double machLimited;
		if (UFO == FALSE) machLimited = limit(mach, 0.2, 1.45);
		else if (UFO == TRUE) machLimited = limit(mach, 0.2, 0.6);

		
		if (Speeeeeeeeed > 0)
		{
			if (UFO == TRUE && Cstate == FALSE && CATI2 == FALSE)  Tidle = -94976.0;
			else if (UFO == TRUE && Cstate == FALSE && CATI2 == TRUE) Tidle = -34976.0;
			else if (UFO == TRUE && Cstate == TRUE)  Tidle = -34976.0;
			else Tidle = (-24976.0 * machLimited + 9091.5) + (altTemp * 12000.0);
		}
		else Tidle = 0;

		if (UFO == FALSE) Tmil = (-25958.0 * pow(machLimited, 3.0) + 34336.0 * pow(machLimited, 2.0) - 14575.0 * machLimited + 58137.0) + (altTemp2 * -42000.0);
		else if (UFO == TRUE) Tmil = (-25958.0 * pow(machLimited, 3.0) + 34336.0 * pow(machLimited, 2.0) - 14575.0 * machLimited + 58137.0) + (altTemp2 * -42000.0) - 54976.0;


		if (UFO == TRUE && Cstate == FALSE && CATI2 == FALSE) Tmax = (4270200.0 * pow(machLimited, 2.0) + 866100.4 * machLimited + 9275600.0) + (altTemp2 * -100000.0);
		else if (UFO == TRUE && Cstate == FALSE && CATI2 == TRUE) Tmax = (42702.0 * pow(machLimited, 2.0) + 8661.4 * machLimited + 92756.0) + (altTemp2 * -100000.0) - 10445.0;
		else if (UFO == TRUE && Cstate == TRUE) Tmax = (42702.0 * pow(machLimited, 2.0) + 8661.4 * machLimited + 92756.0) + (altTemp2 * -100000.0) - 10445.0;
		else  Tmax = (42702.0 * pow(machLimited, 2.0) + 8661.4 * machLimited + 92756.0) + (altTemp2 * -100000.0);

		if(m_power3 < 50.0)
		{
			thrustTmp = Tidle + (Tmil - Tidle)*(m_power3 / 50.0);
		}
		else
		{
			thrustTmp = Tmil + (Tmax-Tmil)*(m_power3 - 50.0)/50.0;
		}

		thrust_N = limit(thrustTmp, -274000.0, 274000.0);

		// TODO: usage by actual engine ?
		//fuelPerFrame =  10 * throttleInput * frameTime; //10 kg persecond
		fuelPerFrame =  10 * frameTime; //10 kg persecond

	}
	
	/*
	A table I read said that the F-16 C expended 415 kg of fuel per minute at mach .5 at sea level, 
	310 kg/min at mach .8 at 15,000 feet, 
	and was at peak fuel efficiency of 260 kg/min at mach 1.4 at 36,000 feet

	//if (afterburner -> 23 gallons per minute?

	-> speed, altitude, throttle -> fuel usage?
	*/
}

#endif // ifndef _F16ENGINE_H_
