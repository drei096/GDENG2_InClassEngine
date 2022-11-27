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
	Vector3D scale = GetOwner()->getLocalScale();
	
	Transform transform;
	transform.setFromOpenGL(GetOwner()->GetPhysicsLocalMatrix());
	boxShape = physicsCommon->createBoxShape(Vector3(scale.x / 2, scale.y / 2, scale.z / 2));
	
	rigidBody = physicsWorld->createRigidBody(transform);
	rigidBody->addCollider(boxShape, transform);
	rigidBody->updateMassPropertiesFromColliders();
	rigidBody->setMass(mass);
	rigidBody->setType(BodyType::DYNAMIC);

	transform = rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	GetOwner()->RecomputeMatrix(matrix);
	
}

void PhysicsComponent::Perform(float deltaTime)
{
	const Transform transform = rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	GetOwner()->RecomputeMatrix(matrix);
	std::cout << "My component is updating: " << this->name << "\n";
}

RigidBody* PhysicsComponent::GetRigidBody()
{
	return rigidBody;
}