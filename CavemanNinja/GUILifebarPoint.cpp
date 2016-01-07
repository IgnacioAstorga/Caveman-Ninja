#include "GUILifebarPoint.h"
#include "GUISpriteRendererComponent.h"
#include "Animator.h"
#include "BasicAnimation.h"
#include "StateSwitcher.h"
#include "StateTransition.h"
#include "FlagEqualsCondition.h"
#include "GUILifebarComponent.h"

void GUILifebarPoint::OnCreate()
{
	// Crea las animaciones
	BasicAnimation* green = new BasicAnimation(0.0f, SDL_FLIP_NONE, false);
	green->frames.push_back({0, 0, 5, 12});

	BasicAnimation* yellow = new BasicAnimation(0.0f, SDL_FLIP_NONE, false);
	yellow->frames.push_back({ 4, 0, 5, 12 });

	BasicAnimation* red = new BasicAnimation(0.0f, SDL_FLIP_NONE, false);
	red->frames.push_back({ 8, 0, 5, 12 });

	BasicAnimation* empty = new BasicAnimation(0.0f, SDL_FLIP_NONE, false);
	empty->frames.push_back({ 12, 0, 5, 12 });

	// Crea los estados
	StateSwitcher<Animation>* greenState = new StateSwitcher<Animation>(green);
	StateSwitcher<Animation>* yellowState = new StateSwitcher<Animation>(yellow);
	StateSwitcher<Animation>* redState = new StateSwitcher<Animation>(red);
	StateSwitcher<Animation>* emptyState = new StateSwitcher<Animation>(empty);

	// Crea las transiciones entre estados
	greenState->AddStateTransition(new StateTransition<Animation>(yellowState, new FlagEqualsCondition("color", YELLOW)));
	greenState->AddStateTransition(new StateTransition<Animation>(redState, new FlagEqualsCondition("color", RED)));
	greenState->AddStateTransition(new StateTransition<Animation>(emptyState, new FlagEqualsCondition("color", EMPTY)));

	yellowState->AddStateTransition(new StateTransition<Animation>(greenState, new FlagEqualsCondition("color", GREEN)));
	yellowState->AddStateTransition(new StateTransition<Animation>(redState, new FlagEqualsCondition("color", RED)));
	yellowState->AddStateTransition(new StateTransition<Animation>(emptyState, new FlagEqualsCondition("color", EMPTY)));

	redState->AddStateTransition(new StateTransition<Animation>(greenState, new FlagEqualsCondition("color", GREEN)));
	redState->AddStateTransition(new StateTransition<Animation>(yellowState, new FlagEqualsCondition("color", YELLOW)));
	redState->AddStateTransition(new StateTransition<Animation>(emptyState, new FlagEqualsCondition("color", EMPTY)));

	emptyState->AddStateTransition(new StateTransition<Animation>(greenState, new FlagEqualsCondition("color", GREEN)));
	emptyState->AddStateTransition(new StateTransition<Animation>(yellowState, new FlagEqualsCondition("color", YELLOW)));
	emptyState->AddStateTransition(new StateTransition<Animation>(redState, new FlagEqualsCondition("color", RED)));

	// Crea el animator
	Animator* animator = new Animator(emptyState);

	// Crea los componentes de la entidad
	AddComponent(new GUISpriteRendererComponent("assets/images/gui_lifebar.png", animator, 0, 0, TOP_LEFT));
}

void GUILifebarPoint::OnDestroy()
{
	// En principio no hace nada
}
