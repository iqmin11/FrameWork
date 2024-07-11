#include "PrecompileHeader.h"
#include "NetworkGUI.h"

NetworkGUI::NetworkGUI() 
{
}

NetworkGUI::~NetworkGUI() 
{
}

void NetworkGUI::Begin()
{
	int a = 0;
}

void NetworkGUI::Tick(float DeltaTime)
{
	std::string Text = "Server Mode";

	if (true == IsServer)
	{
		ImGui::Text(Text.c_str());

		// 처리하면 쉬워진다.
		ImGui::PushID(321312321);
		ImGui::InputText(Text.c_str(), &TestSendBuffer[0], TestSendBuffer.size());
		ImGui::PopID();

		ImGui::PushID(33333121);
		Text = "SendTest";
		if (ImGui::Button(Text.c_str()))
		{
			size_t StrLen = strlen(TestSendBuffer.c_str());
			//NetInst->Send(&TestSendBuffer[0], static_cast<unsigned int>(StrLen));
		}
		ImGui::PopID();


		return;
	}
}

