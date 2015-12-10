#include "Scene.h"

// TODO

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Create()
{
}

void Scene::Destroy()
{
}

bool Scene::Start()
{
	return false;
}

update_status Scene::PreUpdate()
{
	return update_status();
}

update_status Scene::Update()
{
	return update_status();
}

update_status Scene::PostUpdate()
{
	return update_status();
}

bool Scene::CleanUp()
{
	return false;
}

void Scene::AddChild(Entity & child)
{
}

void Scene::RemoveChild(Entity & child)
{
}

const list<Entity*> Scene::GetChildren()
{
	return list<Entity*>();
}

Entity * Scene::FindChild(string name)
{
	return nullptr;
}

list<Entity*> Scene::FindAllChildren(string name)
{
	return list<Entity*>();
}

void Scene::OnCreateScene()
{
}

void Scene::OnDestroyScene()
{
}

void Scene::OnSceneStart()
{
}

void Scene::OnSceneClean()
{
}

void Scene::OnScenePreUpdate()
{
}

void Scene::OnSceneUpdate()
{
}

void Scene::OnScenePostUpdate()
{
}
