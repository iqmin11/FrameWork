#pragma once
#include "framework.h"
#include "Resource.h"
#include <string_view>

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

	static void WindowCreate(HINSTANCE hInstance, std::string_view _TitleName);
	static void WindowLoop();

protected:


private:

	static HINSTANCE hInst;
	static HWND hWnd;
	
	static ATOM MyRegisterClass(HINSTANCE hInstance);
    static LRESULT CALLBACK MsgFunc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static BOOL InitInstance(HINSTANCE hInstance, std::string_view TitleName);
	

};

