#include "GUIPortrait.h"
#include "GUISpriteRendererComponent.h"
#include "Animator.h"
#include "BasicAnimation.h"
#include "StateSwitcher.h"
#include "StateTransition.h"
#include "FlagEqualsCondition.h"
#include "GUIPortraitComponent.h"

void GUIPortrait::OnCreate()
{
	// Crea las animaciones
	BasicAnimation* idle = new BasicAnimation(0.0f, SDL_FLIP_NONE, false);
	idle->frames.push_back({ 0, 0, 24, 28 });

	BasicAnimation* hit = new BasicAnimation(0.0f, SDL_FLIP_NONE, false);
	hit->frames.push_back({ 0, 28, 24, 28 });

	BasicAnimation* dead = new BasicAnimation(0.0f, SDL_FLIP_NONE, false);
	dead->frames.push_back({ 24, 28, 24, 28 });

	// Crea los estados
	StateSwitcher<Animation>* idleState = new StateSwitcher<Animation>(idle);
	StateSwitcher<Animation>* hitState = new StateSwitcher<Animation>(hit);
	StateSwitcher<Animation>* deadState = new StateSwitcher<Animation>(dead);

	// Crea las transiciones entre estados
	idleState->AddStateTransition(new StateTransition<Animation>(hitState, new FlagEqualsCondition("player_status", HIT)));
	idleState->AddStateTransition(new StateTransition<Animation>(deadState, new FlagEqualsCondition("player_status", DEAD)));

	hitState->AddStateTransition(new StateTransition<Animation>(idleState, new FlagEqualsCondition("player_status", IDLE)));
	hitState->AddStateTransition(new StateTransition<Animation>(deadState, new FlagEqualsCondition("player_status", DEAD)));

	deadState->AddStateTransition(new StateTransition<Animation>(idleState, new FlagEqualsCondition("player_status", IDLE)));
	deadState->AddStateTransition(new StateTransition<Animation>(hitState, new FlagEqualsCondition("player_status", HIT)));

	// Crea el animator
	Animator* animator = new Animator(idleState);

	// Crea los componentes de la entidad
	AddComponent(new GUISpriteRendererComponent("assets/images/gui_portrait.png", animator, 0, 0, TOP_LEFT));
	AddComponent(new GUIPortraitComponent());
}

void GUIPortrait::OnDestroy()
{
	// En principio no hace nada
}