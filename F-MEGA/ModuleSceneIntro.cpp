#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModuleAudio.h"


ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	
	App->audio->PlayFx(App->audio->LoadFx("audio/music/theme.ogg"));
	
	bool ret = true;
	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));
	
	//walls colliders

	Cube wall1(2, 3, 250);
	wall1.SetPos(10, 1, 15);
	App->physics->AddBody(wall1, 100000);


	Cube wall2(2, 3, 230);
	wall2.SetPos(-10, 1, 15);
	App->physics->AddBody(wall2, 100000);


	Cube wall3(40, 3, 2);
	wall3.SetPos(-10, 1, 142);
	App->physics->AddBody(wall3, 100000);
	
	Cube wall4(2, 3, 40);
	wall4.SetPos(-30, 1, 120);
	App->physics->AddBody(wall4, 100000);

	Cube wall5(30, 3, 2);
	wall5.SetPos(-25, 1, 80);
	App->physics->AddBody(wall5, 100000);

	Cube wall6(30, 3, 2);
	wall6.SetPos(-45,1, 100);
	App->physics->AddBody(wall6, 100000);

	Cube wall7()
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update


update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();
	
	//render all walls

	Cube wall1(2, 3, 250);
	wall1.SetPos(10, 1, 15);
	wall1.color = Blue;
	wall1.Render();

	Cube wall2(2, 3, 230);
	wall2.SetPos(-10, 1, 15);
	wall2.color = Blue;
	wall2.Render();
	
	Cube wall3(40, 3, 2);
	wall3.SetPos(-10, 1, 142);
	wall3.color = Blue;
	wall3.Render();

	Cube wall4(2, 3, 40);
	wall4.SetPos(-30, 1, 120);
	wall4.color = Blue;
	wall4.Render();

	Cube wall5(30, 3, 2);
	wall5.SetPos(-25, 1, 80);
	wall5.color = Blue;
	wall5.Render();

	Cube wall6(30, 3, 2);
	wall6.SetPos(-45, 1, 100);
	wall6.color = Blue;
	wall5.Render();

	return UPDATE_CONTINUE;
}



void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

