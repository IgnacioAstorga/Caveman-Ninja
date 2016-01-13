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
	BasicAnimation* idle = new BasicAnimation(72, 84, 3, 3, 0.0f, false);
	idle->frames.push_back({ 0, 0 });

	BasicAnimation* hit = new BasicAnimation(72, 84, 3, 3, 0.0f, false);
	hit->frames.push_back({ 0, 1 });

	BasicAnimation* dead = new BasicAnimation(72, 84, 3, 3, 0.0f, false);
	dead->frames.push_back({ 1, 1 });

	// Crea los estados
	AnimationState* idleState = new AnimationState(idle);
	AnimationState* hitState = new AnimationState(hit);
	AnimationState* deadState = new AnimationState(dead);

	// Crea las transiciones entre estados
	idleState->AddStateTransition(new AnimationTransition(hitState, new FlagEqualsCondition("player_status", HIT)));
	idleState->AddStateTransition(new AnimationTransition(deadState, new FlagEqualsCondition("player_status", DEAD)));

	hitState->AddStateTransition(new AnimationTransition(idleState, new FlagEqualsCondition("player_status", IDLE)));
	hitState->AddStateTransition(new AnimationTransition(deadState, new FlagEqualsCondition("player_status", DEAD)));

	deadState->AddStateTransition(new AnimationTransition(idleState, new FlagEqualsCondition("player_status", IDLE)));
	deadState->AddStateTransition(new AnimationTransition(hitState, new FlagEqualsCondition("player_status", HIT)));

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