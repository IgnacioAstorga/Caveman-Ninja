#include "Entity.h"
#include "Transform.h"
#include "Scene.h"
#include "Component.h"

#include <typeinfo>

Entity::Entity(bool start_enabled) : enabled(start_enabled)
{
	dead = false;

	// Crea el transform
	transform = new Transform(this);

	// Llamada al delegado
	OnCreate();
}

Entity::~Entity()
{
	// Llamada al delegado (antes)
	OnDestroy();

	// Limpia la lista de hijos
	for (list<Entity*>::iterator it = children.begin(); it != children.end(); ++it)
		RELEASE(*it);
	children.clear();

	// Limpia la lista de componentes
	for (list<Component*>::iterator it = components.begin(); it != components.end(); ++it)
		RELEASE(*it);
	components.clear();

	// Destruye el transform
	RELEASE(transform);
}

Entity* Entity::Instantiate(string name, Scene* scene)
{
	return Instantiate(name, 0, 0, scene);
}

Entity* Entity::Instantiate(string name, Entity* parent)
{
	return Instantiate(name, 0, 0, parent);
}

Entity* Entity::Instantiate(string name, float x, float y, Scene* scene)
{
	this->name = name;
	scene->AddChild(this);
	this->scene = scene;
	transform->SetPosition(x, y);

	return this;
}

Entity* Entity::Instantiate(string name, float x, float y, Entity* parent)
{
	this->name = name;
	parent->AddChild(this);
	this->scene = parent->scene;
	transform->SetPosition(x, y);

	return this;
}

void Entity::Destroy()
{
	// Marca la entidad para morir
	dead = true;
}

bool Entity::IsEnabled()
{
	return enabled;
}

bool Entity::Enable()
{
	if (enabled == false)
		return enabled = Start();

	return true;
}

bool Entity::Disable()
{
	if (enabled == true)
		return enabled = !CleanUp();

	return true;
}

