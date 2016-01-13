#include "EnemyHitEffect.h"
#include "SpriteRendererComponent.h"
#include "BasicAnimation.h"
#include "EntityLifetimeComponent.h"

EnemyHitEffect::EnemyHitEffect(std::string name, bool big, float positionX, float positionY)
	: Entity(name, positionX, positionY)
{
	this->big = big;
	OnCreate();
}

EnemyHitEffect::~EnemyHitEffect()
{
	OnDestroy();
}

void EnemyHitEffect::OnCreate()
{
	BasicAnimation* animation = new BasicAnimation(256, 128, 4, 2, 0.0f, false);
	if (big)
		animation->frames.push_back({ 2, 0 });
	else
		animation->frames.push_back({ 1, 0 });

	AddComponent(new SpriteRendererComponent("assets/images/effects.png", animation, -32, -32));
	AddComponent(new EntityLifetimeComponent(0.25f));
}
