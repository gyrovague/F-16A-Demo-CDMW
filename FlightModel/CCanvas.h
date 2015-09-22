#ifndef CCANVAS
#define CCANVAS
#pragma once
#include "stdafx.h"

class CCanvas
{
public:
	//Engine Specific 
	virtual void Init(void* Pram)=0;
	virtual void Begin()=0;
	virtual bool IsValid()=0;
	virtual void End()=0;
	virtual void Reset()=0;
	virtual void Text(char* text,int x, int y, DWORD color)=0;
	virtual int TextWidth(char* text)=0;
	virtual int TextHeight(char* text)=0;
	virtual void Line(float x1,float y1,float x2,float y2,DWORD color)=0;
	virtual void FillGradient(float x,float y,float w,float h,DWORD color1,DWORD color2,DWORD color3,DWORD color4)=0;
	virtual void Poly(POINT* points,int count,DWORD color)=0;

	//Extras
	void Fill(float x,float y,float w,float h,DWORD color)
	{
		FillGradient(x,y,w,h,color,color,color,color);
	}
	void FillCentered(float x,float y,float w,float h,DWORD color)
	{
		FillGradient(x-w/2,y-h/2,w,h,color,color,color,color);
	}
	void Textf(int x, int y, DWORD color, const char *fmt, ...)
	{
		if (!IsValid()) return;
		static char buffer[1024];
		va_list va_alist;
		va_start (va_alist, fmt);
		//_vsnprintf(buffer, sizeof(buffer), fmt, va_alist);
		vsnprintf(buffer, sizeof(buffer), fmt, va_alist);
		va_end (va_alist);
		Text(buffer,x,y,color);
	}
	void TextCenteredf(int x, int y, DWORD color, const char *fmt, ...)
	{
		if (!IsValid()) return;
		static char buffer[1024];
		va_list va_alist;
		va_start (va_alist, fmt);
		vsnprintf(buffer, sizeof(buffer), fmt, va_alist);
		va_end (va_alist);
		Text(buffer,x-TextWidth(buffer)/2,y,color);
	}

	void Circle(int x, int y, int r, int s, DWORD color)
	{
		if (!IsValid()) return;
		float Step = 3.14159265*2.0/s;
		for (float a=0; a < 3.14159265*2.0; a += Step)
		{
			float x1 = r * cos(a) + x;
			float y1 = r * sin(a) + y;
			float x2 = r * cos(a+Step) + x;
			float y2 = r * sin(a+Step) + y;
			Line(x1,y1,x2,y2,color);
		}
	}
	void Box(int x, int y, int w, int h, DWORD color)
	{
		if (!IsValid()) return;
		Line(x,y,x+w,y,color);
		Line(x+w,y,x+w,y+h,color);
		Line(x+w,y+h,x,y+h,color);
		Line(x,y+h,x,y,color);
	}
	void BoxCentered(int x, int y, int w, int h, DWORD color)
	{
		if (!IsValid()) return;
		Box(x-w/2,y-h/2,w,h,color);
	}

	int Width,Height;
};


class CDX9Canvas : public CCanvas
{
	struct CUSTOMVERTEX
	{
		FLOAT x, y, z, rhw; // The transformed position for the vertex.
		DWORD color;        // The vertex color.
	};
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

	LPD3DXFONT pFont;
	LPDIRECT3DDEVICE9 pDevice;
	IDirect3DStateBlock9 *pSB;

	bool bValid;

	CUSTOMVERTEX Line_Batch[5000];
	CUSTOMVERTEX Fill_Batch[16000];
	int Line_Index;
	int Fill_Index;

public:
	CDX9Canvas()
	{
		bValid = false;
		pDevice = NULL;
		pFont = NULL;
		pSB = NULL;
		Line_Index = 0;
		Fill_Index = 0;
	}

