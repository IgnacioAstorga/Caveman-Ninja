#include "TomahawkAnimator.h"
#include "StateTransition.h"
#include "StateSwitcher.h"
#include "BasicAnimation.h"
#include "FlagEqualsCondition.h"

TomahawkAnimator::TomahawkAnimator(StateSwitcher<Animation>* initialState)
	: Animator(initialState) {}

TomahawkAnimator* TomahawkAnimator::Create()
{
	// Crea las animaciones del arma
	BasicAnimation* spin = new BasicAnimation(128, 64, 4, 2, 8.0f);
	spin->frames.push_back({ 0, 0 });
	spin->frames.push_back({ 1, 0 });
	spin->frames.push_back({ 2, 0 });
	spin->frames.push_back({ 3, 0 });
	spin->frames.push_back({ 0, 1 });
	spin->frames.push_back({ 1, 1 });
	spin->frames.push_back({ 2, 1 });
	spin->frames.push_back({ 3, 1 });

	BasicAnimation* idle = new BasicAnimation(128, 64, 4, 2, 0.0f, false);
	idle->frames.push_back({ 1, 1 });

	// Crea los estados del personaje
	StateSwitcher<Animation>* spinState = new StateSwitcher<Animation>(spin);
	StateSwitcher<Animation>* idleState = new StateSwitcher<Animation>(idle);

	// Crea las transiciones entre los estados
	spinState->AddStateTransition(new StateTransition<Animation>(idleState, new FlagEqualsCondition("on_ground", true)));

	// Crea y devuelve el animator
	return new TomahawkAnimator(spinState);
}