#ifndef _F16FLIGHTCONTROLS_H_
#define _F16FLIGHTCONTROLS_H_

#include "../stdafx.h"
#include <memory.h>
#include "../UtilityFunctions.h"
#include <Windows.h>
#include<iomanip>

//#include "../include/general_filter.h"

#include "DummyFilter.h"

int         a = 0.0; //LJQC: output KTAS on console
int         AOA = 0;
double      b = 0.0; //LJQC: output AOA on console
int         stickcommand = 0;//LJQC: display pitch input on console
int         rollinput = 0;//LJQC: display roll input on console
double      gload = 0.0;//LJQC: output load factor on console
int         Gs = 0;
int         Speedlevel; // LJQC: add speedlevel
int         autopilot = 0; // LJQC: add autopilot/pull-up when overspeed
int         ALTflaps = 0; // LJQC: ALT Flaps Switch to control the automatic flaps on F-16
int         directmode = 0; //LJQC: Direct control mode just like in Su-27
bool        TVC = FALSE;//LJQC: output TVC on/off on console

//LJQC: DirectX Overlay Below=============================================================================

LPDIRECT3D9             d3d = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9       d3ddev = NULL; // Our rendering device
LPD3DXFONT              pFont = NULL;
HINSTANCE hInstance;
int s_width = 1366;
int s_height = 768;
#define CENTERX (GetSystemMetrics(SM_CXSCREEN)/2)-(s_width/2)
#define CENTERY (GetSystemMetrics(SM_CYSCREEN)/2)-(s_height/2)
const MARGINS  margin = { 0, 0, s_width, s_height };


HWND hWnd;
HWND TargetWnd;
MSG Message;
RECT TargetRect;
HINSTANCE  inj_hModule;




LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void initD3D(HWND hWnd)
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);    // create the Direct3D interface

	D3DPRESENT_PARAMETERS d3dpp;    // create a struct to hold various device information

	ZeroMemory(&d3dpp, sizeof(d3dpp));    // clear out the struct for use
	d3dpp.Windowed = TRUE;    // program windowed, not fullscreen
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;    // discard old frames
	d3dpp.hDeviceWindow = hWnd;    // set the window to be used by Direct3D
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;     // set the back buffer format to 32-bit
	d3dpp.BackBufferWidth = s_width;    // set the width of the buffer
	d3dpp.BackBufferHeight = s_height;    // set the height of the buffer

	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	// create a device class using this information and the info from the d3dpp stuct
	d3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);

	D3DXCreateFont(d3ddev, 20, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial", &pFont);

}



