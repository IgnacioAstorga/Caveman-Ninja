#include "PlayerAnimator.h"
#include "StateTransition.h"
#include "StateSwitcher.h"
#include "BasicAnimation.h"
#include "FlagGreaterThanCondition.h"
#include "FlagLessThanCondition.h"
#include "FlagEqualsCondition.h"

PlayerAnimator::PlayerAnimator(StateSwitcher<Animation>* initialState)
	: Animator(initialState) {}

PlayerAnimator* PlayerAnimator::Create()
{
	// Crea las animaciones del personaje
	BasicAnimation* idle = new BasicAnimation(0.0f);
	idle->frames.push_back({ 0, 0, 64, 64 });

	BasicAnimation* run = new BasicAnimation(8.0f);
	run->frames.push_back({ 64, 0, 64, 64 });
	run->frames.push_back({ 128, 0, 64, 64 });
	run->frames.push_back({ 192, 0, 64, 64 });
	run->frames.push_back({ 0, 64, 64, 64 });

	BasicAnimation* jump = new BasicAnimation(3.0f, SDL_FLIP_NONE, false);
	jump->frames.push_back({ 64, 64, 64, 64 });
	jump->frames.push_back({ 128, 64, 64, 64 });

	BasicAnimation* longJump = new BasicAnimation(16.0f, SDL_FLIP_NONE, false);
	longJump->frames.push_back({ 64, 64, 64, 64 });
	longJump->frames.push_back({ 64, 64, 64, 64 });
	longJump->frames.push_back({ 64, 64, 64, 64 });
	longJump->frames.push_back({ 0, 128, 64, 64 });
	longJump->frames.push_back({ 64, 128, 64, 64 });
	longJump->frames.push_back({ 128, 128, 64, 64 });
	longJump->frames.push_back({ 192, 128, 64, 64 });
	longJump->frames.push_back({ 0, 192, 64, 64 });
	longJump->frames.push_back({ 64, 192, 64, 64 });
	longJump->frames.push_back({ 128, 192, 64, 64 });
	longJump->frames.push_back({ 192, 192, 64, 64 });
	longJump->frames.push_back({ 0, 128, 64, 64 });
	longJump->frames.push_back({ 64, 128, 64, 64 });
	longJump->frames.push_back({ 128, 128, 64, 64 });
	longJump->frames.push_back({ 192, 128, 64, 64 });
	longJump->frames.push_back({ 0, 192, 64, 64 });
	longJump->frames.push_back({ 64, 192, 64, 64 });
	longJump->frames.push_back({ 128, 192, 64, 64 });
	longJump->frames.push_back({ 192, 192, 64, 64 });
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
	StateSwitcher<Animation>* runState = new StateSwitcher<Animation>(run);
	StateSwitcher<Animation>* jumpState = new StateSwitcher<Animation>(jump);
	StateSwitcher<Animation>* longJumpState = new StateSwitcher<Animation>(longJump);
	StateSwitcher<Animation>* fallState = new StateSwitcher<Animation>(fall);

	// Crea las transiciones entre los estados
	idleState->AddStateTransition(new StateTransition<Animation>(runState, new FlagGreaterThanCondition("speedX_absolute", 0.0f)));
	idleState->AddStateTransition(new StateTransition<Animation>(jumpState, new FlagEqualsCondition("jumping", true)));
	idleState->AddStateTransition(new StateTransition<Animation>(longJumpState, new FlagEqualsCondition("jumping_long", true)));
	idleState->AddStateTransition(new StateTransition<Animation>(fallState, new FlagEqualsCondition("falling", true)));

	runState->AddStateTransition(new StateTransition<Animation>(idleState, new FlagEqualsCondition("speedX_absolute", 0.0f)));
	runState->AddStateTransition(new StateTransition<Animation>(jumpState, new FlagEqualsCondition("jumping", true)));
	runState->AddStateTransition(new StateTransition<Animation>(longJumpState, new FlagEqualsCondition("jumping_long", true)));
	runState->AddStateTransition(new StateTransition<Animation>(fallState, new FlagEqualsCondition("falling", true)));

	jumpState->AddStateTransition(new StateTransition<Animation>(fallState, new FlagEqualsCondition("falling", true)));
	jumpState->AddStateTransition(new StateTransition<Animation>(idleState, new FlagEqualsCondition("jumping", false)));

	longJumpState->AddStateTransition(new StateTransition<Animation>(fallState, new FlagEqualsCondition("falling", true)));
	longJumpState->AddStateTransition(new StateTransition<Animation>(idleState, new FlagEqualsCondition("long_jumping", false)));

	fallState->AddStateTransition(new StateTransition<Animation>(idleState, new FlagEqualsCondition("falling", false)));

	// Crea y devuelve el animator
	return new PlayerAnimator(idleState);
}