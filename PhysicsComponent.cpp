#include "PhysicsComponent.h"
#include "BaseComponentSystem.h"
#include "AGameObject.h"
#include "PhysicsSystem.h"

PhysicsComponent::PhysicsComponent(String name, AGameObject* owner) : AComponent(name, ComponentType::Physics, owner)
{
	// whenever a new physics component is initialized. Register to physics system
	BaseComponentSystem::GetInstance()->GetPhysicsSystem()->RegisterComponent(this);
	UpdateRigidBody();
}

PhysicsComponent::~PhysicsComponent()
{
	BaseComponentSystem::GetInstance()->GetPhysicsSystem()->UnRegisterComponent(this);
	AComponent::~AComponent();
}

void PhysicsComponent::UpdateRigidBody()
{
	PhysicsCommon* physicsCommon = BaseComponentSystem::GetInstance()->GetPhysicsSystem()->GetPhysicsCommon();
	PhysicsWorld* physicsWorld = BaseComponentSystem::GetInstance()->GetPhysicsSystem()->GetPhysicsWorld();


	// Create a rigid body in the world
	Vector3D scale = this->GetOwner()->getLocalScale();

	Transform transform;
	transform.setFromOpenGL(this->GetOwner()->GetPhysicsLocalMatrix());
	this->boxShape = physicsCommon->createBoxShape(Vector3(scale.x, scale.y, scale.z));

	this->rigidBody = physicsWorld->createRigidBody(transform);
	this->rigidBody->addCollider(this->boxShape, transform);
	this->rigidBody->updateMassPropertiesFromColliders();
	this->rigidBody->setMass(this->mass);
	this->rigidBody->setType(BodyType::DYNAMIC);

	transform = this->rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	this->GetOwner()->RecomputeMatrix(matrix);
	
}

void PhysicsComponent::Perform(float deltaTime)
{
	const Transform transform = this->rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	this->GetOwner()->RecomputeMatrix(matrix);
	std::cout << "My component is updating: " << this->name << "\n";
}

RigidBody* PhysicsComponent::GetRigidBody()
{
	return this->rigidBody;
}