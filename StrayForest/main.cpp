/***************************************************************************:***
// 
//
//
//
//
*******************************************************************************/
#include "main.h"
#include "Renderer\GameManager.h"
#include <vector>

const std::string CLASS_NAME = "StrayForest";
const std::string WINDOW_NAME = "StrayForest";

//********************************************************************************
//
// プロトタイプ宣言
//
//********************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// ウィンドウプロシージャ
bool Init(HINSTANCE _hInstance, HWND _hWnd, bool _bWindow, int _nWindowWidth, int _nWindowHeight);
void Uninit(void);
void Update(void);
void Draw(void);

#pragma region IMGUIハンドラー
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);
#pragma endregion

//********************************************************************************
//
//グローバル変数
//
//********************************************************************************
GameManager* gamemanager;
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevinstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 使っていない引数の処理
	lpCmdLine = lpCmdLine;
	hPrevinstance = hPrevinstance;

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);

	// ウィンドウクラスの登録
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = CLASS_NAME.c_str();
	wcex.hIconSm = NULL;

	RegisterClassEx(&wcex);		// WNDCLASSEX型のwcexの中身を登録

								// クライアントサイズの設定
	DWORD WStyle = WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME | WS_MAXIMIZEBOX);
	RECT wr = { 0, 0, windows_rect::SCREEN_WIDTH, windows_rect::SCREEN_HEIGHT };	// 矩形データ

	AdjustWindowRect(&wr, WStyle, FALSE);

	int nWindowWidth = wr.right - wr.left;
	int nWindowHeight = wr.bottom - wr.top;

	// ウィンドウの場所を中央に変更
	// デスクトップサイズの取得
	RECT DesktopRect;

	GetWindowRect(GetDesktopWindow(), &DesktopRect);
	int nWindowPosX = (DesktopRect.right - nWindowWidth) / 2;
	int nWindowPosY = (DesktopRect.bottom - nWindowHeight) / 2;

	(DesktopRect.right - DesktopRect.left) < nWindowPosX ? nWindowPosX = 0 : nWindowPosX;
	(DesktopRect.bottom - DesktopRect.top) < nWindowPosY ? nWindowPosY = 0 : nWindowPosY;

	// ウィンドウの作成
	HWND hWnd = CreateWindowEx(0,
		CLASS_NAME.c_str(),
		WINDOW_NAME.c_str(),
		WStyle,
		nWindowPosX + GetSystemMetrics(SM_CXDLGFRAME) * 2,
		nWindowPosY + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),
		nWindowWidth,
		nWindowHeight,
		NULL,
		NULL,
		hInstance,
		NULL);
	// Setup style
	ImGui::StyleColorsClassic();

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	// メッセージ&ゲームループ
	MSG msg = {};
	const int TICKS_PER_SECOND = 60;
	const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
	const int MAX_FRAMESKIP = 5;
	DWORD next_game_tick = GetTickCount();
	int loops;
	float interpolation;
	// タイマーの性能を上げる
	timeBeginPeriod(1);
	// 初期化(チェックあり)
	if (!Init(hInstance, hWnd, true, nWindowWidth, nWindowHeight))
	{
		MessageBox(hWnd, "初期化に失敗しました!!", "警告", MB_OK);

		return -1;
	}

	bool game_is_running = true;
	while (game_is_running)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{// メッセージ処理
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{// ゲーム処理
			loops = 0;

			if (GetTickCount() > next_game_tick && loops < MAX_FRAMESKIP)
			{
				ImGui_ImplDX9_NewFrame();
				// 更新
				Update();

				// 描画
				Draw();

				next_game_tick += SKIP_TICKS;
				loops++;

				ImGui::EndFrame();
			}
			interpolation = float(GetTickCount() + SKIP_TICKS - next_game_tick) / float(SKIP_TICKS);
		}
	}

	ImGui_ImplDX9_Shutdown();
	// 終了
	Uninit();

	timeEndPeriod(1);

	return (int)msg.wParam;
}

//================================================================================
//
// 初期化処理関数
//
//================================================================================

bool Init(HINSTANCE _hInstance, HWND _hWnd, bool _bWindow, int _nWindowWidth, int _nWindowHeight)
{
	// 使っていない引数の処理
	_hInstance = _hInstance;

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);

	gamemanager = new GameManager(_hInstance,_hWnd, _bWindow, _nWindowWidth, _nWindowHeight);
	gamemanager->Init();

	return true;
}

//================================================================================
//
// 終了処理関数
//
//================================================================================
void Uninit(void)
{
	gamemanager->Uninit();
	delete gamemanager;
}

//================================================================================
//
// 更新関数
//
//================================================================================
void Update(void)
{
	gamemanager->Update();
}

//================================================================================
//
// 描画関数
//
//================================================================================
void Draw(void)
{
	gamemanager->Draw();
}
//================================================================================
//
// ウィンドウプロシージャ関数
//
//================================================================================
LRESULT CALLBACK WndProc(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam)
{
	/// <summary>
	/// デバイスとパラメーターを受け取る
	/// </summary>

	LPDIRECT3DDEVICE9 device = GetDevice();
	D3DPRESENT_PARAMETERS parameter = GetParameter();
	if (ImGui_ImplWin32_WndProcHandler(_hWnd, _uMsg, _wParam, _lParam))
		return true;
	switch (_uMsg)
	{
	case WM_SIZE:
		if (device != NULL && _wParam != SIZE_MINIMIZED)
		{
			ImGui_ImplDX9_InvalidateDeviceObjects();
			parameter.BackBufferWidth = LOWORD(_lParam);
			parameter.BackBufferHeight = HIWORD(_lParam);
			HRESULT hr = device->Reset(&parameter);
			if (hr == D3DERR_INVALIDCALL)
				IM_ASSERT(0);
			ImGui_ImplDX9_CreateDeviceObjects();
		}
		return 0;
	case WM_DESTROY: // ウィンドウ破棄メッセージ
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (_wParam)
		{
		case VK_ESCAPE:
		{// 終了メッセージ

			int nID = MessageBox(_hWnd, "終了しますか？", "終了メッセージ", MB_YESNO | MB_DEFBUTTON2);

			if (nID == IDYES)
			{
				DestroyWindow(_hWnd);
			}
		}
		break;

		}
		break;

	case WM_CLOSE:
	{
		int nID = MessageBox(_hWnd, "終了しますか？", "終了メッセージ", MB_YESNO | MB_DEFBUTTON2);

		if (nID == IDYES)
		{
			DestroyWindow(_hWnd);
		}
		break;
	}

	default:
		break;
	}

	return DefWindowProc(_hWnd, _uMsg, _wParam, _lParam);
}
