#include "PrecompileHeader.h"
#include "ChatGUI.h"

ChatGUI::ChatGUI() 
{
}

ChatGUI::~ChatGUI() 
{
}

void ChatGUI::Begin()
{
}

void ChatGUI::Tick(float DeltaTime)
{
    static char buf[32] = "";
    ImGui::InputText("Chat Input", buf, IM_ARRAYSIZE(buf));
    
    if (ImGui::Button("Send"))
    {

    }
    ImGui::Text(buf);
    
}

