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
	BasicAnimation* spin = new BasicAnimation(8.0f);
	spin->frames.push_back({ 0, 0, 32, 32 });
	spin->frames.push_back({ 32, 0, 32, 32 });
	spin->frames.push_back({ 64, 0, 32, 32 });
	spin->frames.push_back({ 96, 0, 32, 32 });
	spin->frames.push_back({ 0, 32, 32, 32 });
	spin->frames.push_back({ 32, 32, 32, 32 });
	spin->frames.push_back({ 64, 32, 32, 32 });
	spin->frames.push_back({ 96, 32, 32, 32 });

	BasicAnimation* idle = new BasicAnimation(0.0f);
	idle->frames.push_back({ 32, 32, 32, 32 });

	// Crea los estados del personaje
	StateSwitcher<Animation>* spinState = new StateSwitcher<Animation>(spin);
	StateSwitcher<Animation>* idleState = new StateSwitcher<Animation>(idle);

	// Crea las transiciones entre los estados
	spinState->AddStateTransition(new StateTransition<Animation>(idleState, new FlagEqualsCondition("on_ground", true)));

	// Crea y devuelve el animator
	return new TomahawkAnimator(spinState);
}