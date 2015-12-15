#include "Entity.h"
#include "Transform.h"
#include "Scene.h"
#include "Component.h"

Entity::Entity(string name, float x, float y, bool start_enabled) : enabled(start_enabled)
{
	// Flags
	dead = false;
	started = false;

	// Crea el transform
	transform = new Transform(this);
	transform->SetPosition(x, y);

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

Entity* Entity::Instantiate(Scene* scene)
{
	scene->AddChild(this);
	Start();

	return this;
}

Entity* Entity::Instantiate(Entity* parent)
{
	parent->AddChild(this);
	Start();

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

bool Entity::OnCollisionEnter(Collider* self, Collider* other)
{
	bool ret = true;

	// Llama al OnCollisionEnter de todos sus componentes activos
	for (list<Component*>::iterator it = components.begin(); it != components.end() && ret; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->OnCollisionEnter(self, other);

	return ret;
}

bool Entity::OnCollisionStay(Collider * self, Collider * other)
{
	bool ret = true;

	// Llama al OnCollisionStay de todos sus componentes activos
	for (list<Component*>::iterator it = components.begin(); it != components.end() && ret; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->OnCollisionStay(self, other);

	return ret;
}

bool Entity::OnCollisionExit(Collider * self, Collider * other)
{
	bool ret = true;

	// Llama al OnCollisionExit de todos sus componentes activos
	for (list<Component*>::iterator it = components.begin(); it != components.end() && ret; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->OnCollisionExit(self, other);

	return ret;
}

bool Entity::Start()
{
	// Comprobación por si acaso de que no se ha iniciado
	if (started == true)
		return true;
	started = true;

	// Llamada al delegado
	bool ret = OnStart();

	// Llamada al Start de los hijos de la entidad
	for (list<Entity*>::iterator it = children.begin(); it != children.end() && ret; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->Start();

	// Llamada al Start de los componentes de la entidad
	for (list<Component*>::iterator it = components.begin(); it != components.end() && ret; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->Start();

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
			ret = (*it)->PreUpdate();

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
			ret = (*it)->Update();

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
			ret = (*it)->PostUpdate();

	// Por último, elimina todas sus entidades hijas que hayan muerto
	list<Entity*> toDestroy;
	for (list<Entity*>::iterator it = children.begin(); it != children.end() && ret == UPDATE_CONTINUE; ++it)
		if ((*it)->dead == true)
			toDestroy.push_back(*it);
	// Forma segura de destruir elementos mientras se recorre la lista
	for (list<Entity*>::iterator it = toDestroy.begin(); it != toDestroy.end() && ret == UPDATE_CONTINUE; ++it) {
		(*it)->CleanUp();
		RemoveChild(*it, false);	// Lo deshereda
		RELEASE(*it);
	}
	toDestroy.clear();

	return ret;
}

bool Entity::CleanUp()
{
	// Comprobación por si acaso de que ya se ha iniciado
	if (started != true)
		return true;
	started = false;

	// Llamada al delegado
	bool ret = OnCleanUp();

	// Llamada al CleanUp de los hijos de la entidad
	for (list<Entity*>::iterator it = children.begin(); it != children.end() && ret; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->CleanUp();

	// Llamada al CleanUp de los componentes de la entidad
	for (list<Component*>::iterator it = components.begin(); it != components.end() && ret; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->CleanUp();

	return ret;
}

Entity* Entity::GetParent()
{
	return parent;
}

void Entity::SetParent(Entity* entity)
{
	if (entity == nullptr)
		SetParent(scene);	// Si se introduce null, la entidad pasará a ser hija de la propia escena
	else
		entity->AddChild(this);
}

void Entity::SetParent(Scene* scene)
{
	if (parent != nullptr)
		parent->RemoveChild(this);
	scene->AddChild(this);
}

void Entity::AddChild(Entity* child)
{
	if (child->parent != nullptr)
		child->parent->RemoveChild(child);
	child->parent = this;
	child->scene = scene;
	children.push_back(child);
}

void Entity::RemoveChild(Entity* child, bool attachRoot)
{
	if (child->parent == this)
	{
		children.remove(child);
		child->parent = nullptr;
		if (attachRoot)
			child->scene->AddChild(child);	// Al quedarse sin padre, la entidad pasará a ser hija de su escena
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
}

void Entity::RemoveComponent(Component* component)
{
	if (component->entity == this)
	{
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

