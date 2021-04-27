// Hide console on release build
#ifndef _DEBUG
	#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#define _CRT_SECURE_NO_WARNINGS

#include <Engine.h>
#include <Scripts.h>
#include <fstream>
#include <chrono>
#include <ctime>

using namespace engine;

class AppleCollector : public Application, EventSystem
{
public:
	AppleCollector(const ApplicationConfig& config) : Application(config)
	{		
		srand(static_cast<uint32_t>(time(0)));

		viewport = new Viewport(config.width, config.height);

		// Create game objects
		background = new Sprite("assets/background.png", { 2.0f, 2.0f });
		ground = new Sprite("assets/ground.png", { 2.0f, 0.4f });
		player = new Sprite("assets/Character/idle.png", { 0.36f, 0.48f });
		text = new Text();
		// Create coins
		for (size_t i = 0; i < 5; i++)
			collectables.push_back(new Sprite("assets/coinGold.png", { 0.12f, 0.12f }));

		// Set ground's position
		ground->GetComponent<Transform>()->SetPosition(0.0f, -0.8f);

		// Set player components
		player->GetComponent<Transform>()->SetPosition(0.0f, -0.4f);
		// Add animator
		player->AddComponent(new Animator());
		player->GetComponent<Animator>()->AddAnimation("anim/playerIdle.bin");
		player->GetComponent<Animator>()->AddAnimation("anim/playerRun.bin");
		// Add sound source
		player->AddComponent(new SoundSource());
		// Add player script
		player->AddComponent(new Player());
		player->GetComponent<Player>()->m_TextRenderer = text->GetComponent<TextRenderer>();		

		// Set coin components
		for (size_t i = 0; i < collectables.size(); i++)
		{
			collectables[i]->AddComponent(new SoundSource());
			collectables[i]->AddComponent(new Collectable());
			collectables[i]->GetComponent<Collectable>()->m_Player = player;
			collectables[i]->GetComponent<Collectable>()->m_CoinAudio = new AudioClip("sound/coin.ogg");
			collectables[i]->GetComponent<Collectable>()->m_PoopAudio = new AudioClip("sound/poop.ogg");
		}

		// Set text components
		// Add Text Renderer
		text->GetComponent<TextRenderer>()->SetText("Score: 0");
		text->GetComponent<TextRenderer>()->SetFont("fonts/Righteous.ttf");
		text->GetComponent<TextRenderer>()->SetColor(0.7f, 0.0f, 0.0f, 1.0f);
		text->GetComponent<TextRenderer>()->SetAnchor(Anchor::TOP_LEFT);
		// Set transform properties
		text->GetComponent<Transform>()->SetScale(0.002f, 0.002f);
		text->GetComponent<Transform>()->SetPosition(-1.0f, 1.0f);

		SetEventListener(this);
	}
	~AppleCollector()
	{
		delete viewport;
		delete background;
		delete ground;
		delete player;
		delete text;

		for (size_t i = 0; i < collectables.size(); i++)
			delete collectables[i];
	}

	void Update() override
	{
		background->Update();
		ground->Update();
		player->Update();
		text->Update();

		for (size_t i = 0; i < collectables.size(); i++)
			collectables[i]->Update();
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
	Text* text;

	std::vector<Sprite*> collectables;
};

int main()
{
	try
	{
		ApplicationConfig config;
		config.width = 600;
		config.height = 600;
		config.fullscreen = false;
		config.title = "Coin Collect Game";

		AppleCollector* game = new AppleCollector(config);
		game->Run();
		delete game;
	}
	catch (const std::exception& ex)
	{
		std::ofstream stream("ErrorLog.txt", std::ios::app);

		if (stream.is_open())
		{
			time_t currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			std::string currentTimeStr = std::string(ctime(&currentTime));
			stream << "[" << currentTimeStr.substr(0, currentTimeStr.size() - 1) << "] " << ex.what() << std::endl;
		}

		stream.close();
	}
}