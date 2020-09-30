#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 750.0f
#define GO_BACK 1500.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 500.0f
#define NITRO 2000.0f;


class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

public:
	
	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;
	float nitro;
	bool camera_back=false;
	bool camera_front = false;
};