	virtual void Init(void* Pram)
	{
		pDevice = (LPDIRECT3DDEVICE9)Pram;
	}
	virtual void Begin()
	{
		bValid = false;

		if (!pDevice)return;
		if (!pSB)
		{
			if (pDevice->CreateStateBlock(D3DSBT_ALL,&pSB) != D3D_OK) return;
		}
		if (!pFont)
		{
			if (D3DXCreateFont(pDevice, 13, 0, FW_NORMAL, 1, FALSE, DEFAULT_CHARSET,OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,L"Bradley Hand",&pFont) != D3D_OK) return;
		}

		Line_Index = 0;
		Fill_Index = 0;
		pSB->Capture();

		bValid = true;
	}
	virtual bool IsValid()
	{
		return bValid;
	}
	virtual void End()
	{
		if (bValid)
		{
			SetupDrawing();
			if (Line_Index>0) pDevice->DrawPrimitiveUP(D3DPT_LINELIST,Line_Index/2,Line_Batch,sizeof(CUSTOMVERTEX));
			if (Fill_Index>0) pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,Fill_Index/3,Fill_Batch,sizeof(CUSTOMVERTEX));
			pSB->Apply();
		}
		bValid = false;
		Line_Index = 0;
		Fill_Index = 0;
	}
	virtual void Reset()
	{
		if (pFont)
		{
			pFont->Release();
			pFont = NULL;
		}

		if (pSB)
		{
			pSB->Release();
			pSB = NULL;
		}
		bValid = false;
	}

	void SetupDrawing()
	{
		pDevice->SetTexture(0,NULL);  
		pDevice->SetTexture(1,NULL);  

		pDevice->SetVertexShader(NULL);
		pDevice->SetPixelShader(NULL);

		//pDevice->SetRenderState( D3DRS_ALPHATESTENABLE ,FALSE );
		//pDevice->SetRenderState( D3DRS_ALPHABLENDENABLE ,FALSE );
		pDevice->SetRenderState( D3DRS_ZENABLE,D3DZB_FALSE );
		pDevice->SetRenderState( D3DRS_FILLMODE,D3DFILL_SOLID );
		pDevice->SetRenderState( D3DRS_SHADEMODE ,D3DSHADE_GOURAUD );
		pDevice->SetRenderState( D3DRS_ZWRITEENABLE ,FALSE );
		pDevice->SetRenderState( D3DRS_SRCBLEND ,D3DBLEND_ONE );
		pDevice->SetRenderState( D3DRS_DESTBLEND ,D3DBLEND_ZERO );
		pDevice->SetRenderState( D3DRS_CULLMODE ,D3DCULL_NONE );
		pDevice->SetRenderState( D3DRS_ZFUNC ,D3DCMP_LESSEQUAL );
		pDevice->SetRenderState( D3DRS_FOGENABLE ,FALSE );
		pDevice->SetRenderState( D3DRS_SPECULARENABLE ,FALSE );
		pDevice->SetRenderState( D3DRS_STENCILENABLE ,FALSE );
		pDevice->SetRenderState( D3DRS_CLIPPING ,FALSE );
		pDevice->SetRenderState( D3DRS_LIGHTING ,FALSE );
		pDevice->SetRenderState( D3DRS_COLORVERTEX ,TRUE );
		pDevice->SetRenderState( D3DRS_CLIPPLANEENABLE ,0 );

		pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	}
	virtual void Text(char* text,int x, int y, DWORD color)
	{
		if (!IsValid()) return;
		color |= 0xFF000000;
		RECT pos;
		SetRect(&pos,x,y,0,0);
		pFont->DrawTextA(NULL,text,-1,&pos,DT_NOCLIP,color);
	}
	virtual int TextWidth(char* text)
	{
		if (!IsValid()) return strlen(text)*8;
		RECT pos;SetRect(&pos,0,0,0,0);
		pFont->DrawTextA(NULL,text,-1,&pos,DT_CALCRECT,0);
		return pos.right;
	}
	virtual int TextHeight(char* text)
	{
		if (!IsValid()) return 12;
		RECT pos;SetRect(&pos,0,0,0,0);
		pFont->DrawTextA(NULL,text,-1,&pos,DT_CALCRECT,0);
		return pos.bottom;
	}
	virtual void Line(float x1,float y1,float x2,float y2,DWORD color)
	{
		if (!IsValid()) return;
		CUSTOMVERTEX v[2];
		SetVert(&v[0], x1,y1,color);
		SetVert(&v[1], x2,y2,color);
		SetupDrawing();
		pDevice->DrawPrimitiveUP(D3DPT_LINELIST,1,v,sizeof(CUSTOMVERTEX));
	}
	virtual void FillGradient(float x,float y,float w,float h,DWORD color1,DWORD color2,DWORD color3,DWORD color4)
	{
		if (!IsValid()) return;
		CUSTOMVERTEX v[4];
		SetVert(&v[0], x,y,color1);
		SetVert(&v[1], x+w,y,color2);
		SetVert(&v[2], x+w,y+h,color3);
		SetVert(&v[3], x,y+h,color4);
		SetupDrawing();
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN,2,v,sizeof(CUSTOMVERTEX));
	}
	void SetVert(CUSTOMVERTEX* v, float x, float y, DWORD color)
	{
		v->x = x; v->y = y; v->z = 0.0f; v->rhw = 1.0f;
		v->color = color;
	}
	virtual void Poly(POINT* points,int count,DWORD color)
	{
		if (!IsValid()) return;
		if (count<3) return;
		CUSTOMVERTEX* v = new CUSTOMVERTEX[count];
		for (int i=0; i < count;i++)
		{
			SetVert(&v[i], points[i].x,points[i].y,color);
		}
		SetupDrawing();
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN,count-3+1,v,sizeof(CUSTOMVERTEX));
		delete v;
	}

	//Extras
	void Line_Batched(float x1,float y1,float x2,float y2,DWORD color)
	{
		SetVert(&Line_Batch[Line_Index+0], x1,y1,color);
		SetVert(&Line_Batch[Line_Index+1], x2,y2,color);
		Line_Index += 2;
	}
	void FillGradient_Batched(float x,float y,float w,float h,DWORD color1,DWORD color2,DWORD color3,DWORD color4)
	{
		SetVert(&Fill_Batch[Fill_Index+0], x,y,color1);
		SetVert(&Fill_Batch[Fill_Index+1], x+w,y,color2);
		SetVert(&Fill_Batch[Fill_Index+2], x+w,y+h,color3);

		SetVert(&Fill_Batch[Fill_Index+3], x,y,color1);
		SetVert(&Fill_Batch[Fill_Index+4], x+w,y+h,color3);
		SetVert(&Fill_Batch[Fill_Index+5], x,y+h,color4);
		Fill_Index += 6;
	}
	void Fill_Batched(float x,float y,float w,float h,DWORD color)
	{
		FillGradient_Batched(x,y,w,h,color,color,color,color);
	}
	void FillCentered_Batched(float x,float y,float w,float h,DWORD color)
	{
		FillGradient_Batched(x-w/2,y-h/2,w,h,color,color,color,color);
	}
	void Circle_Batched(int x, int y, int r, int s, DWORD color)
	{
		float Step = 3.14159265*2.0/s;
		for (float a=0; a < 3.14159265*2.0; a += Step)
		{
			float x1 = r * cos(a) + x;
			float y1 = r * sin(a) + y;
			float x2 = r * cos(a+Step) + x;
			float y2 = r * sin(a+Step) + y;
			Line_Batched(x1,y1,x2,y2,color);
		}
	}
	void Box_Batched(int x, int y, int w, int h, DWORD color)
	{
		Line_Batched(x,y,x+w,y,color);
		Line_Batched(x+w,y,x+w,y+h,color);
		Line_Batched(x+w,y+h,x,y+h,color);
		Line_Batched(x,y+h,x,y,color);
	}
	void BoxCentered_Batched(int x, int y, int w, int h, DWORD color)
	{
		Box_Batched(x-w/2,y-h/2,w,h,color);
	}

};
extern CDX9Canvas Canvas;
extern CCanvas* pCanvas;

#endif