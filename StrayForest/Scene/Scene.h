#pragma once
#include <d3d9.h>
#include <d3dx9.h>
//必要なライブラリファイルのロード
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#ifndef _DEBUG
#pragma comment(lib,"d3dx9d.lib")
#endif
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"XAudio2.lib")

class Scene
{
public:
	Scene() {}
	virtual ~Scene() {}
public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Release() = 0;
};