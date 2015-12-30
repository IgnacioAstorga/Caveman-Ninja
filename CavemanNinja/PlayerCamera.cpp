#include "PlayerCamera.h"
#include "CameraComponent.h"
#include "RectangleColliderComponent.h"
#include "ColliderTypes.h"
#include "CameraMovementComponent.h"
#include "Player.h"

void PlayerCamera::OnCreate()
{
	// Añade el componente de la cámara
	AddComponent(new CameraComponent(SCREEN_WIDTH * SCREEN_SIZE, SCREEN_HEIGHT * SCREEN_SIZE, true));

	// Añade la pared a la izquierda de la cámara
	wall = new Entity("wall", 0, 0);
	wall->AddComponent(new RectangleColliderComponent(0, 1000, 0, 0, 0 , WALL));
	AddChild(wall);

	// Añade el área de movimiento a la derecha de la pantalla
	AddComponent(new CameraMovementComponent());
}

void PlayerCamera::OnDestroy()
{
	// En principio no hace nada
}