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
    ImGui::InputText("Chat Input", InputBuffer, IM_ARRAYSIZE(InputBuffer));
    
    if (ImGui::Button("Send"))
    {
        memcpy_s(OutputBuffer, sizeof(OutputBuffer), InputBuffer, sizeof(InputBuffer));
    }
    ImGui::Text(OutputBuffer);
}

