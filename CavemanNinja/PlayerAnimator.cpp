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
	BasicAnimation* idleRight = new BasicAnimation(0.0f);
	idleRight->frames.push_back({ 0, 0, 64, 64 });
	BasicAnimation* idleLeft = new BasicAnimation(*idleRight);
	idleLeft->flip = SDL_FLIP_HORIZONTAL;

	BasicAnimation* runRight = new BasicAnimation(8.0f);
	runRight->frames.push_back({ 64, 0, 64, 64 });
	runRight->frames.push_back({ 128, 0, 64, 64 });
	runRight->frames.push_back({ 192, 0, 64, 64 });
	runRight->frames.push_back({ 0, 64, 64, 64 });
	BasicAnimation* runLeft = new BasicAnimation(*runRight);
	runLeft->flip = SDL_FLIP_HORIZONTAL;

	BasicAnimation* jumpRight = new BasicAnimation(3.0f, SDL_FLIP_NONE, false);
	jumpRight->frames.push_back({ 64, 64, 64, 64 });
	jumpRight->frames.push_back({ 128, 64, 64, 64 });
	BasicAnimation* jumpLeft = new BasicAnimation(*jumpRight);
	jumpLeft->flip = SDL_FLIP_HORIZONTAL;

	BasicAnimation* fallRight = new BasicAnimation(0.0f);
	fallRight->frames.push_back({ 192, 64, 64, 64 });
	BasicAnimation* fallLeft = new BasicAnimation(*fallRight);
	fallLeft->flip = SDL_FLIP_HORIZONTAL;

	// Crea los estados del personaje
	StateSwitcher<Animation>* idleStateRight = new StateSwitcher<Animation>(idleRight);
	StateSwitcher<Animation>* idleStateLeft = new StateSwitcher<Animation>(idleLeft);
	StateSwitcher<Animation>* runStateRight = new StateSwitcher<Animation>(runRight);
	StateSwitcher<Animation>* runStateLeft = new StateSwitcher<Animation>(runLeft);
	StateSwitcher<Animation>* jumpStateRight = new StateSwitcher<Animation>(jumpRight);
	StateSwitcher<Animation>* jumpStateLeft = new StateSwitcher<Animation>(jumpLeft);
	StateSwitcher<Animation>* fallStateRight = new StateSwitcher<Animation>(fallRight);
	StateSwitcher<Animation>* fallStateLeft = new StateSwitcher<Animation>(fallLeft);

	// Crea las transiciones entre los estados
	idleStateRight->AddStateTransition(new StateTransition<Animation>(runStateRight, new FlagGreaterThanCondition("speedX", 0.0f)));
	idleStateRight->AddStateTransition(new StateTransition<Animation>(runStateLeft, new FlagLessThanCondition("speedX", 0.0f)));
	idleStateRight->AddStateTransition(new StateTransition<Animation>(jumpStateRight, new FlagEqualsCondition("jumping", true)));
	idleStateRight->AddStateTransition(new StateTransition<Animation>(fallStateRight, new FlagEqualsCondition("falling", true)));

	idleStateLeft->AddStateTransition(new StateTransition<Animation>(runStateRight, new FlagGreaterThanCondition("speedX", 0.0f)));
	idleStateLeft->AddStateTransition(new StateTransition<Animation>(runStateLeft, new FlagLessThanCondition("speedX", 0.0f)));
	idleStateLeft->AddStateTransition(new StateTransition<Animation>(jumpStateLeft, new FlagEqualsCondition("jumping", true)));
	idleStateLeft->AddStateTransition(new StateTransition<Animation>(fallStateLeft, new FlagEqualsCondition("falling", true)));

	runStateRight->AddStateTransition(new StateTransition<Animation>(idleStateRight, new FlagEqualsCondition("speedX", 0.0f)));
	runStateRight->AddStateTransition(new StateTransition<Animation>(runStateLeft, new FlagLessThanCondition("speedX", 0.0f)));
	runStateRight->AddStateTransition(new StateTransition<Animation>(jumpStateRight, new FlagEqualsCondition("jumping", true)));
	runStateRight->AddStateTransition(new StateTransition<Animation>(fallStateRight, new FlagEqualsCondition("falling", true)));

	runStateLeft->AddStateTransition(new StateTransition<Animation>(idleStateLeft, new FlagEqualsCondition("speedX", 0.0f)));
	runStateLeft->AddStateTransition(new StateTransition<Animation>(runStateRight, new FlagGreaterThanCondition("speedX", 0.0f)));
	runStateLeft->AddStateTransition(new StateTransition<Animation>(jumpStateLeft, new FlagEqualsCondition("jumping", true)));
	runStateLeft->AddStateTransition(new StateTransition<Animation>(fallStateLeft, new FlagEqualsCondition("falling", true)));

	jumpStateRight->AddStateTransition(new StateTransition<Animation>(jumpStateLeft, new FlagLessThanCondition("speedX", 0.0f)));
	jumpStateRight->AddStateTransition(new StateTransition<Animation>(fallStateRight, new FlagEqualsCondition("falling", true)));

	jumpStateLeft->AddStateTransition(new StateTransition<Animation>(jumpStateRight, new FlagGreaterThanCondition("speedX", 0.0f)));
	jumpStateLeft->AddStateTransition(new StateTransition<Animation>(fallStateLeft, new FlagEqualsCondition("falling", true)));

	fallStateRight->AddStateTransition(new StateTransition<Animation>(fallStateLeft, new FlagLessThanCondition("speedX", 0.0f)));
	fallStateRight->AddStateTransition(new StateTransition<Animation>(idleStateRight, new FlagEqualsCondition("falling", false)));

	fallStateLeft->AddStateTransition(new StateTransition<Animation>(fallStateRight, new FlagGreaterThanCondition("speedX", 0.0f)));
	fallStateLeft->AddStateTransition(new StateTransition<Animation>(idleStateLeft, new FlagEqualsCondition("falling", false)));

	// Crea y devuelve el animator
	return new PlayerAnimator(idleStateRight);
}