#include "EngineWindow.h"
#include <EngineBase/EngineDebug.h>

HINSTANCE EngineWindow::hInst;
HWND EngineWindow::hWnd;

EngineWindow::EngineWindow()
{

}

EngineWindow::~EngineWindow()
{

}

void EngineWindow::WindowCreate(HINSTANCE hInstance, std::string_view TileName)
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
}

ATOM EngineWindow::MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;

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

void EngineWindow::WindowLoop()
{
    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, nullptr, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
}
