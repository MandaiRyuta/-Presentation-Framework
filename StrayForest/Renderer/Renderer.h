#pragma once
#include <unordered_map>
#include "../main.h"
#include "../Entity/Entity.h"

//シングルトンクラス
//デバイスやパラメーターをシングルトンで作る
template <typename U>
class CDXCore
{
public:
	static U getInstance() {
		static U instance;
		return instance;
	}

protected:
	CDXCore() {}
	virtual ~CDXCore() {}
};

class CDX9Device : public CDXCore<LPDIRECT3DDEVICE9>
{
public:
	CDX9Device() {}
	~CDX9Device() {}
	
	LPDIRECT3DDEVICE9 Get() { return device_; }
private:
	LPDIRECT3DDEVICE9 device_;
};

class CDX9Parameter : public CDXCore<D3DPRESENT_PARAMETERS>
{
public:
	CDX9Parameter() {}
	~CDX9Parameter() {}

	D3DPRESENT_PARAMETERS Get() { return d3dpp_; }
private:
	D3DPRESENT_PARAMETERS d3dpp_;
};

template <class U>
class CDXRender
{
public:
	static U* getInstance() {
		static U instance;
		return &instance;
	}

protected:
	CDXRender() {}
	virtual ~CDXRender() {}
};

//DirectX9を使ったレンダリング
class CDX9Renderer : public CDXRender<CDX9Renderer>
{
public:
	CDX9Renderer() {}
	~CDX9Renderer() {}
public:
	//@Summary	Init	:	DirectX9初期化
	bool Init(HWND hWnd, bool bWindow, int nWindowWidth, int nWindowHeight);
	void Uninit();
private:
	//DirectX9 インターフェースポインタ
	LPDIRECT3D9 pD3D_;
};

//@Summary	=	GetParameter	:	パラメーター取得関数
D3DPRESENT_PARAMETERS GetParameter();
//@Summary	=	GetDevice	:	デバイス取得関数
LPDIRECT3DDEVICE9 GetDevice();