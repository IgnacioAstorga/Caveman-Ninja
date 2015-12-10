#include "Entity.h"

Entity::Entity()
{
	Create();
}

Entity::~Entity()
{
	Destroy();
}

void Entity::Create()
{
	// Llamada al método hijo
	OnCreate();
}

void Entity::Destroy()
{
	// Llamada al método hijo
	OnDestroy();

	// Limpia la lista de hijos
	for (list<Entity*>::iterator it = children.begin(); it != children.end(); ++it)
		RELEASE(*it);
	children.clear();
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
	// Llamada al método hijo
	bool ret = OnStart();

	// Llamada al Start de los hijos de la entidad
	for (list<Entity*>::iterator it = children.begin(); it != children.end() && ret; ++it)
	{
		if ((*it)->IsEnabled() == true)
			ret = (*it)->Start();
	}

	return ret;
}

update_status Entity::PreUpdate()
{
	// Llamada al método hijo
	update_status ret = OnPreUpdate();

	// Llamada al PreUpdate de los hijos de la entidad
	for (list<Entity*>::iterator it = children.begin(); it != children.end() && ret == UPDATE_CONTINUE; ++it)
	{
		if ((*it)->IsEnabled() == true)
			ret = (*it)->PreUpdate();
	}

	return ret;
}

update_status Entity::Update()
{
	// Llamada al método hijo
	update_status ret = OnUpdate();

	// Llamada al Update de los hijos de la entidad
	for (list<Entity*>::iterator it = children.begin(); it != children.end() && ret == UPDATE_CONTINUE; ++it)
	{
		if ((*it)->IsEnabled() == true)
			ret = (*it)->Update();
	}

	return ret;
}

update_status Entity::PostUpdate()
{
	// Llamada al método hijo
	update_status ret = OnPostUpdate();

	// Llamada al PostUpdate de los hijos de la entidad
	for (list<Entity*>::iterator it = children.begin(); it != children.end() && ret == UPDATE_CONTINUE; ++it)
	{
		if ((*it)->IsEnabled() == true)
			ret = (*it)->PostUpdate();
	}

	return ret;
}

bool Entity::CleanUp()
{
	// Llamada al método hijo
	bool ret = OnCleanUp();

	// Llamada al CleanUp de los hijos de la entidad
	for (list<Entity*>::iterator it = children.begin(); it != children.end() && ret; ++it)
	{
		if ((*it)->IsEnabled() == true)
			ret = (*it)->CleanUp();
	}

	return ret;
}

Entity* Entity::GetParent()
{
	return parent;
}

void Entity::SetParent(Entity* entity)
{
	parent = entity;
}

void Entity::AddChild(Entity* child)
{
	children.push_back(child);
	child->SetParent(this);
}

void Entity::RemoveChild(Entity* child)
{
	children.remove(child);
	child->SetParent(nullptr);
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

