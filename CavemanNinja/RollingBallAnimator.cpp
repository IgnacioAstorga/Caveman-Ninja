#include "RollingBallAnimator.h"
#include "StateSwitcher.h"
#include "BasicAnimation.h"
#include "NullAnimation.h"
#include "StateTransition.h"
#include "FlagEqualsCondition.h"
#include "AnimationEndCondition.h"

RollingBallAnimator::RollingBallAnimator(AnimationState* initialState)
	: Animator(initialState) {}

RollingBallAnimator* RollingBallAnimator::Create()
{
	// Crea las animaciones del personaje
	BasicAnimation* roll = new BasicAnimation(192, 96, 4, 2, 8.0f);
	roll->frames.push_back({ 0, 0 });
	roll->frames.push_back({ 1, 0 });
	roll->frames.push_back({ 2, 0 });
	roll->frames.push_back({ 3, 0 });

	BasicAnimation* die = new BasicAnimation(192, 96, 4, 2, 8.0f, false);
	die->frames.push_back({ 0, 1 });
	die->frames.push_back({ 1, 1 });
	die->frames.push_back({ 2, 1 });
	die->frames.push_back({ 3, 1 });

	NullAnimation* dissapear = new NullAnimation();

	// Crea los estados del personaje
	AnimationState* rollState = new AnimationState(roll);
	AnimationState* dieState = new AnimationState(die);
	AnimationState* dissapearState = new AnimationState(dissapear);

	// Crea las transiciones entre los estados
	rollState->AddStateTransition(new AnimationTransition(dieState, new FlagEqualsCondition("decaying", true)));

	dieState->AddStateTransition(new AnimationTransition(dissapearState, new AnimationEndCondition()));

	// Crea y devuelve el animator
	return new RollingBallAnimator(rollState);
}