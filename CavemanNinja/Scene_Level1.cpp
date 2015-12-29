#include "Scene_Level1.h"
#include "CameraComponent.h"
#include "SpriteRendererComponent.h"
#include "RectangleColliderComponent.h"
#include "ColliderTypes.h"
#include "Player.h"

void Scene_Level1::OnCreateScene()
{
	camera = new Entity("camera");
	camera->AddComponent(new CameraComponent(SCREEN_WIDTH * SCREEN_SIZE, SCREEN_HEIGHT * SCREEN_SIZE, true));
	AddChild(camera);

	ground = new Entity("ground");
	ground->AddComponent(new SpriteRendererComponent("assets/images/world_1_background.png"));
	ground->AddComponent(new RectangleColliderComponent(100, 5, 0, 220, 0, GROUND));
	AddChild(ground);

	player = new Player("player_1", 20, 190);
	AddChild(player);
}

void Scene_Level1::OnDestroyScene()
{
	// En principio no hace nada
}