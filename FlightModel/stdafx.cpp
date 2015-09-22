// stdafx.cpp : source file that includes just the standard includes
// ED_FM_Template.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

/*LPD3DXFONT ma_font;

HRESULT WINAPI D3DXCreateFont(
	LPDIRECT3DDEVICE9 pDevice,
	unsigned int Height,
	unsigned int Width,
	unsigned int Weight,
	unsigned int MipLevels,
	BOOL Italic,
	DWORD CharSet,
	DWORD OutputPrecision,
	DWORD Quality,
	DWORD PitchAndFamily,
	LPCTSTR pFacename,
	LPD3DXFONT *ppFont
	);

HRESULT WINAPI nEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	if (firstEndCall)
	{
		D3DXCreateSprite(pDevice, &m_sprite);
		D3DXCreateFont(pDevice, 14, 0, 400, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"), &ma_font);

		firstEndCall = false;
	}

	int x = 500;
	int y = 500;

	RECT FontPos;
	FontPos.left = x - 1;
	FontPos.right = x + 1;
	FontPos.top = y - 1;
	FontPos.bottom = y + 1;

	m_sprite->Begin(D3DXSPRITE_ALPHABLEND);

	ma_font->DrawText(m_sprite, L"test", -1, &FontPos, DT_NOCLIP, 0xFFFFFFFF);

	m_sprite->End();

	return pEndScene(pDevice);
}

void DisplaySomeText()
{

	// Create a colour for the text - in this case blue
	D3DCOLOR fontColor = D3DCOLOR_ARGB(255, 0, 0, 255);

	// Create a rectangle to indicate where on the screen it should be drawn
	RECT rct;
	rct.left = 2;
	rct.right = 780;
	rct.top = 10;
	rct.bottom = rct.top + 20;

	// Draw some text 
	ma_font->DrawText(NULL, L"Hello World", -1, &rct, 0, fontColor);
	ma_font->Release();
} */