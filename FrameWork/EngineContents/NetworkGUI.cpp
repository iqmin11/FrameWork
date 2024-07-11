#include "PrecompileHeader.h"
#include "NetworkGUI.h"
#include "EngineCore/EngineLevel.h"

EngineNetwork* NetworkGUI::NetInst = nullptr;


NetworkGUI::NetworkGUI() 
{
	IP.resize(1024);
	TestSendBuffer.resize(1024);
}

NetworkGUI::~NetworkGUI() 
{
}

void NetworkGUI::Begin()
{
}

void NetworkGUI::Tick(float DeltaTime, std::shared_ptr<EngineLevel> CurLevel)
{
	static std::string Text = "";

	if (IsServer)
	{
		Text = "Server Mode";
		ImGui::Text(Text.c_str());
		
		ImGui::PushID(321312321);
		ImGui::InputText(Text.c_str(), &TestSendBuffer[0], TestSendBuffer.size());
		ImGui::PopID();

		ImGui::PushID(33333121);
		Text = "SendTest";
		if (ImGui::Button(Text.c_str()))
		{
			int StrLen = strlen(TestSendBuffer.c_str());
			NetInst->Send(&TestSendBuffer[0], StrLen);
		}
		ImGui::PopID();
		return;
	}
	else if (IsClient)
	{
		Text = "Client Mode";
		ImGui::Text(Text.c_str());

		Text = "SendTest";

		// 처리하면 쉬워진다.
		ImGui::PushID(321312321);
		ImGui::InputText(Text.c_str(), &TestSendBuffer[0], TestSendBuffer.size());
		ImGui::PopID();

		ImGui::PushID(33333121);
		Text = "SendTest";
		if (ImGui::Button(Text.c_str()))
		{
			int StrLen = strlen(TestSendBuffer.c_str());

			// TestSendBuffer = Arr;
			NetInst->Send(&TestSendBuffer[0], StrLen);
		}
		ImGui::PopID();
		return;
	}


	Text = "Port";
	ImGui::InputInt(Text.c_str(), &Port);

	Text = "Open Server";
	if (ImGui::Button(Text.c_str()))
	{
		Server.ServerOpen(static_cast<unsigned short>(Port));
		ServerInit(CurLevel);
		IsServer = true;
		//ChatUser::MainUser->InitServerObject();
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
}

void NetworkGUI::ServerInit(std::shared_ptr<class EngineLevel> CurLevel)
{
	Server.SetAcceptCallback(
		[=](SOCKET, EngineServer* _Server)
		{
			//std::shared_ptr<ConnectIDPacket> Packet = std::make_shared<ConnectIDPacket>();
			//std::shared_ptr<ChatUser> NewPlayer = CurLevel->CreateActor<ChatUser>();
		}
	);
}

