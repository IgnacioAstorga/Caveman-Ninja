#include "Application.h"
#include "ModuleScene.h"
#include "ModuleParticles.h"
#include "Scene.h"
#include "ParticleSystem.h"
#include "EmitContinuouslyEmitter.h"
#include "SpeedRandomInitializer.h"
#include "LifetimeRandomInitializer.h"
#include "ColorRandomInitializer.h"
#include "ScaleRandomInitializer.h"
#include "MovementBasicOperator.h"
#include "RotationMatchingSpeedOperator.h"
#include "LifetimeDecayOperator.h"
#include "AlphaFadeInOutOperator.h"
#include "ScaleBasicOperator.h"
#include "SpriteParticleRenderer.h"
#include "Color.h"
#include "SpriteRendererComponent.h"
#include "ParticleSystemComponent.h"

#include <sstream>

class TestScene : public Scene {};

class TestApp : public Application
{
protected:

	Scene* OnCreateScene()
	{
		return new TestScene();
	}

	bool OnPopulateScene(Scene* scene)
	{
		Animation* a1 = new Animation();
		a1->speed = 24.0f;
		a1->frames.push_back({ 0, 0, 126, 77 });
		a1->frames.push_back({ 126, 0, 126, 77 });

		Animation* a2 = new Animation();
		a2->speed = 12.0f;
		a2->frames.push_back({ 0, 0, 60, 60 });
		a2->frames.push_back({ 60, 0, 60, 60 });
		a2->frames.push_back({ 120, 0, 60, 60 });
		a2->frames.push_back({ 0, 60, 60, 60 });
		a2->frames.push_back({ 60, 60, 60, 60 });
		a2->frames.push_back({ 120, 60, 60, 60 });

		Entity* en1 = new Entity();
		en1->Instantiate("character", 100, 200, scene);
		en1->transform->SetScale(0.667f);

		Component* cp1 = new SpriteRendererComponent("try_character_animated.png", a1, -46, -77);
		cp1->Create(en1);

		Entity* en2 = new Entity();
		en2->Instantiate("particles", 67, -56, en1);
		en2->transform->SetRotation(-90.0f);

		ParticleSystem* ps = new ParticleSystem();
		ps->Add(new EmitContinuouslyEmitter(20));
		ps->Add(new SpeedRandomInitializer(-100, 100, 300, 500));
		ps->Add(new LifetimeRandomInitializer(0.5, 2));
		ps->Add(new ColorRandomInitializer(Color(0.8f, 0.8f, 1.0f), Color(1.0f, 1.0f, 1.0f)));
		ps->Add(new ScaleRandomInitializer(0.75, 1.25));
		ps->Add(new MovementBasicOperator());
		ps->Add(new RotationMatchingSpeedOperator());
		ps->Add(new LifetimeDecayOperator());
		ps->Add(new AlphaFadeInOutOperator(0.1f, 0.75f));
		ps->Add(new ScaleBasicOperator(1.0f, 5.0f));
		ps->Add(new SpriteParticleRenderer("try_particles_animated.png", a2));

		Component* cp2 = new ParticleSystemComponent(ps);
		cp2->Create(en2);

		return true;
	}
};