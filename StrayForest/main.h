#pragma once

#include <Windows.h>
#include <time.h>
#include <crtdbg.h>
#include <d3dx9.h>
#include <string>

//必要なライブラリファイルのロード
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#ifndef _DEBUG
#pragma comment(lib,"d3dx9d.lib")
#endif
#pragma comment(lib,"Winmm.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"XAudio2.lib")

#include "myimgui\imgui.h"
#include "myimgui\imgui_impl_dx9.h"

namespace windows_rect
{
	constexpr int SCREEN_WIDTH = 1024;
	constexpr int SCREEN_HEIGHT = 800;
}