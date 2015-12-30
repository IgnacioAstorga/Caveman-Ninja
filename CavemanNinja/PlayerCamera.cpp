#include "PlayerCamera.h"
#include "CameraComponent.h"
#include "RectangleColliderComponent.h"
#include "ColliderTypes.h"
#include "CameraMovementComponent.h"
#include "Player.h"

void PlayerCamera::OnCreate()
{
	// A�ade el componente de la c�mara
	AddComponent(new CameraComponent(SCREEN_WIDTH * SCREEN_SIZE, SCREEN_HEIGHT * SCREEN_SIZE, true));

	// A�ade la pared a la izquierda de la c�mara
	wall = new Entity("wall", 0, 0);
	wall->AddComponent(new RectangleColliderComponent(0, 1000, 0, 0, 0 , WALL));
	AddChild(wall);

	// A�ade el �rea de movimiento a la derecha de la pantalla
	AddComponent(new CameraMovementComponent());
}

void PlayerCamera::OnDestroy()
{
	// En principio no hace nada
}