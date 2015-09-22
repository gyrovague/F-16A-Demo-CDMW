#include "stdafx.h"

tPresent oPresent;
IDirect3DStateBlock9* pBlock = NULL;
LPD3DXSPRITE Sprite;
D3DVIEWPORT9 g_Viewport;

void InitResources(LPDIRECT3DDEVICE9 pDevice)
{
	if(!pBlock)
		pDevice->CreateStateBlock(D3DSBT_ALL,&pBlock);

}

void DrawESP()
{
	try
	{
		pCanvas->TextCenteredf(500,500,D3DCOLOR_RGBA(255,0,0,255),"Survivor[%dm]",100);
	}
	catch(...){}
}



HRESULT WINAPI HookedPresent(LPDIRECT3DDEVICE9 pDevice, const RECT* pSourceRect,const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion)
{
	if (!pBlock) 
		InitResources(pDevice);

	pDevice->GetViewport(&g_Viewport);
	pBlock->Capture();
	D3DVIEWPORT9 ViewPort;
	pDevice->GetViewport(&ViewPort);
	pCanvas->Init(pDevice);
	pCanvas->Begin();

	D3DXVECTOR3 vecPosition;


	DrawESP();

	pCanvas->End();
	pBlock->Apply();

return oPresent(pDevice,pSourceRect,pDestRect,hDestWindowOverride,pDirtyRegion);
}