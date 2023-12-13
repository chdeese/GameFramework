#include "MoveComponent.h"
#include "Transform2D.h"
#include "Actor.h"

//base constructor call.
MoveComponent::MoveComponent(float maxSpeed, Actor* owner) : Component(owner, "MoveComponent")
{
	m_maxSpeed = maxSpeed;
}

void MoveComponent::update(float deltaTime)
{
	//store the current position
	MathLibrary::Vector2 position = getOwner()->getTransform()->getLocalPosition();

	//if the velocity is greater than the maxSpeed
	//then normalize Velocity and scale it by maxSpeed.
	if (getVelocity().getMagnitude() > getMaxSpeed())
	{
		MathLibrary::Vector2 newVelocity = getVelocity().getNormalized() * getMaxSpeed();
		setVelocity(newVelocity);
	}

	//add the velocity to the current position to get the new position
	position = position + getVelocity() * deltaTime;

	//set the transform's position to be the new position.
	getOwner()->getTransform()->setLocalPosition(position);
}