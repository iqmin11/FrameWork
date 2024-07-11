#include "PrecompileHeader.h"
#include "NetworkGUI.h"

EngineNetwork* NetworkGUI::NetInst = nullptr;


NetworkGUI::NetworkGUI() 
{
	IP.resize(1024);
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
	static std::string Text = "";

	if (IsServer)
	{
		Text = "Server Mode";
		ImGui::Text(Text.c_str());
		return;
	}
	else if (IsClient)
	{
		Text = "Client Mode";
		ImGui::Text(Text.c_str());
		return;
	}


	Text = "Port";
	ImGui::InputInt(Text.c_str(), &Port);

	Text = "Open Server";
	if (ImGui::Button(Text.c_str()))
	{
		Server.ServerOpen(static_cast<unsigned short>(Port));
		IsServer = true;
		NetInst = &Server;
	}

	Text = "IP";
	ImGui::InputText(Text.c_str(), &IP[0], IP.size());

	Text = "Access Server";
	if (ImGui::Button(Text.c_str()))
	{
		IsClient = Client.Connect(IP, static_cast<unsigned short>(Port));
		NetInst = &Client;
	}


	//if (true == IsServer)
	//{
	//	ImGui::Text(Text.c_str());

	//	// 처리하면 쉬워진다.
	//	ImGui::PushID(321312321);
	//	ImGui::InputText(Text.c_str(), &TestSendBuffer[0], TestSendBuffer.size());
	//	ImGui::PopID();

	//	ImGui::PushID(33333121);
	//	Text = "SendTest";
	//	if (ImGui::Button(Text.c_str()))
	//	{
	//		size_t StrLen = strlen(TestSendBuffer.c_str());
	//		//NetInst->Send(&TestSendBuffer[0], static_cast<unsigned int>(StrLen));
	//	}
	//	ImGui::PopID();


	//	return;
	//}
}

