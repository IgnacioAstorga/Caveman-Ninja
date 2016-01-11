#include "Scene_Level1.h"
#include "CameraComponent.h"
#include "SpriteRendererComponent.h"
#include "RectangleColliderComponent.h"
#include "LineColliderComponent.h"
#include "GameControllerComponent.h"
#include "ColliderTypes.h"
#include "Player.h"
#include "PlayerCamera.h"
#include "EnemyCaveman.h"
#include "UserInterfaceComponent.h"
#include "DinosaurEye.h"

void Scene_Level1::OnCreateScene()
{
	backgroundSky = new Entity("background_sky");
	backgroundSky->AddComponent(new SpriteRendererComponent("assets/images/world_1_background_sky.png",
		NULL, 0.0f, 0.0f, 0.0f, 0.4f, true, true));
	AddChild(backgroundSky);

	backgroundMountains = new Entity("background_mountains");
	backgroundMountains->AddComponent(new SpriteRendererComponent("assets/images/world_1_background_mountains.png",
		NULL, 0.0f, 0.0f, 0.0f, 0.6f, true, true));
	AddChild(backgroundMountains);

	backgroundTrees = new Entity("background_trees");
	backgroundTrees->AddComponent(new SpriteRendererComponent("assets/images/world_1_background_trees.png",
		NULL, 0.0f, 114.0f, 0.0f, 0.8f, true, false));
	AddChild(backgroundTrees);

	ground = new Entity("ground");
	ground->AddComponent(new SpriteRendererComponent("assets/images/world_1_background.png"));
	ground->AddComponent(new RectangleColliderComponent(4000, 10, { PLAYER, PLAYER_ATTACK, ENEMY }, 0, 225, 0, FLOOR, true));
	ground->AddComponent(new LineColliderComponent(	// El lomo
	{ 
		fPoint(290, 211),
		fPoint(340, 195),
		fPoint(443, 149),
		fPoint(487, 113),
		fPoint(512, 94),
		fPoint(544, 83),
		fPoint(578, 83),
		fPoint(616, 98),
		fPoint(664, 136),
		fPoint(700, 150),
		fPoint(708, 146),
		fPoint(741, 148),
		fPoint(756, 164),
		fPoint(781, 180),
		fPoint(798, 191)
	}, 1, { PLAYER, ENEMY }, GROUND));
	ground->AddComponent(new LineColliderComponent(	// La pata trasera
	{
		fPoint(520, 129),
		fPoint(550, 115),
		fPoint(562, 115),
		fPoint(576, 124),
		fPoint(587, 145)
	}, 1, { PLAYER, ENEMY }, GROUND));
	ground->AddComponent(new LineColliderComponent(	// La pata delantera
	{
		fPoint(640, 176),
		fPoint(648, 173),
		fPoint(656, 181)
	}, 1, { PLAYER, ENEMY }, GROUND));
	AddChild(ground);

	dinosaurEye = new DinosaurEye("dinosaur_eye", 720, 141);
	ground->AddChild(dinosaurEye);


	player = new Player("player_1", 20, 190);
	AddChild(player);

	camera = new PlayerCamera("camera");
	AddChild(camera);

	gui = new Entity("gui", 0, 0);
	gui->AddComponent(new UserInterfaceComponent());
	AddChild(gui);

	gameController = new Entity("game_controller", 100, 100);
	gameController->AddComponent(new GameControllerComponent());
	AddChild(gameController);

	for (int i = 0; i < 4; ++i)
	{
		EnemyCaveman* enemy = new EnemyCaveman("caveman_" + i, 300.0f + 100.0f * i, 0);
		AddChild(enemy);
	}
}

void Scene_Level1::OnDestroyScene()
{
	// En principio no hace nada
}