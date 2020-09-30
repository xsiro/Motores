#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	
	

	VehicleInfo car;
	// Car properties ----------------------------------------
	car.chassis_size.Set(1.2f, 0.4f, 3);
	car.chassis_offset.Set(0, 1.8, 0);

	car.aleron_size.Set(3, 0.1f, 0.2f);
	car.aleron_offset.Set(0, 2.5f, -1.5f);

	car.aleron_fix_size.Set(0.5f, 0.5f, 0.2f);
	car.aleron_fix_offset.Set(0,2.2,-1.5f );

	car.pipe_size.Set(0.2f, 0.1f, 0.5f);
	car.pipe_offset.Set(0, 1.6f, -1.4f);

	car.frontal_size.Set(2.2f, 0.1f, 0.8f);
	car.frontal_offset.Set(0, 1.7, 1.5f);

	car.mass = 500.0f;
	car.suspensionStiffness = 15.88f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.88f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 50.5;
	car.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.7f;
	float wheel_radius = 0.3f;
	float wheel_width = 0.3f;
	float suspensionRestLength = 0.5f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x*0.5f;
	float half_length = car.chassis_size.z*0.5f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width - 0.05f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width + 0.05f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width - 0.05f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width + 0.05f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	
	
	vehicle = App->physics->AddVehicle(car);
	vehicle->SetPos(0, 20, 10);
	
	
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	float x = vehicle->vehicle->getChassisWorldTransform().getOrigin().getX() + 20 * vehicle->vehicle->getForwardVector().getX();
	float z = vehicle->vehicle->getChassisWorldTransform().getOrigin().getZ() + 20 * vehicle->vehicle->getForwardVector().getZ();
	App->camera->Position.x = vehicle->vehicle->getChassisWorldTransform().getOrigin().getX() - 12.0f * vehicle->vehicle->getForwardVector().getX();
	App->camera->Position.y = vehicle->vehicle->getChassisWorldTransform().getOrigin().getY() + 5.5f * vehicle->vehicle->getUpAxis();
	App->camera->Position.z = vehicle->vehicle->getChassisWorldTransform().getOrigin().getZ() - 7.5f * vehicle->vehicle->getForwardVector().getZ();
	camera_back = true;
	turn = acceleration = brake = 0.0f;

	/*if (camera_back == false)
	{
		if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_REPEAT)
		{
			float x = vehicle->vehicle->getChassisWorldTransform().getOrigin().getX() + 20 * vehicle->vehicle->getForwardVector().getX();
			float z = vehicle->vehicle->getChassisWorldTransform().getOrigin().getZ() + 20 * vehicle->vehicle->getForwardVector().getZ();
			App->camera->Position.x = vehicle->vehicle->getChassisWorldTransform().getOrigin().getX() - 12.0f * vehicle->vehicle->getForwardVector().getX();
			App->camera->Position.y = vehicle->vehicle->getChassisWorldTransform().getOrigin().getY() + 5.5f * vehicle->vehicle->getUpAxis();
			App->camera->Position.z = vehicle->vehicle->getChassisWorldTransform().getOrigin().getZ() - 7.5f * vehicle->vehicle->getForwardVector().getZ();
			camera_back = true;
			camera_front = false;
			App->camera->LookAt(vec3(x, 0, z));
		}
	}*/
	/*if (camera_front == false)
	{
		if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_REPEAT)
		{
			float x = vehicle->vehicle->getChassisWorldTransform().getOrigin().getX() + 20 * vehicle->vehicle->getForwardVector().getX();
			float z = vehicle->vehicle->getChassisWorldTransform().getOrigin().getZ() + 20 * vehicle->vehicle->getForwardVector().getZ();
			App->camera->Position.x = vehicle->vehicle->getChassisWorldTransform().getOrigin().getX() - 12.0f * vehicle->vehicle->getForwardVector().getX();
			App->camera->Position.y = vehicle->vehicle->getChassisWorldTransform().getOrigin().getY() + 3.0f * vehicle->vehicle->getUpAxis();
			App->camera->Position.z = vehicle->vehicle->getChassisWorldTransform().getOrigin().getZ() + 7.5f * vehicle->vehicle->getForwardVector().getZ();
			camera_front = true;
			camera_back = false;
			App->camera->LookAt(vec3(x, 0, z));
		}
	}*/

	App->camera->LookAt(vec3(x, 0, z));

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		acceleration = MAX_ACCELERATION;
	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		if (turn < TURN_DEGREES)
			turn += TURN_DEGREES;
	}

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		if (turn > -TURN_DEGREES)
			turn -= TURN_DEGREES;
	}

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		acceleration = -GO_BACK;
	}

	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT)
	{
		brake = BRAKE_POWER;
	}
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
	{
		acceleration = NITRO;
	}
	
	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);
	vehicle->Render();

	char title[80];
	sprintf_s(title, "%.1f Km/h", vehicle->GetKmh());
	App->window->SetTitle(title);

	return UPDATE_CONTINUE;
}



