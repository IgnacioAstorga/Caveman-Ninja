#include "Animator.h"
#include "StateSwitcher.h"
#include "SDL_rect.h"
#include "Application.h"
#include "ModuleAnimation.h"

Animator::Animator(AnimationState* initialStateSwitcher) : StateMachine(initialStateSwitcher)
{
	this->storedFlip = SDL_FLIP_NONE;
}

Animator::~Animator() {}

bool Animator::Start()
{
	// Inicializa la animaci�n actual
	bool ret = GetActualState()->Start();

	// Llama al delegado
	return OnStart() && ret;
}

bool Animator::CleanUp()
{
	// Limpia la animaci�n actual
	bool ret = GetActualState()->CleanUp();

	// Llama al delegado
	return OnCleanUp() && ret;
}

SDL_Rect Animator::GetCurrentFrame() const
{
	// Devuelve la frame actual de la animaci�n actual
	return GetActualState()->GetCurrentFrame();
}

SDL_RendererFlip Animator::GetFlip() const
{
	// Devuelve el flip de la animaci�n actual
	return GetActualState()->GetFlip();
}

void Animator::SetFlip(SDL_RendererFlip flip)
{
	// Cambia el flip en la animaci�n actual
	this->storedFlip = flip;
	GetActualState()->SetFlip(flip);
}

void Animator::Increment(float amount)
{
	// Incrementa la frame de la animaci�n actual
	GetActualState()->Increment(amount);

	// Comprueba si la animaci�n actual termin�
	if (IsFinished())	// La animaci�n se ha reiniciado
		Trigger(ANIMATION_END);
}

bool Animator::IsFinished() const
{
	return GetActualState()->IsFinished();
}

void Animator::OnStateTransition(Animation* lastState, Animation* newState)
{
	// Hace CleanUp de la animaci�pn anterior y Start de la siguiente
	lastState->CleanUp();
	newState->Start();
	// Cambia el flip de la nueva animaci�n
	newState->SetFlip(storedFlip);
}
