#include "EnemyCavemanAnimator.h"
#include "StateSwitcher.h"
#include "BasicAnimation.h"
#include "StateTransition.h"
#include "FlagEqualsCondition.h"

EnemyCavemanAnimator::EnemyCavemanAnimator(StateSwitcher<Animation>* initialState)
	: Animator(initialState) {}

EnemyCavemanAnimator* EnemyCavemanAnimator::Create()
{
	// Crea las animaciones del personaje
	BasicAnimation* walk = new BasicAnimation(2.0f);
	walk->frames.push_back({ 0, 0, 128, 128 });
	walk->frames.push_back({ 128, 0, 128, 128 });
	walk->frames.push_back({ 256, 0, 128, 128 });
	walk->frames.push_back({ 384, 0, 128, 128 });

	BasicAnimation* flyDead = new BasicAnimation(0.0f);
	flyDead->frames.push_back({ 512, 384, 128, 128 });

	BasicAnimation* decay = new BasicAnimation(4.0f, SDL_FLIP_NONE, false);
	decay->frames.push_back({ 640, 384, 128, 128 });
	decay->frames.push_back({ 768, 384, 128, 128 });
	decay->frames.push_back({ 896, 384, 128, 128 });

	// Crea los estados del personaje
	StateSwitcher<Animation>* walkState = new StateSwitcher<Animation>(walk);
	StateSwitcher<Animation>* flyDeadState = new StateSwitcher<Animation>(flyDead);
	StateSwitcher<Animation>* decayState = new StateSwitcher<Animation>(decay);

	// Crea las transiciones entre los estados
	walkState->AddStateTransition(new StateTransition<Animation>(flyDeadState, new FlagEqualsCondition("dead", true)));

	flyDeadState->AddStateTransition(new StateTransition<Animation>(decayState, new FlagEqualsCondition("decaying", true)));

	// Crea y devuelve el animator
	return new EnemyCavemanAnimator(walkState);
}