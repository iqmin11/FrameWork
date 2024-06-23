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
        _memccpy(OutputBuffer, InputBuffer, 0, sizeof(InputBuffer));
    }
    ImGui::Text(OutputBuffer);
}

