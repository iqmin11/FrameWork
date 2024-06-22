#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"
#include "EngineObject.h"

class EngineGUIWindow : public EngineObject, public std::enable_shared_from_this<EngineGUIWindow>
{
	friend class EngineGUI;

private:
	void Begin()
	{
		std::string_view View = GetName();

		ImGui::Begin(View.data());
	}
	void End()
	{
		ImGui::End();
	}

public:
	virtual void Start() {}
	virtual void OnGUI(std::shared_ptr<class GameEngineLevel> Level, float _DeltaTime) = 0;
};

// 설명 :
class EngineGUI
{
public:
	// constrcuter destructer
	EngineGUI();
	~EngineGUI();

	// delete Function
	EngineGUI(const EngineGUI& _Other) = delete;
	EngineGUI(EngineGUI&& _Other) noexcept = delete;
	EngineGUI& operator=(const EngineGUI& _Other) = delete;
	EngineGUI& operator=(EngineGUI&& _Other) noexcept = delete;

	static void Initalize();
	static void Tick(float DelteTime);
	static void Release();

	template<typename WindowType>
	static std::shared_ptr<EngineGUIWindow> GUIWindowCreate(const std::string_view _Name)
	{
		std::string UpperString = EngineString::ToUpper(_Name);

		if (AllWindow.end() != AllWindow.find(UpperString))
		{
			MsgAssert("이런 이름을 가진 GUI윈도우는 이미 존재합니다.");
			return nullptr;
		}

		std::shared_ptr<EngineGUIWindow> WindowPtr;
		AllWindow[UpperString] = WindowPtr = std::make_shared<WindowType>();
		WindowPtr->SetName(UpperString);
		WindowPtr->Start();

		return WindowPtr;
	}

protected:

private:
	static std::map<std::string, std::shared_ptr<EngineGUIWindow>> AllWindow;
	
	static bool show_demo_window;
	static bool show_another_window;
	static ImVec4 clear_color;
};