int Render()
{
	d3ddev->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0);


	d3ddev->BeginScene();

	if (TargetWnd == GetForegroundWindow())

	{
		
		RECT g_FontPosition = { 0, 0, 1000, 664 }; //LJQC: KTAS符号
		pFont->DrawText(NULL, L"T", -1, &g_FontPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		RECT g_SpeedvaluePosition = { 0, 0, 1050, 664 };//LJQC: KTAS 数值
		std::ostringstream s1(a);
		s1 << a;
		pFont->DrawTextA(NULL, s1.str().c_str(), -1, &g_SpeedvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));





		RECT g_AOAPosition = { 0, 0, 1000, 724 };//LJQC: AOA符号
		pFont->DrawText(NULL, L"α", -1, &g_AOAPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		RECT g_AOAvaluePosition = { 0, 0, 1050, 724 };//LJQC: AOA 数值
		std::ostringstream s2(AOA);
		s2 << AOA;
		pFont->DrawTextA(NULL, s2.str().c_str(), -1, &g_AOAvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));






		RECT g_GPosition = { 0, 0, 1000, 604 };//LJQC: G-load符号
		pFont->DrawText(NULL, L"Gs", -1, &g_GPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		RECT g_GvaluePosition = { 0, 0, 965, 604 };//LJQC: G-load 数值
		std::ostringstream s3(Gs);
		s3 << Gs;
		pFont->DrawTextA(NULL, s3.str().c_str(), -1, &g_GvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));







		if (TVC == TRUE)
		{
			RECT g_TVCPosition = { 0, 0, 1350, 884 };//LJQC: TVC符号
			pFont->DrawText(NULL, L"TVC ON", -1, &g_TVCPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
		}

		if (directmode == 1)
		{
			RECT g_SPosition = { 0, 0, 1350, 944 };
			pFont->DrawText(NULL, L"Direct Mode", -1, &g_SPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
		}

		if (GetAsyncKeyState(0x52) & 0x8000)
		{
			RECT g_GLIMPosition = { 0, 0, 1350, 1004 };
			pFont->DrawText(NULL, L"G-LIM OVRD", -1, &g_GLIMPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
		}






		RECT g_pitchPosition = { 0, 0, 1700, 664 };
		pFont->DrawText(NULL, L"P", -1, &g_pitchPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		RECT g_pvaluePosition = { 0, 0, 1750, 664 };//LJQC: pitch input 数值
		std::ostringstream s4(stickcommand);
		s4 << stickcommand;
		pFont->DrawTextA(NULL, s4.str().c_str(), -1, &g_pvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));






		RECT g_rollPosition = { 0, 0, 1700, 724 };
		pFont->DrawText(NULL, L"R", -1, &g_rollPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		RECT g_rvaluePosition = { 0, 0, 1750, 724 };//LJQC: roll input 数值
		std::ostringstream s5(rollinput);
		s5 << rollinput;
		pFont->DrawTextA(NULL, s5.str().c_str(), -1, &g_rvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

	}

	d3ddev->EndScene(); // End the scene

	// Present the backbuffer contents to the display
	d3ddev->Present(NULL, NULL, NULL, NULL);

	return 0;
}



BOOL RegisterDLLWindowClass(wchar_t szClassName[])
{
	WNDCLASSEX OverlayWnd;

	OverlayWnd.cbClsExtra = 0;
	OverlayWnd.cbSize = sizeof(WNDCLASSEX);
	OverlayWnd.cbWndExtra = 0;
	OverlayWnd.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	OverlayWnd.hCursor = LoadCursor(0, IDC_ARROW);
	OverlayWnd.hIcon = LoadIcon(0, IDI_APPLICATION);
	OverlayWnd.hIconSm = LoadIcon(0, IDI_APPLICATION);
	OverlayWnd.hInstance = hInstance;
	OverlayWnd.lpfnWndProc = WindowProc;
	OverlayWnd.lpszClassName = L"A";
	OverlayWnd.lpszMenuName = L"A";
	OverlayWnd.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&OverlayWnd))
		return 0;
}



LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:

		DwmExtendFrameIntoClientArea(hWnd, &margin);


	case WM_DESTROY:

		PostQuitMessage(0);
		return 0;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}



DWORD WINAPI InputThread(LPVOID lpParam)
{
	Sleep(20*1000);
	wchar_t *pString = reinterpret_cast<wchar_t *> (lpParam);
	RegisterDLLWindowClass(L"A");
	TargetWnd = FindWindow(L"A", L"A");
	hWnd = CreateWindowEx(WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_COMPOSITED | WS_EX_TRANSPARENT, L"A", L"A", WS_EX_TOPMOST | WS_POPUP, 100, 100, 1028, 786, NULL, NULL, NULL, inj_hModule);
	SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 0, ULW_COLORKEY);
	SetLayeredWindowAttributes(hWnd, 0, 255, LWA_ALPHA);
	ShowWindow(hWnd, SW_SHOW);
	initD3D(hWnd);

	for (;;)
	{
		if (PeekMessage(&Message, hWnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		TargetWnd = FindWindow(0, L"DCS");
		GetWindowRect(TargetWnd, &TargetRect);
		MoveWindow(hWnd, TargetRect.left, TargetRect.top, TargetRect.right - TargetRect.left, TargetRect.bottom - TargetRect.top, true);

		if (!TargetWnd)
		{
			exit(0);
		}

		Render();
		Sleep(1);
	}


	return 0;
}


BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
	)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		inj_hModule = hModule;
		CreateThread(0, NULL, InputThread, (LPVOID)L"A", NULL, NULL);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


//LJQC: DirectX Overlay Ends.====================================================================================



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
			double qbarOverPs = dynamicPressure_FTLB / staticPressure_FTLB;

			if (!(simInitialized))
			{
				leading_edge_flap_integral = -alpha_DEG;
				leading_edge_flap_integrated = leading_edge_flap_integral + 2 * alpha_DEG;
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
			//yawrate = yaw_rate;
			if (!(simInitialized))
			{
				double numerators[2] = { 0.0, 4.0 };
				double denominators[2] = { 1.0, 4.0 };
				rudderCommandFilter.InitFilter(numerators, denominators, 1, dt);

				double numerators1[2] = { 1.0, 0.0 };
				double denominators1[2] = { 1.0, 1.0 };
				yawRateWashout.InitFilter(numerators1, denominators1, 1, dt);

				double numerators2[2] = { 3.0, 15.0 };
				double denominators2[2] = { 1.0, 15.0 };
				yawRateFilter.InitFilter(numerators2, denominators2, 1, dt);

				double numerators3[3] = { 0.0, 0.0, pow(52.0, 2.0) };
				double denomiantors3[3] = { 1.0, 2.0*0.7*52.0, pow(52.0, 2.0) };
				yawServoFilter.InitFilter(numerators3, denomiantors3, 2, dt);
			}

			double rudderForceCommand = pedInput * 450.0;

			double rudderCommand = 0.0; //LJQC: Restore rudder command
			if (abs(rudderForceCommand) < 44.0)
			{
				rudderCommand = 0.0;
			}
			else if (rudderForceCommand >= 44.0)
			{
				rudderCommand = -0.0739 * rudderForceCommand + 3.2512;
			}
			else if (rudderForceCommand <= -44.0)
			{
				rudderCommand = -0.0739 * rudderForceCommand - 3.2512;
			}

			rudderCommand = limit(rudderCommand, -30.0, 30.0);
			double rudderCommandFiltered = rudderCommandFilter.Filter(!(simInitialized), dt, rudderCommand);
			double rudderCommandFilteredWTrim = pedTrim - rudderCommandFiltered;

			double alphaGained = aoa_filtered * (1.0 / 57.3);
			double rollRateWithAlpha = roll_rate * alphaGained;
			double yawRateWithRoll = yaw_rate - rollRateWithAlpha;

			double yawRateWithRollWashedOut = yawRateWashout.Filter(!(simInitialized), dt, yawRateWithRoll);
			double yawRateWithRollFiltered = yawRateFilter.Filter(!(simInitialized), dt, yawRateWithRollWashedOut);

			double yawRateFilteredWithSideAccel = yawRateWithRollFiltered;// + (ay * 19.3);

			double aileronGained = 0; //LJQC: make ARI only works at 0~30deg AOA=================================================================
			if (aoa_filtered < 30 && aoa_filtered > 0) aileronGained = limit(0.05 * aoa_filtered, 0.0, 1.5) * aileron_commanded;

			b = aoa_filtered; //double
			AOA = b; //int

			double finalRudderCommand = aileronGained + yawRateFilteredWithSideAccel + rudderCommandFilteredWTrim;

			//yawoutput = finalRudderCommand;

			if (Speedlevel != 4) return finalRudderCommand;
			else return blank;

			//TODO: Figure out why there is a ton of flutter at high speed due to these servo dynamics
			//double yawServoCommand = yawServoFilter.Filter(!(simInitialized),dt,finalRudderCommand);
			//return yawServoCommand;
		}

		double fcs_flap_controller(double airspeed_FPS) //LJQC: FLAPS will deploy when ALT Flaps Switch is ON.=====================================
		{
			double airspeed_KTS = 0.5924838012958964 * airspeed_FPS;
			double trailing_edge_flap_deflection = 0.0;
			a = airspeed_KTS;

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

			if (TVC == TRUE)
			{
				if (longStickInput > 0.0)
				{
					longStickInputForce = longStickInput * 80.0;
				}
				else
				{
					longStickInputForce = longStickInput * 180.0;
				}
			}
			else if (TVC == FALSE)
			{
				longStickInputForce = longStickInput * 180.0;
			}
			stickcommand = longStickInputForce;

			//LJQC: AOA Limiter Fake/Hack when TVC is OFF==============================
			if (TVC == FALSE)
			{
				if (b >= 18.0 && b < 25.4) longStickInputForce = longStickInputForce + (b * 2.0 - 36.0) * (70.0 / 20.8);
				else if (b >= 25.4 && b < 30.0) longStickInputForce = longStickInputForce + 70.0 + (b * 2.0 - 50.8) * (110.0 / 9.2);
				else if (b >= 30.0) longStickInputForce = longStickInputForce + 180.0 + (b * 2.0 - 60.0) * (80.0 / 20.0);

				longStickInputForce = limit(longStickInputForce, -180.0, 180.0);
			}
			else if (TVC == TRUE) longStickInputForce = limit(longStickInputForce, -180.0, 80.0);
			longStickForce = longStickInputForce;


			double longStickCommand_G = 0.0;
			if (abs(longStickInputForce) <= 8.0)
			{
				longStickCommand_G = 0.0;
			}
			else if ((longStickInputForce < -8) && (longStickInputForce > -33.0))
			{
				longStickCommand_G = (0.016 * longStickInputForce) + 0.128;
			}
			else if (longStickInputForce <= -33.0)
			{
				longStickCommand_G = (0.067 * longStickInputForce) + 1.8112;
			}
			else if ((longStickInputForce > 8.0) && (longStickInputForce < 33.0))
			{
				longStickCommand_G = (0.032 * longStickInputForce) - 0.256;
			}
			else if (longStickInputForce >= 33.0)
			{
				longStickCommand_G = 0.0681*longStickInputForce - 1.4468;
			}
			double longStickCommandWithTrim_G = pitchTrim - longStickCommand_G;

			//LJQC: G-limit Override===============================================================================================
			double longStickCommandWithTrimLimited_G;
			if (GetAsyncKeyState(0x52) & 0x8000) longStickCommandWithTrimLimited_G = limit(longStickCommandWithTrim_G, -4.0, 50.0);
			else longStickCommandWithTrimLimited_G = limit(longStickCommandWithTrim_G, -4.0, 11.0);
			double longStickCommandWithTrimLimited_G_Rate;
			if (TVC == TRUE)
			{
				longStickCommandWithTrimLimited_G_Rate = 6.0 * (longStickCommandWithTrimLimited_G - stickCommandPosFiltered);
			}
			else longStickCommandWithTrimLimited_G_Rate = 4.0 * (longStickCommandWithTrimLimited_G - stickCommandPosFiltered); //original value
			stickCommandPosFiltered += (longStickCommandWithTrimLimited_G_Rate * dt);

			return stickCommandPosFiltered;
		}

		// Schedule gain component due to dynamic pressure
		double dynamic_pressure_schedule(double dynPressure_LBFT2)
		{
			double dynamicPressure_kNM2 = dynPressure_LBFT2 * 1.4881639 / 1000.0; //for kN/m^2
			double scheduleOutput = 0.0;

			if (dynamicPressure_kNM2 < 9.576)
			{
				scheduleOutput = 1.0;
			}
			else if ((dynamicPressure_kNM2 >= 9.576) && (dynamicPressure_kNM2 <= 43.0))
			{
				scheduleOutput = (-0.018 * dynamicPressure_kNM2) + 1.1719;
			}
			else if (dynamicPressure_kNM2 > 43.0)
			{
				scheduleOutput = -0.003 * dynamicPressure_kNM2 + 0.5277;
			}

			scheduleOutput = limit(scheduleOutput, 0.05, 1.0);

			return scheduleOutput;
		}

		// Angle of attack limiter logic
		double angle_of_attack_limiter(double alphaFiltered, double pitchRateCommand)
		{
			double topLimit;
			double bottomLimit;
			if (TVC == TRUE)
			{
				topLimit = limit((alphaFiltered - 179.4) * 0.56, 0.0, 99999.0); //LJQC: increase AOA limits
				bottomLimit = limit((alphaFiltered - 170.0 + pitchRateCommand) * 0.322, 0.0, 99999.0);
			}
			else
			{
				topLimit = limit((alphaFiltered - 20.4) * 0.69, 0.0, 99999.0); //LJQC: Standard F-16 limits
				bottomLimit = limit((alphaFiltered - 15.0 + pitchRateCommand) * 0.322, 0.0, 99999.0);
			}
			return (topLimit + bottomLimit);
		}

		// Controller for pitch
		double fcs_pitch_controller(double longStickInput, double pitchTrim, double angle_of_attack_ind, double pitch_rate, double az, double differentialCommand, double dynPressure_LBFT2, double dt)
		{
			gload = az + 1; //double
			Gs = gload; //int
			//pitchrate = pitch_rate;
			if (!(simInitialized))
			{
				double numerators[2] = { 1.0, 0.0 };
				double denominators[2] = { 1.0, 1.0 };
				pitchRateWashout.InitFilter(numerators, denominators, 1, dt);

				numerators[0] = 0.0; numerators[1] = 2.5;
				denominators[0] = 1.0; denominators[1] = 0.0;
				pitchIntegrator.InitFilter(numerators, denominators, 1, dt);

				numerators[0] = 3.0; numerators[1] = 15;
				denominators[0] = 1.0; denominators[1] = 15.0;
				pitchPreActuatorFilter.InitFilter(numerators, denominators, 1, dt);

				double numerators2[3] = { 0.0, 0.0, pow(52.0, 2.0) };
				double denomiantors2[3] = { 1.0, 2.0*0.7*52.0, pow(52.0, 2.0) };
				pitchActuatorDynamicsFilter.InitFilter(numerators2, denomiantors2, 2, dt);

				numerators[0] = 0.0; numerators[1] = 15.0;
				denominators[0] = 1.0; denominators[1] = 15.0;
				accelFilter.InitFilter(numerators, denominators, 1, dt);
			}

			double stickCommandPos = fcs_pitch_controller_force_command(longStickInput, pitchTrim, dt);

			double dynamicPressureScheduled = dynamic_pressure_schedule(dynPressure_LBFT2);

			azFiltered = accelFilter.Filter(!(simInitialized), dt, az - 1.0);

			double alphaLimited = limit(angle_of_attack_ind, -95.0, 179.0);

			double alphaLimitedRate = 10.0 * (alphaLimited - alphaFiltered); //10.0


			alphaFiltered += (alphaLimitedRate * dt);

			double pitchRateWashedOut = pitchRateWashout.Filter(!(simInitialized), dt, pitch_rate);



			//LJQC: Adjust Gains according to speed.=====================================================================================
			double pitchRateCommand;
			if (TVC == TRUE)
			{
				if (Speedlevel == 1 && GetAsyncKeyState(0x52) == 0 && GetAsyncKeyState(0x53) == 0)
				{
					pitchRateCommand = pitchRateWashedOut * 0.4 * dynamicPressureScheduled;
				}
				else if (Speedlevel == 2 && GetAsyncKeyState(0x52) == 0 && GetAsyncKeyState(0x53) == 0)
				{
					pitchRateCommand = pitchRateWashedOut * 0.55 * dynamicPressureScheduled;
				}
				else if (Speedlevel == 3 && GetAsyncKeyState(0x52) == 0 && GetAsyncKeyState(0x53) == 0)
				{
					pitchRateCommand = pitchRateWashedOut * 0.7 * dynamicPressureScheduled;
				}
				else if (Speedlevel == 4 && GetAsyncKeyState(0x52) == 0 && GetAsyncKeyState(0x53) == 0)
				{
					pitchRateCommand = pitchRateWashedOut * 0.1 * dynamicPressureScheduled;
				}
				else if (GetAsyncKeyState(0x52) & 0x8000 || GetAsyncKeyState(0x53) & 0x8000) pitchRateCommand = pitchRateWashedOut * 0.8 * dynamicPressureScheduled;
			}
			else pitchRateCommand = pitchRateWashedOut * 0.7 * dynamicPressureScheduled; //LJQC: Standard F-16 gain

			double limiterCommand = angle_of_attack_limiter(-alphaFiltered, pitchRateCommand);

			double gLimiterCommand;
			if (TVC == TRUE)
			{
				if (Speedlevel == 1 && GetAsyncKeyState(0x52) == 0 && GetAsyncKeyState(0x53) == 0)
				{
					gLimiterCommand = -(azFiltered + (pitchRateWashedOut * 0.2));	//0.2
				}
				else if (Speedlevel == 2 && GetAsyncKeyState(0x52) == 0 && GetAsyncKeyState(0x53) == 0)
				{
					gLimiterCommand = -(azFiltered + (pitchRateWashedOut * 0.15));	//0.2
				}
				else if (Speedlevel == 3 && GetAsyncKeyState(0x52) == 0 && GetAsyncKeyState(0x53) == 0)
				{
					gLimiterCommand = -(azFiltered + (pitchRateWashedOut * 0.1));	//0.2
				}
				else if (Speedlevel == 4 && GetAsyncKeyState(0x52) == 0 && GetAsyncKeyState(0x53) == 0)
				{
					gLimiterCommand = -(azFiltered + (pitchRateWashedOut * 0.7));	//0.2
				}
				else if (GetAsyncKeyState(0x52) & 0x8000 || GetAsyncKeyState(0x53) & 0x8000) gLimiterCommand = -azFiltered;
			}
			else gLimiterCommand = -(azFiltered + (pitchRateWashedOut * 0.2));	//LJQC: Standard F-16 gain


			double finalCombinedCommand = dynamicPressureScheduled * (2.5 * (stickCommandPos + limiterCommand + gLimiterCommand));

			double finalCombinedCommandFilteredLimited = limit(pitchIntegrator.Filter(!(simInitialized), dt, finalCombinedCommand), -25.0, 25.0);
			finalCombinedCommandFilteredLimited = finalCombinedCommandFilteredLimited + finalCombinedCommand;

			double finalPitchCommandTotal = pitchPreActuatorFilter.Filter(!(simInitialized), dt, finalCombinedCommandFilteredLimited);
			if (TVC == TRUE)
			{
				if (Speedlevel == 1 && GetAsyncKeyState(0x52) == 0 && GetAsyncKeyState(0x53) == 0)
				{
					finalPitchCommandTotal += (0.5 * alphaFiltered);
				}
				else if (Speedlevel == 2 && GetAsyncKeyState(0x52) == 0 && GetAsyncKeyState(0x53) == 0)
				{
					finalPitchCommandTotal += (0.6 * alphaFiltered);
				}
				else if (Speedlevel == 3 && GetAsyncKeyState(0x52) == 0 && GetAsyncKeyState(0x53) == 0)
				{
					finalPitchCommandTotal += (0.7 * alphaFiltered);
				}
				else if (Speedlevel == 4 && GetAsyncKeyState(0x52) == 0 && GetAsyncKeyState(0x53) == 0)
				{
					finalPitchCommandTotal += (0.1 * alphaFiltered);
				}
				else if (GetAsyncKeyState(0x52) & 0x8000 || GetAsyncKeyState(0x53) & 0x8000)
				{
					finalPitchCommandTotal += (0.7 * alphaFiltered);
				}
			}
			else finalPitchCommandTotal += (0.5 * alphaFiltered);//original value

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
			if (GetAsyncKeyState(0x44) & 0x8000) autopilot = 1;
			else if (GetAsyncKeyState(0x44) == 0) autopilot = 0;

			if (GetAsyncKeyState(0x46) & 1) //ALT Flaps Switch: Press "F"
			{
				ALTflaps = ALTflaps + 1;
				if (ALTflaps > 1) ALTflaps = 0;
			}

			if (GetAsyncKeyState(0x53) & 0x8000) directmode = 1;
			else if (GetAsyncKeyState(0x53) == 0) directmode = 0;

			if (GetAsyncKeyState(0x54) & 1) TVC = !TVC;

			//pitchinput = finalPitchCommandTotal;


			//LJQC: MPO fuctions here:=====================================================================================================
			if (TVC == TRUE)
			{
				if (directmode == 0)
				{

					if (autopilot == 0)
					{

						if (a < 230)
						{
							if (longStickInputForce2 >= -8 && longStickInputForce2 <= 8 && alphaFiltered <= 10 && alphaFiltered > -179)
							{
								return finalPitchCommandTotal;
							}
							else if (longStickInputForce2 < -8 && alphaFiltered <= 10) return finalPitchCommandTotal;
							else return stickCommandPos;
						}
						else if (a >= 230 && a <= 370)
						{
							if (longStickInputForce2 < -8 && alphaFiltered > 90)
							{
								return stickCommandPos;
							}
							else return finalPitchCommandTotal;
						}
						else if (Speedlevel == 3)
						{
							return finalPitchCommandTotal;
						}
						else if (Speedlevel == 4)
						{
							stickCommandPos = stickCommandPos*0.34 + 4.64;//LJQC: Eliminate the flutter at high speeds.(Fake/Hack)
							return stickCommandPos;
						}
						else return finalPitchCommandTotal;

					}
					else if (autopilot == 1) return overspeed;
					else return overspeed;
				}
				else
				{
					stickCommandPos = stickCommandPos + 5;
					return stickCommandPos;
				}
			}
			else if (TVC == FALSE)
			{
				if (Speedlevel != 4)
				{
					return finalPitchCommandTotal;
				}
				else if (Speedlevel == 4)
				{
					stickCommandPos = stickCommandPos*0.34 + 4.54; //LJQC: Eliminate the flutter at high speeds.(Fake/Hack)
					return stickCommandPos;
				}
				else return finalPitchCommandTotal;
			}

			// TODO: There are problems with flutter with the servo dynamics...needs to be nailed down!
			//double actuatorDynamicsResult = pitchActuatorDynamicsFilter.Filter(!(simInitialized),dt,finalPitchCommandTotal);
			//return actuatorDynamicsResult;	
		}

		// Controller for roll
		double fcs_roll_controller(double latStickInput, double longStickForce, double ay, double roll_rate, double roll_rate_trim, double dynPressure_LBFT2, double dt)
		{
			//rollrate = roll_rate;
			if (!(simInitialized))
			{
				double numerators[2] = { 0.0, 60.0 };
				double denominators[2] = { 1.0, 60.0 };
				latStickForceFilter.InitFilter(numerators, denominators, 1, dt);

				double numerators1[2] = { 0.0, 10.0 };
				double denominators1[2] = { 1.0, 10.0 };
				rollCommandFilter.InitFilter(numerators1, denominators1, 1, dt);

				double numerators2[3] = { 0.0, 0.0, pow(52.0, 2.0) };
				double denomiantors2[3] = { 1.0, 2.0*0.7*52.0, pow(52.0, 2.0) };
				rollActuatorDynamicsFilter.InitFilter(numerators2, denomiantors2, 2, dt);

				double numerators3[2] = { 0.0, 50.0 };
				double denominators3[2] = { 1.0, 50.0 };
				rollRateFilter1.InitFilter(numerators3, denominators3, 1, dt);

				double numerators4[3] = { 4.0, 64.0, 6400.0 };
				double denomiantors4[3] = { 1.0, 80.0, 6400.0 };
				rollRateFilter2.InitFilter(numerators4, denomiantors4, 2, dt);
			}

			double latStickForceCmd = latStickInput * 75.0;
			rollinput = latStickForceCmd;

			double latStickForce = latStickForceFilter.Filter(!(simInitialized), dt, latStickForceCmd);



			double latStickForceBiased = latStickForce - (ay * 8.9);  // CJS: remove side acceleration bias?

			double longStickForceGained = longStickForce * 0.0667;
			double rollFeelGain = 0.0;
			if (abs(longStickForce) > 25.0)
			{
				rollFeelGain = 0.7;
			}
			else if (longStickForce >= 0.0)
			{
				rollFeelGain = -0.012 * longStickForceGained + 1.0;
			}
			else if (longStickForce < 0.0)
			{
				rollFeelGain = 0.012 * longStickForceGained + 1.0;
			}

			double latStickForceFinal = latStickForceBiased * rollFeelGain;

			double rollRateCommand = 0.0;
			if (abs(latStickForceFinal) < 3.0)
			{
				rollRateCommand = 0.0;
			}
			else if ((latStickForceFinal >= 3.0) && (latStickForceFinal <= 25.0))
			{
				rollRateCommand = 0.9091 * latStickForceFinal - 2.7273;
			}
			else if ((latStickForceFinal > 25.0) && (latStickForceFinal <= 46.0))
			{
				rollRateCommand = 2.8571 * latStickForceFinal - 51.429;
			}
			else if ((latStickForceFinal > 46.0))
			{
				rollRateCommand = 7.5862 * latStickForceFinal - 268.97;
			}
			else if ((latStickForceFinal <= -3.0) && (latStickForceFinal >= -25.0))
			{
				rollRateCommand = 0.9091 * latStickForceFinal + 2.7273;
			}
			else if ((latStickForceFinal < -25.0) && (latStickForceFinal >= -46.0))
			{
				rollRateCommand = 2.8571 * latStickForceFinal + 51.429;
			}
			else if ((latStickForceFinal < -46.0))
			{
				rollRateCommand = 7.5862 * latStickForceFinal + 268.97;
			}

			double rollRateCommandFilterd = rollCommandFilter.Filter(!(simInitialized), dt, rollRateCommand);

			double rollRateFiltered1 = rollRateFilter1.Filter(!(simInitialized), dt, roll_rate);

			double rollRateFiltered2 = (rollRateFilter2.Filter(!(simInitialized), dt, rollRateFiltered1));

			double rollRateCommandCombined = rollRateFiltered2 - rollRateCommandFilterd - roll_rate_trim;

			double dynamicPressure_NM2 = dynPressure_LBFT2 * 47.880258889;

			double pressureGain = 0.0;
			if (dynamicPressure_NM2 < 19153.0)
			{
				pressureGain = 0.2;
			}
			else if ((dynamicPressure_NM2 >= 19153.0) && (dynamicPressure_NM2 <= 23941.0))
			{
				pressureGain = -0.00002089 * dynamicPressure_NM2 + 0.6;
			}
			else
			{
				pressureGain = 0.1;
			}

			double rollCommandGained = limit(rollRateCommandCombined * pressureGain, -21.5, 21.5);

			// Mechanical servo dynamics
			double rollActuatorCommand = rollActuatorDynamicsFilter.Filter(!(simInitialized), dt, rollCommandGained);

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