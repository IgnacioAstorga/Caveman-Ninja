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
	BasicAnimation* idle = new BasicAnimation(0.0f);
	idle->frames.push_back({ 0, 0, 64, 64 });

	BasicAnimation* idleUp = new BasicAnimation(0.0f);
	idleUp->frames.push_back({ 0, 256, 64, 64 });

	BasicAnimation* attack = new BasicAnimation(16.0f, SDL_FLIP_NONE, false);
	attack->frames.push_back({ 256, 0, 64, 64 });
	attack->frames.push_back({ 320, 0, 64, 64 });

	BasicAnimation* attackJump = new BasicAnimation(16.0f, SDL_FLIP_NONE, false);
	attackJump->frames.push_back({ 384, 0, 64, 64 });
	attackJump->frames.push_back({ 448, 0, 64, 64 });

	BasicAnimation* run = new BasicAnimation(8.0f);
	run->frames.push_back({ 64, 0, 64, 64 });
	run->frames.push_back({ 128, 0, 64, 64 });
	run->frames.push_back({ 192, 0, 64, 64 });
	run->frames.push_back({ 0, 64, 64, 64 });

	BasicAnimation* jump = new BasicAnimation(6.0f, SDL_FLIP_NONE, false);
	jump->frames.push_back({ 64, 64, 64, 64 });
	jump->frames.push_back({ 128, 64, 64, 64 });

	BasicAnimation* longJumpStart = new BasicAnimation(8.0f, SDL_FLIP_NONE, false);
	longJumpStart->frames.push_back({ 64, 64, 64, 64 });

	BasicAnimation* longJump = new BasicAnimation(16.0f);
	longJump->frames.push_back({ 0, 128, 64, 64 });
	longJump->frames.push_back({ 64, 128, 64, 64 });
	longJump->frames.push_back({ 128, 128, 64, 64 });
	longJump->frames.push_back({ 192, 128, 64, 64 });
	longJump->frames.push_back({ 0, 192, 64, 64 });
	longJump->frames.push_back({ 64, 192, 64, 64 });
	longJump->frames.push_back({ 128, 192, 64, 64 });
	longJump->frames.push_back({ 192, 192, 64, 64 });

	BasicAnimation* fall = new BasicAnimation(0.0f);
	fall->frames.push_back({ 192, 64, 64, 64 });

	// Crea los estados del personaje
	StateSwitcher<Animation>* idleState = new StateSwitcher<Animation>(idle);
	StateSwitcher<Animation>* idleUpState = new StateSwitcher<Animation>(idleUp);
	StateSwitcher<Animation>* attackState = new StateSwitcher<Animation>(attack);
	StateSwitcher<Animation>* attackJumpState = new StateSwitcher<Animation>(attackJump);
	StateSwitcher<Animation>* runState = new StateSwitcher<Animation>(run);
	StateSwitcher<Animation>* jumpState = new StateSwitcher<Animation>(jump);
	StateSwitcher<Animation>* longJumpStartState = new StateSwitcher<Animation>(longJumpStart);
	StateSwitcher<Animation>* longJumpState = new StateSwitcher<Animation>(longJump);
	StateSwitcher<Animation>* fallState = new StateSwitcher<Animation>(fall);

	// Crea las transiciones entre los estados
	idleState->AddStateTransition(new StateTransition<Animation>(runState, new FlagGreaterThanCondition("speedX_absolute", 0.0f)));
	idleState->AddStateTransition(new StateTransition<Animation>(jumpState, new FlagEqualsCondition("jumping", true)));
	idleState->AddStateTransition(new StateTransition<Animation>(longJumpStartState, new FlagEqualsCondition("jumping_long", true)));
	idleState->AddStateTransition(new StateTransition<Animation>(fallState, new FlagEqualsCondition("falling", true)));
	idleState->AddStateTransition(new StateTransition<Animation>(idleUpState, new FlagEqualsCondition("looking_up", true)));
	idleState->AddStateTransition(new StateTransition<Animation>(attackState, new FlagEqualsCondition("weapon_attack", true)));

	idleUpState->AddStateTransition(new StateTransition<Animation>(runState, new FlagGreaterThanCondition("speedX_absolute", 0.0f)));
	idleUpState->AddStateTransition(new StateTransition<Animation>(jumpState, new FlagEqualsCondition("jumping", true)));
	idleUpState->AddStateTransition(new StateTransition<Animation>(longJumpStartState, new FlagEqualsCondition("jumping_long", true)));
	idleUpState->AddStateTransition(new StateTransition<Animation>(fallState, new FlagEqualsCondition("falling", true)));
	idleUpState->AddStateTransition(new StateTransition<Animation>(idleState, new FlagEqualsCondition("looking_up", false)));
	idleUpState->AddStateTransition(new StateTransition<Animation>(attackState, new FlagEqualsCondition("weapon_attack", true)));

	attackState->AddStateTransition(new StateTransition<Animation>(idleState, new AnimationEndCondition()));

	attackJumpState->AddStateTransition(new StateTransition<Animation>(jumpState, new AnimationEndCondition()));

	runState->AddStateTransition(new StateTransition<Animation>(idleState, new FlagEqualsCondition("speedX_absolute", 0.0f)));
	runState->AddStateTransition(new StateTransition<Animation>(jumpState, new FlagEqualsCondition("jumping", true)));
	runState->AddStateTransition(new StateTransition<Animation>(longJumpStartState, new FlagEqualsCondition("jumping_long", true)));
	runState->AddStateTransition(new StateTransition<Animation>(fallState, new FlagEqualsCondition("falling", true)));
	runState->AddStateTransition(new StateTransition<Animation>(attackState, new FlagEqualsCondition("weapon_attack", true)));

	jumpState->AddStateTransition(new StateTransition<Animation>(fallState, new FlagEqualsCondition("falling", true)));
	jumpState->AddStateTransition(new StateTransition<Animation>(idleState, new FlagEqualsCondition("jumping", false)));
	jumpState->AddStateTransition(new StateTransition<Animation>(attackJumpState, new FlagEqualsCondition("weapon_attack", true)));

	longJumpStartState->AddStateTransition(new StateTransition<Animation>(longJumpState, new AnimationEndCondition()));
	longJumpStartState->AddStateTransition(new StateTransition<Animation>(fallState, new FlagEqualsCondition("falling", true)));
	longJumpStartState->AddStateTransition(new StateTransition<Animation>(idleState, new FlagEqualsCondition("jumping_long", false)));

	longJumpState->AddStateTransition(new StateTransition<Animation>(fallState, new FlagEqualsCondition("falling", true)));
	longJumpState->AddStateTransition(new StateTransition<Animation>(idleState, new FlagEqualsCondition("jumping_long", false)));

	fallState->AddStateTransition(new StateTransition<Animation>(idleState, new FlagEqualsCondition("falling", false)));
	fallState->AddStateTransition(new StateTransition<Animation>(attackJumpState, new FlagEqualsCondition("weapon_attack", true)));

	// Crea y devuelve el animator
	return new PlayerAnimator(idleState);
}