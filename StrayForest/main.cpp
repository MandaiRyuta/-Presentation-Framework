/***************************************************************************:***
// 
//
//
//
//
*******************************************************************************/
#include "main.h"
#include <vector>

const std::string CLASS_NAME = "StrayForest";
const std::string WINDOW_NAME = "StrayForest";

//********************************************************************************
//
// プロトタイプ宣言
//
//********************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// ウィンドウプロシージャ
bool Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow, int nWindowWidth, int nWindowHeight);
void Uninit(void);
void Update(void);
void Draw(void);

//********************************************************************************
//
//グローバル変数
//
//********************************************************************************

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
		nWindowPosX,
		nWindowPosY,
		nWindowWidth,
		nWindowHeight,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	// メッセージ&ゲームループ
	MSG msg;
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
				// 更新
				Update();

				// 描画
				Draw();

				next_game_tick += SKIP_TICKS;
				loops++;
			}
			interpolation = float(GetTickCount() + SKIP_TICKS - next_game_tick) / float(SKIP_TICKS);
		}
	}

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

bool Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow, int nWindowWidth, int nWindowHeight)
{
	bool bSetWindow;
	// 使っていない引数の処理
	hInstance = hInstance;

	bWindow >= 1 ? bSetWindow = true : bSetWindow = false;


	return true;
}

//================================================================================
//
// 終了処理関数
//
//================================================================================
void Uninit(void)
{

}

//================================================================================
//
// 更新関数
//
//================================================================================
void Update(void)
{

}

//================================================================================
//
// 描画関数
//
//================================================================================
void Draw(void)
{

}
//================================================================================
//
// ウィンドウプロシージャ関数
//
//================================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY: // ウィンドウ破棄メッセージ
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
		{// 終了メッセージ

			int nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO | MB_DEFBUTTON2);

			if (nID == IDYES)
			{
				DestroyWindow(hWnd);
			}
		}
		break;

		}
		break;

	case WM_CLOSE:
	{
		int nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO | MB_DEFBUTTON2);

		if (nID == IDYES)
		{
			DestroyWindow(hWnd);
		}
		break;
	}

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
