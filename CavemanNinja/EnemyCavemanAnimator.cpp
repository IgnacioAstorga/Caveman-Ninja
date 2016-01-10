#include "EnemyCavemanAnimator.h"
#include "StateSwitcher.h"
#include "BasicAnimation.h"
#include "StateTransition.h"
#include "FlagEqualsCondition.h"
#include "AICavemanComponent.h"

EnemyCavemanAnimator::EnemyCavemanAnimator(StateSwitcher<Animation>* initialState)
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
	StateSwitcher<Animation>* walkState = new StateSwitcher<Animation>(walk);
	StateSwitcher<Animation>* searchState = new StateSwitcher<Animation>(search);
	StateSwitcher<Animation>* chargeState = new StateSwitcher<Animation>(charge);
	StateSwitcher<Animation>* attackState = new StateSwitcher<Animation>(attack);
	StateSwitcher<Animation>* runStartState = new StateSwitcher<Animation>(runStart);
	StateSwitcher<Animation>* runState = new StateSwitcher<Animation>(run);
	StateSwitcher<Animation>* hitBackState = new StateSwitcher<Animation>(hitBack);
	StateSwitcher<Animation>* dieBackState = new StateSwitcher<Animation>(dieBack);
	StateSwitcher<Animation>* hitFrontState = new StateSwitcher<Animation>(hitFront);
	StateSwitcher<Animation>* dieFrontState = new StateSwitcher<Animation>(dieFront);

	// Crea las transiciones entre los estados
	walkState->AddStateTransition(new StateTransition<Animation>(searchState, new FlagEqualsCondition("AI_state", SEARCH)));
	walkState->AddStateTransition(new StateTransition<Animation>(hitBackState, new FlagEqualsCondition("hit_back", true)));
	walkState->AddStateTransition(new StateTransition<Animation>(hitFrontState, new FlagEqualsCondition("hit_front", true)));

	searchState->AddStateTransition(new StateTransition<Animation>(walkState, new FlagEqualsCondition("AI_state", IDLE)));
	searchState->AddStateTransition(new StateTransition<Animation>(chargeState, new FlagEqualsCondition("AI_state", CHARGE)));
	searchState->AddStateTransition(new StateTransition<Animation>(hitBackState, new FlagEqualsCondition("hit_back", true)));
	searchState->AddStateTransition(new StateTransition<Animation>(hitFrontState, new FlagEqualsCondition("hit_front", true)));

	chargeState->AddStateTransition(new StateTransition<Animation>(searchState, new FlagEqualsCondition("AI_state", SEARCH)));
	chargeState->AddStateTransition(new StateTransition<Animation>(attackState, new FlagEqualsCondition("AI_state", ATTACK)));
	chargeState->AddStateTransition(new StateTransition<Animation>(hitBackState, new FlagEqualsCondition("hit_back", true)));
	chargeState->AddStateTransition(new StateTransition<Animation>(hitFrontState, new FlagEqualsCondition("hit_front", true)));

	attackState->AddStateTransition(new StateTransition<Animation>(runStartState, new FlagEqualsCondition("AI_state", START_RUN)));
	attackState->AddStateTransition(new StateTransition<Animation>(hitBackState, new FlagEqualsCondition("hit_back", true)));
	attackState->AddStateTransition(new StateTransition<Animation>(hitFrontState, new FlagEqualsCondition("hit_front", true)));

	runStartState->AddStateTransition(new StateTransition<Animation>(runState, new FlagEqualsCondition("AI_state", RUN)));
	runStartState->AddStateTransition(new StateTransition<Animation>(hitBackState, new FlagEqualsCondition("hit_back", true)));
	runStartState->AddStateTransition(new StateTransition<Animation>(hitFrontState, new FlagEqualsCondition("hit_front", true)));

	hitBackState->AddStateTransition(new StateTransition<Animation>(walkState, new FlagEqualsCondition("hit_back", false)));
	hitBackState->AddStateTransition(new StateTransition<Animation>(dieBackState, new FlagEqualsCondition("decaying", true)));

	hitFrontState->AddStateTransition(new StateTransition<Animation>(walkState, new FlagEqualsCondition("hit_front", false)));
	hitFrontState->AddStateTransition(new StateTransition<Animation>(dieFrontState, new FlagEqualsCondition("decaying", true)));

	// Crea y devuelve el animator
	return new EnemyCavemanAnimator(walkState);
}