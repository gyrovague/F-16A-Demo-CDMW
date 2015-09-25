#ifndef _F16FLIGHTCONTROLS_H_
#define _F16FLIGHTCONTROLS_H_

#include "../stdafx.h"
#include <memory.h>
#include "../UtilityFunctions.h"
#include <Windows.h>
#include <math.h>
#include<iomanip>

//#include "../include/general_filter.h"

#include "DummyFilter.h"

double      dele;//LJQC: Elevator deflection for debug use
bool        HMCS = TRUE;//LJQC: Turn ON/OFF HMCS
bool        CATI = TRUE;//LJQC: CAT I/III Swtich
int         a = 0; //LJQC: display KTAS on HMCS
int         AOA = 0;//LJQC: AOA display on HMCS
double      b = 0.0; //LJQC: AOA used for FPM (Velocity Vector) display
double      Beta;//LJQC: Beta used for FPM (Velocity Vector) display
int         stickcommand = 0;//LJQC: display pitch input
int         rollinput = 0;//LJQC: display roll input
double      gload = 0.0;//LJQC: output load factor
double         Gs = 0.0;
int         Speedlevel; // LJQC: add speedlevel
int         autopilot = 0; // LJQC: a 0 value
int         ALTflaps = 0; // LJQC: ALT Flaps Switch to control the automatic flaps on F-16
int         directmode = 0; //LJQC: Direct control mode just like in Su-27
bool        TVC = FALSE;//LJQC: output TVC on/off on console
double      MACH; //LJQC: Mach Number for HMCS display
int         ALT; //LJQC: Altitude for HMCS display
double      dALT;//Double: Altitude
int         VVI; //LJQC: Vertical Velocity for HMCS display
double      gAccelx; //quaternion_x
double      pAccelx;//ax
double airspeed_KTS;//Double: TAS
int Height;//Height for HMCS display
int Sideforce;//Sideforce for HMCS display


double      num7 = 0.0;//vx in body system
double      num8 = 0.0;//vx in world coordinate system
double      num9 = 0.0;//Double: Vertical Velocity (m/s)
double      num10 = 0.0;//ay in body system
double      num11 = 0.0;//Bank / Height


double         KTASast = 0.0;
double         ALTast = 0.0;

//Trim function:
double         pitchtrim = 0.0;

