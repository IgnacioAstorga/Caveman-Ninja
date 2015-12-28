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
#include "CircleColliderComponent.h"
#include "RectangleColliderComponent.h"
#include "LineColliderComponent.h"
#include "DestroyOnCollisionComponent.h"
#include "MovementSimpleComponent.h"
#include "CameraComponent.h"
#include "BasicAnimation.h"
#include "Animator.h"
#include "FlagGreaterThanCondition.h"
#include "GUISpriteRendererComponent.h"

#include "Scene_Level1.h"

#include <sstream>

class TestScene : public Scene {};

class TestComponent : public Component {
public:
	TestComponent(Animator* animator, string flag) : animator(animator), flag(flag) {}
	bool OnUpdate()
	{ 
		animator->SetFlagValue(flag, entity->transform->GetGlobalPosition().y);
		return true;
	}
	string flag;
	Animator* animator;
};

class TestApp : public Application
{
protected:

	Scene* OnCreateScene()
	{
		return new Scene_Level1();
	}

	/*bool OnPopulateScene(Scene* scene)
	{
		Entity* camera = new Entity("camera", 0, 0);
		camera->AddComponent(new CameraComponent(SCREEN_WIDTH * SCREEN_SIZE, SCREEN_HEIGHT * SCREEN_SIZE, true));
		camera->Instantiate(scene);

		BasicAnimation* a1 = new BasicAnimation();
		a1->speed = 24.0f;
		a1->frames.push_back({ 0, 0, 126, 77 });
		a1->frames.push_back({ 126, 0, 126, 77 });

		BasicAnimation* a2 = new BasicAnimation();
		a2->speed = 12.0f;
		a2->frames.push_back({ 0, 0, 60, 60 });
		a2->frames.push_back({ 60, 0, 60, 60 });
		a2->frames.push_back({ 120, 0, 60, 60 });
		a2->frames.push_back({ 0, 60, 60, 60 });
		a2->frames.push_back({ 60, 60, 60, 60 });
		a2->frames.push_back({ 120, 60, 60, 60 });

		BasicAnimation* a3 = new BasicAnimation(*a2);
		a3->speed = 12.0f;
		BasicAnimation* a4 = new BasicAnimation(*a2);
		a4->speed = -6.0f;
		StateSwitcher<Animation>* ss = new StateSwitcher<Animation>(a3);
		ss->AddStateTransition(new StateTransition<Animation>(new StateSwitcher<Animation>(a4), new FlagGreaterThanCondition("positionY", 50)));
		Animator* animator = new Animator(ss);

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

		Entity* en1 = new Entity("character", 100, 200);
		en1->transform->SetScale(0.667f);
		en1->AddComponent(new SpriteRendererComponent("try_character_animated.png", a1, -46, -77));
		en1->AddComponent(new RectangleColliderComponent(60, 60, 0, -20, 30, 0));
		en1->AddComponent(new DestroyOnCollisionComponent());

		Entity* en2 = new Entity("particles", 67, -56);
		en1->AddChild(en2);
		en2->transform->SetRotation(-90.0f);
		en2->AddComponent(new ParticleSystemComponent(ps));

		Entity* en3 = new Entity("killer", 100 -20 -10 -2, 0);
		en3->transform->SetRotation(90.0f);
		en3->transform->SetSpeed(0.0f, 20.0f);
		en3->AddComponent(new SpriteRendererComponent("try_particles_animated.png", animator, -30, -30));
		en3->AddComponent(new RectangleColliderComponent(40, 20, 0, 0, -45, 1));
		en3->AddComponent(new DestroyOnCollisionComponent());
		en3->AddComponent(new MovementSimpleComponent());
		en3->AddComponent(new TestComponent(animator, "positionY"));

		BasicAnimation* a5 = new BasicAnimation(*a2);

		Entity* en4 = new Entity("gui", 0, 0);
		en4->transform->SetRotation(30.0f);
		en4->transform->SetPosition(30.0f, 30.0f);
		en4->AddComponent(new GUISpriteRendererComponent("try_particles_animated.png", a5, -30, -30, CENTER));

		vector<fPoint> points;
		points.push_back(fPoint(0.0f, 200.0f));
		points.push_back(fPoint(100.0f, 150.0f));
		points.push_back(fPoint(200.0f, 120.0f));
		points.push_back(fPoint(300.0f, 200.0f));

		Entity* en5 = new Entity("line");
		en5->AddComponent(new LineColliderComponent(points, 10, 5));

		en1->Instantiate(scene);
		en3->Instantiate(scene);
		en4->Instantiate(scene);
		en5->Instantiate(scene);

		return true;
	}*/
};