#include "PlayerAnimator.h"
#include "StateTransition.h"
#include "StateSwitcher.h"
#include "BasicAnimation.h"
#include "FlagGreaterThanCondition.h"
#include "FlagLessThanCondition.h"
#include "FlagEqualsCondition.h"
#include "AnimationEndCondition.h"

PlayerAnimator::PlayerAnimator(AnimationState* initialState)
	: Animator(initialState) {}

PlayerAnimator* PlayerAnimator::Create()
{
	// Crea las animaciones del personaje
	BasicAnimation* idle = new BasicAnimation(1024, 1024, 8, 8, 0.0f);
	idle->frames.push_back({ 0, 0 });

	BasicAnimation* idleUp = new BasicAnimation(1024, 1024, 8, 8, 0.0f);
	idleUp->frames.push_back({ 0, 4 });

	BasicAnimation* idleCrouch = new BasicAnimation(1024, 1024, 8, 8, 0.0f);
	idleCrouch->frames.push_back({ 1, 4 });

	BasicAnimation* attack = new BasicAnimation(1024, 1024, 8, 8, 12.0f, false);
	attack->frames.push_back({ 4, 0 });
	attack->frames.push_back({ 5, 0 });

	BasicAnimation* attackJump = new BasicAnimation(1024, 1024, 8, 8, 12.0f, false);
	attackJump->frames.push_back({ 6, 0 });
	attackJump->frames.push_back({ 7, 0 });

	BasicAnimation* attackUp = new BasicAnimation(1024, 1024, 8, 8, 12.0f, false);
	attackUp->frames.push_back({ 4, 4 });
	attackUp->frames.push_back({ 5, 4 });

	BasicAnimation* attackUpJump = new BasicAnimation(1024, 1024, 8, 8, 12.0f, false);
	attackUpJump->frames.push_back({ 6, 4 });
	attackUpJump->frames.push_back({ 7, 4 });

	BasicAnimation* attackCrouch = new BasicAnimation(1024, 1024, 8, 8, 12.0f, false);
	attackCrouch->frames.push_back({ 2, 4 });
	attackCrouch->frames.push_back({ 3, 4 });

	BasicAnimation* attackMelee = new BasicAnimation(1024, 1024, 8, 8, 12.0f, false);
	attackMelee->frames.push_back({ 0, 5 });
	attackMelee->frames.push_back({ 1, 5 });

	BasicAnimation* attackUpMelee = new BasicAnimation(1024, 1024, 8, 8, 12.0f, false);
	attackUpMelee->frames.push_back({ 2, 5 });
	attackUpMelee->frames.push_back({ 3, 5 });

	BasicAnimation* attackJumpMelee = new BasicAnimation(1024, 1024, 8, 8, 12.0f, false);
	attackJumpMelee->frames.push_back({ 4, 5 });
	attackJumpMelee->frames.push_back({ 5, 5 });

	BasicAnimation* attackUpJumpMelee = new BasicAnimation(1024, 1024, 8, 8, 12.0f, false);
	attackUpJumpMelee->frames.push_back({ 6, 5 });
	attackUpJumpMelee->frames.push_back({ 7, 5 });

	BasicAnimation* attackCrouchMelee = new BasicAnimation(1024, 1024, 8, 8, 12.0f, false);
	attackCrouchMelee->frames.push_back({ 0, 6 });
	attackCrouchMelee->frames.push_back({ 1, 6 });

	BasicAnimation* run = new BasicAnimation(1024, 1024, 8, 8, 8.0f);
	run->frames.push_back({ 1, 0 });
	run->frames.push_back({ 2, 0 });
	run->frames.push_back({ 3, 0 });
	run->frames.push_back({ 0, 1 });

	BasicAnimation* jump = new BasicAnimation(1024, 1024, 8, 8, 6.0f, false);
	jump->frames.push_back({ 1, 1 });
	jump->frames.push_back({ 2, 1 });

	BasicAnimation* longJumpStart = new BasicAnimation(1024, 1024, 8, 8, 8.0f, false);
	longJumpStart->frames.push_back({ 1, 1 });

	BasicAnimation* longJump = new BasicAnimation(1024, 1024, 8, 8, 16.0f);
	longJump->frames.push_back({ 0, 2 });
	longJump->frames.push_back({ 1, 2 });
	longJump->frames.push_back({ 2, 2 });
	longJump->frames.push_back({ 3, 2 });
	longJump->frames.push_back({ 0, 3 });
	longJump->frames.push_back({ 1, 3 });
	longJump->frames.push_back({ 2, 3 });
	longJump->frames.push_back({ 3, 3 });

	BasicAnimation* fall = new BasicAnimation(1024, 1024, 8, 8, 0.0f);
	fall->frames.push_back({ 3, 1 });

	BasicAnimation* hitBack = new BasicAnimation(1024, 1024, 8, 8, 0.0f, false);
	hitBack->frames.push_back({ 4, 1 });

	BasicAnimation* dieBack = new BasicAnimation(1024, 1024, 8, 8, 4.0f, false);
	dieBack->frames.push_back({ 4, 1 });
	dieBack->frames.push_back({ 5, 1 });
	dieBack->frames.push_back({ 6, 1 });
	dieBack->frames.push_back({ 7, 1 });

	BasicAnimation* hitFront = new BasicAnimation(1024, 1024, 8, 8, 0.0f, false);
	hitFront->frames.push_back({ 4, 2 });

	BasicAnimation* dieFront = new BasicAnimation(1024, 1024, 8, 8, 4.0f, false);
	dieFront->frames.push_back({ 4, 2 });
	dieFront->frames.push_back({ 5, 2 });
	dieFront->frames.push_back({ 6, 2 });
	dieFront->frames.push_back({ 7, 2 });

	BasicAnimation* dieHarvest = new BasicAnimation(1024, 1024, 8, 8, 4.0f, false);
	dieHarvest->frames.push_back({ 4, 3 });
	dieHarvest->frames.push_back({ 5, 3 });
	dieHarvest->frames.push_back({ 6, 3 });
	dieHarvest->frames.push_back({ 7, 3 });

	BasicAnimation* victory = new BasicAnimation(1024, 1024, 8, 8, 4.0f);
	victory->frames.push_back({ 2, 6 });
	victory->frames.push_back({ 3, 6 });
	victory->frames.push_back({ 4, 6 });
	victory->frames.push_back({ 3, 6 });

	// Crea los estados del personaje
	AnimationState* idleState = new AnimationState(idle);
	AnimationState* idleUpState = new AnimationState(idleUp);
	AnimationState* idleCrouchState = new AnimationState(idleCrouch);
	AnimationState* attackState = new AnimationState(attack);
	AnimationState* attackJumpState = new AnimationState(attackJump);
	AnimationState* attackUpState = new AnimationState(attackUp);
	AnimationState* attackUpJumpState = new AnimationState(attackUpJump);
	AnimationState* attackCrouchState = new AnimationState(attackCrouch);
	AnimationState* attackMeleeState = new AnimationState(attackMelee);
	AnimationState* attackJumpMeleeState = new AnimationState(attackJumpMelee);
	AnimationState* attackUpMeleeState = new AnimationState(attackUpMelee);
	AnimationState* attackUpJumpMeleeState = new AnimationState(attackUpJumpMelee);
	AnimationState* attackCrouchMeleeState = new AnimationState(attackCrouchMelee);
	AnimationState* runState = new AnimationState(run);
	AnimationState* jumpState = new AnimationState(jump);
	AnimationState* longJumpStartState = new AnimationState(longJumpStart);
	AnimationState* longJumpState = new AnimationState(longJump);
	AnimationState* fallState = new AnimationState(fall);
	AnimationState* hitBackState = new AnimationState(hitBack);
	AnimationState* dieBackState = new AnimationState(dieBack);
	AnimationState* hitFrontState = new AnimationState(hitFront);
	AnimationState* dieFrontState = new AnimationState(dieFront);
	AnimationState* dieHarvestState = new AnimationState(dieHarvest);
	AnimationState* victoryState = new AnimationState(victory);

	// Crea las transiciones entre los estados
	idleState->AddStateTransition(new AnimationTransition(runState, new FlagGreaterThanCondition("speedX_absolute", 0.0f)));
	idleState->AddStateTransition(new AnimationTransition(jumpState, new FlagEqualsCondition("jumping", true)));
	idleState->AddStateTransition(new AnimationTransition(longJumpStartState, new FlagEqualsCondition("jumping_long", true)));
	idleState->AddStateTransition(new AnimationTransition(fallState, new FlagEqualsCondition("falling", true)));
	idleState->AddStateTransition(new AnimationTransition(idleUpState, new FlagEqualsCondition("looking_up", true)));
	idleState->AddStateTransition(new AnimationTransition(idleCrouchState, new FlagEqualsCondition("crouch", true)));
	idleState->AddStateTransition(new AnimationTransition(attackUpState, new FlagEqualsCondition("weapon_attack_up", true)));
	idleState->AddStateTransition(new AnimationTransition(attackState, new FlagEqualsCondition("weapon_attack", true)));
	idleState->AddStateTransition(new AnimationTransition(attackUpMeleeState, new FlagEqualsCondition("melee_attack_up", true)));
	idleState->AddStateTransition(new AnimationTransition(attackMeleeState, new FlagEqualsCondition("melee_attack", true)));
	idleState->AddStateTransition(new AnimationTransition(hitBackState, new FlagEqualsCondition("hit_back", true)));
	idleState->AddStateTransition(new AnimationTransition(hitFrontState, new FlagEqualsCondition("hit_front", true)));
	idleState->AddStateTransition(new AnimationTransition(dieHarvestState, new FlagEqualsCondition("dead_harvest", true)));
	idleState->AddStateTransition(new AnimationTransition(victoryState, new FlagEqualsCondition("victory", true)));

	idleUpState->AddStateTransition(new AnimationTransition(runState, new FlagGreaterThanCondition("speedX_absolute", 0.0f)));
	idleUpState->AddStateTransition(new AnimationTransition(jumpState, new FlagEqualsCondition("jumping", true)));
	idleUpState->AddStateTransition(new AnimationTransition(longJumpStartState, new FlagEqualsCondition("jumping_long", true)));
	idleUpState->AddStateTransition(new AnimationTransition(fallState, new FlagEqualsCondition("falling", true)));
	idleUpState->AddStateTransition(new AnimationTransition(idleState, new FlagEqualsCondition("looking_up", false)));
	idleUpState->AddStateTransition(new AnimationTransition(attackUpState, new FlagEqualsCondition("weapon_attack_up", true)));
	idleUpState->AddStateTransition(new AnimationTransition(attackState, new FlagEqualsCondition("weapon_attack", true)));
	idleUpState->AddStateTransition(new AnimationTransition(attackUpMeleeState, new FlagEqualsCondition("melee_attack_up", true)));
	idleUpState->AddStateTransition(new AnimationTransition(attackMeleeState, new FlagEqualsCondition("melee_attack", true)));
	idleUpState->AddStateTransition(new AnimationTransition(hitBackState, new FlagEqualsCondition("hit_back", true)));
	idleUpState->AddStateTransition(new AnimationTransition(hitFrontState, new FlagEqualsCondition("hit_front", true)));
	idleUpState->AddStateTransition(new AnimationTransition(dieHarvestState, new FlagEqualsCondition("dead_harvest", true)));
	idleUpState->AddStateTransition(new AnimationTransition(victoryState, new FlagEqualsCondition("victory", true)));

	idleCrouchState->AddStateTransition(new AnimationTransition(attackCrouchState, new FlagEqualsCondition("weapon_attack", true)));
	idleCrouchState->AddStateTransition(new AnimationTransition(attackCrouchMeleeState, new FlagEqualsCondition("melee_attack", true)));
	idleCrouchState->AddStateTransition(new AnimationTransition(fallState, new FlagEqualsCondition("falling", true)));
	idleCrouchState->AddStateTransition(new AnimationTransition(idleState, new FlagEqualsCondition("crouch", false)));
	idleCrouchState->AddStateTransition(new AnimationTransition(hitBackState, new FlagEqualsCondition("hit_back", true)));
	idleCrouchState->AddStateTransition(new AnimationTransition(hitFrontState, new FlagEqualsCondition("hit_front", true)));
	idleCrouchState->AddStateTransition(new AnimationTransition(dieHarvestState, new FlagEqualsCondition("dead_harvest", true)));
	idleCrouchState->AddStateTransition(new AnimationTransition(victoryState, new FlagEqualsCondition("victory", true)));

	runState->AddStateTransition(new AnimationTransition(idleState, new FlagEqualsCondition("speedX_absolute", 0.0f)));
	runState->AddStateTransition(new AnimationTransition(jumpState, new FlagEqualsCondition("jumping", true)));
	runState->AddStateTransition(new AnimationTransition(longJumpStartState, new FlagEqualsCondition("jumping_long", true)));
	runState->AddStateTransition(new AnimationTransition(fallState, new FlagEqualsCondition("falling", true)));
	runState->AddStateTransition(new AnimationTransition(attackUpState, new FlagEqualsCondition("weapon_attack_up", true)));
	runState->AddStateTransition(new AnimationTransition(attackState, new FlagEqualsCondition("weapon_attack", true)));
	runState->AddStateTransition(new AnimationTransition(attackUpMeleeState, new FlagEqualsCondition("melee_attack_up", true)));
	runState->AddStateTransition(new AnimationTransition(attackMeleeState, new FlagEqualsCondition("melee_attack", true)));
	runState->AddStateTransition(new AnimationTransition(hitBackState, new FlagEqualsCondition("hit_back", true)));
	runState->AddStateTransition(new AnimationTransition(hitFrontState, new FlagEqualsCondition("hit_front", true)));

	jumpState->AddStateTransition(new AnimationTransition(fallState, new FlagEqualsCondition("falling", true)));
	jumpState->AddStateTransition(new AnimationTransition(idleState, new FlagEqualsCondition("jumping", false)));
	jumpState->AddStateTransition(new AnimationTransition(attackUpJumpState, new FlagEqualsCondition("weapon_attack_up", true)));
	jumpState->AddStateTransition(new AnimationTransition(attackJumpState, new FlagEqualsCondition("weapon_attack", true)));
	jumpState->AddStateTransition(new AnimationTransition(attackUpJumpMeleeState, new FlagEqualsCondition("melee_attack_up", true)));
	jumpState->AddStateTransition(new AnimationTransition(attackJumpMeleeState, new FlagEqualsCondition("melee_attack", true)));
	jumpState->AddStateTransition(new AnimationTransition(hitBackState, new FlagEqualsCondition("hit_back", true)));
	jumpState->AddStateTransition(new AnimationTransition(hitFrontState, new FlagEqualsCondition("hit_front", true)));

	longJumpStartState->AddStateTransition(new AnimationTransition(longJumpState, new AnimationEndCondition()));
	longJumpStartState->AddStateTransition(new AnimationTransition(fallState, new FlagEqualsCondition("falling", true)));
	longJumpStartState->AddStateTransition(new AnimationTransition(idleState, new FlagEqualsCondition("jumping_long", false)));
	longJumpStartState->AddStateTransition(new AnimationTransition(hitBackState, new FlagEqualsCondition("hit_back", true)));
	longJumpStartState->AddStateTransition(new AnimationTransition(hitFrontState, new FlagEqualsCondition("hit_front", true)));

	longJumpState->AddStateTransition(new AnimationTransition(fallState, new FlagEqualsCondition("falling", true)));
	longJumpState->AddStateTransition(new AnimationTransition(idleState, new FlagEqualsCondition("jumping_long", false)));
	longJumpState->AddStateTransition(new AnimationTransition(hitBackState, new FlagEqualsCondition("hit_back", true)));
	longJumpState->AddStateTransition(new AnimationTransition(hitFrontState, new FlagEqualsCondition("hit_front", true)));

	fallState->AddStateTransition(new AnimationTransition(idleState, new FlagEqualsCondition("falling", false)));
	fallState->AddStateTransition(new AnimationTransition(jumpState, new FlagLessThanCondition("speedY_absolute", 0.0f)));
	fallState->AddStateTransition(new AnimationTransition(attackUpJumpState, new FlagEqualsCondition("weapon_attack_up", true)));
	fallState->AddStateTransition(new AnimationTransition(attackJumpState, new FlagEqualsCondition("weapon_attack", true)));
	fallState->AddStateTransition(new AnimationTransition(attackUpJumpMeleeState, new FlagEqualsCondition("melee_attack_up", true)));
	fallState->AddStateTransition(new AnimationTransition(attackJumpMeleeState, new FlagEqualsCondition("melee_attack", true)));
	fallState->AddStateTransition(new AnimationTransition(hitBackState, new FlagEqualsCondition("hit_back", true)));
	fallState->AddStateTransition(new AnimationTransition(hitFrontState, new FlagEqualsCondition("hit_front", true)));

	attackState->AddStateTransition(new AnimationTransition(idleState, new AnimationEndCondition()));
	attackState->AddStateTransition(new AnimationTransition(hitBackState, new FlagEqualsCondition("hit_back", true)));
	attackState->AddStateTransition(new AnimationTransition(hitFrontState, new FlagEqualsCondition("hit_front", true)));

	attackJumpState->AddStateTransition(new AnimationTransition(jumpState, new AnimationEndCondition()));
	attackJumpState->AddStateTransition(new AnimationTransition(hitBackState, new FlagEqualsCondition("hit_back", true)));
	attackJumpState->AddStateTransition(new AnimationTransition(hitFrontState, new FlagEqualsCondition("hit_front", true)));

	attackUpState->AddStateTransition(new AnimationTransition(idleState, new AnimationEndCondition()));
	attackUpState->AddStateTransition(new AnimationTransition(hitBackState, new FlagEqualsCondition("hit_back", true)));
	attackUpState->AddStateTransition(new AnimationTransition(hitFrontState, new FlagEqualsCondition("hit_front", true)));

	attackUpJumpState->AddStateTransition(new AnimationTransition(jumpState, new AnimationEndCondition()));
	attackUpJumpState->AddStateTransition(new AnimationTransition(hitBackState, new FlagEqualsCondition("hit_back", true)));
	attackUpJumpState->AddStateTransition(new AnimationTransition(hitFrontState, new FlagEqualsCondition("hit_front", true)));

	attackCrouchState->AddStateTransition(new AnimationTransition(idleCrouchState, new AnimationEndCondition()));
	attackCrouchState->AddStateTransition(new AnimationTransition(hitBackState, new FlagEqualsCondition("hit_back", true)));
	attackCrouchState->AddStateTransition(new AnimationTransition(hitFrontState, new FlagEqualsCondition("hit_front", true)));

	attackMeleeState->AddStateTransition(new AnimationTransition(idleState, new AnimationEndCondition()));
	attackMeleeState->AddStateTransition(new AnimationTransition(hitBackState, new FlagEqualsCondition("hit_back", true)));
	attackMeleeState->AddStateTransition(new AnimationTransition(hitFrontState, new FlagEqualsCondition("hit_front", true)));

	attackJumpMeleeState->AddStateTransition(new AnimationTransition(jumpState, new AnimationEndCondition()));
	attackJumpMeleeState->AddStateTransition(new AnimationTransition(hitBackState, new FlagEqualsCondition("hit_back", true)));
	attackJumpMeleeState->AddStateTransition(new AnimationTransition(hitFrontState, new FlagEqualsCondition("hit_front", true)));

	attackUpMeleeState->AddStateTransition(new AnimationTransition(idleState, new AnimationEndCondition()));
	attackUpMeleeState->AddStateTransition(new AnimationTransition(hitBackState, new FlagEqualsCondition("hit_back", true)));
	attackUpMeleeState->AddStateTransition(new AnimationTransition(hitFrontState, new FlagEqualsCondition("hit_front", true)));

	attackUpJumpMeleeState->AddStateTransition(new AnimationTransition(jumpState, new AnimationEndCondition()));
	attackUpJumpMeleeState->AddStateTransition(new AnimationTransition(hitBackState, new FlagEqualsCondition("hit_back", true)));
	attackUpJumpMeleeState->AddStateTransition(new AnimationTransition(hitFrontState, new FlagEqualsCondition("hit_front", true)));

	attackCrouchMeleeState->AddStateTransition(new AnimationTransition(idleCrouchState, new AnimationEndCondition()));
	attackCrouchMeleeState->AddStateTransition(new AnimationTransition(hitBackState, new FlagEqualsCondition("hit_back", true)));
	attackCrouchMeleeState->AddStateTransition(new AnimationTransition(hitFrontState, new FlagEqualsCondition("hit_front", true)));

	hitBackState->AddStateTransition(new AnimationTransition(idleState, new FlagEqualsCondition("hit_back", false)));
	hitBackState->AddStateTransition(new AnimationTransition(dieBackState, new FlagEqualsCondition("decaying", true)));

	hitFrontState->AddStateTransition(new AnimationTransition(idleState, new FlagEqualsCondition("hit_front", false)));
	hitFrontState->AddStateTransition(new AnimationTransition(dieFrontState, new FlagEqualsCondition("decaying", true)));

	// Crea y devuelve el animator
	return new PlayerAnimator(idleState);
}