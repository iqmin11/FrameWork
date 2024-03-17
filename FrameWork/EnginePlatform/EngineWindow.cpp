#include "EngineWindow.h"
#include <EngineBase/EngineDebug.h>

WNDCLASSEX EngineWindow::wcex;
HINSTANCE EngineWindow::hInst;
HWND EngineWindow::hWnd;
HDC EngineWindow::hDC;
bool EngineWindow::bIsWindowUpdate = false;
const float4 EngineWindow::DefaultWindowPos = float4::Zero();
const float4 EngineWindow::DefaultWindowSize = { 1600.f, 900.f, 0.f, 1.f };
float4 EngineWindow::WindowPos = float4::Zero();
float4 EngineWindow::WindowSize = EngineWindow::DefaultWindowSize;

EngineWindow::EngineWindow()
{

}

EngineWindow::~EngineWindow()
{

}

void EngineWindow::WindowCreate(HINSTANCE hInstance, std::string_view TileName, const float4& Pos, const float4& Size)
{
	// ������ ���� ��� (� Ư¡�� ���� �����츦 ����ž�!)
	if (!static_cast<bool>(MyRegisterClass(hInstance)))
	{
		MsgAssert("Window Ŭ���� ��Ͽ� �����߽��ϴ�.");
		return;
	}

	// ���ø����̼� �ʱ�ȭ�� �����մϴ�: ������ ����
	if (!InitInstance(hInstance, TileName)) // �����Լ����� ���ڷ� ���� hInstance�� �޾� �������� HINSTANCE hInst�� ����
	{
		MsgAssert("Window â ������ �����߽��ϴ�.");
		return; // InitInstance�� false�� ���μ��� ����
	}

	hDC = GetDC(hWnd);
	bIsWindowUpdate = true;
	InitWndRect(Pos, Size);
}

ATOM EngineWindow::MyRegisterClass(HINSTANCE hInstance)
{
	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = MsgFunc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	// �־����� ������ ������ �⺻Icon�� �˴ϴ�.
	wcex.hIcon = nullptr;//LoadIcon(_hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // ��� 
	wcex.lpszMenuName = nullptr;//MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
	wcex.lpszClassName = "GameEngineWindowDefault";
	wcex.hIconSm = nullptr;// LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex); //�������� Ŭ�����Լ���
}

LRESULT EngineWindow::MsgFunc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		// �� �����찡 ���õǾ���.
	case WM_SETFOCUS:
	{
		int a = 0;
		break;
	}
	case WM_ACTIVATE:
	{
		int a = 0;
		break;
	}
	case WM_KILLFOCUS:
	{
		int a = 0;
		break;
	}
	case WM_DESTROY:
	{
		// Message�Լ��� 0�� �����ϰ� ������.
		PostQuitMessage(0);
		bIsWindowUpdate = false;
		break;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

BOOL EngineWindow::InitInstance(HINSTANCE hInstance, std::string_view TitleName)
{
	hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

	hWnd = CreateWindow("GameEngineWindowDefault", TitleName.data(), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	return TRUE;
}

void EngineWindow::InitWndRect(const float4& Pos, const float4& Size)
{
	WindowPos = Pos;
	RECT WindowRect = { 0, 0, Size.ix(), Size.iy() };
	AdjustWindowRect(&WindowRect, WS_OVERLAPPEDWINDOW, FALSE);
	WindowSize = { static_cast<float>(WindowRect.right - WindowRect.left), static_cast<float>(WindowRect.bottom - WindowRect.top) };
	SetWindowPos(hWnd, nullptr, WindowPos.ix(), WindowPos.iy(), WindowSize.ix(), WindowSize.iy(), SWP_NOZORDER);
}

void EngineWindow::WindowLoop(std::function<void()> Begin, std::function<void()> Tick, std::function<void()> End)
{
	if (Begin != nullptr)
	{
		Begin();
	}

	MSG msg;

	while (bIsWindowUpdate)
	{
		if (GetMessage(&msg, nullptr, 0, 0))
		{
			if (Tick != nullptr)
			{
				Tick();
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	if (End != nullptr)
	{
		End();
	}
}

void EngineWindow::WinodwRelease()
{
	UnregisterClassA(wcex.lpszClassName, hInst);
}
