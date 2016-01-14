#include "SpawnEntityOnEnterCameraComponent.h"
#include "Entity.h"
#include "Transform.h"
#include "Application.h"
#include "ModuleRender.h"
#include "Camera.h"

SpawnEntityOnEnterCameraComponent::SpawnEntityOnEnterCameraComponent(Entity * spawnedEntity)
{
	this->spawnedEntity = spawnedEntity;
}

SpawnEntityOnEnterCameraComponent::~SpawnEntityOnEnterCameraComponent()
{
	// Si la entidad no ha sido spawneada, la elimina
	if (!spawned)
		RELEASE(spawnedEntity);
}

bool SpawnEntityOnEnterCameraComponent::OnUpdate()
{
	if (!spawned)
	{
		fPoint position = entity->transform->GetGlobalPosition();
		if (App->renderer->GetActiveCamera()->Contains(position))
		{
			spawnedEntity->transform->SetGlobalPosition(position.x, position.y);
			spawnedEntity->Instantiate();
			spawned = true;
			this->Disable();
		}
	}
	return true;
}
