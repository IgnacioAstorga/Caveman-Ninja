#include "AIBehaviour.h"

AIBehaviour::AIBehaviour(int identifier)
{
	this->identifier = identifier;
}

AIBehaviour::~AIBehaviour()
{
	// No hace nada
}

void AIBehaviour::Configure(AIManager* manager, Entity* entity)
{
	this->manager = manager;
	this->entity = entity;
}

int AIBehaviour::GetIdentifier()
{
	return identifier;
}