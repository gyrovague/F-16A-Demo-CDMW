// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"


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

	D3DXCreateFont(d3ddev, 50, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial", &pFont);

}


int Render()
{
	d3ddev->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0);

	
	d3ddev->BeginScene(); 
	
	if (TargetWnd == GetForegroundWindow())

		{
			RECT g_FontPosition = { 0, 0, 1000, 484 }; //ÎÄ±¾Î»ÖÃ
			pFont->DrawText(NULL, L"KTAS", -1, &g_FontPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));

			RECT g_AOAPosition = { 0, 0, 1000, 584 };
			pFont->DrawText(NULL, L"AOA", -1, &g_AOAPosition, DT_CENTER | DT_VCENTER, D3DCOLOR_XRGB(132, 251, 169));
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
	MSG messages;

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
		CreateThread(0, NULL, InputThread, (LPVOID)L"d3ddev", NULL, NULL);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}