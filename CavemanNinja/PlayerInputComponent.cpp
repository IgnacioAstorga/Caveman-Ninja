#include "PlayerInputComponent.h"
#include "Application.h"
#include "ModuleInput.h"
#include "Entity.h"
#include "Transform.h"
#include "SDL.h"

PlayerInputComponent::PlayerInputComponent(float speed) : speed(speed) {}

PlayerInputComponent::~PlayerInputComponent() {}

bool PlayerInputComponent::OnPreUpdate()
{
	// Lee las pulsaciones de las teclas A y D y las mapea a la velocidad
	KeyState left = App->input->GetKey(SDL_SCANCODE_A);
	KeyState right = App->input->GetKey(SDL_SCANCODE_D);
	bool leftPressed = left == KEY_DOWN || left == KEY_REPEAT;
	bool rightPressed = right == KEY_DOWN || right == KEY_REPEAT;

	if (leftPressed && !rightPressed)
		entity->transform->speed.x = -speed;
	else if (!leftPressed && rightPressed)
		entity->transform->speed.x = speed;
	else
		entity->transform->speed.x = 0.0f;

	return true;
}
