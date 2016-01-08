#include "ModuleTime.h"

#include "SDL.h"

#include <stdlib.h>
#include <time.h>

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

	// Establece una semilla para los números aleatorios
	srand(time(NULL));

	return true;
}

update_status ModuleTime::PreUpdate()
{
	// Calcula el tiempo transcurrido entre esta frame y la anterior (en segundos)
	unsigned long newFrameTime = SDL_GetTicks();
	deltaTime = (newFrameTime - lastFrameTime) / 1000.0f;
	lastFrameTime = newFrameTime;
	return UPDATE_CONTINUE;
}

bool ModuleTime::CleanUp()
{
	// Por ahora no hace nada
	return true;
}

float ModuleTime::DeltaTime()
{
	return deltaTime;
}