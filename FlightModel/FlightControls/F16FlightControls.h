#ifndef _F16FLIGHTCONTROLS_H_
#define _F16FLIGHTCONTROLS_H_

#include "../stdafx.h"
#include <memory.h>
#include "../UtilityFunctions.h"
#include <Windows.h>
#include <math.h>
#include<iomanip>
#include <ctime>

//#include "../include/general_filter.h"

#include "DummyFilter.h"


bool        ladder = TRUE;
int         dele;//LJQC: Speed Brake Display
int        HMCS = 0;//LJQC: Turn ON/OFF HMCS
bool        CATI = TRUE;//LJQC: CAT I/III Swtich
int         a = 0; //LJQC: display KTAS on HMCS
int         IAS; //LJQC: display KIAS on HMCS
double      AOA = 0.0;//LJQC: AOA display on HMCS
double      b = 0.0; //LJQC: AOA used for FPM (Velocity Vector) display
double      Beta;//LJQC: Beta used for FPM (Velocity Vector) display
int         stickcommand = 0;//LJQC: display pitch input
int         rollinput = 0;//LJQC: display roll input
double      gload = 0.0;//LJQC: output load factor
double         Gs = 0.0;
double      MaxG = 0.0;
int         Speedlevel; // LJQC: add speedlevel
int         autopilot = 0; // LJQC: a 0 value
int         ALTflaps = 0; // LJQC: ALT Flaps Switch to control the automatic flaps on F-16
int         directmode = 0; //LJQC: Direct control mode just like in Su-27
bool        TVC = FALSE;//LJQC: output TVC on/off on console
double      MACH; //LJQC: Mach Number for HMCS display, 2 deci num
double      MACHfull;//LJQC: Mach Number for calculation
int         ALT; //LJQC: Altitude for HMCS display
double      dALT;//Double: Altitude for calculation
double         VVI; //LJQC: Vertical Velocity
double         thousandVVI;////LJQC: Vertical Velocity for HMCS display
double      gAccelx; //quaternion_x
double      pAccelx;//ax
double      airspeed_KTS;//LJQC: TAS for calculation
double      proc5;//LJQC: IAS for calculation
int         Height;//Height for HMCS display
double         Sideforce;//Sideforce for EEGS calculation
double      rollrate;//rollrate for EEGS calculation
double      pitchrate;//pitchrate for EEGS calculation
double      yawrate;//pitchrate for EEGS calculation
bool       canopystate;//Hook
//double     CompressF;//get wheel compression for debug



double pitchangle; //Pitch ladder = 0 (Horizon Ladder)
double pitchangle20;
double pitchangle40;
double pitchangle60;
double pitchangle602;
double pitchangle80;
double pitchangle802;
double pitchangleminus60;
double pitchangleminus80;


double      num7 = 0.0;//Bank angle
double      num8 = 0.0;//=tan(pitch angle)
double      num9 = 0.0;//LJQC: Vertical Velocity (m/s)
double      num10 = 0.0;//LJQC: ay (az actually) in body system
double      num11 = 0.0;//LJQC: Ground Object Height

double quaternionx = 0.0; //LJQC: Heading of Aircraft in rad
double quaterniony = 0.0; //LJQC: Engine RPM
bool quaternionz = FALSE; //LJQC: landingear state
double quaternionw = 0.0;//LJQC: Bank angle in rad
double bankangle = 0.0;
double heading = 0.0; //LJQC: Heading of Aircraft in deg
int    headingdisplay = 0;

double         KTASast = 0.0;
double         ALTast = 0.0;

//Trim function:
double         pitchtrim = 0.0;

//for HMCS debug
double         displayX = -1.0;
double         displayY = -183.0;
double         GundisplayY = -158.0;
double         displayZ = 1.0;
double         displayZ2;
double         displayW = 1.0;
double         displayW2;
double         displayC = 20.4;
double         HeadingTapeCorrection = 0.0;

//For clock display:
double c1 = 30.0 / 180.0 * M_PI;
double c2 = 60.0 / 180.0 * M_PI;
double c3 = 90.0 / 180.0 * M_PI;
double c4 = 120.0 / 180.0 * M_PI;
double c5 = 150.0 / 180.0 * M_PI;
double c6 = M_PI;
double c7 = 210.0 / 180.0 * M_PI;
double c8 = 240.0 / 180.0 * M_PI;
double c9 = 270.0 / 180.0 * M_PI;
double c10 = 300.0 / 180.0 * M_PI;
double c11 = 330.0 / 180.0 * M_PI;
double c14 = -2000.0 / 60.0 / F16::meterToFoot;
double c15 = 2000.0 / 60.0 / F16::meterToFoot;


//LJQC: DirectX Overlay Below=============================================================================

