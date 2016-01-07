#include "GUILifebarComponent.h"
#include "GameControllerComponent.h"
#include "Player.h"
#include "PlayerLifeComponent.h"
#include "Entity.h"
#include "GUILifebarPoint.h"
#include "GUISpriteRendererComponent.h"
#include "Animator.h"
#include "Application.h"
#include "ModuleTime.h"

GUILifebarComponent::GUILifebarComponent(float representedIncreaseSpeed)
{
	this->representedIncreaseSpeed = representedIncreaseSpeed;
}

GUILifebarComponent::~GUILifebarComponent()
{
	// En principio no hace nada
}

bool GUILifebarComponent::OnStart()
{
	// Obtiene la referencia a la vida del jugador
	lifeComponent = GameController->player->FindComponent<PlayerLifeComponent>();

	// Crea todos los puntos de vida del jugador
	for (int i = 0; i < lifeComponent->maxLifePoints; ++i)
	{
		GUILifebarPoint* point = new GUILifebarPoint("lifebar_point_" + i, i * 4.0f, 0.0f);
		point->Instantiate(entity);
		lifebarPoints.push_back(point);
	}

	// Establece los puntos de vida representados
	representedLifePoints = lifeComponent->currentLifePoints;

	return true;
}

bool GUILifebarComponent::OnCleanUp()
{
	// Destruye todos los puntos de vida del jugador
	for (unsigned int i = 0; i < lifebarPoints.size(); ++i)
		lifebarPoints[i]->Destroy();

	// Vacía el vector
	lifebarPoints.clear();

	return true;
}

bool GUILifebarComponent::OnPostUpdate()
{
	// Actualiza los puntos de vida representados
	if (representedLifePoints < lifeComponent->currentLifePoints)
	{
		representedLifePoints += representedIncreaseSpeed * App->time->DeltaTime();
		if (representedLifePoints > lifeComponent->currentLifePoints)
			representedLifePoints = (float) lifeComponent->currentLifePoints;
	}
	else if (representedLifePoints > lifeComponent->currentLifePoints)
	{
		representedLifePoints -= representedIncreaseSpeed * App->time->DeltaTime();
		if (representedLifePoints < lifeComponent->currentLifePoints)
			representedLifePoints = (float)lifeComponent->currentLifePoints;
	}

	// Determina el color de la barra de vida
	LifebarPointColor color;
	if(lifeComponent->currentLifePoints <= lifeComponent->maxLifePoints / 3)
		color = RED;
	else if (lifeComponent->currentLifePoints <= 2 * lifeComponent->maxLifePoints / 3)
		color = YELLOW;
	else
		color = GREEN;

	// Actualiza los animators de cada punto de vida de forma adecuada
	for (int i = 0; i < lifeComponent->maxLifePoints; ++i)
	{
		// Recupera el animator del punto de vida
		Animator* animator = dynamic_cast<Animator*>(lifebarPoints[i]->FindComponent<GUISpriteRendererComponent>()->GetAnimation());
		if (animator == NULL)
			return false;

		// Lo colorea de forma adecuada
		if (i < representedLifePoints)
			animator->SetFlagValue("color", color);
		else
			animator->SetFlagValue("color", EMPTY);
	}

	return true;
}
