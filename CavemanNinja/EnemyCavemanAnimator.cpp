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
	BasicAnimation* walk = new BasicAnimation(1024, 1024, 8, 8, 2.0f);
	walk->frames.push_back({ 0, 0 });
	walk->frames.push_back({ 1, 0 });
	walk->frames.push_back({ 2, 0 });
	walk->frames.push_back({ 3, 0 });

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
	StateSwitcher<Animation>* hitBackState = new StateSwitcher<Animation>(hitBack);
	StateSwitcher<Animation>* dieBackState = new StateSwitcher<Animation>(dieBack);
	StateSwitcher<Animation>* hitFrontState = new StateSwitcher<Animation>(hitFront);
	StateSwitcher<Animation>* dieFrontState = new StateSwitcher<Animation>(dieFront);

	// Crea las transiciones entre los estados
	walkState->AddStateTransition(new StateTransition<Animation>(hitBackState, new FlagEqualsCondition("hit_back", true)));
	walkState->AddStateTransition(new StateTransition<Animation>(hitFrontState, new FlagEqualsCondition("hit_front", true)));

	hitBackState->AddStateTransition(new StateTransition<Animation>(walkState, new FlagEqualsCondition("hit_back", false)));
	hitBackState->AddStateTransition(new StateTransition<Animation>(dieBackState, new FlagEqualsCondition("decaying", true)));

	hitFrontState->AddStateTransition(new StateTransition<Animation>(walkState, new FlagEqualsCondition("hit_front", false)));
	hitFrontState->AddStateTransition(new StateTransition<Animation>(dieFrontState, new FlagEqualsCondition("decaying", true)));

	// Crea y devuelve el animator
	return new EnemyCavemanAnimator(walkState);
}