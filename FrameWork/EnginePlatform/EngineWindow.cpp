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
    // 윈도우 정보 등록 (어떤 특징을 가진 윈도우를 만들거야!)
    if (!static_cast<bool>(MyRegisterClass(hInstance)))
    {
        MsgAssert("Window 클래스 등록에 실패했습니다.");
        return;
    }

    // 애플리케이션 초기화를 수행합니다: 윈도우 생성
    if (!InitInstance(hInstance, TileName)) // 메인함수에서 인자로 받은 hInstance를 받아 전역변수 HINSTANCE hInst에 넣음
    {
        MsgAssert("Window 창 생성에 실패했습니다.");
        return; // InitInstance가 false면 프로세스 종료
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
    // 넣어주지 않으면 윈도우 기본Icon이 됩니다.
    wcex.hIcon = nullptr;//LoadIcon(_hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // 흰색 
    wcex.lpszMenuName = nullptr;//MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName = "GameEngineWindowDefault";
    wcex.hIconSm = nullptr;// LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassEx(&wcex); //레지스터 클래스함수가
}

LRESULT EngineWindow::MsgFunc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        // 내 윈도우가 선택되었다.
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
        // Message함수가 0을 리턴하게 만들어라.
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
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

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
