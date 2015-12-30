#include "Animator.h"
#include "StateSwitcher.h"
#include "SDL_rect.h"
#include "Application.h"
#include "ModuleAnimation.h"

Animator::Animator(StateSwitcher<Animation>* initialStateSwitcher) : StateMachine(initialStateSwitcher) {}

Animator::~Animator() {}

bool Animator::Start()
{
	// Llama al delegado
	return OnStart();
}

bool Animator::CleanUp()
{
	// Llama al delegado
	return OnCleanUp();
}

SDL_Rect& Animator::GetCurrentFrame()
{
	// Devuelve la frame actual de la animaci�n actual
	return GetActualState()->GetCurrentFrame();
}

SDL_RendererFlip Animator::GetFlip()
{
	// Devuelve el flip de la animaci�n actual
	return GetActualState()->GetFlip();
}

void Animator::Increment(float amount)
{
	// Incrementa la frame de la animaci�n actual
	GetActualState()->Increment(amount);
}

void Animator::OnStateTransition(Animation* lastState, Animation* newState)
{
	// Hace CleanUp de la animaci�pn anterior y Start de la siguiente
	lastState->CleanUp();
	newState->Start();
}
