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
// �v���g�^�C�v�錾
//
//********************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// �E�B���h�E�v���V�[�W��
bool Init(HINSTANCE _hInstance, HWND _hWnd, bool _bWindow, int _nWindowWidth, int _nWindowHeight);
void Uninit(void);
void Update(void);
void Draw(void);

#pragma region IMGUI�n���h���[
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);
#pragma endregion

//********************************************************************************
//
//�O���[�o���ϐ�
//
//********************************************************************************
GameManager* gamemanager;
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevinstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �g���Ă��Ȃ������̏���
	lpCmdLine = lpCmdLine;
	hPrevinstance = hPrevinstance;

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);

	// �E�B���h�E�N���X�̓o�^
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

	RegisterClassEx(&wcex);		// WNDCLASSEX�^��wcex�̒��g��o�^

								// �N���C�A���g�T�C�Y�̐ݒ�
	DWORD WStyle = WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME | WS_MAXIMIZEBOX);
	RECT wr = { 0, 0, windows_rect::SCREEN_WIDTH, windows_rect::SCREEN_HEIGHT };	// ��`�f�[�^

	AdjustWindowRect(&wr, WStyle, FALSE);

	int nWindowWidth = wr.right - wr.left;
	int nWindowHeight = wr.bottom - wr.top;

	// �E�B���h�E�̏ꏊ�𒆉��ɕύX
	// �f�X�N�g�b�v�T�C�Y�̎擾
	RECT DesktopRect;

	GetWindowRect(GetDesktopWindow(), &DesktopRect);
	int nWindowPosX = (DesktopRect.right - nWindowWidth) / 2;
	int nWindowPosY = (DesktopRect.bottom - nWindowHeight) / 2;

	(DesktopRect.right - DesktopRect.left) < nWindowPosX ? nWindowPosX = 0 : nWindowPosX;
	(DesktopRect.bottom - DesktopRect.top) < nWindowPosY ? nWindowPosY = 0 : nWindowPosY;

	// �E�B���h�E�̍쐬
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
	// ���b�Z�[�W&�Q�[�����[�v
	MSG msg = {};
	const int TICKS_PER_SECOND = 60;
	const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
	const int MAX_FRAMESKIP = 5;
	DWORD next_game_tick = GetTickCount();
	int loops;
	float interpolation;
	// �^�C�}�[�̐��\���グ��
	timeBeginPeriod(1);
	// ������(�`�F�b�N����)
	if (!Init(hInstance, hWnd, true, nWindowWidth, nWindowHeight))
	{
		MessageBox(hWnd, "�������Ɏ��s���܂���!!", "�x��", MB_OK);

		return -1;
	}

	bool game_is_running = true;
	while (game_is_running)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{// ���b�Z�[�W����
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
		{// �Q�[������
			loops = 0;

			if (GetTickCount() > next_game_tick && loops < MAX_FRAMESKIP)
			{
				ImGui_ImplDX9_NewFrame();
				// �X�V
				Update();

				// �`��
				Draw();

				next_game_tick += SKIP_TICKS;
				loops++;

				ImGui::EndFrame();
			}
			interpolation = float(GetTickCount() + SKIP_TICKS - next_game_tick) / float(SKIP_TICKS);
		}
	}

	ImGui_ImplDX9_Shutdown();
	// �I��
	Uninit();

	timeEndPeriod(1);

	return (int)msg.wParam;
}

//================================================================================
//
// �����������֐�
//
//================================================================================

bool Init(HINSTANCE _hInstance, HWND _hWnd, bool _bWindow, int _nWindowWidth, int _nWindowHeight)
{
	// �g���Ă��Ȃ������̏���
	_hInstance = _hInstance;

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);

	gamemanager = new GameManager(_hInstance,_hWnd, _bWindow, _nWindowWidth, _nWindowHeight);
	gamemanager->Init();

	return true;
}

//================================================================================
//
// �I�������֐�
//
//================================================================================
void Uninit(void)
{
	gamemanager->Uninit();
	delete gamemanager;
}

//================================================================================
//
// �X�V�֐�
//
//================================================================================
void Update(void)
{
	gamemanager->Update();
}

//================================================================================
//
// �`��֐�
//
//================================================================================
void Draw(void)
{
	gamemanager->Draw();
}
//================================================================================
//
// �E�B���h�E�v���V�[�W���֐�
//
//================================================================================
LRESULT CALLBACK WndProc(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam)
{
	/// <summary>
	/// �f�o�C�X�ƃp�����[�^�[���󂯎��
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
	case WM_DESTROY: // �E�B���h�E�j�����b�Z�[�W
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (_wParam)
		{
		case VK_ESCAPE:
		{// �I�����b�Z�[�W

			int nID = MessageBox(_hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO | MB_DEFBUTTON2);

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
		int nID = MessageBox(_hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO | MB_DEFBUTTON2);

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