//HMCS position debug
double         displayX = 0.0;
double         displayY = 0.0;

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

	if (TargetWnd == GetForegroundWindow())

	{
		//Airspeed Display==========================================================================================

		RECT g_SpeedvaluePosition = { 0, 0, 1025, 784 };//LJQC: KTAS 数值
		std::ostringstream s1(a);
		s1 << a;
		pFont->DrawTextA(NULL, s1.str().c_str(), -1, &g_SpeedvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));



		KTASast = airspeed_KTS * 2 / M_PI;

		DrawLine(1025 / 2.0 + 25.0*sin(KTASast) / 2.0, 784 / 2.0 + 25.0*cos(KTASast) / 2.0, 1025 / 2.0 + 70.0*sin(KTASast) / 2.0, 784 / 2.0 + 70.0*cos(KTASast) / 2.0, 132, 251, 169, 255);

		//Dots for KTAS digital clock display
		DrawDot(1025 / 2.0 + 80.0*sin(0) / 2.0, 784 / 2.0 + 80.0*cos(0) / 2.0, 1025 / 2.0 + 88.0*sin(0) / 2.0, 784 / 2.0 + 88.0*cos(0) / 2.0, 132, 251, 169, 255);
		DrawDot(1025 / 2.0 + 80.0*sin(c1) / 2.0, 784 / 2.0 + 80.0*cos(c1) / 2.0, 1025 / 2.0 + 88.0*sin(c1) / 2.0, 784 / 2.0 + 88.0*cos(c1) / 2.0, 132, 251, 169, 255);
		DrawDot(1025 / 2.0 + 80.0*sin(c2) / 2.0, 784 / 2.0 + 80.0*cos(c2) / 2.0, 1025 / 2.0 + 88.0*sin(c2) / 2.0, 784 / 2.0 + 88.0*cos(c2) / 2.0, 132, 251, 169, 255);
		DrawDot(1025 / 2.0 + 80.0*sin(c3) / 2.0, 784 / 2.0 + 80.0*cos(c3) / 2.0, 1025 / 2.0 + 88.0*sin(c3) / 2.0, 784 / 2.0 + 88.0*cos(c3) / 2.0, 132, 251, 169, 255);
		DrawDot(1025 / 2.0 + 80.0*sin(c4) / 2.0, 784 / 2.0 + 80.0*cos(c4) / 2.0, 1025 / 2.0 + 88.0*sin(c4) / 2.0, 784 / 2.0 + 88.0*cos(c4) / 2.0, 132, 251, 169, 255);
		DrawDot(1025 / 2.0 + 80.0*sin(c5) / 2.0, 784 / 2.0 + 80.0*cos(c5) / 2.0, 1025 / 2.0 + 88.0*sin(c5) / 2.0, 784 / 2.0 + 88.0*cos(c5) / 2.0, 132, 251, 169, 255);
		DrawDot(1025 / 2.0 + 80.0*sin(c6) / 2.0, 784 / 2.0 + 80.0*cos(c6) / 2.0, 1025 / 2.0 + 88.0*sin(c6) / 2.0, 784 / 2.0 + 88.0*cos(c6) / 2.0, 132, 251, 169, 255);
		DrawDot(1025 / 2.0 + 80.0*sin(c7) / 2.0, 784 / 2.0 + 80.0*cos(c7) / 2.0, 1025 / 2.0 + 88.0*sin(c7) / 2.0, 784 / 2.0 + 88.0*cos(c7) / 2.0, 132, 251, 169, 255);
		DrawDot(1025 / 2.0 + 80.0*sin(c8) / 2.0, 784 / 2.0 + 80.0*cos(c8) / 2.0, 1025 / 2.0 + 88.0*sin(c8) / 2.0, 784 / 2.0 + 88.0*cos(c8) / 2.0, 132, 251, 169, 255);
		DrawDot(1025 / 2.0 + 80.0*sin(c9) / 2.0, 784 / 2.0 + 80.0*cos(c9) / 2.0, 1025 / 2.0 + 88.0*sin(c9) / 2.0, 784 / 2.0 + 88.0*cos(c9) / 2.0, 132, 251, 169, 255);
		DrawDot(1025 / 2.0 + 80.0*sin(c10) / 2.0, 784 / 2.0 + 80.0*cos(c10) / 2.0, 1025 / 2.0 + 88.0*sin(c10) / 2.0, 784 / 2.0 + 88.0*cos(c10) / 2.0, 132, 251, 169, 255);
		DrawDot(1025 / 2.0 + 80.0*sin(c11) / 2.0, 784 / 2.0 + 80.0*cos(c11) / 2.0, 1025 / 2.0 + 88.0*sin(c11) / 2.0, 784 / 2.0 + 88.0*cos(c11) / 2.0, 132, 251, 169, 255);
		

		//AOA display=====================================================================================================

		RECT g_AOAPosition = { 0, 0, 1056, 504 };
		pFont->DrawText(NULL, L"— α", -1, &g_AOAPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		RECT g_AOAsymPosition = { 0, 0, 1015, 504 - b * 0.56 };
		pFont->DrawText(NULL, L">", -1, &g_AOAsymPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));


		RECT g_AOAvaluePosition = { 0, 0, 969, 504 - b * 0.56 };//LJQC: AOA 数值
		std::ostringstream s2(AOA);
		s2 << AOA;
		pFont->DrawTextA(NULL, s2.str().c_str(), -1, &g_AOAvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		//Mach number display===============================================================================================

		RECT g_MACHPosition = { 0, 0, 990 - 26, 1024 - 7 };//LJQC: Mach
		pFont->DrawText(NULL, L"M", -1, &g_MACHPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		RECT g_MACHvaluePosition = { 0, 0, 1050 - 26, 1024 - 7 };//LJQC: Mach Number
		std::ostringstream s6(MACH);
		s6 << MACH;
		pFont->DrawTextA(NULL, s6.str().c_str(), -1, &g_MACHvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));



		//G-load display ===============================================================================================


		RECT g_GPosition = { 0, 0, 990 -26, 984 -7 };//LJQC: G-load符号
		pFont->DrawText(NULL, L"G", -1, &g_GPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		RECT g_GvaluePosition = { 0, 0, 1050 - 26, 984 - 7 };//LJQC: G-load 数值
		std::ostringstream s3(Gs);
		s3 << Gs;
		pFont->DrawTextA(NULL, s3.str().c_str(), -1, &g_GvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));





		//Additional Indications================================================================================

		if (TVC == TRUE)
		{
			RECT g_TVCPosition = { 0, 0, 1350, 1184 };//LJQC: TVC符号
			pFont->DrawText(NULL, L"TVC ON", -1, &g_TVCPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
		}

		if (TVC == TRUE && directmode == 1)
		{
			RECT g_SPosition = { 0, 0, 1350, 1244 };
			pFont->DrawText(NULL, L"Direct Mode", -1, &g_SPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
		}

		if (TVC == TRUE && GetAsyncKeyState(0x52) & 0x8000)
		{
			RECT g_GLIMPosition = { 0, 0, 1350, 1304 };
			pFont->DrawText(NULL, L"G-LIM OVRD", -1, &g_GLIMPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
		}



		//LJQC: Sideforce Display============================================================================================

		Sideforce = num7 * 20.0;

		RECT g_headingvaluePosition = { 0, 0, 1350 + num7 * 50.0, 304 };
		std::ostringstream s13(Sideforce);
		s13 << Sideforce;
		pFont->DrawTextA(NULL, s13.str().c_str(), -1, &g_headingvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		RECT g_DeltasymbolPosition = { 0, 0, 1350 + num7 * 50.0, 274 };
		pFont->DrawText(NULL, L"Δ", -1, &g_DeltasymbolPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
		
		RECT g_Deltasymbol2Position = { 0, 0, 1350, 274 };
		pFont->DrawText(NULL, L"•", -1, &g_Deltasymbol2Position, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
		


		//LJQC: Input Display =========================================================================================

		RECT g_PITCHsvaluePosition = { 0, 0, 2180, 854 };
		std::ostringstream s14(stickcommand);
		s14 << stickcommand;
		pFont->DrawTextA(NULL, s14.str().c_str(), -1, &g_PITCHsvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		RECT g_ROLLsvaluePosition = { 0, 0, 2360, 1064 };
		std::ostringstream s15(rollinput);
		s15 << rollinput;
		pFont->DrawTextA(NULL, s15.str().c_str(), -1, &g_ROLLsvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));


		RECT g_pitchvPosition = { 0, 0, 2180, 1064};
		pFont->DrawText(NULL, L"+", -1, &g_pitchvPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		RECT g_pitchPosition = { 0, 0, 2180 + rollinput * 2.0, 1064 - stickcommand };
		pFont->DrawText(NULL, L"+", -1, &g_pitchPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
		
		DrawLine2(2030 / 2.0, 884 / 2.0, 2330 / 2.0, 884 / 2.0, 132, 251, 169, 255);
		DrawLine2(2030 / 2.0, 884 / 2.0, 2030 / 2.0, 1244 / 2.0, 132, 251, 169, 255);
		DrawLine2(2330 / 2.0, 1244 / 2.0, 2330 / 2.0, 884 / 2.0, 132, 251, 169, 255);
		DrawLine2(2330 / 2.0, 1244 / 2.0, 2030 / 2.0, 1244 / 2.0, 132, 251, 169, 255);

		//HMCS position for debug only===================================================================================
		/*
		RECT g_PITCHtrimsvaluePosition = { 0, 0, 850, 854 };
		std::ostringstream s19(displayX);
		s19 << displayX;
		pFont->DrawTextA(NULL, s19.str().c_str(), -1, &g_PITCHtrimsvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		RECT g_PITCHoutputsvaluePosition = { 0, 0, 850, 804 };
		std::ostringstream s20(displayY);
		s20 << displayY;
		pFont->DrawTextA(NULL, s20.str().c_str(), -1, &g_PITCHoutputsvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
		*/



		RECT g_CATPosition = { 0, 0, 1640 - 26 + 61, 1024 + 28 -40};//CAT I/III display==============================================================================================
		if (CATI == TRUE) pFont->DrawText(NULL, L"CAT I", -1, &g_CATPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
		else if (CATI == FALSE) pFont->DrawText(NULL, L"CAT III", -1, &g_CATPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
		
		//Altitude display =================================================================================================

		RECT g_ALTvaluePosition = { 0, 0, 1675, 784 };//LJQC: Altitude Number Display
		std::ostringstream s7(ALT);
		s7 << ALT;
		pFont->DrawTextA(NULL, s7.str().c_str(), -1, &g_ALTvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		ALTast = (dALT / 10.0) / M_PI;

		DrawLine(1675 / 2.0 + 25.0*sin(ALTast) / 2.0, 784 / 2.0 + 25.0*cos(ALTast) / 2.0, 1675 / 2.0 + 70.0*sin(ALTast) / 2.0, 784 / 2.0 + 70.0*cos(ALTast) / 2.0, 132, 251, 169, 255);

		//Dots for ALT digital clock display
		DrawDot(1675 / 2.0 + 80.0*sin(0) / 2.0, 784 / 2.0 + 80.0*cos(0) / 2.0, 1675 / 2.0 + 88.0*sin(0) / 2.0, 784 / 2.0 + 88.0*cos(0) / 2.0, 132, 251, 169, 255);
		DrawDot(1675 / 2.0 + 80.0*sin(c1) / 2.0, 784 / 2.0 + 80.0*cos(c1) / 2.0, 1675 / 2.0 + 88.0*sin(c1) / 2.0, 784 / 2.0 + 88.0*cos(c1) / 2.0, 132, 251, 169, 255);
		DrawDot(1675 / 2.0 + 80.0*sin(c2) / 2.0, 784 / 2.0 + 80.0*cos(c2) / 2.0, 1675 / 2.0 + 88.0*sin(c2) / 2.0, 784 / 2.0 + 88.0*cos(c2) / 2.0, 132, 251, 169, 255);
		DrawDot(1675 / 2.0 + 80.0*sin(c3) / 2.0, 784 / 2.0 + 80.0*cos(c3) / 2.0, 1675 / 2.0 + 88.0*sin(c3) / 2.0, 784 / 2.0 + 88.0*cos(c3) / 2.0, 132, 251, 169, 255);
		DrawDot(1675 / 2.0 + 80.0*sin(c4) / 2.0, 784 / 2.0 + 80.0*cos(c4) / 2.0, 1675 / 2.0 + 88.0*sin(c4) / 2.0, 784 / 2.0 + 88.0*cos(c4) / 2.0, 132, 251, 169, 255);
		DrawDot(1675 / 2.0 + 80.0*sin(c5) / 2.0, 784 / 2.0 + 80.0*cos(c5) / 2.0, 1675 / 2.0 + 88.0*sin(c5) / 2.0, 784 / 2.0 + 88.0*cos(c5) / 2.0, 132, 251, 169, 255);
		DrawDot(1675 / 2.0 + 80.0*sin(c6) / 2.0, 784 / 2.0 + 80.0*cos(c6) / 2.0, 1675 / 2.0 + 88.0*sin(c6) / 2.0, 784 / 2.0 + 88.0*cos(c6) / 2.0, 132, 251, 169, 255);
		DrawDot(1675 / 2.0 + 80.0*sin(c7) / 2.0, 784 / 2.0 + 80.0*cos(c7) / 2.0, 1675 / 2.0 + 88.0*sin(c7) / 2.0, 784 / 2.0 + 88.0*cos(c7) / 2.0, 132, 251, 169, 255);
		DrawDot(1675 / 2.0 + 80.0*sin(c8) / 2.0, 784 / 2.0 + 80.0*cos(c8) / 2.0, 1675 / 2.0 + 88.0*sin(c8) / 2.0, 784 / 2.0 + 88.0*cos(c8) / 2.0, 132, 251, 169, 255);
		DrawDot(1675 / 2.0 + 80.0*sin(c9) / 2.0, 784 / 2.0 + 80.0*cos(c9) / 2.0, 1675 / 2.0 + 88.0*sin(c9) / 2.0, 784 / 2.0 + 88.0*cos(c9) / 2.0, 132, 251, 169, 255);
		DrawDot(1675 / 2.0 + 80.0*sin(c10) / 2.0, 784 / 2.0 + 80.0*cos(c10) / 2.0, 1675 / 2.0 + 88.0*sin(c10) / 2.0, 784 / 2.0 + 88.0*cos(c10) / 2.0, 132, 251, 169, 255);
		DrawDot(1675 / 2.0 + 80.0*sin(c11) / 2.0, 784 / 2.0 + 80.0*cos(c11) / 2.0, 1675 / 2.0 + 88.0*sin(c11) / 2.0, 784 / 2.0 + 88.0*cos(c11) / 2.0, 132, 251, 169, 255);
		
		
		//VVI display =======================================================================================================


		VVI = num9 * F16::meterToFoot * 60.0;

		RECT g_VVIPosition = { 0, 0, 1689 -55, 504 }; // VVI symbol position
		pFont->DrawText(NULL, L"VV —", -1, &g_VVIPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		if (VVI > -2000 && VVI < 2000)
		{
			RECT g_VVIsymPosition = { 0, 0, 1746 - 56, 504 - num9 * 10.0 };
			pFont->DrawText(NULL, L"<", -1, &g_VVIsymPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

			RECT g_VVIvaluePosition = { 0, 0, 1808 - 55, 504 - num9 * 10.0 };
			std::ostringstream s11(VVI);
			s11 << VVI;
			pFont->DrawTextA(NULL, s11.str().c_str(), -1, &g_VVIvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
		}
		else if (VVI <= -2000)
		{
			RECT g_VVIsymPosition = { 0, 0, 1746 - 55, 504 - c14 * 10.0 };
			pFont->DrawText(NULL, L"<", -1, &g_VVIsymPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

			RECT g_VVIvaluePosition = { 0, 0, 1808 - 55, 504 - c14 * 10.0 };
			std::ostringstream s11(VVI);
			s11 << VVI;
			pFont->DrawTextA(NULL, s11.str().c_str(), -1, &g_VVIvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
		}
		else if (VVI >= 2000)
		{
			RECT g_VVIsymPosition = { 0, 0, 1746 - 55, 504 - c15 * 10.0 };
			pFont->DrawText(NULL, L"<", -1, &g_VVIsymPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

			RECT g_VVIvaluePosition = { 0, 0, 1808 - 55, 504 - c15 * 10.0 };
			std::ostringstream s11(VVI);
			s11 << VVI;
			pFont->DrawTextA(NULL, s11.str().c_str(), -1, &g_VVIvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
		}




		//Other Displays =================================================================================================

		Height = ALT - num11 * F16::meterToFoot;

		RECT g_HeightvaluePosition = { 0, 0, 1675 - 26 + 61, 1024 + 28 }; //Experiment =================================================
		std::ostringstream s12(Height);
		s12 << Height;
		pFont->DrawTextA(NULL, s12.str().c_str(), -1, &g_HeightvaluePosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		RECT g_BAROPosition = { 0, 0, 1600 - 26 + 61, 1024 + 28 };
		pFont->DrawText(NULL, L"R", -1, &g_BAROPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		
		

		RECT g_CrossPosition = { 0, 0, 1350, 764}; //LJQC: Gun cross display
		pFont->DrawText(NULL, L"+", -1, &g_CrossPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		RECT g_AccelxPosition = { 0, 0, 1365 + num10 * 5, 764 - pAccelx * 25 };
		pFont->DrawText(NULL, L"<", -1, &g_AccelxPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		RECT g_pAccelPosition = { 0, 0, 1335 - num10 * 5, 764 - pAccelx * 25 };
		pFont->DrawText(NULL, L">", -1, &g_pAccelPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));


		RECT g_FPMPosition = { 0, 0, 1350 + Beta * 15.0, 764 + b * 15.0 }; //LJQC: Flight Path Marker display (Velocity Vector)
		pFont->DrawText(NULL, L"O", -1, &g_FPMPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
		RECT g_FPM2Position = { 0, 0, 1333.5 + Beta * 15.0, 760 + b * 15.0 }; //LJQC: Flight Path Marker display (Velocity Vector)
		pFont->DrawText(NULL, L"-", -1, &g_FPM2Position, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
		RECT g_FPM3Position = { 0, 0, 1365 + Beta * 15.0, 760 + b * 15.0 }; //LJQC: Flight Path Marker display (Velocity Vector)
		pFont->DrawText(NULL, L"-", -1, &g_FPM3Position, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
		



		//RECT g_aAccelPosition = { 0, 0, 1350 + gAccelx * 5, 764 };
		//pFont->DrawText(NULL, L"||", -1, &g_aAccelPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

		

		//RECT g_wAccelPosition = { 0, 0, 1350, 764 + num8 * 5 };
		//pFont->DrawText(NULL, L"   -z", -1, &g_wAccelPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
/*
double      gAccelx; //world ax*
double      pAccelx;//ax
double      num7 = 0.0;//world ay*
double      num8 = 0.0;//world az*
double      num9 = 0.0;//vy
double      num10 = 0.0;//ay
double      num11 = 0.0;//az
*/



		//Vertical lines for AOA display BELOW========================================================
		RECT g_LinePositionm1 = { 0, 0, 1025, 584 - 170 };
		pFont->DrawText(NULL, L"|", -1, &g_LinePositionm1, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));


		RECT g_LinePosition0 = { 0, 0, 1025, 614 - 170 };
		pFont->DrawText(NULL, L"|", -1, &g_LinePosition0, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));


		RECT g_LinePosition1 = { 0, 0, 1025, 644 - 170 };
		pFont->DrawText(NULL, L"|", -1, &g_LinePosition1, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));


		RECT g_LinePosition2 = { 0, 0, 1025, 674 - 170 };
		pFont->DrawText(NULL, L"|", -1, &g_LinePosition2, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));


		RECT g_LinePosition3 = { 0, 0, 1025, 704 - 170 };
		pFont->DrawText(NULL, L"|", -1, &g_LinePosition3, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));


		RECT g_LinePosition4 = { 0, 0, 1025, 734 - 170 };
		pFont->DrawText(NULL, L"|", -1, &g_LinePosition4, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));


		RECT g_LinePosition5 = { 0, 0, 1025, 759 - 170 };
		pFont->DrawText(NULL, L"|", -1, &g_LinePosition5, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
		//Vertical lines for AOA display ABOVE========================================================



		//Vertical lines for VVI display BELOW========================================================
		RECT g_LinePosition6 = { 0, 0, 1730 -55, 584 - 170 };
		pFont->DrawText(NULL, L"|", -1, &g_LinePosition6, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));


		RECT g_LinePosition7 = { 0, 0, 1730 - 55, 614 - 170 };
		pFont->DrawText(NULL, L"|", -1, &g_LinePosition7, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));


		RECT g_LinePosition8 = { 0, 0, 1730 - 55, 644 - 170 };
		pFont->DrawText(NULL, L"|", -1, &g_LinePosition8, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));


		RECT g_LinePosition9 = { 0, 0, 1730 - 55, 674 - 170 };
		pFont->DrawText(NULL, L"|", -1, &g_LinePosition9, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));


		RECT g_LinePosition10 = { 0, 0, 1730 - 55, 704 - 170 };
		pFont->DrawText(NULL, L"|", -1, &g_LinePosition10, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));


		RECT g_LinePosition11 = { 0, 0, 1730 - 55, 734 - 170 };
		pFont->DrawText(NULL, L"|", -1, &g_LinePosition11, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));


		RECT g_LinePosition12 = { 0, 0, 1730 - 55, 759 - 170 };
		pFont->DrawText(NULL, L"|", -1, &g_LinePosition12, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
		//Vertical lines for VVI display ABOVE========================================================
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
		if (HMCS == TRUE)
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
		else if (HMCS == FALSE)
		{
			Sleep(1);
			d3ddev->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0);
			d3ddev->Present(NULL, NULL, NULL, NULL);
		}
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
			airspeed_KTS = 0.5924838012958964 * airspeed_FPS;
			double trailing_edge_flap_deflection = 0.0;
			a = airspeed_KTS;//int for HMCS number display

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
			else if ((airspeed_KTS > 370.0) && (airspeed_KTS <= 600.0))
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

		double getnumber7(double numm7)
		{
			num7 = numm7;
			return num7;
		}

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
					else if (b >= 13.4 && b < 16.0) longStickInputForce = longStickInputForce + 70.0 + (b * 2.0 - 26.8) * (110.0 / 5.2);
					else if (b >= 16.0) longStickInputForce = longStickInputForce + 180.0 + (b * 2.0 - 32.0) * (180.0 / 8.0);
				}
			}

			//LJQC: Auto Trim Hack

			if (TVC == FALSE && airspeed_KTS < 260) pitchtrim = 0.068 * airspeed_KTS * airspeed_KTS - 43.34 * airspeed_KTS + 7058;
			else if (TVC == FALSE && airspeed_KTS >= 260 && airspeed_KTS < 270) pitchtrim = -55.0 * airspeed_KTS + 14709;
			else if (TVC == FALSE && airspeed_KTS >= 270 && airspeed_KTS < 600) pitchtrim = 0.015 * airspeed_KTS * airspeed_KTS - 14.78 * airspeed_KTS + 2550;
			else if (TVC == FALSE && airspeed_KTS >= 600) pitchtrim = -1533;
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
			Gs = floor(gload * 1000.0f + 0.5) / 1000.0f;
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

			if (GetAsyncKeyState(0x4D) & 1) HMCS = !HMCS;

			if (GetAsyncKeyState(0x43) & 1) CATI = !CATI;

			//HMCS position debug:
			if (GetAsyncKeyState(VK_UP) & 1) displayY = displayY - 1;
			if (GetAsyncKeyState(VK_DOWN) & 1) displayY = displayY + 1;
			if (GetAsyncKeyState(VK_LEFT) & 1) displayX = displayX - 1;
			if (GetAsyncKeyState(VK_RIGHT) & 1) displayX = displayX + 1;

			dele = finalPitchCommandTotal;


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