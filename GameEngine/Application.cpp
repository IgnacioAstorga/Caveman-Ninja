#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleTime.h"
#include "ModuleAnimation.h"
#include "ModuleParticles.h"
#include "ModuleScene.h"
#include "Globals.h"
#include "Scene.h"

#include <stdlib.h>

using namespace std;

enum application_states
{
	APPLICATION_CREATION,
	APPLICATION_START,
	APPLICATION_UPDATE,
	APPLICATION_FINISH,
	APPLICATION_EXIT
};

Application* App = NULL;

int Application::Run()
{
	int application_return = EXIT_FAILURE;
	application_states state = APPLICATION_CREATION;

	while (state != APPLICATION_EXIT)
	{
		switch (state)
		{
		case APPLICATION_CREATION:
			LOG("Application Creation --------------");
			App = this;
			Create();
			state = APPLICATION_START;
			break;

		case APPLICATION_START:
			LOG("Application Init --------------");
			if (Init() == false)
			{
				LOG("Application Init exits with error -----");
				state = APPLICATION_EXIT;
			}
			else
			{
				state = APPLICATION_UPDATE;
				LOG("Application Update --------------");
			}
			break;

		case APPLICATION_UPDATE:
		{
			int update_return = Update();
			if (update_return == UPDATE_ERROR)
			{
				LOG("Application Update exits with error -----");
				state = APPLICATION_EXIT;
			}
			if (update_return == UPDATE_STOP)
				state = APPLICATION_FINISH;
		}
		break;

		case APPLICATION_FINISH:
			LOG("Application CleanUp --------------");
			if (CleanUp() == false)
			{
				LOG("Application CleanUp exits with error -----");
			}
			else
				application_return = EXIT_SUCCESS;
			state = APPLICATION_EXIT;
			break;
		}
	}

	LOG("Bye :)\n");
	return application_return;
}

Application::Application()
{
	// La creación ha sido delegada al método Create()
}

Application::~Application()
{
	for (list<Module*>::iterator it = modules.begin(); it != modules.end(); ++it)
		RELEASE(*it);

	// Llamada al delegado
	OnDestroyApplication();
}

void Application::Create() {
	modules.push_back(input = new ModuleInput());
	modules.push_back(window = new ModuleWindow());
	modules.push_back(textures = new ModuleTextures());
	modules.push_back(audio = new ModuleAudio());
	modules.push_back(time = new ModuleTime());
	modules.push_back(animation = new ModuleAnimation());
	modules.push_back(particles = new ModuleParticles());
	modules.push_back(scene = new ModuleScene());

	// El renderer siempre es el último módulo
	modules.push_back(renderer = new ModuleRender());

	// Llamada al delegado
	OnCreateApplication();
}

bool Application::Init()
{
	bool ret = true;

	// Inicialización de los módulos
	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Init();	// Se hace Init incluso a módulos desactivados

	// Llamada al delegado que determina la escena inicial
	try {
		scene->ChangeScene(OnCreateScene());
		scene->DoChangeScene();	// Fuerza el cambio de forma inmediata
	}
	catch (const runtime_error re) {
		LOG("Unhandled user runtime error: ", re.what());
	}
	catch (const exception e) {
		LOG("Unhandled user exception: ", e.what());
	}
	catch (...) {
		LOG("Unknown unhandled user error.");
	}

	// Arranque de los módulos
	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		if((*it)->IsEnabled() == true)
			ret = (*it)->Start();

	// Llamada al delegado que actúa tras el arranque de la escena
	try {
		ret = OnPopulateScene(scene->currentScene);
	}
	catch (const runtime_error re) {
		LOG("Unhandled user runtime error: ", re.what());
	}
	catch (const exception e) {
		LOG("Unhandled user exception: ", e.what());
	}
	catch (...) {
		LOG("Unknown unhandled user error.");
	}

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if((*it)->IsEnabled() == true) 
			ret = (*it)->PreUpdate();

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if((*it)->IsEnabled() == true) 
			ret = (*it)->Update();

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if((*it)->IsEnabled() == true) 
			ret = (*it)->PostUpdate();

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(list<Module*>::reverse_iterator it = modules.rbegin(); it != modules.rend() && ret; ++it)
		if((*it)->IsEnabled() == true) 
			ret = (*it)->CleanUp();

	return ret;
}

