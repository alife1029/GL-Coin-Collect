// Hide console on release build
#ifndef _DEBUG
	#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include <Engine.h>
#include <Scripts.h>
#include <stdio.h>

using namespace engine;

class AppleCollector : public Application
{
public:
	AppleCollector(const ApplicationConfig& config) : Application(config)
	{
		background = new Sprite("assets/background.png", { 2.0f, 2.0f });
		ground = new Sprite("assets/ground.png", { 2.0f, 0.4f });
		player = new Sprite("assets/Character/idle.png", { 0.36f, 0.48f });
		coin = new Sprite("assets/coinGold.png", { 0.12f, 0.12f });

		ground->GetComponent<Transform>()->SetPosition(0.0f, -0.8f);

		player->AddComponent(new Animator());
		player->GetComponent<Transform>()->SetPosition(0.0f, -0.4f);
		player->GetComponent<Animator>()->AddAnimation("anim/playerIdle.bin");
		player->GetComponent<Animator>()->AddAnimation("anim/playerRun.bin");
		player->AddComponent(new Player());

		coin->AddComponent(new Coin());
		coin->GetComponent<Coin>()->m_Player = player;
	}
	~AppleCollector()
	{
		delete background;
		delete ground;
		delete player;
		delete coin;
	}

	void Update() override
	{
		background->Update();
		ground->Update();
		player->Update();
		coin->Update();
	}

private:
	Sprite* background;
	Sprite* ground;
	Sprite* player;
	Sprite* coin;
};

int main()
{
	ApplicationConfig config;
	config.width = 600;
	config.height = 600;
	config.fullscreen = false;
	config.title = "Apple Collector";

	AppleCollector* game = new AppleCollector(config);
	game->Run();
	delete game;
}