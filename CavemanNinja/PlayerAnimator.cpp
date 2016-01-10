#include "PlayerAnimator.h"
#include "StateTransition.h"
#include "StateSwitcher.h"
#include "BasicAnimation.h"
#include "FlagGreaterThanCondition.h"
#include "FlagLessThanCondition.h"
#include "FlagEqualsCondition.h"
#include "AnimationEndCondition.h"

PlayerAnimator::PlayerAnimator(StateSwitcher<Animation>* initialState)
	: Animator(initialState) {}

PlayerAnimator* PlayerAnimator::Create()
{
	// Crea las animaciones del personaje
	BasicAnimation* idle = new BasicAnimation(1024, 512, 8, 8, 0.0f);
	idle->frames.push_back({ 0, 0 });

	BasicAnimation* idleUp = new BasicAnimation(1024, 512, 8, 8, 0.0f);
	idleUp->frames.push_back({ 0, 4 });

	BasicAnimation* attack = new BasicAnimation(1024, 512, 8, 8, 16.0f, false);
	attack->frames.push_back({ 4, 0 });
	attack->frames.push_back({ 5, 0 });

	BasicAnimation* attackJump = new BasicAnimation(1024, 512, 8, 8, 16.0f, false);
	attackJump->frames.push_back({ 6, 0 });
	attackJump->frames.push_back({ 7, 0 });

	BasicAnimation* attackUp = new BasicAnimation(1024, 512, 8, 8, 16.0f, false);
	attackUp->frames.push_back({ 4, 4 });
	attackUp->frames.push_back({ 5, 4 });

	BasicAnimation* attackUpJump = new BasicAnimation(1024, 512, 8, 8, 16.0f, false);
	attackUpJump->frames.push_back({ 6, 4 });
	attackUpJump->frames.push_back({ 7, 4 });

	BasicAnimation* run = new BasicAnimation(1024, 512, 8, 8, 8.0f);
	run->frames.push_back({ 1, 0 });
	run->frames.push_back({ 2, 0 });
	run->frames.push_back({ 3, 0 });
	run->frames.push_back({ 0, 1 });

	BasicAnimation* jump = new BasicAnimation(1024, 512, 8, 8, 6.0f, false);
	jump->frames.push_back({ 1, 1 });
	jump->frames.push_back({ 2, 1 });

	BasicAnimation* longJumpStart = new BasicAnimation(1024, 512, 8, 8, 8.0f, false);
	longJumpStart->frames.push_back({ 1, 1 });

	BasicAnimation* longJump = new BasicAnimation(1024, 512, 8, 8, 16.0f);
	longJump->frames.push_back({ 0, 2 });
	longJump->frames.push_back({ 1, 2 });
	longJump->frames.push_back({ 2, 2 });
	longJump->frames.push_back({ 3, 2 });
	longJump->frames.push_back({ 0, 3 });
	longJump->frames.push_back({ 1, 3 });
	longJump->frames.push_back({ 2, 3 });
	longJump->frames.push_back({ 3, 3 });

	BasicAnimation* fall = new BasicAnimation(1024, 512, 8, 8, 0.0f);
	fall->frames.push_back({ 3, 1 });

	BasicAnimation* hitBack = new BasicAnimation(1024, 512, 8, 8, 0.0f, false);
	hitBack->frames.push_back({ 4, 1 });

	BasicAnimation* dieBack = new BasicAnimation(1024, 512, 8, 8, 4.0f, false);
	dieBack->frames.push_back({ 4, 1 });
	dieBack->frames.push_back({ 5, 1 });
	dieBack->frames.push_back({ 6, 1 });
	dieBack->frames.push_back({ 7, 1 });

	BasicAnimation* hitFront = new BasicAnimation(1024, 512, 8, 8, 0.0f, false);
	hitFront->frames.push_back({ 4, 2 });

	BasicAnimation* dieFront = new BasicAnimation(1024, 512, 8, 8, 4.0f, false);
	dieFront->frames.push_back({ 4, 2 });
	dieFront->frames.push_back({ 5, 2 });
	dieFront->frames.push_back({ 6, 2 });
	dieFront->frames.push_back({ 7, 2 });

	BasicAnimation* dieHarvest = new BasicAnimation(1024, 512, 8, 8, 4.0f, false);
	dieHarvest->frames.push_back({ 4, 3 });
	dieHarvest->frames.push_back({ 5, 3 });
	dieHarvest->frames.push_back({ 6, 3 });
	dieHarvest->frames.push_back({ 7, 3 });

	// Crea los estados del personaje
	StateSwitcher<Animation>* idleState = new StateSwitcher<Animation>(idle);
	StateSwitcher<Animation>* idleUpState = new StateSwitcher<Animation>(idleUp);
	StateSwitcher<Animation>* attackState = new StateSwitcher<Animation>(attack);
	StateSwitcher<Animation>* attackJumpState = new StateSwitcher<Animation>(attackJump);
	StateSwitcher<Animation>* attackUpState = new StateSwitcher<Animation>(attackUp);
	StateSwitcher<Animation>* attackUpJumpState = new StateSwitcher<Animation>(attackUpJump);
	StateSwitcher<Animation>* runState = new StateSwitcher<Animation>(run);
	StateSwitcher<Animation>* jumpState = new StateSwitcher<Animation>(jump);
	StateSwitcher<Animation>* longJumpStartState = new StateSwitcher<Animation>(longJumpStart);
	StateSwitcher<Animation>* longJumpState = new StateSwitcher<Animation>(longJump);
	StateSwitcher<Animation>* fallState = new StateSwitcher<Animation>(fall);
	StateSwitcher<Animation>* hitBackState = new StateSwitcher<Animation>(hitBack);
	StateSwitcher<Animation>* dieBackState = new StateSwitcher<Animation>(dieBack);
	StateSwitcher<Animation>* hitFrontState = new StateSwitcher<Animation>(hitFront);
	StateSwitcher<Animation>* dieFrontState = new StateSwitcher<Animation>(dieFront);
	StateSwitcher<Animation>* dieHarvestState = new StateSwitcher<Animation>(dieHarvest);

	// Crea las transiciones entre los estados
	idleState->AddStateTransition(new StateTransition<Animation>(runState, new FlagGreaterThanCondition("speedX_absolute", 0.0f)));
	idleState->AddStateTransition(new StateTransition<Animation>(jumpState, new FlagEqualsCondition("jumping", true)));
	idleState->AddStateTransition(new StateTransition<Animation>(longJumpStartState, new FlagEqualsCondition("jumping_long", true)));
	idleState->AddStateTransition(new StateTransition<Animation>(fallState, new FlagEqualsCondition("falling", true)));
	idleState->AddStateTransition(new StateTransition<Animation>(idleUpState, new FlagEqualsCondition("looking_up", true)));
	idleState->AddStateTransition(new StateTransition<Animation>(attackUpState, new FlagEqualsCondition("weapon_attack_up", true)));
	idleState->AddStateTransition(new StateTransition<Animation>(attackState, new FlagEqualsCondition("weapon_attack", true)));
	idleState->AddStateTransition(new StateTransition<Animation>(hitBackState, new FlagEqualsCondition("hit_back", true)));
	idleState->AddStateTransition(new StateTransition<Animation>(hitFrontState, new FlagEqualsCondition("hit_front", true)));
	idleState->AddStateTransition(new StateTransition<Animation>(dieHarvestState, new FlagEqualsCondition("dead_harvest", true)));

	idleUpState->AddStateTransition(new StateTransition<Animation>(runState, new FlagGreaterThanCondition("speedX_absolute", 0.0f)));
	idleUpState->AddStateTransition(new StateTransition<Animation>(jumpState, new FlagEqualsCondition("jumping", true)));
	idleUpState->AddStateTransition(new StateTransition<Animation>(longJumpStartState, new FlagEqualsCondition("jumping_long", true)));
	idleUpState->AddStateTransition(new StateTransition<Animation>(fallState, new FlagEqualsCondition("falling", true)));
	idleUpState->AddStateTransition(new StateTransition<Animation>(idleState, new FlagEqualsCondition("looking_up", false)));
	idleUpState->AddStateTransition(new StateTransition<Animation>(attackUpState, new FlagEqualsCondition("weapon_attack_up", true)));
	idleUpState->AddStateTransition(new StateTransition<Animation>(attackState, new FlagEqualsCondition("weapon_attack", true)));
	idleUpState->AddStateTransition(new StateTransition<Animation>(hitBackState, new FlagEqualsCondition("hit_back", true)));
	idleUpState->AddStateTransition(new StateTransition<Animation>(hitFrontState, new FlagEqualsCondition("hit_front", true)));
	idleUpState->AddStateTransition(new StateTransition<Animation>(dieHarvestState, new FlagEqualsCondition("dead_harvest", true)));

	attackState->AddStateTransition(new StateTransition<Animation>(idleState, new AnimationEndCondition()));
	attackState->AddStateTransition(new StateTransition<Animation>(hitBackState, new FlagEqualsCondition("hit_back", true)));
	attackState->AddStateTransition(new StateTransition<Animation>(hitFrontState, new FlagEqualsCondition("hit_front", true)));

	attackJumpState->AddStateTransition(new StateTransition<Animation>(jumpState, new AnimationEndCondition()));
	attackJumpState->AddStateTransition(new StateTransition<Animation>(hitBackState, new FlagEqualsCondition("hit_back", true)));
	attackJumpState->AddStateTransition(new StateTransition<Animation>(hitFrontState, new FlagEqualsCondition("hit_front", true)));

	attackUpState->AddStateTransition(new StateTransition<Animation>(idleState, new AnimationEndCondition()));
	attackUpState->AddStateTransition(new StateTransition<Animation>(hitBackState, new FlagEqualsCondition("hit_back", true)));
	attackUpState->AddStateTransition(new StateTransition<Animation>(hitFrontState, new FlagEqualsCondition("hit_front", true)));

	attackUpJumpState->AddStateTransition(new StateTransition<Animation>(jumpState, new AnimationEndCondition()));
	attackUpJumpState->AddStateTransition(new StateTransition<Animation>(hitBackState, new FlagEqualsCondition("hit_back", true)));
	attackUpJumpState->AddStateTransition(new StateTransition<Animation>(hitFrontState, new FlagEqualsCondition("hit_front", true)));

	runState->AddStateTransition(new StateTransition<Animation>(idleState, new FlagEqualsCondition("speedX_absolute", 0.0f)));
	runState->AddStateTransition(new StateTransition<Animation>(jumpState, new FlagEqualsCondition("jumping", true)));
	runState->AddStateTransition(new StateTransition<Animation>(longJumpStartState, new FlagEqualsCondition("jumping_long", true)));
	runState->AddStateTransition(new StateTransition<Animation>(fallState, new FlagEqualsCondition("falling", true)));
	runState->AddStateTransition(new StateTransition<Animation>(attackUpState, new FlagEqualsCondition("weapon_attack_up", true)));
	runState->AddStateTransition(new StateTransition<Animation>(attackState, new FlagEqualsCondition("weapon_attack", true)));
	runState->AddStateTransition(new StateTransition<Animation>(hitBackState, new FlagEqualsCondition("hit_back", true)));
	runState->AddStateTransition(new StateTransition<Animation>(hitFrontState, new FlagEqualsCondition("hit_front", true)));

	jumpState->AddStateTransition(new StateTransition<Animation>(fallState, new FlagEqualsCondition("falling", true)));
	jumpState->AddStateTransition(new StateTransition<Animation>(idleState, new FlagEqualsCondition("jumping", false)));
	jumpState->AddStateTransition(new StateTransition<Animation>(attackUpJumpState, new FlagEqualsCondition("weapon_attack_up", true)));
	jumpState->AddStateTransition(new StateTransition<Animation>(attackJumpState, new FlagEqualsCondition("weapon_attack", true)));
	jumpState->AddStateTransition(new StateTransition<Animation>(hitBackState, new FlagEqualsCondition("hit_back", true)));
	jumpState->AddStateTransition(new StateTransition<Animation>(hitFrontState, new FlagEqualsCondition("hit_front", true)));

	longJumpStartState->AddStateTransition(new StateTransition<Animation>(longJumpState, new AnimationEndCondition()));
	longJumpStartState->AddStateTransition(new StateTransition<Animation>(fallState, new FlagEqualsCondition("falling", true)));
	longJumpStartState->AddStateTransition(new StateTransition<Animation>(idleState, new FlagEqualsCondition("jumping_long", false)));
	longJumpStartState->AddStateTransition(new StateTransition<Animation>(hitBackState, new FlagEqualsCondition("hit_back", true)));
	longJumpStartState->AddStateTransition(new StateTransition<Animation>(hitFrontState, new FlagEqualsCondition("hit_front", true)));

	longJumpState->AddStateTransition(new StateTransition<Animation>(fallState, new FlagEqualsCondition("falling", true)));
	longJumpState->AddStateTransition(new StateTransition<Animation>(idleState, new FlagEqualsCondition("jumping_long", false)));
	longJumpState->AddStateTransition(new StateTransition<Animation>(hitBackState, new FlagEqualsCondition("hit_back", true)));
	longJumpState->AddStateTransition(new StateTransition<Animation>(hitFrontState, new FlagEqualsCondition("hit_front", true)));

	fallState->AddStateTransition(new StateTransition<Animation>(idleState, new FlagEqualsCondition("falling", false)));
	fallState->AddStateTransition(new StateTransition<Animation>(jumpState, new FlagLessThanCondition("speedY_absolute", 0.0f)));
	fallState->AddStateTransition(new StateTransition<Animation>(attackUpJumpState, new FlagEqualsCondition("weapon_attack_up", true)));
	fallState->AddStateTransition(new StateTransition<Animation>(attackJumpState, new FlagEqualsCondition("weapon_attack", true)));
	fallState->AddStateTransition(new StateTransition<Animation>(hitBackState, new FlagEqualsCondition("hit_back", true)));
	fallState->AddStateTransition(new StateTransition<Animation>(hitFrontState, new FlagEqualsCondition("hit_front", true)));

	hitBackState->AddStateTransition(new StateTransition<Animation>(idleState, new FlagEqualsCondition("hit_back", false)));
	hitBackState->AddStateTransition(new StateTransition<Animation>(dieBackState, new FlagEqualsCondition("decaying", true)));

	hitFrontState->AddStateTransition(new StateTransition<Animation>(idleState, new FlagEqualsCondition("hit_front", false)));
	hitFrontState->AddStateTransition(new StateTransition<Animation>(dieFrontState, new FlagEqualsCondition("decaying", true)));

	// Crea y devuelve el animator
	return new PlayerAnimator(idleState);
}