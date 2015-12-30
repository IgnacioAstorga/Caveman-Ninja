#include "CameraMovementComponent.h"
#include "Player.h"
#include "Transform.h"

CameraMovementComponent::CameraMovementComponent()
{
	// En principio no hace nada
}

CameraMovementComponent::~CameraMovementComponent()
{
	// En principio no hace nada
}

bool CameraMovementComponent::OnStart()
{
	// Recupera el jugador
	player = entity->GetParent()->FindChild<Player>();
	return player != NULL;
}

bool CameraMovementComponent::OnUpdate()
{
	// Si el jugador se encuentra más avanzado que la mitad de la cámara...
	if (player->transform->GetGlobalPosition().x >= entity->transform->GetGlobalPosition().x + SCREEN_WIDTH / 2)
		// Mueve la cámara a la posición del jugador
		entity->transform->SetGlobalPosition(player->transform->GetGlobalPosition().x - SCREEN_WIDTH / 2, entity->transform->GetGlobalPosition().y);

	return true;
}
