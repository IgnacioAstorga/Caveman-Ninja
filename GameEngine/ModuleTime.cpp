#include "ModuleTime.h"

#include "SDL.h"

ModuleTime::ModuleTime(bool start_enabled) : Module(start_enabled)
{
	// Por ahora no hace nada
}

ModuleTime::~ModuleTime()
{
	// Por ahora no hace nada
}

bool ModuleTime::Start()
{
	// Establece el tiempo de la frame inicial (en milisegundos)
	lastFrameTime = SDL_GetTicks();
}

update_status ModuleTime::PreUpdate()
{
	// Calcula el tiempo transcurrido entre esta frame y la anterior (en segundos)
	unsigned long newFrameTime = SDL_GetTicks();
	deltaTime = (newFrameTime - lastFrameTime) / 1000.0f;
	lastFrameTime = newFrameTime;
}

bool ModuleTime::CleanUp()
{
	// Por ahora no hace nada
}

float ModuleTime::DeltaTime()
{
	return deltaTime;
}