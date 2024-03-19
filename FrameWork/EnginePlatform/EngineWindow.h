#pragma once

class EngineWindow
{
public:
	// construtor destructor
	EngineWindow();
	~EngineWindow();

	// delete Function
	EngineWindow(const EngineWindow& _Other) = delete;
	EngineWindow(EngineWindow&& _Other) noexcept = delete;
	EngineWindow& operator=(const EngineWindow& _Other) = delete;
	EngineWindow& operator=(EngineWindow&& _Other) noexcept = delete;

	static void WindowCreate(HINSTANCE hInstance, std::string_view TitleName, const float4& StartPos = float4::Zero(), const float4& Size = DefaultWindowSize);
	static void WindowLoop(std::function<void()> Begin, std::function<void()> Tick, std::function<void()> End);
	static void WinodwRelease();

	static const float4 DefaultWindowPos;
	static const float4 DefaultWindowSize;

protected:


private:

	static WNDCLASSEX wcex;
	static HINSTANCE hInst;
	static HWND hWnd;
	static HDC hDC;
	
	//InitWindow
	static ATOM MyRegisterClass(HINSTANCE hInstance);
    static LRESULT CALLBACK MsgFunc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static BOOL InitInstance(HINSTANCE hInstance, std::string_view TitleName);
	static void InitWndRect(const float4& Pos, const float4& Size);
	
	//SetWindowOption

	static bool bIsWindowUpdate;

	static float4 WindowPos;
	static float4 WindowSize;
};

