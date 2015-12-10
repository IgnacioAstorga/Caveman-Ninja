#include "Scene.h"
#include "Entity.h"

Scene::Scene()
{
	Create();
}

Scene::~Scene()
{
	Destroy();
}

void Scene::Create()
{
	// Crea la entidad padre
	root = new Entity();

	try {
		// Llamada al método hijo (después)
		OnCreateScene();
	}
	catch (const runtime_error re) {
		LOG("Unhandled user runtime error while creating scene: ", re.what());
	}
	catch (const exception e) {
		LOG("Unhandled user exception while creating scene: ", e.what());
	}
	catch (...) {
		LOG("Unknown unhandled user error while creating scene.");
	}
}

void Scene::Destroy()
{
	try {
		// Llamada al método hijo
		OnDestroyScene();
	}
	catch (const runtime_error re) {
		LOG("Unhandled user runtime error while destroying scene: ", re.what());
	}
	catch (const exception e) {
		LOG("Unhandled user exception while destroying scene: ", e.what());
	}
	catch (...) {
		LOG("Unknown unhandled user error while destroying scene.");
	}

	// Limpia las entidades
	RELEASE(root);
}

bool Scene::Start()
{
	bool ret = true;
	try {
		// Llamada al método hijo
		ret = OnSceneStart();
	}
	catch (const runtime_error re) {
		LOG("Unhandled user runtime error while starting scene: ", re.what());
		ret = false;
	}
	catch (const exception e) {
		LOG("Unhandled user exception while starting scene: ", e.what());
		ret = false;
	}
	catch (...) {
		LOG("Unknown unhandled user error while starting scene.");
		ret = false;
	}

	// Llamada al Start de los hijos de la escena
	if (root->IsEnabled() == true && ret == true)
		ret = root->Start();

	return ret;
}

update_status Scene::PreUpdate()
{
	update_status ret = UPDATE_CONTINUE;
	try {
		// Llamada al método hijo
		ret = OnScenePreUpdate();
	}
	catch (const runtime_error re) {
		LOG("Unhandled user runtime error while preupdating scene: ", re.what());
		ret = UPDATE_ERROR;
	}
	catch (const exception e) {
		LOG("Unhandled user exception while preupdating scene: ", e.what());
		ret = UPDATE_ERROR;
	}
	catch (...) {
		LOG("Unknown unhandled user error while preupdating scene.");
		ret = UPDATE_ERROR;
	}

	// Llamada al PreUpdate de los hijos de la escena
	if (root->IsEnabled() == true && ret == UPDATE_CONTINUE)
		ret = root->PreUpdate();

	return ret;
}

update_status Scene::Update()
{
	update_status ret = UPDATE_CONTINUE;
	try {
		// Llamada al método hijo
		ret = OnSceneUpdate();
	}
	catch (const runtime_error re) {
		LOG("Unhandled user runtime error while updating scene: ", re.what());
		ret = UPDATE_ERROR;
	}
	catch (const exception e) {
		LOG("Unhandled user exception while updating scene: ", e.what());
		ret = UPDATE_ERROR;
	}
	catch (...) {
		LOG("Unknown unhandled user error while updating scene.");
		ret = UPDATE_ERROR;
	}

	// Llamada al Update de los hijos de la escena
	if (root->IsEnabled() == true && ret == UPDATE_CONTINUE)
		ret = root->Update();

	return ret;
}

update_status Scene::PostUpdate()
{
	update_status ret = UPDATE_CONTINUE;
	try {
		// Llamada al método hijo
		ret = OnScenePostUpdate();
	}
	catch (const runtime_error re) {
		LOG("Unhandled user runtime error while postupdating scene: ", re.what());
		ret = UPDATE_ERROR;
	}
	catch (const exception e) {
		LOG("Unhandled user exception while postupdating scene: ", e.what());
		ret = UPDATE_ERROR;
	}
	catch (...) {
		LOG("Unknown unhandled user error while postupdating scene.");
		ret = UPDATE_ERROR;
	}

	// Llamada al PostUpdate de los hijos de la escena
	if (root->IsEnabled() == true && ret == UPDATE_CONTINUE)
		ret = root->PostUpdate();

	return ret;
}

bool Scene::CleanUp()
{
	bool ret = true;
	try {
		// Llamada al método hijo
		ret = OnSceneCleanUp();
	}
	catch (const runtime_error re) {
		LOG("Unhandled user runtime error while cleaning scene: ", re.what());
		ret = false;
	}
	catch (const exception e) {
		LOG("Unhandled user exception while cleaning scene: ", e.what());
		ret = false;
	}
	catch (...) {
		LOG("Unknown unhandled user error while cleaning scene.");
		ret = false;
	}

	// Llamada al CleanUp de los hijos de la escena
	if (root->IsEnabled() == true && ret == true)
		ret = root->CleanUp();

	return ret;
}

void Scene::AddChild(Entity* child)
{
	root->AddChild(child);
}

void Scene::RemoveChild(Entity* child)
{
	root->RemoveChild(child);
}

const list<Entity*>& Scene::GetChildren()
{
	return root->GetChildren();
}

Entity* Scene::FindChild(string name)
{
	return root->FindChild(name);
}

Entity * Scene::FindChild(string name, int deepness)
{
	return root->FindChild(name, deepness);
}

template<class T>
inline T* Scene::FindChild()
{
	return root->FindChild<T>();
}

template<class T>
T* Scene::FindChild(int deepness)
{
	return root->FindChild<T>(deepness);
}

list<Entity*> Scene::FindAllChildren(string name)
{
	return root->FindAllChildren(name);
}

list<Entity*> Scene::FindAllChildren(string name, int deepness)
{
	return root->FindAllChildren(name, deepness);
}

template<class T>
inline list<T*> Scene::FindAllChildren()
{
	return root->FindAllChildren<T>();
}

template<class T>
list<T*> Scene::FindAllChildren(int deepness)
{
	return root->FindAllChildren<T>(deepness);
}

