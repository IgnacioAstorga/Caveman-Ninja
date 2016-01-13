#include "ThrowerThrowStartAIBehaviour.h"
#include "ThrowerAIManager.h"
#include "Entity.h"
#include "Transform.h"
#include "SpriteRendererComponent.h"
#include "Animator.h"

ThrowerThrowStartAIBehaviour::ThrowerThrowStartAIBehaviour()
	: AIBehaviour(THROW_START) {}

ThrowerThrowStartAIBehaviour::~ThrowerThrowStartAIBehaviour()
{
	// No hace nada
}

void ThrowerThrowStartAIBehaviour::OnEnter()
{
	// Recupera el animator de la entidad
	animator = dynamic_cast<Animator*>(entity->FindComponent<SpriteRendererComponent>()->GetAnimation());

	// Detiene al personaje mientras ataca
	entity->transform->speed.x = 0.0f;
}

void ThrowerThrowStartAIBehaviour::OnTick()
{
	if (animator == NULL)
		return;

	// Si la animación ha acabado, completa el lanzamiento
	if (animator->IsFinished())
		manager->SetFlagValue(STATE, THROW_DO);
}

void ThrowerThrowStartAIBehaviour::OnExit()
{
	// No hace nada
}
