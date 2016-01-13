#include "PlayerHitEffect.h"
#include "SpriteRendererComponent.h"
#include "BasicAnimation.h"
#include "EntityLifetimeComponent.h"

#define EFFECT_LIFETIME 0.25f

void PlayerHitEffect::OnCreate()
{
	BasicAnimation* animation = new BasicAnimation(256, 128, 4, 2, 12.0f, false);
	animation->frames.push_back({ 1, 1 });
	animation->frames.push_back({ 2, 1 });
	animation->frames.push_back({ 3, 1 });

	AddComponent(new SpriteRendererComponent("assets/images/effects.png", animation, -32, -32));
	AddComponent(new EntityLifetimeComponent(EFFECT_LIFETIME));
}
