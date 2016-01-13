#include "EnemyThrowerAnimator.h"
#include "StateSwitcher.h"
#include "BasicAnimation.h"
#include "StateTransition.h"
#include "FlagEqualsCondition.h"
#include "ThrowerAIManager.h"

EnemyThrowerAnimator::EnemyThrowerAnimator(AnimationState* initialState)
		: Animator(initialState) {}

EnemyThrowerAnimator* EnemyThrowerAnimator::Create()
{
	// Crea las animaciones del personaje
	BasicAnimation* walk = new BasicAnimation(1024, 1024, 8, 8, 4.0f);
	walk->frames.push_back({ 0, 6 });
	walk->frames.push_back({ 2, 6 });
	walk->frames.push_back({ 1, 6 });
	walk->frames.push_back({ 3, 6 });

	BasicAnimation* throwStart = new BasicAnimation(1024, 1024, 8, 8, 8.0f, false);
	throwStart->frames.push_back({ 1, 7 });
	throwStart->frames.push_back({ 0, 7 });
	throwStart->frames.push_back({ 1, 7 });

	BasicAnimation* throwDo = new BasicAnimation(1024, 1024, 8, 8, 8.0f, false);
	throwDo->frames.push_back({ 2, 7 });
	throwDo->frames.push_back({ 3, 7 });
	throwDo->frames.push_back({ 1, 4 });

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
	AnimationState* throwStartState = new AnimationState(throwStart);
	AnimationState* throwDoState = new AnimationState(throwDo);
	AnimationState* runStartState = new AnimationState(runStart);
	AnimationState* runState = new AnimationState(run);
	AnimationState* hitBackState = new AnimationState(hitBack);
	AnimationState* dieBackState = new AnimationState(dieBack);
	AnimationState* hitFrontState = new AnimationState(hitFront);
	AnimationState* dieFrontState = new AnimationState(dieFront);

	// Crea las transiciones entre los estados
	walkState->AddStateTransition(new AnimationTransition(throwStartState, new FlagEqualsCondition("AI_state", THROW_START)));
	walkState->AddStateTransition(new AnimationTransition(hitBackState, new FlagEqualsCondition("hit_back", true)));
	walkState->AddStateTransition(new AnimationTransition(hitFrontState, new FlagEqualsCondition("hit_front", true)));

	throwStartState->AddStateTransition(new AnimationTransition(throwDoState, new FlagEqualsCondition("AI_state", THROW_DO)));
	throwStartState->AddStateTransition(new AnimationTransition(hitBackState, new FlagEqualsCondition("hit_back", true)));
	throwStartState->AddStateTransition(new AnimationTransition(hitFrontState, new FlagEqualsCondition("hit_front", true)));

	throwDoState->AddStateTransition(new AnimationTransition(runStartState, new FlagEqualsCondition("AI_state", RUN_START)));
	throwDoState->AddStateTransition(new AnimationTransition(hitBackState, new FlagEqualsCondition("hit_back", true)));
	throwDoState->AddStateTransition(new AnimationTransition(hitFrontState, new FlagEqualsCondition("hit_front", true)));

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
	return new EnemyThrowerAnimator(walkState);
}
