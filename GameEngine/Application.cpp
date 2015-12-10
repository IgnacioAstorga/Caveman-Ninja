#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleScene.h"
#include "Globals.h"

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
	// El constructor no hace nada
}

Application::~Application()
{
	Destroy();
}

void Application::Create() {

	// Creación de la aplicación
	modules.push_back(input = new ModuleInput());
	modules.push_back(window = new ModuleWindow());
	modules.push_back(renderer = new ModuleRender());
	modules.push_back(textures = new ModuleTextures());
	modules.push_back(audio = new ModuleAudio());
	modules.push_back(scene = new ModuleScene());

	try {
		// Llamada al método hijo (después)
		OnCreateApplication();
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
}

void Application::Destroy() {
	try {
		// Llamada al método hijo
		OnDestroyApplication();
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

	for (list<Module*>::iterator it = modules.begin(); it != modules.end(); ++it)
		RELEASE(*it);
}

bool Application::Init()
{
	bool ret = true;
	try {
		// Llamada al método hijo
		ret = OnApplicationInit();
	}
	catch (const runtime_error re) {
		LOG("Unhandled user runtime error: ", re.what());
		ret = false;
	}
	catch (const exception e) {
		LOG("Unhandled user exception: ", e.what());
		ret = false;
	}
	catch (...) {
		LOG("Unknown unhandled user error.");
		ret = false;
	}

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Init();	// Se hace Init incluso a módulos desactivados

	try {
		// Llamada al método hijo
		ret = OnApplicationStart();
	}
	catch (const runtime_error re) {
		LOG("Unhandled user runtime error: ", re.what());
		ret = false;
	}
	catch (const exception e) {
		LOG("Unhandled user exception: ", e.what());
		ret = false;
	}
	catch (...) {
		LOG("Unknown unhandled user error.");
		ret = false;
	}

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
	{
		if((*it)->IsEnabled() == true)
			ret = (*it)->Start();
	}

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	try {
		// Llamada al método hijo
		ret = OnApplicationUpdate();
	}
	catch (const runtime_error re) {
		LOG("Unhandled user runtime error: ", re.what());
		ret = UPDATE_ERROR;
	}
	catch (const exception e) {
		LOG("Unhandled user exception: ", e.what());
		ret = UPDATE_ERROR;
	}
	catch (...) {
		LOG("Unknown unhandled user error.");
		ret = UPDATE_ERROR;
	}

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
	try {
		// Llamada al método hijo
		ret = OnApplicationCleanUp();
	}
	catch (const runtime_error re) {
		LOG("Unhandled user runtime error: ", re.what());
		ret = false;
	}
	catch (const exception e) {
		LOG("Unhandled user exception: ", e.what());
		ret = false;
	}
	catch (...) {
		LOG("Unknown unhandled user error.");
		ret = false;
	}

	for(list<Module*>::reverse_iterator it = modules.rbegin(); it != modules.rend() && ret; ++it)
		if((*it)->IsEnabled() == true) 
			ret = (*it)->CleanUp();

	return ret;
}

