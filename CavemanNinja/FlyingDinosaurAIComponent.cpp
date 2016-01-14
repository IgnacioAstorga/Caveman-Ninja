#include "FlyingDinosaurAIComponent.h"
#include "Entity.h"
#include "EnemyGravityComponent.h"
#include "DieOnPlayerAttackComponent.h"
#include "EntityLifetimeComponent.h"
#include "Transform.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTime.h"
#include "Camera.h"

#define DISTANCE_TOLERANCE 10.0f
#define SCAPE_SPEED -150.0f

FlyingDinosaurAIComponent::FlyingDinosaurAIComponent(float horizontalSpeed, float acceleration, int numberOfPasses)
{
	this->horizontalSpeed = horizontalSpeed;
	this->acceleration = acceleration;
	this->numberOfPasses = numberOfPasses;
}

FlyingDinosaurAIComponent::~FlyingDinosaurAIComponent()
{
	// En principio no hace nada
}

bool FlyingDinosaurAIComponent::OnStart()
{
	// Recupera y desactiva el componente de gravedad de la entidad
	gravityComponent = entity->FindComponent<EnemyGravityComponent>();
	if (gravityComponent == NULL)
		return false;
	gravityComponent->Disable();

	// Recupera y desactiva el componente de tiempo de vida de la entidad
	lifetimeComponent = entity->FindComponent<EntityLifetimeComponent>();
	if (lifetimeComponent == NULL)
		return false;
	lifetimeComponent->Disable();

	// Recupera el componente de vida de la entidad
	lifeComponent = entity->FindComponent<DieOnPlayerAttackComponent>();
	if (lifeComponent == NULL)
		return false;

	// Establece los flags
	movingRight = false;
	passCount = 0;

	return true;
}

bool FlyingDinosaurAIComponent::OnUpdate()
{
	// Si está muerto, desactiva el componente, activa la gravedad y sale
	if (lifeComponent->dead)
	{
		this->Disable();
		gravityComponent->Enable();
		return true;
	}

	// Comprueba si ha llegado a su destino
	if (entity->transform->GetGlobalPosition().DistanceTo(targetPosition) <= DISTANCE_TOLERANCE)
	{
		movingRight = !movingRight;
		passCount += 1;
		if (passCount >= numberOfPasses)
		{
			// Desactiva el componente, hace volar al personaje hacia arriba y activa el componente de lifetime
			this->Disable();
			lifetimeComponent->Enable();
			entity->transform->speed.y = SCAPE_SPEED;
			return true;
		}
	}

	// Establece su posición objetivo
	SDL_Rect viewArea = App->renderer->GetActiveCamera()->GetViewArea();
	float offsetX;
	if (movingRight)
		offsetX = ((float) viewArea.w) / SCREEN_SIZE - acceleration;	// Chapuza: No debería tener que calcular esto
	else
		offsetX = acceleration;
	targetPosition = fPoint(viewArea.x + offsetX, entity->transform->GetGlobalPosition().y);

	// Establece su velocidad
	if (movingRight)
	{
		entity->transform->speed.x += acceleration * App->time->DeltaTime();
		if (entity->transform->speed.x > horizontalSpeed)
			entity->transform->speed.x = horizontalSpeed;
	}
	else
	{
		entity->transform->speed.x -= acceleration * App->time->DeltaTime();
		if (entity->transform->speed.x < -horizontalSpeed)
			entity->transform->speed.x = -horizontalSpeed;
	}

	return true;
}
