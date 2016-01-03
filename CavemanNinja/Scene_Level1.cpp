#include "Scene_Level1.h"
#include "CameraComponent.h"
#include "SpriteRendererComponent.h"
#include "RectangleColliderComponent.h"
#include "LineColliderComponent.h"
#include "GameControllerComponent.h"
#include "ColliderTypes.h"
#include "Player.h"
#include "PlayerCamera.h"

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
	ground->AddComponent(new RectangleColliderComponent(2000, 0, 1, 220 - 14, 0, GROUND));
	ground->AddComponent(new LineColliderComponent(	// El lomo
	{ 
		fPoint(328, 200),
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
	}, 1, GROUND));
	ground->AddComponent(new LineColliderComponent(	// La pata trasera
	{
		fPoint(520, 119),
		fPoint(550, 105),
		fPoint(562, 105),
		fPoint(576, 114),
		fPoint(587, 135)
	}, 1, GROUND));
	ground->AddComponent(new LineColliderComponent(	// La pata delantera
	{
		fPoint(640, 166),
		fPoint(648, 163),
		fPoint(656, 171)
	}, 1, GROUND));
	AddChild(ground);

	player = new Player("player_1", 20, 190);
	AddChild(player);

	camera = new PlayerCamera("camera");
	AddChild(camera);

	gameController = new Entity("game_controller");
	gameController->AddComponent(new GameControllerComponent());
	AddChild(gameController);
}

void Scene_Level1::OnDestroyScene()
{
	// En principio no hace nada
}