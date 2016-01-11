#include "ScoreTextEffect.h"
#include "SpriteRendererComponent.h"
#include "BasicAnimation.h"
#include "EntityLifetimeComponent.h"
#include "MovementSimpleComponent.h"

ScoreTextEffect::ScoreTextEffect(int score, std::string name, float positionX, float positionY)
	: Entity(name, positionX, positionY) 
{
	this->score = score;
	OnCreate();
}

void ScoreTextEffect::OnCreate()
{
	BasicAnimation* animation = new BasicAnimation(48, 32, 3, 2, 0.0f, false);
	switch (score)
	{
	case 100:
		animation->frames.push_back({ 0, 0 });
		break;
	case 200:
		animation->frames.push_back({ 1, 0 });
		break;
	case 300:
		animation->frames.push_back({ 2, 0 });
		break;
	case 500:
		animation->frames.push_back({ 0, 1 });
		break;
	case 1000:
		animation->frames.push_back({ 1, 1 });
		break;
	case -1:	// -1 es un código especial para ganar una vida
		animation->frames.push_back({ 2, 1 });
		break;
	default:
		return;
	}

	AddComponent(new SpriteRendererComponent("assets/images/pickups_score.png", animation, -8, -16));
	AddComponent(new EntityLifetimeComponent(1.0f));
	AddComponent(new MovementSimpleComponent());

	transform->SetSpeed(0.0f, -30.0f);
}