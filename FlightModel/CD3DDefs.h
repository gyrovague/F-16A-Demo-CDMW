#ifndef CD3DDEFS
#define CD3DDEFS

#include "stdafx.h"

typedef HRESULT ( WINAPI* tBeginScene )( LPDIRECT3DDEVICE9 pDevice);
extern tBeginScene oBeginScene;

typedef HRESULT ( WINAPI* tReset )( LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters );
extern tReset oReset;


typedef HRESULT (_stdcall *tPresent)(void*, const RECT*, const RECT*, HWND, const RGNDATA* );
extern tPresent oPresent;


HRESULT WINAPI HookedReset( LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters );
HRESULT WINAPI HookedBeginScene(LPDIRECT3DDEVICE9 pDevice);
HRESULT WINAPI HookedPresent(LPDIRECT3DDEVICE9 pDevice, const RECT* pSourceRect,const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion);

#endif