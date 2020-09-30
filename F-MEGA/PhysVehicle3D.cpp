#include "PhysVehicle3D.h"
#include "Primitive.h"
#include "Bullet/include/btBulletDynamicsCommon.h"

// ----------------------------------------------------------------------------
VehicleInfo::~VehicleInfo()
{
	//if(wheels != NULL)
		//delete wheels;
}

// ----------------------------------------------------------------------------
PhysVehicle3D::PhysVehicle3D(btRigidBody* body, btRaycastVehicle* vehicle, const VehicleInfo& info) : PhysBody3D(body), vehicle(vehicle), info(info)
{
}

// ----------------------------------------------------------------------------
PhysVehicle3D::~PhysVehicle3D()
{
	delete vehicle;
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Render()
{
	Cylinder wheel;

	wheel.color.Set(0.3f,0.3f,0.3f);

	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		wheel.radius = info.wheels[0].radius;
		wheel.height = info.wheels[0].width;

		vehicle->updateWheelTransform(i);
		vehicle->getWheelInfo(i).m_worldTransform.getOpenGLMatrix(&wheel.transform);

		wheel.Render();
	}

	Cube chassis(info.chassis_size.x, info.chassis_size.y, info.chassis_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis.transform);
	Cube aleron(info.aleron_size.x, info.aleron_size.y, info.aleron_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&aleron.transform);
	Cube aleron_fix(info.aleron_fix_size.x, info.aleron_fix_size.y, info.aleron_fix_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&aleron_fix.transform);
	Cube pipe(info.pipe_size.x, info.pipe_size.y,info.pipe_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&pipe.transform);
	Cube frontal(info.frontal_size.x, info.frontal_size.y, info.frontal_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&frontal.transform);
	
	btQuaternion q = vehicle->getChassisWorldTransform().getRotation();

	btVector3 offset(info.chassis_offset.x, info.chassis_offset.y, info.chassis_offset.z);
	offset = offset.rotate(q.getAxis(), q.getAngle());
	btVector3 offset_aleron(info.aleron_offset.x, info.aleron_offset.y, info.aleron_offset.z);
	offset_aleron = offset_aleron.rotate(q.getAxis(), q.getAngle());
	btVector3 offset_aleron_fix(info.aleron_fix_offset.x, info.aleron_fix_offset.y, info.aleron_fix_offset.z);
	offset_aleron_fix = offset_aleron_fix.rotate(q.getAxis(), q.getAngle());
	btVector3 offset_pipe(info.pipe_offset.x, info.pipe_offset.y, info.pipe_offset.z);
	offset_pipe = offset_pipe.rotate(q.getAxis(), q.getAngle());
	btVector3 offset_frontal(info.frontal_offset.x, info.frontal_offset.y, info.frontal_offset.z);
	offset_frontal = offset_frontal.rotate(q.getAxis(), q.getAngle());

	chassis.transform.M[12] += offset.getX();
	chassis.transform.M[13] += offset.getY();
	chassis.transform.M[14] += offset.getZ();

	aleron.transform.M[12] += offset_aleron.getX();
	aleron.transform.M[13] += offset_aleron.getY();
	aleron.transform.M[14] += offset_aleron.getZ();

	aleron_fix.transform.M[12] += offset_aleron_fix.getX();
	aleron_fix.transform.M[13] += offset_aleron_fix.getY();
	aleron_fix.transform.M[14] += offset_aleron_fix.getZ();

	pipe.transform.M[12] += offset_pipe.getX();
	pipe.transform.M[13] += offset_pipe.getY();
	pipe.transform.M[14] += offset_pipe.getZ();

	frontal.transform.M[12] += offset_frontal.getX();
	frontal.transform.M[13] += offset_frontal.getY();
	frontal.transform.M[14] += offset_frontal.getZ();

	chassis.color.Set(1.0f, 0.3f, 0.0f);
	aleron.color.Set(1.0f, 0.05f, 0.0f);
	aleron_fix.color.Set(1.0f, 0.3f, 0.0f);
	pipe.color.Set(0.5f,0.5f,0.5f);
	frontal.color.Set(1.0f, 0.05f, 0.0f);


	chassis.Render();
	aleron.Render();
	aleron_fix.Render();
	pipe.Render();
	frontal.Render();
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::ApplyEngineForce(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].drive == true)
		{
			vehicle->applyEngineForce(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Brake(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].brake == true)
		{
			vehicle->setBrake(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Turn(float degrees)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].steering == true)
		{
			vehicle->setSteeringValue(degrees, i);
		}
	}
}

// ----------------------------------------------------------------------------
float PhysVehicle3D::GetKmh() const
{
	return vehicle->getCurrentSpeedKmHour();
}