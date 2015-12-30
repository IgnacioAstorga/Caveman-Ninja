#include "Scene_Level1.h"
#include "CameraComponent.h"
#include "SpriteRendererComponent.h"
#include "RectangleColliderComponent.h"
#include "LineColliderComponent.h"
#include "ColliderTypes.h"
#include "Player.h"

void Scene_Level1::OnCreateScene()
{
	ground = new Entity("ground");
	ground->AddComponent(new SpriteRendererComponent("assets/images/world_1_background.png"));
	ground->AddComponent(new RectangleColliderComponent(2000, 0, 0, 220, 0, GROUND));
	ground->AddComponent(new LineColliderComponent(
	{ 
		fPoint(297, 210),
		fPoint(340, 195),
		fPoint(443, 149),
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
	}, 0, GROUND));
	AddChild(ground);

	player = new Player("player_1", 20, 190);
	AddChild(player);

	camera = new Entity("camera");
	camera->AddComponent(new CameraComponent(SCREEN_WIDTH * SCREEN_SIZE, SCREEN_HEIGHT * SCREEN_SIZE, true));
	camera->transform->SetPosition(-100, -100);
	player->AddChild(camera);
}

void Scene_Level1::OnDestroyScene()
{
	// En principio no hace nada
}