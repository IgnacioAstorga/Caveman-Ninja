#include "FlyingDinosaurAnimator.h"
#include "StateSwitcher.h"
#include "BasicAnimation.h"
#include "StateTransition.h"
#include "FlagEqualsCondition.h"
#include "AnimationEndCondition.h"

FlyingDinosaurAnimator::FlyingDinosaurAnimator(AnimationState* initialState)
	: Animator(initialState) {}

FlyingDinosaurAnimator* FlyingDinosaurAnimator::Create()
{
	// Crea las animaciones del personaje
	BasicAnimation* fly = new BasicAnimation(512, 512, 4, 4, 8.0f);
	fly->frames.push_back({ 0, 0 });
	fly->frames.push_back({ 1, 0 });
	fly->frames.push_back({ 2, 0 });
	fly->frames.push_back({ 3, 0 });
	fly->frames.push_back({ 0, 1 });
	fly->frames.push_back({ 1, 1 });
	fly->frames.push_back({ 2, 1 });
	fly->frames.push_back({ 3, 1 });

	BasicAnimation* hit = new BasicAnimation(512, 512, 4, 4, 8.0f, false);
	hit->frames.push_back({ 0, 2 });
	hit->frames.push_back({ 1, 2 });
	hit->frames.push_back({ 2, 2 });
	hit->frames.push_back({ 3, 2 });

	BasicAnimation* die = new BasicAnimation(512, 512, 4, 4, 0.0f, false);
	die->frames.push_back({ 0, 3 });

	// Crea los estados del personaje
	AnimationState* flyState = new AnimationState(fly);
	AnimationState* hitState = new AnimationState(hit);
	AnimationState* dieState = new AnimationState(die);

	// Crea las transiciones entre los estados
	flyState->AddStateTransition(new AnimationTransition(hitState, new FlagEqualsCondition("hit_back", true)));
	flyState->AddStateTransition(new AnimationTransition(hitState, new FlagEqualsCondition("hit_front", true)));

	hitState->AddStateTransition(new AnimationTransition(dieState, new FlagEqualsCondition("decaying", true)));

	// Crea y devuelve el animator
	return new FlyingDinosaurAnimator(flyState);
}