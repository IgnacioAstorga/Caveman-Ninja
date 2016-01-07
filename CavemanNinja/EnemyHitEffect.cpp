#include "EnemyHitEffect.h"
#include "SpriteRendererComponent.h"
#include "BasicAnimation.h"
#include "EffectLifespanComponent.h"

void EnemyHitEffect::OnCreate()
{
	BasicAnimation* animation = new BasicAnimation(256, 128, 4, 2, 0.0f, false);
	animation->frames.push_back({ 1, 0 });

	AddComponent(new SpriteRendererComponent("assets/images/effects.png", animation, -32, -32));
	AddComponent(new EffectLifespanComponent(0.25f));
}