LPDIRECT3D9             d3d = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9       d3ddev = NULL; // Our rendering device
LPD3DXFONT              pFont = NULL;
LPD3DXFONT              pFontHUD = NULL;
LPD3DXFONT              pFont2 = NULL;
LPD3DXFONT              pFont3 = NULL;
LPD3DXFONT              pFontOFF = NULL;
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
	D3DXCreateFont(d3ddev, 35, 0, 400, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial", &pFontHUD);
	D3DXCreateFont(d3ddev, 45, 0, FW_LIGHT, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial", &pFont2);
	D3DXCreateFont(d3ddev, 45, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial", &pFont3);
	D3DXCreateFont(d3ddev, 14, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial", &pFontOFF);
}

void DrawDot(double x, double y, double w, double h, int r, int g, int b, int a)
{
	static ID3DXLine* pLine;

	if (!pLine)
		D3DXCreateLine(d3ddev, &pLine);

	D3DXVECTOR2 vLine[2];

	pLine->SetWidth(3);
	pLine->SetAntialias(true);
	pLine->SetGLLines(true);

	vLine[0].x = x;
	vLine[0].y = y;
	vLine[1].x = w;
	vLine[1].y = h;

	pLine->Begin();
	pLine->Draw(vLine, 2, D3DCOLOR_RGBA(r, g, b, a));
	pLine->End();
}


void DrawLine(double x, double y, double w, double h, int r, int g, int b, int a)
{
	static ID3DXLine* pLine;

	if (!pLine)
		D3DXCreateLine(d3ddev, &pLine);

	D3DXVECTOR2 vLine[2];

	pLine->SetWidth(2);
	pLine->SetAntialias(true);
	pLine->SetGLLines(true);

	vLine[0].x = x;
	vLine[0].y = y;
	vLine[1].x = w;
	vLine[1].y = h;

	pLine->Begin();
	pLine->Draw(vLine, 2, D3DCOLOR_RGBA(r, g, b, a));
	pLine->End();
}

void DashedLine(double x, double y, double w, double h, int r, int g, int b, int a)
{
	static ID3DXLine* pLine;

	DWORD dwPattern = 01010101;

	if (!pLine)
		D3DXCreateLine(d3ddev, &pLine);

	D3DXVECTOR2 vLine[2];

	pLine->SetWidth(2);
	pLine->SetAntialias(true);
	pLine->SetGLLines(true);
	pLine->SetPattern(dwPattern);
	pLine->SetPatternScale(4);

	vLine[0].x = x;
	vLine[0].y = y;
	vLine[1].x = w;
	vLine[1].y = h;

	pLine->Begin();
	pLine->Draw(vLine, 2, D3DCOLOR_RGBA(r, g, b, a));
	pLine->End();
}

void DrawLine2(double x, double y, double w, double h, int r, int g, int b, int a)
{
	static ID3DXLine* pLine;

	if (!pLine)
		D3DXCreateLine(d3ddev, &pLine);

	D3DXVECTOR2 vLine[2];

	pLine->SetWidth(1);
	pLine->SetAntialias(false);
	pLine->SetGLLines(true);

	vLine[0].x = x;
	vLine[0].y = y;
	vLine[1].x = w;
	vLine[1].y = h;

	pLine->Begin();
	pLine->Draw(vLine, 2, D3DCOLOR_RGBA(r, g, b, a));
	pLine->End();
}

int Render()
{
	d3ddev->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0);


	d3ddev->BeginScene();

	if (HMCS == 1)

	{
		//LJQC: Airspeed Display==========================================================================================

		RECT g_TASPosition = { 0, 0, 1350 - 709 - 10 + 16, 944 - 36 };//LJQC: KTAS symbol
		pFont->DrawText(NULL, L"T", -1, &g_TASPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		RECT g_SpeedvaluePosition = { 0, 0, 1350 - 649 + 16, 944 - 36 };//LJQC: KTAS value
		std::ostringstream s1(a);
		s1 << a;
		pFont->DrawTextA(NULL, s1.str().c_str(), -1, &g_SpeedvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		//LJQC: calculate IAS

		double procX = pow(1.0 - (6.8755856E-6)*dALT, 5.2558797);
		double proc1 = 1.0 + MACHfull * MACHfull / 5.0;
		double proc2 = pow(proc1, 3.5) - 1.0;
		double proc3 = 1.0 + procX * proc2;
		double proc4 = pow(proc3, 2.0 / 7.0) - 1.0;
		proc5 = 661.4786*pow(5.0*proc4, 0.5);

		/*In the reverse direction, given Mach number M and pressure altitude PA, we can find the IAS with:

		x=(1-6.8755856e-6*PA)^5.2558797
		ias=661.4786*(5*((1 + x*((1 + M^2/5)^3.5 - 1))^(2/7.) - 1))^0.5 (for M <=1)*/

		IAS = proc5;

		RECT g_SpeedvalueIASPosition = { 0, 0, 1350 - 630 + 16, 784 };//LJQC: KIAS value
		std::ostringstream s31(IAS);
		s31 << IAS;
		pFontHUD->DrawTextA(NULL, s31.str().c_str(), -1, &g_SpeedvalueIASPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));



		KTASast = proc5 / 50.0 * M_PI;//LJQC: 360deg for 100Kts according to RL F-22 HUD Tape

		DrawLine(720 / 2.0 + 62.123*sin(KTASast) / 2.0 + 8, 784 / 2.0 - 48.0*cos(KTASast) / 2.0, 720 / 2.0 + 92.055*sin(KTASast) / 2.0 + 8, 784 / 2.0 - 70.0*cos(KTASast) / 2.0, 132, 251, 169, 255);

		//LJQC: Dots for KIAS digital clock display
		DrawDot(8 + 720 / 2.0 + 96.0*sin(0) / 2.0, 784 / 2.0 + 73.0*cos(0) / 2.0, 8 + 720 / 2.0 + 104.0*sin(0) / 2.0, 784 / 2.0 + 81.0*cos(0) / 2.0, 132, 251, 169, 255);
		DrawDot(8 + 720 / 2.0 + 96.0*sin(c1) / 2.0, 784 / 2.0 + 73.0*cos(c1) / 2.0, 8 + 720 / 2.0 + 104.0*sin(c1) / 2.0, 784 / 2.0 + 81.0*cos(c1) / 2.0, 132, 251, 169, 255);
		DrawDot(8 + 720 / 2.0 + 96.0*sin(c2) / 2.0, 784 / 2.0 + 73.0*cos(c2) / 2.0, 8 + 720 / 2.0 + 104.0*sin(c2) / 2.0, 784 / 2.0 + 81.0*cos(c2) / 2.0, 132, 251, 169, 255);
		DrawDot(8 + 720 / 2.0 + 96.0*sin(c3) / 2.0, 784 / 2.0 + 73.0*cos(c3) / 2.0, 8 + 720 / 2.0 + 104.0*sin(c3) / 2.0, 784 / 2.0 + 81.0*cos(c3) / 2.0, 132, 251, 169, 255);
		DrawDot(8 + 720 / 2.0 + 96.0*sin(c4) / 2.0, 784 / 2.0 + 73.0*cos(c4) / 2.0, 8 + 720 / 2.0 + 104.0*sin(c4) / 2.0, 784 / 2.0 + 81.0*cos(c4) / 2.0, 132, 251, 169, 255);
		DrawDot(8 + 720 / 2.0 + 96.0*sin(c5) / 2.0, 784 / 2.0 + 73.0*cos(c5) / 2.0, 8 + 720 / 2.0 + 104.0*sin(c5) / 2.0, 784 / 2.0 + 81.0*cos(c5) / 2.0, 132, 251, 169, 255);
		DrawDot(8 + 720 / 2.0 + 96.0*sin(c6) / 2.0, 784 / 2.0 + 73.0*cos(c6) / 2.0, 8 + 720 / 2.0 + 104.0*sin(c6) / 2.0, 784 / 2.0 + 81.0*cos(c6) / 2.0, 132, 251, 169, 255);
		DrawDot(8 + 720 / 2.0 + 96.0*sin(c7) / 2.0, 784 / 2.0 + 73.0*cos(c7) / 2.0, 8 + 720 / 2.0 + 104.0*sin(c7) / 2.0, 784 / 2.0 + 81.0*cos(c7) / 2.0, 132, 251, 169, 255);
		DrawDot(8 + 720 / 2.0 + 96.0*sin(c8) / 2.0, 784 / 2.0 + 73.0*cos(c8) / 2.0, 8 + 720 / 2.0 + 104.0*sin(c8) / 2.0, 784 / 2.0 + 81.0*cos(c8) / 2.0, 132, 251, 169, 255);
		DrawDot(8 + 720 / 2.0 + 96.0*sin(c9) / 2.0, 784 / 2.0 + 73.0*cos(c9) / 2.0, 8 + 720 / 2.0 + 104.0*sin(c9) / 2.0, 784 / 2.0 + 81.0*cos(c9) / 2.0, 132, 251, 169, 255);
		DrawDot(8 + 720 / 2.0 + 96.0*sin(c10) / 2.0, 784 / 2.0 + 73.0*cos(c10) / 2.0, 8 + 720 / 2.0 + 104.0*sin(c10) / 2.0, 784 / 2.0 + 81.0*cos(c10) / 2.0, 132, 251, 169, 255);
		DrawDot(8 + 720 / 2.0 + 96.0*sin(c11) / 2.0, 784 / 2.0 + 73.0*cos(c11) / 2.0, 8 + 720 / 2.0 + 104.0*sin(c11) / 2.0, 784 / 2.0 + 81.0*cos(c11) / 2.0, 132, 251, 169, 255);


		//LJQC: AOA display=====================================================================================================

		DrawLine(8 + 720 / 2.0, (784 - 198 + 90) / 2.0, 8 + 720 / 2.0, (784 - 198 - 90) / 2.0, 132, 251, 169, 255);
		DrawLine(8 + 720 / 2.0, (784 - 198 + 88) / 2.0, 8 + 680 / 2.0, (784 - 198 + 88) / 2.0, 132, 251, 169, 255);
		DrawLine(8 + 720 / 2.0, (784 - 198 - 90) / 2.0, 8 + 680 / 2.0, (784 - 198 - 90) / 2.0, 132, 251, 169, 255);

		RECT g_AOAsym33Position = { 0, 0, 16 + 1350 - 673 + 26, 364 + 105 };
		pFont->DrawText(NULL, L"α", -1, &g_AOAsym33Position, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		RECT g_AOAPosition = { 0, 0, 16 + 1350 - 673, 784 - 198 };

		if (TVC == FALSE) pFont->DrawText(NULL, L"15.0 >", -1, &g_AOAPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
		else if (TVC == TRUE) pFont->DrawText(NULL, L"90.0 >", -1, &g_AOAPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));



		if (TVC == FALSE)
		{
			if (b <= 30 && b >= 0)
			{

				RECT g_AOAsymPosition = { 0, 0, 16 + 1350 - 588 - 30, 784 - 198 + 90 - b * 6.0 };
				pFont->DrawText(NULL, L"<", -1, &g_AOAsymPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));


				RECT g_AOAvaluePosition = { 0, 0, 16 + 1350 - 560, 784 - 198 + 90 - b * 6.0 };//LJQC: AOA 数值
				std::ostringstream s2(AOA);
				s2 << AOA;
				pFont->DrawTextA(NULL, s2.str().c_str(), -1, &g_AOAvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
			}
			else if (b > 30)
			{

				RECT g_AOAsymPosition = { 0, 0, 16 + 1350 - 588 - 30, 784 - 198 - 90 };
				pFont->DrawText(NULL, L"<", -1, &g_AOAsymPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));


				RECT g_AOAvaluePosition = { 0, 0, 16 + 1350 - 560, 784 - 198 - 90 };//LJQC: AOA 数值
				std::ostringstream s2(AOA);
				s2 << AOA;
				pFont->DrawTextA(NULL, s2.str().c_str(), -1, &g_AOAvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
			}
			else if (b < 0)
			{

				RECT g_AOAsymPosition = { 0, 0, 16 + 1350 - 588 - 30, 784 - 198 + 90 };
				pFont->DrawText(NULL, L"<", -1, &g_AOAsymPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));


				RECT g_AOAvaluePosition = { 0, 0, 16 + 1350 - 560, 784 - 198 + 90 };//LJQC: AOA 数值
				std::ostringstream s2(AOA);
				s2 << AOA;
				pFont->DrawTextA(NULL, s2.str().c_str(), -1, &g_AOAvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
			}
		}
		else if (TVC == TRUE)
		{
			if (b >= 0)
			{

				RECT g_AOAsymPosition = { 0, 0, 16 + 1350 - 588 - 30, 784 - 198 + 90 - b * 1.0 };
				pFont->DrawText(NULL, L"<", -1, &g_AOAsymPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));


				RECT g_AOAvaluePosition = { 0, 0, 16 + 1350 - 560, 784 - 198 + 90 - b * 1.0 };//LJQC: AOA 数值
				std::ostringstream s2(AOA);
				s2 << AOA;
				pFont->DrawTextA(NULL, s2.str().c_str(), -1, &g_AOAvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
			}
			else if (b < 0)
			{

				RECT g_AOAsymPosition = { 0, 0, 16 + 1350 - 588 - 30, 784 - 198 + 90 };
				pFont->DrawText(NULL, L"<", -1, &g_AOAsymPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));


				RECT g_AOAvaluePosition = { 0, 0, 16 + 1350 - 560, 784 - 198 + 90 };//LJQC: AOA 数值
				std::ostringstream s2(AOA);
				s2 << AOA;
				pFont->DrawTextA(NULL, s2.str().c_str(), -1, &g_AOAvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
			}
		}

		//LJQC: Mach number display===============================================================================================

		RECT g_MACHPosition = { 0, 0, 16 + 1350 - 709, 984 - 30 };//LJQC: Mach
		pFont->DrawText(NULL, L"M", -1, &g_MACHPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		RECT g_MACHvaluePosition = { 0, 0, 16 + 1350 - 653, 984 - 30 };//LJQC: Mach Number
		std::ostringstream s6(MACH);
		s6 << MACH;
		pFont->DrawTextA(NULL, s6.str().c_str(), -1, &g_MACHvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));



		//LJQC: G-load display ===============================================================================================


		RECT g_GPosition = { 0, 0, 16 + 1350 - 709, 1064 - 30 };//LJQC: G-load符号
		pFont->DrawText(NULL, L"G", -1, &g_GPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		RECT g_GvaluePosition = { 0, 0, 16 + 1350 - 645, 1064 - 30 };//LJQC: G-load 数值
		std::ostringstream s3(Gs);
		s3 << Gs;
		pFont->DrawTextA(NULL, s3.str().c_str(), -1, &g_GvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		//LJQC: Additional AOA display=====================================================================

		RECT g_AOA2Position = { 0, 0, 16 + 1350 - 709 - 10, 1104 - 30 };//LJQC: G-load符号
		pFont->DrawText(NULL, L"α", -1, &g_AOA2Position, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		RECT g_AOAvaluePosition2 = { 0, 0, 16 + 1350 - 645, 1104 - 30 };//LJQC: AOA 数值
		std::ostringstream s442(AOA);
		s442 << AOA;
		pFont->DrawTextA(NULL, s442.str().c_str(), -1, &g_AOAvaluePosition2, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		//LJQC: Maximum G========================================================================================

		if (Gs > MaxG) MaxG = Gs;
		MaxG = floor(MaxG * 10.0f + 0.5) / 10.0f;

		RECT g_MaxGPosition = { 0, 0, 16 + 1350 - 645, 1184 - 30 };//LJQC: AOA 数值
		std::ostringstream s443(MaxG);
		s443 << MaxG;
		pFont->DrawTextA(NULL, s443.str().c_str(), -1, &g_MaxGPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));


		//LJQC: Misc Indications================================================================================


		RECT g_CATPosition = { 0, 0, 16 + 1860, 1064 - 30 };
		if (CATI == TRUE && TVC == FALSE) pFont->DrawText(NULL, L"CAT I", -1, &g_CATPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
		else if (CATI == FALSE && TVC == FALSE) pFont->DrawText(NULL, L"CAT III", -1, &g_CATPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));


		if (TVC == TRUE)
		{
			RECT g_TVCPosition = { 0, 0, 16 + 1860, 1064 - 30 };//LJQC: TVC符号
			pFont->DrawText(NULL, L"TVC ON", -1, &g_TVCPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
		}

		if (TVC == TRUE && directmode == 1)
		{
			RECT g_SPosition = { 0, 0, 16 + 1860, 1104 - 30 };
			pFont->DrawText(NULL, L"Direct Mode", -1, &g_SPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
		}

		if (TVC == TRUE && GetAsyncKeyState(0x52) & 0x8000)
		{
			RECT g_GLIMPosition = { 0, 0, 16 + 1860, 1144 - 30 };
			pFont->DrawText(NULL, L"G-LIM OVRD", -1, &g_GLIMPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
		}

		if (dele == 1) //LJQC: Speed Brake Display
		{
			RECT g_UFOPosition = { 0, 0, 16 + 1860, 1184 - 30 };
			pFont->DrawText(NULL, L"SPD BRK", -1, &g_UFOPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
		}

		if (canopystate == FALSE) //LJQC: Speed Brake Display
		{
			RECT g_UFO22Position = { 0, 0, 16 + 1860, 1224 - 30 };
			pFont->DrawText(NULL, L"HOOK/LBAR", -1, &g_UFO22Position, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
		}



		//LJQC: Input Display =========================================================================================

		RECT g_PITCHsvaluePosition = { 0, 0, 16 + 2180 - 50, 854 + 150 };
		std::ostringstream s14(stickcommand);
		s14 << stickcommand;
		pFont->DrawTextA(NULL, s14.str().c_str(), -1, &g_PITCHsvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		RECT g_ROLLsvaluePosition = { 0, 0, 16 + 2360 - 50, 1064 + 150 };
		std::ostringstream s15(rollinput);
		s15 << rollinput;
		pFont->DrawTextA(NULL, s15.str().c_str(), -1, &g_ROLLsvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));


		RECT g_pitchvPosition = { 0, 0, 16 + 2180 - 50, 1064 + 150 };
		pFont->DrawText(NULL, L"+", -1, &g_pitchvPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		RECT g_pitchPosition = { 0, 0, 16 + 2180 - 50 + rollinput * 2.0, 1064 + 150 - stickcommand };
		pFont->DrawText(NULL, L"+", -1, &g_pitchPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		DrawLine2(8 + (2030 - 50) / 2.0, (884 + 150) / 2.0, 8 + (2330 - 50) / 2.0, (884 + 150) / 2.0, 132, 251, 169, 255);
		DrawLine2(8 + (2030 - 50) / 2.0, (884 + 150) / 2.0, 8 + (2030 - 50) / 2.0, (1244 + 150) / 2.0, 132, 251, 169, 255);
		DrawLine2(8 + (2330 - 50) / 2.0, (1244 + 150) / 2.0, 8 + (2330 - 50) / 2.0, (884 + 150) / 2.0, 132, 251, 169, 255);
		DrawLine2(8 + (2330 - 50) / 2.0, (1244 + 150) / 2.0, 8 + (2030 - 50) / 2.0, (1244 + 150) / 2.0, 132, 251, 169, 255);

		double throttlepos = quaterniony / 3000.0 * 360.0;
		RECT g_throttlepos = { 0, 0, 16 + 2330 - 50, 1244 + 150 - throttlepos };
		pFont->DrawText(NULL, L"+", -1, &g_throttlepos, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		RECT g_MILpos = { 0, 0, 16 + 2330 - 54, 1244 + 150 - 2400.0 / 3000.0 * 360.0 };
		pFont->DrawText(NULL, L">", -1, &g_MILpos, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));


		//LJQC: Values for debug only===================================================================================
		/*
		RECT g_PITCHtrimsvaluePosition = { 0, 0, 25 + 850, 800 };
		std::ostringstream s19(displayC);
		s19 << displayC;
		pFont->DrawTextA(NULL, s19.str().c_str(), -1, &g_PITCHtrimsvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
		
		RECT g_PITCHoutputsvaluePosition = { 0, 0, 25 + 850, 840 };
		std::ostringstream s20(displayY);
		s20 << displayY;
		pFont->DrawTextA(NULL, s20.str().c_str(), -1, &g_PITCHoutputsvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
		
		RECT g_zzvaluePosition = { 0, 0, 25 + 850, 880 };
		std::ostringstream s21(HeadingTapeCorrection);
		s21 << HeadingTapeCorrection;
		pFont->DrawTextA(NULL, s21.str().c_str(), -1, &g_zzvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
		
		RECT g_wwvaluePosition = { 0, 0, 850, 920 };
		std::ostringstream s22(displayW);
		s22 << displayW;
		pFont->DrawTextA(NULL, s22.str().c_str(), -1, &g_wwvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));


		RECT g_value444Position = { 0, 0, 850, 960 };
		std::ostringstream s444(displayC);
		s444 << displayC;
		pFont->DrawTextA(NULL, s444.str().c_str(), -1, &g_value444Position, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
		*/
		/*
		RECT g_value445Position = { 0, 0, 850, 1000 };
		std::ostringstream s445(pitchrate);
		s445 << pitchrate;
		pFont->DrawTextA(NULL, s445.str().c_str(), -1, &g_value445Position, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		RECT g_value446Position = { 0, 0, 850, 1040 };
		std::ostringstream s446(rollrate);
		s446 << rollrate;
		pFont->DrawTextA(NULL, s446.str().c_str(), -1, &g_value446Position, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		RECT g_value447Position = { 0, 0, 850, 1080 };
		std::ostringstream s447(yawrate);
		s447 << yawrate;
		pFont->DrawTextA(NULL, s447.str().c_str(), -1, &g_value447Position, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
		*/


		//LJQC: Gun sight display===================================================================================================================

		//double gunsightX = (displayX * Sideforce * 10.0 + displayY * rollrate / 10.0 + displayZ * yawrate * 5.0);
		//double gunsightY = (displayW * pitchrate * 2.0 + displayC * num10 * 2.0);

		if (ladder == FALSE)
		{
			//Left Line
			DrawLine(8 + 1300 / 2.0, 764 / 2.0 + GundisplayY / 2.0, 8 + (1330 + 0.8 * (2.1 * Sideforce * 10.0 - 1.4 * rollrate / 10.0 - 2.4 * yawrate * 5.0)) / 2.0, (764 + 0.8 * (2.3 * pitchrate * 2.0)) / 2.0 + GundisplayY / 2.0, 132, 251, 169, 255);
			DrawLine(8 + (1330 + 0.8 * (2.1 * Sideforce * 10.0 - 1.4 * rollrate / 10.0 - 2.4 * yawrate * 5.0)) / 2.0, (764 + 0.8 * (2.3 * pitchrate * 2.0)) / 2.0 + GundisplayY / 2.0, 8 + (1340 + 1.2 * (-1.0 * Sideforce * 10.0 - 10.5 * rollrate / 10.0 - 1.6 * yawrate * 5.0)) / 2.0, (764 + 1.2 * (1.1 * pitchrate * 2.0 + num10 * 2.0)) / 2.0 + GundisplayY / 2.0, 132, 251, 169, 255);
			DrawLine(8 + (1340 + 1.2 * (-1.0 * Sideforce * 10.0 - 10.5 * rollrate / 10.0 - 1.6 * yawrate * 5.0)) / 2.0, (764 + 1.2 * (1.1 * pitchrate * 2.0 + num10 * 2.0)) / 2.0 + GundisplayY / 2.0, 8 + (1345 + 1.6 * (-0.9 * Sideforce * 10.0 + 12.4 * rollrate / 10.0 - 1.8 * yawrate * 5.0)) / 2.0, (764 + 1.6 * (-0.2 * pitchrate * 2.0 + 1.9 * num10 * 2.0)) / 2.0 + GundisplayY / 2.0, 132, 251, 169, 255);

			//Right Line
			DrawLine(8 + 1400 / 2.0, 764 / 2.0 + GundisplayY / 2.0, 8 + (1370 + 0.8 * (2.1 * Sideforce * 10.0 - 1.4 * rollrate / 10.0 - 2.4 * yawrate * 5.0)) / 2.0, (764 + 0.8 * (2.3 * pitchrate * 2.0)) / 2.0 + GundisplayY / 2.0, 132, 251, 169, 255);
			DrawLine(8 + (1370 + 0.8 * (2.1 * Sideforce * 10.0 - 1.4 * rollrate / 10.0 - 2.4 * yawrate * 5.0)) / 2.0, (764 + 0.8 * (2.3 * pitchrate * 2.0)) / 2.0 + GundisplayY / 2.0, 8 + (1360 + 1.2 * (-1.0 * Sideforce * 10.0 - 10.5 * rollrate / 10.0 - 1.6 * yawrate * 5.0)) / 2.0, (764 + 1.2 * (1.1 * pitchrate * 2.0 + num10 * 2.0)) / 2.0 + GundisplayY / 2.0, 132, 251, 169, 255);
			DrawLine(8 + (1360 + 1.2 * (-1.0 * Sideforce * 10.0 - 10.5 * rollrate / 10.0 - 1.6 * yawrate * 5.0)) / 2.0, (764 + 1.2 * (1.1 * pitchrate * 2.0 + num10 * 2.0)) / 2.0 + GundisplayY / 2.0, 8 + (1355 + 1.6 * (-0.9 * Sideforce * 10.0 + 12.4 * rollrate / 10.0 - 1.8 * yawrate * 5.0)) / 2.0, (764 + 1.6 * (-0.2 * pitchrate * 2.0 + 1.9 * num10 * 2.0)) / 2.0 + GundisplayY / 2.0, 132, 251, 169, 255);

			//Aiming dot 1
			RECT g_dot1Position = { 0, 0, 16 + (1350 + 0.8 * (2.1 * Sideforce * 10.0 - 1.4 * rollrate / 10.0 - 2.4 * yawrate * 5.0)) / 1.0, (764 + 0.8 * (2.3 * pitchrate * 2.0)) / 1.0 + GundisplayY };
			pFont->DrawText(NULL, L"•", -1, &g_dot1Position, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

			//Aiming dot 2
			RECT g_dot2Position = { 0, 0, 16 + (1350 + 1.0 * (-1.0 * Sideforce * 10.0 - 10.5 * rollrate / 10.0 - 1.6 * yawrate * 5.0)) / 1.0, (764 + 1.0 * (1.1 * pitchrate * 2.0 + num10 * 2.0)) / 1.0 + GundisplayY };
			pFont->DrawText(NULL, L"•", -1, &g_dot2Position, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		}


		//DrawLine((1350 + 0.8 * (-42.7 * Sideforce * 10.0 + 3.0 * rollrate / 10.0)) / 2.0, (764 + 0.8 * (2.9 * num10 * 5.0 - 2.5 * pitchrate * 2.0)) / 2.0, (1350 + 1.2 * gunsightX) / 2.0, (764 + 1.2 * gunsightY) / 2.0, 132, 251, 169, 255);



		//LJQC: Altitude display =================================================================================================

		DrawLine(8 + 1860 / 2.0, (784 - 198 + 90) / 2.0, 8 + 1860 / 2.0, (784 - 198 - 90) / 2.0, 132, 251, 169, 255);
		DrawLine(8 + 1860 / 2.0, (784 - 198 + 88) / 2.0, 8 + 1900 / 2.0, (784 - 198 + 88) / 2.0, 132, 251, 169, 255);
		DrawLine(8 + 1860 / 2.0, (784 - 198 - 90) / 2.0, 8 + 1900 / 2.0, (784 - 198 - 90) / 2.0, 132, 251, 169, 255);


		RECT g_ALTvaluePosition = { 0, 0, 16 + 1350 + 630, 784 };//LJQC: Altitude Number Display
		std::ostringstream s7(ALT);
		s7 << ALT;
		pFontHUD->DrawTextA(NULL, s7.str().c_str(), -1, &g_ALTvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		ALTast = dALT / 500.0 * M_PI; //LJQC: 360deg for 1000Ft according to RL F-22 HUD Tape

		DrawLine(8 + 1980 / 2.0 + 74.895*sin(ALTast) / 2.0, 784 / 2.0 - 57.0 * cos(ALTast) / 2.0, 8 + 1980 / 2.0 + 110.372*sin(ALTast) / 2.0, 784 / 2.0 - 84.0*cos(ALTast) / 2.0, 132, 251, 169, 255);

		//LJQC: Dots for ALT digital clock display
		DrawDot(8 + 1980 / 2.0 + 113.0 *sin(0) / 2.0, 784 / 2.0 + 86.0*cos(0) / 2.0, 8 + 1980 / 2.0 + 121.0*sin(0) / 2.0, 784 / 2.0 + 94.0*cos(0) / 2.0, 132, 251, 169, 255);
		DrawDot(8 + 1980 / 2.0 + 113.0 * sin(c1) / 2.0, 784 / 2.0 + 86.0*cos(c1) / 2.0, 8 + 1980 / 2.0 + 121.0*sin(c1) / 2.0, 784 / 2.0 + 94.0*cos(c1) / 2.0, 132, 251, 169, 255);
		DrawDot(8 + 1980 / 2.0 + 113.0 * sin(c2) / 2.0, 784 / 2.0 + 86.0*cos(c2) / 2.0, 8 + 1980 / 2.0 + 121.0*sin(c2) / 2.0, 784 / 2.0 + 94.0*cos(c2) / 2.0, 132, 251, 169, 255);
		DrawDot(8 + 1980 / 2.0 + 113.0 * sin(c3) / 2.0, 784 / 2.0 + 86.0*cos(c3) / 2.0, 8 + 1980 / 2.0 + 121.0*sin(c3) / 2.0, 784 / 2.0 + 94.0*cos(c3) / 2.0, 132, 251, 169, 255);
		DrawDot(8 + 1980 / 2.0 + 113.0 * sin(c4) / 2.0, 784 / 2.0 + 86.0*cos(c4) / 2.0, 8 + 1980 / 2.0 + 121.0*sin(c4) / 2.0, 784 / 2.0 + 94.0*cos(c4) / 2.0, 132, 251, 169, 255);
		DrawDot(8 + 1980 / 2.0 + 113.0 * sin(c5) / 2.0, 784 / 2.0 + 86.0*cos(c5) / 2.0, 8 + 1980 / 2.0 + 121.0*sin(c5) / 2.0, 784 / 2.0 + 94.0*cos(c5) / 2.0, 132, 251, 169, 255);
		DrawDot(8 + 1980 / 2.0 + 113.0 * sin(c6) / 2.0, 784 / 2.0 + 86.0*cos(c6) / 2.0, 8 + 1980 / 2.0 + 121.0*sin(c6) / 2.0, 784 / 2.0 + 94.0*cos(c6) / 2.0, 132, 251, 169, 255);
		DrawDot(8 + 1980 / 2.0 + 113.0 * sin(c7) / 2.0, 784 / 2.0 + 86.0*cos(c7) / 2.0, 8 + 1980 / 2.0 + 121.0*sin(c7) / 2.0, 784 / 2.0 + 94.0*cos(c7) / 2.0, 132, 251, 169, 255);
		DrawDot(8 + 1980 / 2.0 + 113.0 * sin(c8) / 2.0, 784 / 2.0 + 86.0*cos(c8) / 2.0, 8 + 1980 / 2.0 + 121.0*sin(c8) / 2.0, 784 / 2.0 + 94.0*cos(c8) / 2.0, 132, 251, 169, 255);
		DrawDot(8 + 1980 / 2.0 + 113.0 * sin(c9) / 2.0, 784 / 2.0 + 86.0*cos(c9) / 2.0, 8 + 1980 / 2.0 + 121.0*sin(c9) / 2.0, 784 / 2.0 + 94.0*cos(c9) / 2.0, 132, 251, 169, 255);
		DrawDot(8 + 1980 / 2.0 + 113.0 * sin(c10) / 2.0, 784 / 2.0 + 86.0*cos(c10) / 2.0, 8 + 1980 / 2.0 + 121.0*sin(c10) / 2.0, 784 / 2.0 + 94.0*cos(c10) / 2.0, 132, 251, 169, 255);
		DrawDot(8 + 1980 / 2.0 + 113.0 * sin(c11) / 2.0, 784 / 2.0 + 86.0*cos(c11) / 2.0, 8 + 1980 / 2.0 + 121.0*sin(c11) / 2.0, 784 / 2.0 + 94.0*cos(c11) / 2.0, 132, 251, 169, 255);


		//LJQC: VVI display =======================================================================================================


		VVI = num9 * F16::meterToFoot * 60.0;
		thousandVVI = floor(VVI / 1000.0 * 100.0f + 0.5) / 100.0f;
		int VV2 = VVI;

		RECT g_VVI2valuePosition = { 0, 0, 16 + 1980 - 133 + 40, 944 - 36 };
		std::ostringstream s560(VV2);
		s560 << VV2;
		pFont->DrawTextA(NULL, s560.str().c_str(), -1, &g_VVI2valuePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		RECT g_VV2Position = { 0, 0, 16 + 1980 - 183 + 10, 944 - 36 };
		pFont->DrawText(NULL, L"VV", -1, &g_VV2Position, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));




		RECT g_VVIPosition = { 0, 0, 16 + 1980 - 83 + 10 + 2, 784 - 198 }; // VVI symbol position
		pFont->DrawText(NULL, L"< 0.00", -1, &g_VVIPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		RECT g_VVIsym33Position = { 0, 0, 16 + 1980 - 83 + 10 - 26, 364 + 105 };
		pFont->DrawText(NULL, L"VV", -1, &g_VVIsym33Position, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		if (num9 > -9 && num9 < 9)
		{
			RECT g_VVIsymPosition = { 0, 0, 16 + 1980 - 113 - 10 - 2, 784 - 198 - num9 * 10.0 };
			pFont->DrawText(NULL, L">", -1, &g_VVIsymPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

			RECT g_VVIvaluePosition = { 0, 0, 16 + 1980 - 133 - 49 - 2, 784 - 198 - num9 * 10.0 };
			std::ostringstream s11(thousandVVI);
			s11 << thousandVVI;
			pFont->DrawTextA(NULL, s11.str().c_str(), -1, &g_VVIvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
		}
		else if (num9 <= -9)
		{
			RECT g_VVIsymPosition = { 0, 0, 16 + 1980 - 113 - 10 - 2, 784 - 198 + 90.0 };
			pFont->DrawText(NULL, L">", -1, &g_VVIsymPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

			RECT g_VVIvaluePosition = { 0, 0, 16 + 1980 - 133 - 49 - 2, 784 - 198 + 90.0 };
			std::ostringstream s11(thousandVVI);
			s11 << thousandVVI;
			pFont->DrawTextA(NULL, s11.str().c_str(), -1, &g_VVIvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
		}
		else if (num9 >= 9)
		{
			RECT g_VVIsymPosition = { 0, 0, 16 + 1980 - 113 - 10 - 2, 784 - 198 - 90.0 };
			pFont->DrawText(NULL, L">", -1, &g_VVIsymPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

			RECT g_VVIvaluePosition = { 0, 0, 16 + 1980 - 133 - 49 - 2, 784 - 198 - 90.0 };
			std::ostringstream s11(thousandVVI);
			s11 << thousandVVI;
			pFont->DrawTextA(NULL, s11.str().c_str(), -1, &g_VVIvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
		}




		//LJQC: Height Displays =================================================================================================

		Height = ALT - num11 * F16::meterToFoot;

		RECT g_HeightvaluePosition = { 0, 0, 16 + 1980 - 133 + 40, 984 - 30 };
		std::ostringstream s12(Height);
		s12 << Height;
		pFont->DrawTextA(NULL, s12.str().c_str(), -1, &g_HeightvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		RECT g_BAROPosition = { 0, 0, 16 + 1980 - 183 + 10, 984 - 30 };
		pFont->DrawText(NULL, L"R", -1, &g_BAROPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));


		//LJQC: Gun Cross & Accel Info Displays =================================================================================================

		RECT g_CrossPosition = { 0, 0, 16 + 1350, 764 + displayY }; //LJQC: Gun cross display
		pFont->DrawText(NULL, L"+", -1, &g_CrossPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		RECT g_AccelxPosition = { 0, 0, 16 + 1385 + Beta * displayC, 764 - pAccelx * displayC + displayY + b * displayC };
		pFont->DrawText(NULL, L"<", -1, &g_AccelxPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		//RECT g_pAccelPosition = { 0, 0, 16 + 1335, 764 - pAccelx * 25 + displayY / 1.0 };
		//pFont->DrawText(NULL, L">", -1, &g_pAccelPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));




		//LJQC: Heading Display============================================================================================

		heading = 360.0 - quaternionx * F16::radiansToDegrees;
		double headingmodifier = floor(heading / 30.0f) * 30.0f;
		double headingmodifier2 = floor((heading - 30.0) / 30.0f) * 30.0f;
		double headingmodifier3 = floor((heading + 30.0) / 30.0f) * 30.0f;
		double headingmodifier4 = floor((heading + 60.0) / 30.0f) * 30.0f;
		double headingmodifier5 = floor((heading - 60.0) / 30.0f) * 30.0f;
		double headingmodifier6 = floor((heading + 90.0) / 30.0f) * 30.0f;
		double headingmodifier7 = floor((heading - 90.0) / 30.0f) * 30.0f;
		double Close1 = headingmodifier - heading;
		double North = headingmodifier2 - heading;
		double East = headingmodifier3 - heading;
		double South = headingmodifier4 - heading;
		double West = headingmodifier5 - heading;
		double Close2 = headingmodifier6 - heading;
		double Close3 = headingmodifier7 - heading;

		headingdisplay = heading;//headingdisplay = heading;

		RECT g_headingvaluePosition = { 0, 0, 16 + 1350, 279 + 109 + HeadingTapeCorrection };
		std::ostringstream s13(headingdisplay);
		s13 << headingdisplay;
		pFont->DrawTextA(NULL, s13.str().c_str(), -1, &g_headingvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		RECT g_DeltasymbolPosition = { 0, 0, 16 + 1350, 304 + 109 + HeadingTapeCorrection };
		pFont->DrawText(NULL, L"┯", -1, &g_DeltasymbolPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		if (ladder == TRUE)
		{
			DrawLine(8 + 1125 / 2.0, (320 + 105 + HeadingTapeCorrection) / 2.0, 8 + 1575 / 2.0, (320 + 105 + HeadingTapeCorrection) / 2.0, 132, 251, 169, 255);
			//1
			if (North >= -75 && North <= 75)
			{
				RECT g_DeltasymbolNPosition = { 0, 0, 16 + 1350 + North*3.0, 334 + 105 + HeadingTapeCorrection };
				pFont->DrawText(NULL, L"|", -1, &g_DeltasymbolNPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

				if (headingmodifier2 >= 360) headingmodifier2 -= 360;
				else if (headingmodifier2 < 0) headingmodifier2 += 360;

				RECT g_DeltasymbolN2Position = { 0, 0, 16 + 1350 + North*3.0, 364 + 105 + HeadingTapeCorrection };
				std::ostringstream s553(headingmodifier2);
				s553 << headingmodifier2;
				pFont->DrawTextA(NULL, s553.str().c_str(), -1, &g_DeltasymbolN2Position, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
			}

			//2
			if (East >= -75 && East <= 75)
			{
				RECT g_DeltasymbolEPosition = { 0, 0, 16 + 1350 + East*3.0, 334 + 105 + HeadingTapeCorrection };
				pFont->DrawText(NULL, L"|", -1, &g_DeltasymbolEPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

				if (headingmodifier3 >= 360) headingmodifier3 -= 360;
				else if (headingmodifier3 < 0) headingmodifier3 += 360;

				RECT g_DeltasymbolE2Position = { 0, 0, 16 + 1350 + East*3.0, 364 + 105 + HeadingTapeCorrection };
				std::ostringstream s554(headingmodifier3);
				s554 << headingmodifier3;
				pFont->DrawTextA(NULL, s554.str().c_str(), -1, &g_DeltasymbolE2Position, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
			}


			if (South >= -75 && South <= 75)
			{
				//3
				RECT g_DeltasymbolSPosition = { 0, 0, 16 + 1350 + South*3.0, 334 + 105 + HeadingTapeCorrection };
				pFont->DrawText(NULL, L"|", -1, &g_DeltasymbolSPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

				if (headingmodifier4 >= 360) headingmodifier4 -= 360;
				else if (headingmodifier4 < 0) headingmodifier4 += 360;

				RECT g_DeltasymbolS2Position = { 0, 0, 16 + 1350 + South*3.0, 364 + 105 + HeadingTapeCorrection };
				std::ostringstream s555(headingmodifier4);
				s555 << headingmodifier4;
				pFont->DrawTextA(NULL, s555.str().c_str(), -1, &g_DeltasymbolS2Position, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
			}


			if (West >= -75 && West <= 75)
			{
				//4
				RECT g_DeltasymbolWPosition = { 0, 0, 16 + 1350 + West*3.0, 334 + 105 + HeadingTapeCorrection };
				pFont->DrawText(NULL, L"|", -1, &g_DeltasymbolWPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

				if (headingmodifier5 >= 360) headingmodifier5 -= 360;
				else if (headingmodifier5 < 0) headingmodifier5 += 360;

				RECT g_DeltasymbolW2Position = { 0, 0, 16 + 1350 + West*3.0, 364 + 105 + HeadingTapeCorrection };
				std::ostringstream s556(headingmodifier5);
				s556 << headingmodifier5;
				pFont->DrawTextA(NULL, s556.str().c_str(), -1, &g_DeltasymbolW2Position, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
			}


			if (Close1 >= -75 && Close1 <= 75)
			{
				//5
				RECT g_DeltasymbolNPosition2 = { 0, 0, 16 + 1350 + Close1*3.0, 334 + 105 + HeadingTapeCorrection };
				pFont->DrawText(NULL, L"|", -1, &g_DeltasymbolNPosition2, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

				if (headingmodifier >= 360) headingmodifier -= 360;
				else if (headingmodifier < 0) headingmodifier += 360;

				RECT g_DeltasymbolN2Position2 = { 0, 0, 16 + 1350 + Close1*3.0, 364 + 105 + HeadingTapeCorrection };
				std::ostringstream s557(headingmodifier);
				s557 << headingmodifier;
				pFont->DrawTextA(NULL, s557.str().c_str(), -1, &g_DeltasymbolN2Position2, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
			}

			if (Close2 >= -75 && Close2 <= 75)
			{
				//5
				RECT g_DeltasymbolNPosition3 = { 0, 0, 16 + 1350 + Close2*3.0, 334 + 105 + HeadingTapeCorrection };
				pFont->DrawText(NULL, L"|", -1, &g_DeltasymbolNPosition3, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

				if (headingmodifier6 >= 360) headingmodifier6 -= 360;
				else if (headingmodifier6 < 0) headingmodifier6 += 360;

				RECT g_DeltasymbolN2Position4 = { 0, 0, 16 + 1350 + Close2*3.0, 364 + 105 + HeadingTapeCorrection };
				std::ostringstream s558(headingmodifier6);
				s558 << headingmodifier6;
				pFont->DrawTextA(NULL, s558.str().c_str(), -1, &g_DeltasymbolN2Position4, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
			}

			if (Close3 >= -75 && Close3 <= 75)
			{
				//5
				RECT g_DeltasymbolNPosition5 = { 0, 0, 16 + 1350 + Close3*3.0, 334 + 105 + HeadingTapeCorrection };
				pFont->DrawText(NULL, L"|", -1, &g_DeltasymbolNPosition5, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

				if (headingmodifier7 >= 360) headingmodifier7 -= 360;
				else if (headingmodifier7 < 0) headingmodifier7 += 360;

				RECT g_DeltasymbolN2Position6 = { 0, 0, 16 + 1350 + Close3*3.0, 364 + 105 + HeadingTapeCorrection };
				std::ostringstream s559(headingmodifier7);
				s559 << headingmodifier7;
				pFont->DrawTextA(NULL, s559.str().c_str(), -1, &g_DeltasymbolN2Position6, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
			}
		}

		//LJQC: FPM display====================================================================================================


		RECT g_FPMPosition = { 0, 0, 16 + 1350 + Beta * displayC, 764 + b * displayC + displayY };
		pFont->DrawText(NULL, L"O", -1, &g_FPMPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
		RECT g_FPM2Position = { 0, 0, 16 + 1333.5 + Beta * displayC, 760 + b * displayC + displayY };
		pFont->DrawText(NULL, L"-", -1, &g_FPM2Position, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
		RECT g_FPM3Position = { 0, 0, 16 + 1365 + Beta * displayC, 760 + b * displayC + displayY };
		pFont->DrawText(NULL, L"-", -1, &g_FPM3Position, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		//LJQC: AOA Bracket display===============================================================================================

		double alphaa = (b - 8.1)*20.0;

		if (quaternionz == TRUE)
		{
			DrawLine((1310 + Beta * displayC) / 2.0, (720 + b * displayC + alphaa) / 2.0 + displayY / 2.0, (1310 + Beta * displayC) / 2.0, (800 + b * displayC + alphaa) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
			DrawLine((1310 + Beta * displayC) / 2.0, (760 + b * displayC + alphaa) / 2.0 + displayY / 2.0, (1330 + Beta * displayC) / 2.0, (760 + b * displayC + alphaa) / 2.0 + displayY / 2.0, 132, 251, 169, 255);

			DrawLine((1310 + Beta * displayC) / 2.0, (720 + b * displayC + alphaa) / 2.0 + displayY / 2.0, (1330 + Beta * displayC) / 2.0, (720 + b * displayC + alphaa) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
			DrawLine((1310 + Beta * displayC) / 2.0, (800 + b * displayC + alphaa) / 2.0 + displayY / 2.0, (1330 + Beta * displayC) / 2.0, (800 + b * displayC + alphaa) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
		}

		num7 = (quaternionw * F16::radiansToDegrees) / 9.0; // = (Bank angle / 9.0)

		//LJQC: Pitch ladder horizon line =====================================================================================
		pitchangle = atan(num8) * 180.0 / M_PI;
		DrawLine(8 + (1350 + Beta * displayC + 30.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 30.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 400.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 400.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
		DrawLine(8 + (1350 + Beta * displayC - 30.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 30.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 400.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 400.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);


		if (ladder == TRUE)
		{
			if (HeadingTapeCorrection == 0)
			{

			//LJQC: Pitch ladder 10 =====================================================================================
			double pitchangle10 = pitchangle - 10.0;
			DrawLine(8 + (1350 + Beta * displayC + 100.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle10 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 100.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle10 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle10 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle10 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
			DrawLine(8 + (1350 + Beta * displayC - 100.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle10 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 100.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle10 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle10 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle10 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);

			DrawLine(8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle10 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle10 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle10 + 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle10 + 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
			DrawLine(8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle10 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle10 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle10 + 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle10 + 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);

			RECT ladder10R = { 0, 0, 16 + (1350 + Beta * displayC - 169.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle10 + 0.7 * 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 1.0, (764 + b * displayC + 169.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle10 + 0.7 * 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 1.0 + displayY / 1.0 };
			pFont->DrawText(NULL, L"10", -1, &ladder10R, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));


			//LJQC: Pitch ladder 20 =====================================================================================
			pitchangle20 = pitchangle - 20.0;
			DrawLine(8 + (1350 + Beta * displayC + 100.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle20 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 100.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle20 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle20 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle20 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
			DrawLine(8 + (1350 + Beta * displayC - 100.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle20 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 100.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle20 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle20 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle20 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);

			DrawLine(8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle20 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle20 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle20 + 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle20 + 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
			DrawLine(8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle20 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle20 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle20 + 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle20 + 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);

			RECT ladder20R = { 0, 0, 16 + (1350 + Beta * displayC - 169.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle20 + 0.7 * 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 1.0, (764 + b * displayC + 169.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle20 + 0.7 * 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 1.0 + displayY / 1.0 };
			pFont->DrawText(NULL, L"20", -1, &ladder20R, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

			//LJQC: Pitch ladder 30 =====================================================================================
			double pitchangle30 = pitchangle - 30.0;
			DrawLine(8 + (1350 + Beta * displayC + 100.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle30 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 100.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle30 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle30 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle30 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
			DrawLine(8 + (1350 + Beta * displayC - 100.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle30 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 100.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle30 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle30 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle30 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);

			DrawLine(8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle30 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle30 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle30 + 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle30 + 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
			DrawLine(8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle30 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle30 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle30 + 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle30 + 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);

			RECT ladder30R = { 0, 0, 16 + (1350 + Beta * displayC - 169.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle30 + 0.7 * 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 1.0, (764 + b * displayC + 169.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle30 + 0.7 * 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 1.0 + displayY / 1.0 };
			pFont->DrawText(NULL, L"30", -1, &ladder30R, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

			//LJQC: Pitch ladder 40 =====================================================================================
			pitchangle40 = pitchangle - 40.0;
			DrawLine(8 + (1350 + Beta * displayC + 100.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle40 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 100.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle40 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle40 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle40 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
			DrawLine(8 + (1350 + Beta * displayC - 100.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle40 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 100.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle40 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle40 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle40 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);

			DrawLine(8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle40 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle40 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle40 + 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle40 + 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
			DrawLine(8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle40 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle40 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle40 + 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle40 + 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);


			RECT ladder40R = { 0, 0, 16 + (1350 + Beta * displayC - 169.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle40 + 0.7 * 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 1.0, (764 + b * displayC + 169.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle40 + 0.7 * 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 1.0 + displayY / 1.0 };
			pFont->DrawText(NULL, L"40", -1, &ladder40R, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));


			//LJQC: Pitch ladder 60 =====================================================================================
			pitchangle602 = pitchangle - 60.0;
			DrawLine(8 + (1350 + Beta * displayC + 100.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle602 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 100.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle602 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle602 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle602 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
			DrawLine(8 + (1350 + Beta * displayC - 100.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle602 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 100.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle602 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle602 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle602 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);

			DrawLine(8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle602 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle602 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle602 + 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle602 + 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
			DrawLine(8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle602 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle602 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle602 + 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle602 + 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);

			RECT ladder602R = { 0, 0, 16 + (1350 + Beta * displayC - 169.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle602 + 0.7 * 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 1.0, (764 + b * displayC + 169.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle602 + 0.7 * 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 1.0 + displayY / 1.0 };
			pFont->DrawText(NULL, L"60", -1, &ladder602R, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));


			//LJQC: Pitch ladder 80 =====================================================================================
			pitchangle802 = pitchangle - 80.0;
			DrawLine(8 + (1350 + Beta * displayC + 100.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle802 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 100.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle802 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle802 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle802 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
			DrawLine(8 + (1350 + Beta * displayC - 100.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle802 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 100.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle802 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle802 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle802 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);

			DrawLine(8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle802 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle802 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle802 + 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle802 + 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
			DrawLine(8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle802 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle802 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle802 + 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle802 + 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);

			RECT ladder802R = { 0, 0, 16 + (1350 + Beta * displayC - 169.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle802 + 0.7 * 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 1.0, (764 + b * displayC + 169.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle802 + 0.7 * 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 1.0 + displayY / 1.0 };
			pFont->DrawText(NULL, L"80", -1, &ladder802R, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

			//LJQC: Pitch ladder -3 when Landing Gear Down =====================================================================================
			if (quaternionz == TRUE)
			{
				double pitchanglem3 = pitchangle + 3.5;
				DashedLine(8 + (1350 + Beta * displayC + 35.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchanglem3 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 35.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchanglem3 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 100.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchanglem3 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 100.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchanglem3 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
				DashedLine(8 + (1350 + Beta * displayC - 35.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchanglem3 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 35.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchanglem3 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 100.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchanglem3 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 100.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchanglem3 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
			}

			//LJQC: Pitch ladder -10 =====================================================================================
			double pitchanglem10 = pitchangle + 10.0;
			DashedLine(8 + (1350 + Beta * displayC + 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchanglem10 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchanglem10 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchanglem10 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchanglem10 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
			DashedLine(8 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchanglem10 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchanglem10 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchanglem10 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchanglem10 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);

			DrawLine(8 + (1350 + Beta * displayC + 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchanglem10 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchanglem10 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchanglem10 - 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchanglem10 - 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
			DrawLine(8 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchanglem10 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchanglem10 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchanglem10 - 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchanglem10 - 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);

			RECT ladderm10R = { 0, 0, 16 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchanglem10 - 1.3 * 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 1.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchanglem10 - 1.3 * 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 1.0 + displayY / 1.0 };
			pFont->DrawText(NULL, L"-10", -1, &ladderm10R, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));


			//LJQC: Pitch ladder -20 =====================================================================================
			pitchangle60 = pitchangle + 20.0;
			DashedLine(8 + (1350 + Beta * displayC + 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle60 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle60 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle60 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle60 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
			DashedLine(8 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle60 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle60 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle60 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle60 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);

			DrawLine(8 + (1350 + Beta * displayC + 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle60 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle60 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle60 - 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle60 - 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
			DrawLine(8 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle60 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle60 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle60 - 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle60 - 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);



			RECT ladder60R = { 0, 0, 16 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle60 - 1.3 * 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 1.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle60 - 1.3 * 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 1.0 + displayY / 1.0 };
			pFont->DrawText(NULL, L"-20", -1, &ladder60R, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));


			//LJQC: Pitch ladder -30 =====================================================================================
			double  pitchanglem30 = pitchangle + 30.0;
			DashedLine(8 + (1350 + Beta * displayC + 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchanglem30 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchanglem30 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchanglem30 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchanglem30 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
			DashedLine(8 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchanglem30 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchanglem30 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchanglem30 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchanglem30 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);

			DrawLine(8 + (1350 + Beta * displayC + 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchanglem30 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchanglem30 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchanglem30 - 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchanglem30 - 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
			DrawLine(8 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchanglem30 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchanglem30 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchanglem30 - 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchanglem30 - 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);



			RECT ladderm30R = { 0, 0, 16 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchanglem30 - 1.3 * 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 1.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchanglem30 - 1.3 * 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 1.0 + displayY / 1.0 };
			pFont->DrawText(NULL, L"-30", -1, &ladderm30R, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

			//LJQC: Pitch ladder -40 =====================================================================================
			pitchangle80 = pitchangle + 40.0;
			DashedLine(8 + (1350 + Beta * displayC + 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle80 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle80 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle80 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle80 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
			DashedLine(8 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle80 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle80 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle80 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle80 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);

			DrawLine(8 + (1350 + Beta * displayC + 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle80 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle80 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle80 - 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle80 - 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
			DrawLine(8 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle80 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle80 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle80 - 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle80 - 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);

			RECT ladderminus40number = { 0, 0, 16 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle80 - 1.3 * 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 1.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle80 - 1.3 * 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 1.0 + displayY / 1.0 };
			pFont->DrawText(NULL, L"-40", -1, &ladderminus40number, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));


			//LJQC: Pitch ladder -60 =====================================================================================
			pitchangleminus60 = pitchangle + 60.0;
			DashedLine(8 + (1350 + Beta * displayC + 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangleminus60 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangleminus60 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangleminus60 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangleminus60 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
			DashedLine(8 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangleminus60 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangleminus60 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangleminus60 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangleminus60 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);

			DrawLine(8 + (1350 + Beta * displayC + 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangleminus60 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangleminus60 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangleminus60 - 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangleminus60 - 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
			DrawLine(8 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangleminus60 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangleminus60 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangleminus60 - 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangleminus60 - 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);


			RECT ladderminus60number = { 0, 0, 16 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangleminus60 - 1.3 * 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 1.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangleminus60 - 1.3 * 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 1.0 + displayY / 1.0 };
			pFont->DrawText(NULL, L"-60", -1, &ladderminus60number, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));


			//LJQC: Pitch ladder -80 =====================================================================================
			pitchangleminus80 = pitchangle + 80.0;
			DashedLine(8 + (1350 + Beta * displayC + 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangleminus80 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangleminus80 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangleminus80 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangleminus80 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
			DashedLine(8 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangleminus80 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangleminus80 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangleminus80 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangleminus80 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);

			DrawLine(8 + (1350 + Beta * displayC + 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangleminus80 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangleminus80 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangleminus80 - 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangleminus80 - 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
			DrawLine(8 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangleminus80 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangleminus80 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangleminus80 - 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangleminus80 - 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);


			RECT ladderminus80number = { 0, 0, 16 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangleminus80 - 1.3 * 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 1.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangleminus80 - 1.3 * 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 1.0 + displayY / 1.0 };
			pFont->DrawText(NULL, L"-80", -1, &ladderminus80number, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
			}

			else
			{
				//LJQC: Pitch ladder 5 =====================================================================================
				double pitchangle10 = pitchangle - 5.0;
				DrawLine(8 + (1350 + Beta * displayC + 100.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle10 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 100.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle10 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle10 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle10 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
				DrawLine(8 + (1350 + Beta * displayC - 100.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle10 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 100.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle10 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle10 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle10 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);

				DrawLine(8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle10 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle10 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle10 + 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle10 + 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
				DrawLine(8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle10 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle10 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle10 + 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle10 + 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);

				RECT ladder10R = { 0, 0, 16 + (1350 + Beta * displayC - 169.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle10 + 0.7 * 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 1.0, (764 + b * displayC + 169.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle10 + 0.7 * 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 1.0 + displayY / 1.0 };
				pFont->DrawText(NULL, L"5", -1, &ladder10R, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));


				//LJQC: Pitch ladder 10 =====================================================================================
				pitchangle20 = pitchangle - 10.0;
				DrawLine(8 + (1350 + Beta * displayC + 100.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle20 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 100.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle20 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle20 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle20 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
				DrawLine(8 + (1350 + Beta * displayC - 100.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle20 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 100.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle20 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle20 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle20 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);

				DrawLine(8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle20 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle20 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle20 + 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle20 + 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
				DrawLine(8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle20 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle20 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle20 + 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle20 + 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);

				RECT ladder20R = { 0, 0, 16 + (1350 + Beta * displayC - 169.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle20 + 0.7 * 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 1.0, (764 + b * displayC + 169.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle20 + 0.7 * 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 1.0 + displayY / 1.0 };
				pFont->DrawText(NULL, L"10", -1, &ladder20R, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

				//LJQC: Pitch ladder 15 =====================================================================================
				double pitchangle30 = pitchangle - 15.0;
				DrawLine(8 + (1350 + Beta * displayC + 100.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle30 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 100.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle30 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle30 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle30 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
				DrawLine(8 + (1350 + Beta * displayC - 100.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle30 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 100.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle30 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle30 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle30 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);

				DrawLine(8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle30 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle30 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle30 + 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle30 + 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
				DrawLine(8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle30 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle30 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle30 + 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle30 + 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);

				RECT ladder30R = { 0, 0, 16 + (1350 + Beta * displayC - 169.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle30 + 0.7 * 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 1.0, (764 + b * displayC + 169.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle30 + 0.7 * 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 1.0 + displayY / 1.0 };
				pFont->DrawText(NULL, L"15", -1, &ladder30R, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

				//LJQC: Pitch ladder 20 =====================================================================================
				pitchangle40 = pitchangle - 20.0;
				DrawLine(8 + (1350 + Beta * displayC + 100.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle40 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 100.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle40 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle40 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle40 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
				DrawLine(8 + (1350 + Beta * displayC - 100.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle40 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 100.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle40 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle40 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle40 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);

				DrawLine(8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle40 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle40 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle40 + 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle40 + 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
				DrawLine(8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle40 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle40 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle40 + 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle40 + 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);


				RECT ladder40R = { 0, 0, 16 + (1350 + Beta * displayC - 169.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle40 + 0.7 * 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 1.0, (764 + b * displayC + 169.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle40 + 0.7 * 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 1.0 + displayY / 1.0 };
				pFont->DrawText(NULL, L"20", -1, &ladder40R, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));


				//LJQC: Pitch ladder 25 =====================================================================================
				pitchangle602 = pitchangle - 25.0;
				DrawLine(8 + (1350 + Beta * displayC + 100.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle602 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 100.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle602 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle602 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle602 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
				DrawLine(8 + (1350 + Beta * displayC - 100.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle602 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 100.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle602 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle602 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle602 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);

				DrawLine(8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle602 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle602 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle602 + 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle602 + 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
				DrawLine(8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle602 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle602 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle602 + 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle602 + 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);

				RECT ladder602R = { 0, 0, 16 + (1350 + Beta * displayC - 169.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle602 + 0.7 * 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 1.0, (764 + b * displayC + 169.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle602 + 0.7 * 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 1.0 + displayY / 1.0 };
				pFont->DrawText(NULL, L"25", -1, &ladder602R, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));


				//LJQC: Pitch ladder 30 =====================================================================================
				pitchangle802 = pitchangle - 30.0;
				DrawLine(8 + (1350 + Beta * displayC + 100.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle802 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 100.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle802 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle802 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle802 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
				DrawLine(8 + (1350 + Beta * displayC - 100.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle802 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 100.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle802 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle802 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle802 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);

				DrawLine(8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle802 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle802 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle802 + 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle802 + 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
				DrawLine(8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle802 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle802 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle802 + 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle802 + 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);

				RECT ladder802R = { 0, 0, 16 + (1350 + Beta * displayC - 169.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle802 + 0.7 * 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 1.0, (764 + b * displayC + 169.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle802 + 0.7 * 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 1.0 + displayY / 1.0 };
				pFont->DrawText(NULL, L"30", -1, &ladder802R, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

				//LJQC: Pitch ladder -3 when Landing Gear Down =====================================================================================
				if (quaternionz == TRUE)
				{
					double pitchanglem3 = pitchangle + 3.5;
					DashedLine(8 + (1350 + Beta * displayC + 35.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchanglem3 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 35.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchanglem3 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 100.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchanglem3 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 100.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchanglem3 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
					DashedLine(8 + (1350 + Beta * displayC - 35.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchanglem3 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 35.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchanglem3 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 100.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchanglem3 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 100.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchanglem3 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
				}

				//LJQC: Pitch ladder -5 =====================================================================================
				double pitchanglem10 = pitchangle + 5.0;
				DashedLine(8 + (1350 + Beta * displayC + 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchanglem10 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchanglem10 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchanglem10 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchanglem10 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
				DashedLine(8 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchanglem10 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchanglem10 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchanglem10 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchanglem10 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);

				DrawLine(8 + (1350 + Beta * displayC + 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchanglem10 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchanglem10 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchanglem10 - 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchanglem10 - 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
				DrawLine(8 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchanglem10 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchanglem10 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchanglem10 - 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchanglem10 - 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);

				RECT ladderm10R = { 0, 0, 16 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchanglem10 - 1.3 * 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 1.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchanglem10 - 1.3 * 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 1.0 + displayY / 1.0 };
				pFont->DrawText(NULL, L"-5", -1, &ladderm10R, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));


				//LJQC: Pitch ladder -10 =====================================================================================
				pitchangle60 = pitchangle + 10.0;
				DashedLine(8 + (1350 + Beta * displayC + 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle60 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle60 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle60 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle60 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
				DashedLine(8 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle60 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle60 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle60 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle60 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);

				DrawLine(8 + (1350 + Beta * displayC + 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle60 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle60 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle60 - 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle60 - 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
				DrawLine(8 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle60 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle60 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle60 - 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle60 - 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);



				RECT ladder60R = { 0, 0, 16 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle60 - 1.3 * 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 1.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle60 - 1.3 * 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 1.0 + displayY / 1.0 };
				pFont->DrawText(NULL, L"-10", -1, &ladder60R, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));


				//LJQC: Pitch ladder -15 =====================================================================================
				double  pitchanglem30 = pitchangle + 15.0;
				DashedLine(8 + (1350 + Beta * displayC + 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchanglem30 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchanglem30 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchanglem30 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchanglem30 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
				DashedLine(8 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchanglem30 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchanglem30 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchanglem30 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchanglem30 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);

				DrawLine(8 + (1350 + Beta * displayC + 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchanglem30 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchanglem30 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchanglem30 - 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchanglem30 - 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
				DrawLine(8 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchanglem30 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchanglem30 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchanglem30 - 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchanglem30 - 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);



				RECT ladderm30R = { 0, 0, 16 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchanglem30 - 1.3 * 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 1.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchanglem30 - 1.3 * 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 1.0 + displayY / 1.0 };
				pFont->DrawText(NULL, L"-15", -1, &ladderm30R, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

				//LJQC: Pitch ladder -20 =====================================================================================
				pitchangle80 = pitchangle + 20.0;
				DashedLine(8 + (1350 + Beta * displayC + 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle80 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle80 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle80 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle80 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
				DashedLine(8 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle80 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle80 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle80 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle80 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);

				DrawLine(8 + (1350 + Beta * displayC + 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle80 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle80 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle80 - 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle80 - 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
				DrawLine(8 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangle80 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangle80 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle80 - 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle80 - 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);

				RECT ladderminus40number = { 0, 0, 16 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangle80 - 1.3 * 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 1.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangle80 - 1.3 * 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 1.0 + displayY / 1.0 };
				pFont->DrawText(NULL, L"-20", -1, &ladderminus40number, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));


				//LJQC: Pitch ladder -25 =====================================================================================
				pitchangleminus60 = pitchangle + 25.0;
				DashedLine(8 + (1350 + Beta * displayC + 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangleminus60 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangleminus60 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangleminus60 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangleminus60 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
				DashedLine(8 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangleminus60 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangleminus60 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangleminus60 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangleminus60 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);

				DrawLine(8 + (1350 + Beta * displayC + 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangleminus60 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangleminus60 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangleminus60 - 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangleminus60 - 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
				DrawLine(8 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangleminus60 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangleminus60 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangleminus60 - 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangleminus60 - 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);


				RECT ladderminus60number = { 0, 0, 16 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangleminus60 - 1.3 * 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 1.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangleminus60 - 1.3 * 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 1.0 + displayY / 1.0 };
				pFont->DrawText(NULL, L"-25", -1, &ladderminus60number, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));


				//LJQC: Pitch ladder -30 =====================================================================================
				pitchangleminus80 = pitchangle + 30.0;
				DashedLine(8 + (1350 + Beta * displayC + 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangleminus80 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangleminus80 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangleminus80 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangleminus80 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
				DashedLine(8 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangleminus80 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangleminus80 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 200.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangleminus80 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 200.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangleminus80 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);

				DrawLine(8 + (1350 + Beta * displayC + 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangleminus80 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangleminus80 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC + 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangleminus80 - 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC - 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangleminus80 - 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);
				DrawLine(8 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + pitchangleminus80 * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + pitchangleminus80 * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 8 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangleminus80 - 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 2.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangleminus80 - 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 2.0 + displayY / 2.0, 132, 251, 169, 255);


				RECT ladderminus80number = { 0, 0, 16 + (1350 + Beta * displayC - 85.0 * cos(num7 * 9.0 * M_PI / 180.0) + (pitchangleminus80 - 1.3 * 20.4 / displayC) * displayC * sin(num7 * 9.0 * M_PI / 180.0)) / 1.0, (764 + b * displayC + 85.0 * sin(num7 * 9.0 * M_PI / 180.0) + (pitchangleminus80 - 1.3 * 20.4 / displayC) * displayC * cos(num7 * 9.0 * M_PI / 180.0) - 4) / 1.0 + displayY / 1.0 };
				pFont->DrawText(NULL, L"-30", -1, &ladderminus80number, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
			}
		}

	}

			if (HMCS == 2)
			{
				time_t t = time(0);   // get time now
				struct tm * now = localtime(&t);

				//Carrier symbol
				DrawLine((7.16 * 1366.0 / 48.2) / 1.0, (4.18* 768.0 / 27.1) / 1.0, (8.09 * 1366.0 / 48.2) / 1.0, (4.18* 768.0 / 27.1) / 1.0, 3, 144, 52, 255);
				DrawLine((7.16 * 1366.0 / 48.2) / 1.0, (4.18* 768.0 / 27.1) / 1.0, (7.16 * 1366.0 / 48.2) / 1.0, (5.85* 768.0 / 27.1) / 1.0, 3, 144, 52, 255);
				DrawLine((7.16 * 1366.0 / 48.2) / 1.0, (5.85* 768.0 / 27.1) / 1.0, (6.74 * 1366.0 / 48.2) / 1.0, (6.34* 768.0 / 27.1) / 1.0, 3, 144, 52, 255);
				DrawLine((6.74 * 1366.0 / 48.2) / 1.0, (6.34* 768.0 / 27.1) / 1.0, (7.49 * 1366.0 / 48.2) / 1.0, (7.97* 768.0 / 27.1) / 1.0, 3, 144, 52, 255);
				DrawLine((7.49 * 1366.0 / 48.2) / 1.0, (7.97* 768.0 / 27.1) / 1.0, (8.09 * 1366.0 / 48.2) / 1.0, (7.97* 768.0 / 27.1) / 1.0, 3, 144, 52, 255);
				DrawLine((8.09 * 1366.0 / 48.2) / 1.0, (7.97* 768.0 / 27.1) / 1.0, (8.09 * 1366.0 / 48.2) / 1.0, (4.18* 768.0 / 27.1) / 1.0, 3, 144, 52, 255);

				int numberincarrier = 7;

				RECT g_SpeedvaluePosition22 = { 0, 0, 2.0 * 7.53 * 1366.0 / 48.2, 2.0 * 6.60* 768.0 / 27.1 };//Number in the carrier symbol
				std::ostringstream s122(numberincarrier);
				s122 << numberincarrier;
				pFont->DrawTextA(NULL, s122.str().c_str(), -1, &g_SpeedvaluePosition22, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				//=====================================================

				RECT g_AsterSpeedPosition22 = { 0, 0, 2.0 * 7.58 * 1366.0 / 48.2, 2.0 *  9.12* 768.0 / 27.1 };//KTS
				pFont->DrawText(NULL, L"KTS", -1, &g_AsterSpeedPosition22, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g_AsterSpeed2Position22 = { 0, 0, 2.0 * 7.58 * 1366.0 / 48.2, 2.0 *  9.94* 768.0 / 27.1 };//NM
				pFont->DrawText(NULL, L"NM", -1, &g_AsterSpeed2Position22, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g_AsterSpeed3Position22 = { 0, 0, 2.0 *  9.92 * 1366.0 / 48.2, 2.0 *  9.12* 768.0 / 27.1 };//CLSG
				pFont->DrawText(NULL, L"CLSG", -1, &g_AsterSpeed3Position22, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));



				RECT g_AOAPosition = { 0, 0, 2.0 * 7.76 * 1366.0 / 48.2, 2.0 * 13.34* 768.0 / 27.1 };//LIST (DEG)
				pFont->DrawText(NULL, L"LIST (DEG)", -1, &g_AOAPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g_AOAsymPosition = { 0, 0, 2.0 * 9.14 * 1366.0 / 48.2, 2.0 * 14.47* 768.0 / 27.1 };//PORT DOWN
				pFont->DrawText(NULL, L"PORT DOWN", -1, &g_AOAsymPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				displayZ2 = floor((displayZ/100.0) * 100.0f + 0.5) / 100.0f;

				RECT g_AOAvaluePosition = { 0, 0, 2.0 * 6.91 * 1366.0 / 48.2 - 30, 2.0 *  14.47* 768.0 / 27.1 };//Numer PORT DOWN
				std::ostringstream s2(displayZ2);
				s2 << displayZ2;
				pFont->DrawTextA(NULL, s2.str().c_str(), -1, &g_AOAvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));



				RECT g_MACHPosition = { 0, 0, 2.0 * 7.76 * 1366.0 / 48.2, 2.0 * 15.87* 768.0 / 27.1 };//TRIM (DEG)
				pFont->DrawText(NULL, L"TRIM (DEG)", -1, &g_MACHPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g_MACH22Position = { 0, 0, 2.0 *  8.73 * 1366.0 / 48.2, 2.0 * 16.69* 768.0 / 27.1 };//BOW UP
				pFont->DrawText(NULL, L"BOW UP", -1, &g_MACH22Position, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				displayW2 = floor((displayW/100.0) * 100.0f + 0.5) / 100.0f;

				RECT g_MACHvaluePosition = { 0, 0, 2.0 *  6.91 * 1366.0 / 48.2 - 30, 2.0 * 16.69* 768.0 / 27.1 };//number BOW UP
				std::ostringstream s6(displayW2);
				s6 << displayW2;
				pFont->DrawTextA(NULL, s6.str().c_str(), -1, &g_MACHvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));






				RECT g_GPosition = { 0, 0, 2.0 *  7.95 * 1366.0 / 48.2, 2.0 * 20.13* 768.0 / 27.1 };//Aircraft ID
				pFont->DrawText(NULL, L"F/A-18C (Hornet)", -1, &g_GPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g_G2Position = { 0, 0, 2.0 *  7.95 * 1366.0 / 48.2, 2.0 * 20.97 * 768.0 / 27.1 };//H/E = 16.35 ft
				pFont->DrawText(NULL, L"H/E = 16.35 ft", -1, &g_G2Position, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g_G3Position = { 0, 0, 2.0 *  7.95 * 1366.0 / 48.2, 2.0 * 21.82 * 768.0 / 27.1 };//B/A = 3.50 deg
				pFont->DrawText(NULL, L"B/A = 3.50 deg", -1, &g_G3Position, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g_GvaluePosition = { 0, 0, 2.0 *  16.99 * 1366.0 / 48.2, 2.0 * 22.45 * 768.0 / 27.1 };//012 number at left-down corner
				std::ostringstream s3(Gs * 10);
				s3 << Gs * 10;
				pFont2->DrawTextA(NULL, s3.str().c_str(), -1, &g_GvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(240, 238, 238));






				RECT g_TVCPosition = { 0, 0, 2.0 *  27.11 * 1366.0 / 48.2, 2.0 * 22.45 * 768.0 / 27.1 };//LJQC: TVC睫瘍
				pFont2->DrawText(NULL, L"24700", -1, &g_TVCPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(240, 238, 238));

				RECT g_SPosition = { 0, 0, 2.0 *  32.27 * 1366.0 / 48.2, 2.0 * 22.45 * 768.0 / 27.1 };
				pFont2->DrawText(NULL, L"01", -1, &g_SPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(240, 238, 238));

				RECT g_GLIMPosition = { 0, 0, 2.0 *  29.79 * 1366.0 / 48.2, 2.0 * 7.21 * 768.0 / 27.1 };
				pFont2->DrawText(NULL, L"27", -1, &g_GLIMPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(240, 238, 238));

				RECT g_GLIM22Position = { 0, 0, 2.0 *  31.25 * 1366.0 / 48.2, 2.0 * 5.54 * 768.0 / 27.1 };
				pFont2->DrawText(NULL, L"77", -1, &g_GLIM22Position, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(240, 238, 238));

				//Date============================================================================================================

				RECT g_pvalue12Position = { 0, 0, 2.0 *  15.55 * 1366.0 / 48.2, 2.0 * 5.54 * 768.0 / 27.1 };//TIME NOW
				std::ostringstream s423(now->tm_mon + 1);
				s423 << now->tm_mon + 1;
				pFont2->DrawTextA(NULL, s423.str().c_str(), -1, &g_pvalue12Position, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(240, 238, 238));


				RECT g_pitch22Position = { 0, 0, 2.0 *  16.73 * 1366.0 / 48.2, 2.0 * 5.54 * 768.0 / 27.1 };
				pFont2->DrawText(NULL, L"-", -1, &g_pitch22Position, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(240, 238, 238));

				RECT g_pvalue1Position = { 0, 0, 2.0 *  17.99 * 1366.0 / 48.2, 2.0 * 5.54 * 768.0 / 27.1 };//TIME NOW
				std::ostringstream s424(now->tm_mday);
				s424 << now->tm_mday;
				pFont2->DrawTextA(NULL, s424.str().c_str(), -1, &g_pvalue1Position, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(240, 238, 238));


				RECT g_pitchPosition = { 0, 0, 2.0 *  19.18 * 1366.0 / 48.2, 2.0 * 5.54 * 768.0 / 27.1 };
				pFont2->DrawText(NULL, L"-", -1, &g_pitchPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(240, 238, 238));

				RECT g_pvaluePosition = { 0, 0, 2.0 *  20.44 * 1366.0 / 48.2, 2.0 * 5.54 * 768.0 / 27.1 };//TIME NOW
				std::ostringstream s425(now->tm_year - 100);
				s425 << now->tm_year - 100;
				pFont2->DrawTextA(NULL, s425.str().c_str(), -1, &g_pvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(240, 238, 238));



				//Time===========================================================================


				RECT g_pvalue2Position24 = { 0, 0, 2.0 *  15.55 * 1366.0 / 48.2, 2.0 * 7.21 * 768.0 / 27.1 };//TIME NOW
				std::ostringstream s426(now->tm_hour);
				s426 << now->tm_hour;
				pFont2->DrawTextA(NULL, s426.str().c_str(), -1, &g_pvalue2Position24, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(240, 238, 238));

				RECT g_pitch22Position23 = { 0, 0, 2.0 *  16.73 * 1366.0 / 48.2, 2.0 * 7.21 * 768.0 / 27.1 };
				pFont2->DrawText(NULL, L":", -1, &g_pitch22Position23, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(240, 238, 238));

				RECT g_pvalue2Position22 = { 0, 0, 2.0 *  17.99 * 1366.0 / 48.2, 2.0 * 7.21 * 768.0 / 27.1 };//TIME NOW
				std::ostringstream s427(now->tm_min);
				s427 << now->tm_min;
				pFont2->DrawTextA(NULL, s427.str().c_str(), -1, &g_pvalue2Position22, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(240, 238, 238));

				RECT g_pitchPosition2 = { 0, 0, 2.0 *  19.18 * 1366.0 / 48.2, 2.0 * 7.21 * 768.0 / 27.1 };
				pFont2->DrawText(NULL, L":", -1, &g_pitchPosition2, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(240, 238, 238));

				RECT g_pvalue2Position2 = { 0, 0, 2.0 *  20.44 * 1366.0 / 48.2, 2.0 * 7.21 * 768.0 / 27.1 };//TIME NOW
				std::ostringstream s428(now->tm_sec);
				s428 << now->tm_sec;
				pFont2->DrawTextA(NULL, s428.str().c_str(), -1, &g_pvalue2Position2, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(240, 238, 238));

				//===============================================================================

				DrawDot(11.14 * 1366.0 / 48.2, 13.53 * 768.0 / 27.1, 22.65 * 1366.0 / 48.2, 13.53 * 768.0 / 27.1, 0, 0, 0, 255);
				DrawDot(1366 - 11.14 * 1366.0 / 48.2, 13.53 * 768.0 / 27.1, 25.91 * 1366.0 / 48.2, 13.53 * 768.0 / 27.1, 0, 0, 0, 255);
				DrawDot(24.2 * 1366.0 / 48.2, 3.4 * 768.0 / 27.1, 24.2 * 1366.0 / 48.2, 12.72 * 768.0 / 27.1, 0, 0, 0, 255);
				DrawDot(24.2 * 1366.0 / 48.2, 768 - 3.4 * 768.0 / 27.1, 24.2 * 1366.0 / 48.2, 768 - 12.72 * 768.0 / 27.1, 0, 0, 0, 255);

				//================================================================================

				RECT g_1 = { 0, 0, 2.0 *  39.01 * 1366.0 / 48.2, 2.0 * 3.62 * 768.0 / 27.1 };
				pFont->DrawText(NULL, L"―", -1, &g_1, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g2 = { 0, 0, 2.0 *  39.01 * 1366.0 / 48.2, 2.0 * 3.62 * 768.0 / 27.1 + 32 * 1};
				pFont->DrawText(NULL, L"―", -1, &g2, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g3 = { 0, 0, 2.0 *  39.01 * 1366.0 / 48.2, 2.0 * 3.62 * 768.0 / 27.1 + 32 * 2};
				pFont->DrawText(NULL, L"―", -1, &g3, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g4 = { 0, 0, 2.0 *  39.01 * 1366.0 / 48.2, 2.0 * 3.62 * 768.0 / 27.1 + 32 * 3};
				pFont->DrawText(NULL, L"―", -1, &g4, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g5 = { 0, 0, 2.0 *  39.01 * 1366.0 / 48.2, 2.0 * 3.62 * 768.0 / 27.1 + 32 * 4};
				pFont->DrawText(NULL, L"―30―", -1, &g5, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g6 = { 0, 0, 2.0 *  39.01 * 1366.0 / 48.2, 2.0 * 3.62 * 768.0 / 27.1 + 32 * 5};
				pFont->DrawText(NULL, L"―", -1, &g6, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g7 = { 0, 0, 2.0 *  39.01 * 1366.0 / 48.2, 2.0 * 3.62 * 768.0 / 27.1 + 32 * 6};
				pFont->DrawText(NULL, L"―", -1, &g7, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g8 = { 0, 0, 2.0 *  39.01 * 1366.0 / 48.2, 2.0 * 3.62 * 768.0 / 27.1 + 32 * 7};
				pFont->DrawText(NULL, L"―", -1, &g8, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g9 = { 0, 0, 2.0 *  39.01 * 1366.0 / 48.2, 2.0 * 3.62 * 768.0 / 27.1 + 32 * 8};
				pFont->DrawText(NULL, L"―", -1, &g9, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g10 = { 0, 0, 2.0 *  39.01 * 1366.0 / 48.2, 2.0 * 3.62 * 768.0 / 27.1 + 32 * 9};
				pFont->DrawText(NULL, L"―", -1, &g10, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g11 = { 0, 0, 2.0 *  39.01 * 1366.0 / 48.2, 2.0 * 3.62 * 768.0 / 27.1 + 32 * 10};
				pFont->DrawText(NULL, L"―", -1, &g11, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g12 = { 0, 0, 2.0 *  39.01 * 1366.0 / 48.2, 2.0 * 3.62 * 768.0 / 27.1 + 32 * 11};
				pFont->DrawText(NULL, L"―", -1, &g12, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g13 = { 0, 0, 2.0 *  39.01 * 1366.0 / 48.2, 2.0 * 3.62 * 768.0 / 27.1 + 32 * 12};
				pFont->DrawText(NULL, L"―", -1, &g13, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g14 = { 0, 0, 2.0 *  39.01 * 1366.0 / 48.2, 2.0 * 3.62 * 768.0 / 27.1 + 32 * 13};
				pFont->DrawText(NULL, L"―", -1, &g14, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g15 = { 0, 0, 2.0 *  39.01 * 1366.0 / 48.2, 2.0 * 3.62 * 768.0 / 27.1 + 32 * 14};
				pFont->DrawText(NULL, L"―20―", -1, &g15, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g16 = { 0, 0, 2.0 *  39.01 * 1366.0 / 48.2, 2.0 * 3.62 * 768.0 / 27.1 + 32 * 15};
				pFont->DrawText(NULL, L"―", -1, &g16, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g17 = { 0, 0, 2.0 *  39.01 * 1366.0 / 48.2, 2.0 * 3.62 * 768.0 / 27.1 + 32 * 16};
				pFont->DrawText(NULL, L"―", -1, &g17, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g18 = { 0, 0, 2.0 *  39.01 * 1366.0 / 48.2, 2.0 * 3.62 * 768.0 / 27.1 + 32 * 17};
				pFont->DrawText(NULL, L"―", -1, &g18, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g19 = { 0, 0, 2.0 *  39.01 * 1366.0 / 48.2, 2.0 * 3.62 * 768.0 / 27.1 + 32 * 18};
				pFont->DrawText(NULL, L"―", -1, &g19, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g20 = { 0, 0, 2.0 *  39.01 * 1366.0 / 48.2, 2.0 * 3.62 * 768.0 / 27.1 + 32 * 19};
				pFont->DrawText(NULL, L"―", -1, &g20, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g21 = { 0, 0, 2.0 *  39.01 * 1366.0 / 48.2, 2.0 * 3.62 * 768.0 / 27.1 + 32 * 20};
				pFont->DrawText(NULL, L"―", -1, &g21, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g22 = { 0, 0, 2.0 *  39.01 * 1366.0 / 48.2, 2.0 * 3.62 * 768.0 / 27.1 + 32 * 21};
				pFont->DrawText(NULL, L"―", -1, &g22, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g23 = { 0, 0, 2.0 *  39.01 * 1366.0 / 48.2, 2.0 * 3.62 * 768.0 / 27.1 + 32 * 22};
				pFont->DrawText(NULL, L"―", -1, &g23, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g24 = { 0, 0, 2.0 *  39.01 * 1366.0 / 48.2, 2.0 * 3.62 * 768.0 / 27.1 + 32 * 23};
				pFont->DrawText(NULL, L"―", -1, &g24, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g25 = { 0, 0, 2.0 *  39.01 * 1366.0 / 48.2, 2.0 * 3.62 * 768.0 / 27.1 + 32 * 24};
				pFont->DrawText(NULL, L"―10―", -1, &g25, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g26 = { 0, 0, 2.0 *  39.01 * 1366.0 / 48.2, 2.0 * 3.62 * 768.0 / 27.1 + 32 * 25};
				pFont->DrawText(NULL, L"―", -1, &g26, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g27 = { 0, 0, 2.0 *  39.01 * 1366.0 / 48.2, 2.0 * 3.62 * 768.0 / 27.1 + 32 * 26};
				pFont->DrawText(NULL, L"―", -1, &g27, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g28 = { 0, 0, 2.0 *  39.01 * 1366.0 / 48.2, 2.0 * 3.62 * 768.0 / 27.1 + 32 * 27};
				pFont->DrawText(NULL, L"―", -1, &g28, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g29 = { 0, 0, 2.0 *  39.01 * 1366.0 / 48.2, 2.0 * 3.62 * 768.0 / 27.1 + 32 * 28};
				pFont->DrawText(NULL, L"―", -1, &g29, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g30 = { 0, 0, 2.0 *  39.01 * 1366.0 / 48.2, 2.0 * 3.62 * 768.0 / 27.1 + 32 * 29};
				pFont->DrawText(NULL, L"―", -1, &g30, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g31 = { 0, 0, 2.0 *  39.01 * 1366.0 / 48.2, 2.0 * 3.62 * 768.0 / 27.1 + 32 * 30};
				pFont->DrawText(NULL, L"―", -1, &g31, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g32 = { 0, 0, 2.0 *  39.01 * 1366.0 / 48.2, 2.0 * 3.62 * 768.0 / 27.1 + 32 * 31};
				pFont->DrawText(NULL, L"―", -1, &g32, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g33 = { 0, 0, 2.0 *  39.01 * 1366.0 / 48.2, 2.0 * 3.62 * 768.0 / 27.1 + 32 * 32};
				pFont->DrawText(NULL, L"―", -1, &g33, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g34 = { 0, 0, 2.0 *  39.01 * 1366.0 / 48.2, 2.0 * 3.62 * 768.0 / 27.1 + 32 * 33};
				pFont->DrawText(NULL, L"―", -1, &g34, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g35 = { 0, 0, 2.0 *  39.01 * 1366.0 / 48.2, 2.0 * 3.62 * 768.0 / 27.1 + 32 * 34};
				pFont->DrawText(NULL, L"―0―", -1, &g35, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g36 = { 0, 0, 2.0 *  37.99 * 1366.0 / 48.2, 2.0 * 3.62 * 768.0 / 27.1 + 32 * 32 - displayW };
				pFont3->DrawText(NULL, L"-", -1, &g36, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g37 = { 0, 0, 2.0 *  40.82 * 1366.0 / 48.2, 2.0 * 3.62 * 768.0 / 27.1 + 32 * 28 - displayZ };
				pFont3->DrawText(NULL, L"<", -1, &g37, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g38 = { 0, 0, 2.0 *  39.01 * 1366.0 / 48.2, 2.0 * 3.62 * 768.0 / 27.1 + 32 * 35 };
				pFont->DrawText(NULL, L"―", -1, &g38, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));

				RECT g39 = { 0, 0, 2.0 *  39.01 * 1366.0 / 48.2, 2.0 * 3.62 * 768.0 / 27.1 + 32 * 36 };
				pFont->DrawText(NULL, L"―", -1, &g39, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(3, 144, 52));
			}
			if (HMCS == 0)
			{
				RECT g1 = { 0, 0, 90, 30 };
				pFontOFF->DrawText(NULL, L"HMCS OFF", -1, &g1, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
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

		TargetWnd = FindWindow(L"DCS", L"DCS");
		if (TargetWnd == NULL) TargetWnd = FindWindow(L"Digital Combat Simulator", L"Digital Combat Simulator");
		//TargetWnd = FindWindow(L"Digital Combat Simulator", L"Digital Combat Simulator");
		hWnd = CreateWindowEx(WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_COMPOSITED | WS_EX_TRANSPARENT, L"A", L"A", WS_EX_TOPMOST | WS_POPUP, 0, 0, 1366*2.0, 768*2.0, NULL, NULL, NULL, inj_hModule);
		SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 0, ULW_COLORKEY);
		SetLayeredWindowAttributes(hWnd, 0, 255, LWA_ALPHA);
		ShowWindow(hWnd, SW_SHOW);
		initD3D(hWnd);

		for (;;)
		{
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

			if (GetAsyncKeyState(0x4D) & 1) HMCS += 1;
			if (HMCS > 2) HMCS = 0;


			if (GetAsyncKeyState(0x43) & 1) CATI = !CATI;

			if (GetAsyncKeyState(0x50) & 1) ladder = !ladder;

			//HMCS position debug:
			//if (GetAsyncKeyState(VK_UP) & 0x8000) displayY += 1;
			//if (GetAsyncKeyState(VK_DOWN) & 0x8000) displayY -= 1;
			//if (GetAsyncKeyState(VK_LEFT) & 0x8000) displayC += 0.05;
			//if (GetAsyncKeyState(VK_RIGHT) & 0x8000) displayC -= 0.05;
			//if (GetAsyncKeyState(0x22) & 1) HeadingTapeCorrection += 1;//Page up & down
			//if (GetAsyncKeyState(0x21) & 1) HeadingTapeCorrection -= 1;
			if (GetAsyncKeyState(0xBD) & 1) //"-"
			{
				HeadingTapeCorrection = 0;
				displayY = -183.0;
				GundisplayY = -158.0;
				displayC = 20.4;
			}
			if (GetAsyncKeyState(0xBB) & 1)//"+"
			{
				HeadingTapeCorrection = 607;
				displayY = -581.0;
				GundisplayY = -496.0;
				displayC = 62.3;
			}
			//if (GetAsyncKeyState(VK_OEM_COMMA) & 1) displayW += 0.1;
			//if (GetAsyncKeyState(VK_OEM_PERIOD) & 1) displayW -= 0.1;
			//if (GetAsyncKeyState(0x76) & 1) displayC += 0.1;
			//if (GetAsyncKeyState(0x74) & 1) displayC -= 0.1;

			if (PeekMessage(&Message, hWnd, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&Message);
				DispatchMessage(&Message);
			}

			TargetWnd = FindWindow(0, L"DCS");
			if (!TargetWnd) TargetWnd = FindWindow(0, L"Digital Combat Simulator");
			//TargetWnd = FindWindow(0, L"Digital Combat Simulator");
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
		double      blank = 0; //LJQC: Force elevator deflect 0deg
		double      overspeed = 10; //LJQC: Force elevator deflect 10deg
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
			//airbrake = 1;
			airbrakeExtended = false;
		}
		void switchAirbrake()
		{
			airbrakeExtended = !airbrakeExtended;
		}

		float getAirbrake()
		{
			if (dele == 1)
			{
				return 1.0;
			}
			else if (dele == 0)
			{
				return 0.0;
			}
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
			yawrate = yaw_rate;
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
			AOA = floor(b * 10.0f + 0.5) / 10.0f;

			double finalRudderCommand = aileronGained + yawRateFilteredWithSideAccel + rudderCommandFilteredWTrim;

			//yawoutput = finalRudderCommand;

			if (Speedlevel != 4) return finalRudderCommand;
			else return blank;

			//TODO: Figure out why there is a ton of flutter at high speed due to these servo dynamics
			//double yawServoCommand = yawServoFilter.Filter(!(simInitialized),dt,finalRudderCommand);
			//return yawServoCommand;
		}

		double fcs_flap_controller(double airspeed_FPS) //LJQC: FLAPS will deploy when ALT Flaps Switch is ON or when Landing Gear is down.=====================================
		{
			airspeed_KTS = 0.5924838012958964 * airspeed_FPS;
			double trailing_edge_flap_deflection = 0.0;
			a = airspeed_KTS;//int for HMCS number display

			if (proc5 < 240.0)
			{
				Speedlevel = 1;
				if (quaternionz == FALSE)
				{
					if (ALTflaps == 1) trailing_edge_flap_deflection = 20.0;
					else trailing_edge_flap_deflection = 0;
				}
				else if (quaternionz == TRUE)
				{
					trailing_edge_flap_deflection = 20.0;
				}
			}
			else if ((proc5 >= 240.0) && (proc5 <= 370.0))
			{
				Speedlevel = 2;

				if (quaternionz == FALSE)
				{
					if (ALTflaps == 1) trailing_edge_flap_deflection = (1.0 - ((proc5 - 240.0) / (370.0 - 240.0))) * 20.0;
					else trailing_edge_flap_deflection = 0;
				}
				else if (quaternionz == TRUE)
				{
					trailing_edge_flap_deflection = 20.0;
				}
			}
			else if ((proc5 > 370.0) && (proc5 <= 600.0))
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



		double getnumber(double mach)
		{
			MACHfull = mach;
			MACH = floor(mach * 100.0f + 0.5) / 100.0f;
			return MACH;
		}

		double getnumber2(double altitude_FT)
		{
			ALT = altitude_FT;
			dALT = altitude_FT; 
			return ALT;
		}

		double getnumber4(double beta_DEG)
		{
			Beta = beta_DEG;
			return Beta;
		}

		double getnumber5(double ax)
		{
			gAccelx = ax;
			return gAccelx;
		}

		double getnumber6(double accel)
		{
			pAccelx = accel;
			return pAccelx;
		}

		//double getnumber7(double numm7)
		//{
			//num7 = numm7;
			//return num7;
		//}

		double getnumber8(double numm8)
		{
			num8 = numm8;
			return num8;
		}

		double getnumber9(double numm9)
		{
			num9 = numm9;
			return num9;
		}

		double getnumber10(double numm10)
		{
			num10 = numm10;
			return num10;
		}

		double getnumber11(double numm11)
		{
			num11 = numm11;
			return num11;
		}

		double getquaternionx(double quaternion_x)
		{
			quaternionx = quaternion_x;
			return quaternionx;
		}

		double getquaterniony(double quaternion_y)
		{
			quaterniony = quaternion_y;
			return quaterniony;
		}

		bool getquaternionz(bool quaternion_z)
		{
			quaternionz = quaternion_z;
			return quaternionz;
		}

		bool getcanopystate(bool cccc)
		{
			canopystate = cccc;
			return canopystate;
		}

		double getquaternionw(double quaternion_w)
		{
			quaternionw = quaternion_w;
			return quaternionw;
		}
		/*
		double getCompressF(double comf) //for debug
		{
			CompressF = comf;
			return CompressF;
		}
		*/
		int getdele(int de)
		{
			dele = de;
			return dele;
		}

		// Stick force schedule for pitch control
		double fcs_pitch_controller_force_command(double longStickInput, double pitchTrim, double dt)
		{
			double longStickInputForce = longStickInput * 180.0;
			stickcommand = longStickInputForce;

			//LJQC: AOA Limiter Fake/Hack when TVC is OFF==============================
			if (TVC == FALSE)
			{
				if (CATI == TRUE) //CAT I Limiter
				{
					if (b >= 18.0 && b < 25.4) longStickInputForce = longStickInputForce + (b * 2.0 - 36.0) * (70.0 / 14.8);
					else if (b >= 25.4 && b < 30.0) longStickInputForce = longStickInputForce + 70.0 + (b * 2.0 - 50.8) * (110.0 / 9.2);
					else if (b >= 30.0) longStickInputForce = longStickInputForce + 180.0 + (b * 2.0 - 60.0) * (180.0 / 20.0);
				}
				else if (CATI == FALSE) //CAT III Limiter
				{
					if (b >= 8.0 && b < 13.4) longStickInputForce = longStickInputForce + (b * 2.0 - 16.0) * (70.0 / 10.8);
					else if (b >= 13.4 && b < 20.0) longStickInputForce = longStickInputForce + 70.0 + (b * 2.0 - 26.8) * (110.0 / 13.2);
					else if (b >= 20.0) longStickInputForce = longStickInputForce + 180.0 + (b * 2.0 - 40.0) * (180.0 / 20.0);
				}
			}

			//LJQC: Auto Trim Hack

			if (TVC == FALSE && proc5 < 260) pitchtrim = 0.068 * proc5 * proc5 - 43.34 * proc5 + 7058;
			else if (TVC == FALSE && proc5 >= 260 && proc5 < 270) pitchtrim = -55.0 * proc5 + 14709;
			else if (TVC == FALSE && proc5 >= 270 && proc5 < 600) pitchtrim = 0.015 * proc5 * proc5 - 14.78 * proc5 + 2550;
			else if (TVC == FALSE && proc5 >= 600) pitchtrim = -1533;
			else pitchtrim = 0;
			longStickInputForce = longStickInputForce + pitchtrim / 50.0;


			longStickInputForce = limit(longStickInputForce, -180.0, 180.0);
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

			if (GetAsyncKeyState(0x52) & 0x8000) longStickCommandWithTrimLimited_G = limit(longStickCommandWithTrim_G, -11.0, 50.0);
			else longStickCommandWithTrimLimited_G = limit(longStickCommandWithTrim_G, -11.0, 11.0);

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
			Gs = floor(gload * 10.0f + 0.5) / 10.0f;
			pitchrate = pitch_rate;
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

			double alphaLimited = limit(angle_of_attack_ind, -179.0, 179.0);

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



			//LJQC: MPO fuctions here:=====================================================================================================
			if (TVC == TRUE)
			{
				if (directmode == 0)
				{

					if (autopilot == 0)
					{

						if (proc5 < 230)
						{
							if (longStickInputForce2 >= -8 && longStickInputForce2 <= 8 && alphaFiltered <= 10 && alphaFiltered > -179)
							{
								return finalPitchCommandTotal;
							}
							else if (longStickInputForce2 < -8 && alphaFiltered <= 10) return finalPitchCommandTotal;
							else return stickCommandPos;
						}
						else if (proc5 >= 230 && proc5 <= 370)
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

		bool getCAT() const
		{
			return CATI;
		}

		// Controller for roll
		double fcs_roll_controller(double latStickInput, double longStickForce, double ay, double roll_rate, double roll_rate_trim, double dynPressure_LBFT2, double dt)
		{
			rollrate = roll_rate;
			Sideforce = ay;
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