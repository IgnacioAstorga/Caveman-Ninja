#include "Animator.h"
#include "StateSwitcher.h"
#include "SDL_rect.h"
#include "Application.h"
#include "ModuleAnimation.h"

Animator::Animator(StateSwitcher<Animation>* initialStateSwitcher) : StateMachine(initialStateSwitcher)
{
	this->storedFlip = SDL_FLIP_NONE;
}

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
	// Devuelve la frame actual de la animación actual
	return GetActualState()->GetCurrentFrame();
}

SDL_RendererFlip Animator::GetFlip()
{
	// Devuelve el flip de la animación actual
	return GetActualState()->GetFlip();
}

void Animator::SetFlip(SDL_RendererFlip flip)
{
	// Cambia el flip en la animación actual
	this->storedFlip = flip;
	GetActualState()->SetFlip(flip);
}

void Animator::Increment(float amount)
{
	// Incrementa la frame de la animación actual
	GetActualState()->Increment(amount);

	// Comprueba si la animación actual terminó
	if (IsFinished())	// La animación se ha reiniciado
	{
		SetFlagValue(ANIMATION_END, true);	// Dispara el flag
		SetFlagValue(ANIMATION_END, false);
	}
}

bool Animator::IsFinished()
{
	return GetActualState()->IsFinished();
}

void Animator::OnStateTransition(Animation* lastState, Animation* newState)
{
	// Hace CleanUp de la animaciópn anterior y Start de la siguiente
	lastState->CleanUp();
	newState->Start();
	// Cambia el flip de la nueva animación
	newState->SetFlip(storedFlip);
}
