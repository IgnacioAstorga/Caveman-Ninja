#include "EnemyCavemanAnimator.h"
#include "StateSwitcher.h"
#include "BasicAnimation.h"
#include "StateTransition.h"
#include "FlagEqualsCondition.h"
#include "CavemanAIManager.h"

EnemyCavemanAnimator::EnemyCavemanAnimator(AnimationState* initialState)
	: Animator(initialState) {}

EnemyCavemanAnimator* EnemyCavemanAnimator::Create()
{
	// Crea las animaciones del personaje
	BasicAnimation* walk = new BasicAnimation(1024, 1024, 8, 8, 4.0f);
	walk->frames.push_back({ 0, 0 });
	walk->frames.push_back({ 1, 0 });
	walk->frames.push_back({ 2, 0 });
	walk->frames.push_back({ 3, 0 });

	BasicAnimation* search = new BasicAnimation(1024, 1024, 8, 8, 4.0f);
	search->frames.push_back({ 0, 0 });
	search->frames.push_back({ 2, 3 });
	search->frames.push_back({ 3, 3 });
	search->frames.push_back({ 2, 3 });

	BasicAnimation* charge = new BasicAnimation(1024, 1024, 8, 8, 8.0f);
	charge->frames.push_back({ 0, 1 });
	charge->frames.push_back({ 1, 1 });
	charge->frames.push_back({ 2, 1 });
	charge->frames.push_back({ 3, 1 });

	BasicAnimation* attack = new BasicAnimation(1024, 1024, 8, 8, 8.0f, false);
	attack->frames.push_back({ 0, 2 });
	attack->frames.push_back({ 1, 2 });
	attack->frames.push_back({ 2, 2 });

	BasicAnimation* runStart = new BasicAnimation(1024, 1024, 8, 8, 8.0f);
	runStart->frames.push_back({ 0, 5 });
	runStart->frames.push_back({ 1, 5 });
	runStart->frames.push_back({ 2, 5 });
	runStart->frames.push_back({ 1, 5 });

	BasicAnimation* run = new BasicAnimation(1024, 1024, 8, 8, 8.0f);
	run->frames.push_back({ 3, 5 });
	run->frames.push_back({ 4, 5 });
	run->frames.push_back({ 5, 5 });
	run->frames.push_back({ 6, 5 });
	run->frames.push_back({ 7, 5 });

	BasicAnimation* hitBack = new BasicAnimation(1024, 1024, 8, 8, 0.0f, false);
	hitBack->frames.push_back({ 4, 4 });

	BasicAnimation* dieBack = new BasicAnimation(1024, 1024, 8, 8, 4.0f, false);
	dieBack->frames.push_back({ 4, 4 });
	dieBack->frames.push_back({ 5, 4 });
	dieBack->frames.push_back({ 6, 4 });
	dieBack->frames.push_back({ 7, 4 });

	BasicAnimation* hitFront = new BasicAnimation(1024, 1024, 8, 8, 0.0f, false);
	hitFront->frames.push_back({ 4, 3 });

	BasicAnimation* dieFront = new BasicAnimation(1024, 1024, 8, 8, 4.0f, false);
	dieFront->frames.push_back({ 4, 3 });
	dieFront->frames.push_back({ 5, 3 });
	dieFront->frames.push_back({ 6, 3 });
	dieFront->frames.push_back({ 7, 3 });

	// Crea los estados del personaje
	AnimationState* walkState = new AnimationState(walk);
	AnimationState* searchState = new AnimationState(search);
	AnimationState* chargeState = new AnimationState(charge);
	AnimationState* attackState = new AnimationState(attack);
	AnimationState* runStartState = new AnimationState(runStart);
	AnimationState* runState = new AnimationState(run);
	AnimationState* hitBackState = new AnimationState(hitBack);
	AnimationState* dieBackState = new AnimationState(dieBack);
	AnimationState* hitFrontState = new AnimationState(hitFront);
	AnimationState* dieFrontState = new AnimationState(dieFront);

	// Crea las transiciones entre los estados
	walkState->AddStateTransition(new AnimationTransition(searchState, new FlagEqualsCondition("AI_state", SEARCH)));
	walkState->AddStateTransition(new AnimationTransition(hitBackState, new FlagEqualsCondition("hit_back", true)));
	walkState->AddStateTransition(new AnimationTransition(hitFrontState, new FlagEqualsCondition("hit_front", true)));

	searchState->AddStateTransition(new AnimationTransition(walkState, new FlagEqualsCondition("AI_state", IDLE)));
	searchState->AddStateTransition(new AnimationTransition(chargeState, new FlagEqualsCondition("AI_state", CHARGE)));
	searchState->AddStateTransition(new AnimationTransition(hitBackState, new FlagEqualsCondition("hit_back", true)));
	searchState->AddStateTransition(new AnimationTransition(hitFrontState, new FlagEqualsCondition("hit_front", true)));

	chargeState->AddStateTransition(new AnimationTransition(searchState, new FlagEqualsCondition("AI_state", SEARCH)));
	chargeState->AddStateTransition(new AnimationTransition(attackState, new FlagEqualsCondition("AI_state", ATTACK)));
	chargeState->AddStateTransition(new AnimationTransition(hitBackState, new FlagEqualsCondition("hit_back", true)));
	chargeState->AddStateTransition(new AnimationTransition(hitFrontState, new FlagEqualsCondition("hit_front", true)));

	attackState->AddStateTransition(new AnimationTransition(runStartState, new FlagEqualsCondition("AI_state", RUN_START)));
	attackState->AddStateTransition(new AnimationTransition(hitBackState, new FlagEqualsCondition("hit_back", true)));
	attackState->AddStateTransition(new AnimationTransition(hitFrontState, new FlagEqualsCondition("hit_front", true)));

	runStartState->AddStateTransition(new AnimationTransition(runState, new FlagEqualsCondition("AI_state", RUN)));
	runStartState->AddStateTransition(new AnimationTransition(hitBackState, new FlagEqualsCondition("hit_back", true)));
	runStartState->AddStateTransition(new AnimationTransition(hitFrontState, new FlagEqualsCondition("hit_front", true)));

	runState->AddStateTransition(new AnimationTransition(hitBackState, new FlagEqualsCondition("hit_back", true)));
	runState->AddStateTransition(new AnimationTransition(hitFrontState, new FlagEqualsCondition("hit_front", true)));

	hitBackState->AddStateTransition(new AnimationTransition(walkState, new FlagEqualsCondition("hit_back", false)));
	hitBackState->AddStateTransition(new AnimationTransition(dieBackState, new FlagEqualsCondition("decaying", true)));

	hitFrontState->AddStateTransition(new AnimationTransition(walkState, new FlagEqualsCondition("hit_front", false)));
	hitFrontState->AddStateTransition(new AnimationTransition(dieFrontState, new FlagEqualsCondition("decaying", true)));

	// Crea y devuelve el animator
	return new EnemyCavemanAnimator(walkState);
}