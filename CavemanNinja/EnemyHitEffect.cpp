#include "EnemyHitEffect.h"
#include "SpriteRendererComponent.h"
#include "BasicAnimation.h"
#include "EffectLifespanComponent.h"

void EnemyHitEffect::OnCreate()
{
	BasicAnimation* animation = new BasicAnimation(0.0f);
	animation->frames.push_back({ 64, 0, 64, 64 });

	AddComponent(new SpriteRendererComponent("assets/images/effects.png", animation, -32, -32));
	AddComponent(new EffectLifespanComponent(0.25f));
}
