#include "EggAnimator.h"
#include "StateSwitcher.h"
#include "BasicAnimation.h"
#include "NullAnimation.h"
#include "StateTransition.h"
#include "FlagEqualsCondition.h"
#include "AnimationEndCondition.h"

EggAnimator::EggAnimator(AnimationState* initialState)
	: Animator(initialState) {}

EggAnimator* EggAnimator::Create()
{
	// Crea las animaciones del personaje
	BasicAnimation* idle = new BasicAnimation(96, 64, 3, 2, 0.0f, false);
	idle->frames.push_back({ 0, 0 });

	BasicAnimation* die = new BasicAnimation(96, 64, 3, 2, 8.0f, false);
	die->frames.push_back({ 1, 0 });
	die->frames.push_back({ 2, 0 });
	die->frames.push_back({ 0, 1 });
	die->frames.push_back({ 1, 1 });

	NullAnimation* dissapear = new NullAnimation();

	// Crea los estados del personaje
	AnimationState* idleState = new AnimationState(idle);
	AnimationState* dieState = new AnimationState(die);
	AnimationState* dissapearState = new AnimationState(dissapear);

	// Crea las transiciones entre los estados
	idleState->AddStateTransition(new AnimationTransition(dieState, new FlagEqualsCondition("hit_back", true)));

	dieState->AddStateTransition(new AnimationTransition(dissapearState, new AnimationEndCondition()));

	// Crea y devuelve el animator
	return new EggAnimator(idleState);
}