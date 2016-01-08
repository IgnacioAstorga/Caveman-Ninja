#include "DinosaurEye.h"
#include "BasicAnimation.h"
#include "StateSwitcher.h"
#include "StateTransition.h"
#include "FlagEqualsCondition.h"
#include "AnimationEndCondition.h"
#include "Animator.h"
#include "SpriteRendererComponent.h"
#include "DinosaurEyeComponent.h"

void DinosaurEye::OnCreate()
{
	// Crea las animaciones del personaje
	BasicAnimation* idle = new BasicAnimation(192, 96, 4, 2, 0.0f, false);
	idle->frames.push_back({ 0, 0 });

	BasicAnimation* startLooking = new BasicAnimation(192, 96, 4, 2, 4.0f, false);
	startLooking->frames.push_back({ 1, 0 });
	startLooking->frames.push_back({ 2, 0 });

	BasicAnimation* looking = new BasicAnimation(192, 96, 4, 2, 4.0f);
	looking->frames.push_back({ 3, 0 });
	looking->frames.push_back({ 0, 1 });
	looking->frames.push_back({ 1, 1 });
	looking->frames.push_back({ 2, 1 });
	looking->frames.push_back({ 3, 1 });
	looking->frames.push_back({ 2, 1 });
	looking->frames.push_back({ 1, 1 });
	looking->frames.push_back({ 0, 1 });

	// Crea los estados del personaje
	StateSwitcher<Animation>* idleState = new StateSwitcher<Animation>(idle);
	StateSwitcher<Animation>* startLookingState = new StateSwitcher<Animation>(startLooking);
	StateSwitcher<Animation>* lookingState = new StateSwitcher<Animation>(looking);

	// Crea las transiciones entre los estados
	idleState->AddStateTransition(new StateTransition<Animation>(startLookingState, new FlagEqualsCondition("player_in_sight", true)));

	startLookingState->AddStateTransition(new StateTransition<Animation>(lookingState, new AnimationEndCondition()));

	// Crea el animator
	Animator* animator = new Animator(idleState);

	// Crea las componentes
	AddComponent(new SpriteRendererComponent("assets/images/dinosaur_eye.png", animator));
	AddComponent(new DinosaurEyeComponent());
}

void DinosaurEye::OnDestroy()
{
	// En principio no hace nada
}