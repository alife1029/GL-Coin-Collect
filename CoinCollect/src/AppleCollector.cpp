// Hide console on release build
#ifndef _DEBUG
	#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include <Engine.h>
#include <Scripts.h>

using namespace engine;

class AppleCollector : public Application, EventSystem
{
public:
	AppleCollector(const ApplicationConfig& config) : Application(config)
	{
		viewport = new Viewport(config.width, config.height);

		background = new Sprite("assets/background.png", { 2.0f, 2.0f });
		ground = new Sprite("assets/ground.png", { 2.0f, 0.4f });
		player = new Sprite("assets/Character/idle.png", { 0.36f, 0.48f });
		coin = new Sprite("assets/coinGold.png", { 0.12f, 0.12f });
		text = new Text();

		ground->GetComponent<Transform>()->SetPosition(0.0f, -0.8f);

		player->AddComponent(new Animator());
		player->GetComponent<Transform>()->SetPosition(0.0f, -0.4f);
		player->GetComponent<Animator>()->AddAnimation("anim/playerIdle.bin");
		player->GetComponent<Animator>()->AddAnimation("anim/playerRun.bin");
		player->AddComponent(new Player());
		player->GetComponent<Player>()->m_TextRenderer = text->GetComponent<TextRenderer>();

		coin->AddComponent(new Coin());
		coin->GetComponent<Coin>()->m_Player = player;

		text->GetComponent<TextRenderer>()->SetText("Score: 0");
		text->GetComponent<TextRenderer>()->SetFont("fonts/Righteous.ttf");
		text->GetComponent<TextRenderer>()->SetColor(0.7f, 0.0f, 0.0f, 1.0f);
		text->GetComponent<Transform>()->SetScale(0.002f, 0.002f);
		text->GetComponent<Transform>()->SetPosition(-0.95f, 0.85f);

		SetEventListener(this);
	}
	~AppleCollector()
	{
		delete viewport;
		delete background;
		delete ground;
		delete player;
		delete coin;
		delete text;
	}

	void Update() override
	{
		background->Update();
		ground->Update();
		player->Update();
		coin->Update();
		text->Update();
	}

	void Resize(int width, int height) override
	{
		viewport->Update(width, height);
	}

private:
	Viewport* viewport;
	Sprite* background;
	Sprite* ground;
	Sprite* player;
	Sprite* coin;
	Text* text;
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