bool Entity::Start()
{
	// Llamada al delegado
	bool ret = OnStart();

	// Llamada al Start de los hijos de la entidad
	for (list<Entity*>::iterator it = children.begin(); it != children.end() && ret; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->Start();

	// Llamada al Start de los componentes de la entidad
	for (list<Component*>::iterator it = components.begin(); it != components.end() && ret; ++it)
		if ((*it)->IsEnabled() == true)
			if (!(*it)->Start())
				LOG("Error al hacer Start en el componente: ", typeid(*(*it)).name());

	return ret;
}

update_status Entity::PreUpdate()
{
	update_status ret = UPDATE_CONTINUE;

	// Llamada al PreUpdate de los hijos de la entidad
	for (list<Entity*>::iterator it = children.begin(); it != children.end() && ret == UPDATE_CONTINUE; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->PreUpdate();

	// Llamada al PreUpdate de los componentes de la entidad
	for (list<Component*>::iterator it = components.begin(); it != components.end() && ret == UPDATE_CONTINUE; ++it)
		if ((*it)->IsEnabled() == true)
			if (!(*it)->PreUpdate())
				LOG("Error al hacer PreUpdate en el componente: ", typeid(*(*it)).name());

	return ret;
}

update_status Entity::Update()
{
	update_status ret = UPDATE_CONTINUE;

	// Llamada al Update de los hijos de la entidad
	for (list<Entity*>::iterator it = children.begin(); it != children.end() && ret == UPDATE_CONTINUE; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->Update();

	// Llamada al Update de los componentes de la entidad
	for (list<Component*>::iterator it = components.begin(); it != components.end() && ret == UPDATE_CONTINUE; ++it)
		if ((*it)->IsEnabled() == true)
			if (!(*it)->Update())
				LOG("Error al hacer Update en el componente: ", typeid(*(*it)).name());

	return ret;
}

update_status Entity::PostUpdate()
{
	update_status ret = UPDATE_CONTINUE;

	// Llamada al PostUpdate de los hijos de la entidad
	for (list<Entity*>::iterator it = children.begin(); it != children.end() && ret == UPDATE_CONTINUE; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->PostUpdate();

	// Llamada al PostUpdate de los componentes de la entidad
	for (list<Component*>::iterator it = components.begin(); it != components.end() && ret == UPDATE_CONTINUE; ++it)
		if ((*it)->IsEnabled() == true)
			if (!(*it)->PostUpdate())
				LOG("Error al hacer PostUpdate en el componente: ", typeid(*(*it)).name());

	// Por último, elimina todas sus entidades hijas que hayan muerto
	list<Entity*> toDestroy;
	for (list<Entity*>::iterator it = children.begin(); it != children.end() && ret == UPDATE_CONTINUE; ++it)
		if ((*it)->dead == true)
			toDestroy.push_back(*it);
	// Forma segura de destruir elementos mientras se recorre la lista
	for (list<Entity*>::iterator it = toDestroy.begin(); it != toDestroy.end() && ret == UPDATE_CONTINUE; ++it) {
		(*it)->CleanUp();
		RELEASE(*it);
	}
	toDestroy.clear();

	return ret;
}

bool Entity::CleanUp()
{
	// Llamada al delegado
	bool ret = OnCleanUp();

	// Llamada al CleanUp de los hijos de la entidad
	for (list<Entity*>::iterator it = children.begin(); it != children.end() && ret; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->CleanUp();

	// Llamada al CleanUp de los componentes de la entidad
	for (list<Component*>::iterator it = components.begin(); it != components.end() && ret; ++it)
		if ((*it)->IsEnabled() == true)
			if (!(*it)->CleanUp())
				LOG("Error al hacer CleanUp en el componente: ", typeid(*(*it)).name());

	return ret;
}

Entity* Entity::GetParent()
{
	return parent;
}

void Entity::SetParent(Entity* entity)
{
	if (entity == nullptr) {
		if (parent != nullptr)
			parent->RemoveChild(this);
		parent = nullptr;
	}
	else
		entity->AddChild(this);
}

void Entity::AddChild(Entity* child)
{
	if (child->parent != nullptr)
		child->parent->RemoveChild(child);
	child->parent = this;
	children.push_back(child);
	child->Start();
}

void Entity::RemoveChild(Entity* child)
{
	if (child->parent == this)
	{
		child->CleanUp();
		child->parent = nullptr;
		children.remove(child);
	}
}

const list<Entity*>& Entity::GetChildren()
{
	return children;
}

Entity* Entity::FindChild(string name)
{
	return FindChild(name, -1);
}

Entity * Entity::FindChild(string name, int deepness)
{
	for (list<Entity*>::iterator it = children.begin(); it != children.end(); ++it)
	{
		if ((*it)->name == name)
			return *it;
		else if (deepness != 0)
		{
			Entity* ret = (*it)->FindChild(name, deepness - 1);
			if (ret != nullptr)
				return ret;
		}
	}
	return nullptr;
}

template<class T>
inline T* Entity::FindChild()
{
	return FindChild<T>(-1);
}

template<class T>
T * Entity::FindChild(int deepness)
{
	for (list<Entity*>::iterator it = children.begin(); it != children.end(); ++it)
	{
		if (dynamic_cast<T*>(*it) != NULL)
			return *it;
		else if (deepness != 0)
		{
			Entity* ret = (*it)->FindChild<T>(deepness - 1);
			if (ret != nullptr)
				return ret;
		}
	}
	return nullptr;
}

list<Entity*> Entity::FindAllChildren(string name)
{
	return FindAllChildren(name, -1);
}

list<Entity*> Entity::FindAllChildren(string name, int deepness)
{
	list<Entity*> allChildren;
	for (list<Entity*>::iterator it = children.begin(); it != children.end(); ++it)
	{
		if ((*it)->name == name)
			allChildren.push_back(*it);
		if (deepness != 0)
		{
			list<Entity*> ret = (*it)->FindAllChildren(name, deepness - 1);
			if (!ret.empty())
				allChildren.insert(allChildren.end(), ret.begin(), ret.end());
		}
	}
	return allChildren;
}

void Entity::AddComponent(Component* component)
{
	if (component->entity != nullptr)
		component->entity->RemoveComponent(component);
	component->entity = this;
	components.push_back(component);
	component->Start();
}

void Entity::RemoveComponent(Component* component)
{
	if (component->entity == this)
	{
		component->CleanUp();
		component->entity = nullptr;
		components.remove(component);
	}
}

const list<Component*>& Entity::GetComponents()
{
	return components;
}

template<class T>
inline list<T*> Entity::FindAllChildren()
{
	return FindAllChildren<T>(-1);
}

template<class T>
inline list<T*> Entity::FindAllChildren(int deepness)
{
	list<Entity*> allChildren;
	for (list<Entity*>::iterator it = children.begin(); it != children.end(); ++it)
	{
		if (dynamic_cast<T*>(*it) != NULL)
			allChildren.push_back(*it);
		if (deepness != 0)
		{
			list<Entity*> ret = (*it)->FindAllChildren<T>(deepness - 1);
			if (!ret.empty())
				allChildren.insert(allChildren.end(), ret.begin(), ret.end());
		}
	}
	return allChildren;
}

template<class T>
T* Entity::FindComponent()
{
	for (list<Component*>::iterator it = components.begin(); it != components.end(); ++it)
		if (dynamic_cast<T*>(*it) != NULL)
			return *it;

	return nullptr;
}

template<class T>
list<T*> Entity::FindAllComponents()
{
	list<Component*> allComponents;
	for (list<Component*>::iterator it = components.begin(); it != components.end(); ++it)
		if (dynamic_cast<T*>(*it) != NULL)
			allComponents.push_back(*it);

	return allComponents;
}

