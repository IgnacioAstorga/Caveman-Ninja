#include "Application.h"
#include "ModuleScene.h"
#include "ModuleParticles.h"
#include "Scene.h"
#include "ParticleSystem.h"
#include "EmitContinuously.h"
#include "SpeedRandom.h"
#include "LifetimeRandom.h"
#include "MovementBasic.h"
#include "RotationMatchingSpeed.h"
#include "LifetimeDecay.h"
#include "SpriteRenderer.h"

#include <sstream>

class TestScene : public Scene
{
protected:
};

class TestApp : public Application
{
protected:

	Scene* OnCreateScene()
	{
		return new TestScene();
	}

	bool OnPopulateScene(Scene* scene)
	{
		Entity* en1 = new Entity();
		en1->Instantiate("try", 200, 100, scene);
		en1->transform->rotation = 90.0f;
		Entity* en2 = new Entity();
		en2->Instantiate("try", 0, 100, scene);
		en1->AddChild(en2);

		ParticleSystem* ps = new ParticleSystem(en2->transform);
		ps->Add(new EmitContinuously(200));
		ps->Add(new SpeedRandom(-300, 300, -300, 300));
		ps->Add(new LifetimeRandom(0.5, 2));
		ps->Add(new MovementBasic());
		ps->Add(new RotationMatchingSpeed());
		ps->Add(new LifetimeDecay());
		ps->Add(new SpriteRenderer("try.png"));
		App->particles->RegisterParticleSystem(ps);

		return true;
	}
};