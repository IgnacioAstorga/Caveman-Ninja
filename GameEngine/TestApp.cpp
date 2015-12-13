#include "Application.h"
#include "ModuleScene.h"
#include "ModuleParticles.h"
#include "Scene.h"
#include "ParticleSystem.h"
#include "EmitContinuously.h"
#include "SpeedRandom.h"
#include "LifetimeRandom.h"
#include "ColorRandom.h"
#include "MovementBasic.h"
#include "RotationMatchingSpeed.h"
#include "LifetimeDecay.h"
#include "AlphaFadeInOut.h"
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

		Component* cp1 = new SpriteRendererComponent("try_character_animated.png", a1, -46, -77);
		cp1->Create(en1);

		Entity* en2 = new Entity();
		en2->Instantiate("particles", 67, -56, en1);
		en2->transform->rotation = -90.0f;

		Component* cpX = new SpriteRendererComponent("try_character_animated.png", a1, -46, -77);
		cpX->Create(en2);

		ParticleSystem* ps = new ParticleSystem();
		ps->Add(new EmitContinuously(20));
		ps->Add(new SpeedRandom(-100, 100, 300, 500));
		ps->Add(new LifetimeRandom(0.5, 2));
		ps->Add(new ColorRandom(Color(0.9f, 0.9f, 1.0f), Color(1.0f, 1.0f, 1.0f)));
		ps->Add(new MovementBasic());
		ps->Add(new RotationMatchingSpeed());
		ps->Add(new LifetimeDecay());
		ps->Add(new AlphaFadeInOut(0.1f, 0.75f));
		ps->Add(new SpriteParticleRenderer("try_particles_animated.png", a2));

		Component* cp2 = new ParticleSystemComponent(ps);
		cp2->Create(en2);

		return true;
	}
};