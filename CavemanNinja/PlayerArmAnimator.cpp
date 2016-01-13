#include "PlayerArmAnimator.h"
#include "StateTransition.h"
#include "StateSwitcher.h"
#include "BasicAnimation.h"
#include "FlagEqualsCondition.h"
#include "AnimationEndCondition.h"

PlayerArmAnimator::PlayerArmAnimator(AnimationState* initialState)
	: Animator(initialState) {}

PlayerArmAnimator* PlayerArmAnimator::Create()
{
	// Crea las animaciones del personaje
	BasicAnimation* start = new BasicAnimation(192, 144, 4, 3, 16.0f, false);
	start->frames.push_back({ 0, 0 });
	start->frames.push_back({ 1, 0 });
	start->frames.push_back({ 2, 0 });
	start->frames.push_back({ 3, 0 });
	start->frames.push_back({ 0, 1 });
	start->frames.push_back({ 1, 1 });
	start->frames.push_back({ 2, 1 });
	start->frames.push_back({ 3, 1 });

	BasicAnimation* phase1 = new BasicAnimation(*start);
	phase1->speed = 24.0f;

	BasicAnimation* phase2 = new BasicAnimation(*start);
	phase2->speed = 32.0f;
	phase2->loop = true;

	BasicAnimation* charged = new BasicAnimation(192, 144, 4, 3, 8.0f);
	charged->frames.push_back({ 0, 2 });
	charged->frames.push_back({ 1, 2 });
	charged->frames.push_back({ 2, 2 });
	charged->frames.push_back({ 3, 2 });

	// Crea los estados del personaje
	AnimationState* startState = new AnimationState(start);
	AnimationState* phase1State = new AnimationState(phase1);
	AnimationState* phase2State = new AnimationState(phase2);
	AnimationState* chargedState = new AnimationState(charged);

	// Crea las transiciones entre los estados
	startState->AddStateTransition(new AnimationTransition(phase1State, new AnimationEndCondition()));
	startState->AddStateTransition(new AnimationTransition(chargedState, new FlagEqualsCondition("attack_charged", true)));

	phase1State->AddStateTransition(new AnimationTransition(phase2State, new AnimationEndCondition()));
	phase1State->AddStateTransition(new AnimationTransition(startState, new FlagEqualsCondition("charging", false)));
	phase1State->AddStateTransition(new AnimationTransition(chargedState, new FlagEqualsCondition("attack_charged", true)));

	phase2State->AddStateTransition(new AnimationTransition(startState, new FlagEqualsCondition("charging", false)));
	phase2State->AddStateTransition(new AnimationTransition(chargedState, new FlagEqualsCondition("attack_charged", true)));

	chargedState->AddStateTransition(new AnimationTransition(startState, new FlagEqualsCondition("charging", false)));
	chargedState->AddStateTransition(new AnimationTransition(startState, new FlagEqualsCondition("attack_charged", false)));

	// Crea y devuelve el animator
	return new PlayerArmAnimator(startState);
}