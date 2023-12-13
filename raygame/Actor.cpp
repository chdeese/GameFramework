#include "Actor.h"
#include "Transform2D.h"
#include <string.h>
#include "Collider.h"
#include "Component.h"

Actor::Actor()
{
    m_transform = new Transform2D(this);
}

Actor::~Actor()
{
    delete m_transform;
}


Actor::Actor(float x, float y, const char* name = "Actor")
{
    //Initialze default values
    m_transform = new Transform2D(this);
    m_transform->setLocalPosition({ x,y });
    m_name = name;
}

void Actor::start()
{
    m_started = true;

    for (int i = 0; i < m_componentCount; i++)
        m_components[i]->start();
}

void Actor::onCollision(Actor* other)
{
    for (int i = 0; i < m_componentCount; i++)
        m_components[i]->onCollision(other);
}

Component* Actor::getComponent(const char* componentName)
{
    //if there is no name to compare a Component to,
    //return nullptr.
    if (!componentName)
    {
        return nullptr;
    }

    //iterate through all components and see if their name matches
    //the one we are looking for.
    for (int i = 0; i < m_componentCount; i++)
    {
        //if the current Component in the list's name is the same
        //as the name we are looking for, return the Component.
        if (m_components[i]->getName() == componentName)
        {
            return m_components[i];
        }
    }

    //if the component name exists but doesnt match any in the array,
    //return nullptr.
    return nullptr;
}

Component* Actor::addComponent(Component* component)
{
    //must include component in .cpp to define it.
    Actor* owner = component->getOwner();

    //returns nullptr if there is an owner AND its not this Actor.
    if (owner && owner != this)
       return nullptr;

    //create a pointer pointer to point to an array of Component pointers
    //1 bigger than the old array.
    Component** temp = new Component * [m_componentCount + 1];

    //put the contents of the old array into the new array
    for (int i = 0; i < m_componentCount; i++)
    {
        temp[i] = m_components[i];
    }

    //delete the old contents of the array we will replace
    delete[] m_components;

    //add the new Component to the last(new) position in the array
    temp[m_componentCount] = component;

    //point m_components at the new array to store its location
    m_components = temp;

    //increase m_componentCount because we increased the amount of Components
    m_componentCount++;

    //return the Component we added to the caller of the function
    return component;
}

bool Actor::removeComponent(const char* componentName)
{
    //if the component doesnt exist, exit the function.
    if (!componentName)
        return false;

    //boolean to store if the Component has been removed or not.
    bool componentRemoved = false;

    //create a temporary Component array 1 bigger than the component array
    Component** temp = new Component * [m_componentCount - 1];

    //j to store the iteration count of 
    int j = 0;

    //copy all values except the one we need to remove.
    for (int i = 0; i < m_componentCount; i++)
    {
        //if this component is the one we want to remove
        if (componentName == m_components[i]->getName())
        {
            //set componentRemoved to true and go to the next iteration of the loop.
            componentRemoved = true;
            continue;
        }
        //otherwise, copy the component into the new array.
        temp[j] = m_components[i];
        //increase j by 1 everytime temp stores a new value
        j++;
    }

    return false;
}

void Actor::update(float deltaTime)
{
    m_transform->updateTransforms();

    for (int i = 0; i < m_componentCount; i++)
        m_components[i]->update(deltaTime);
}

void Actor::draw()
{
    for (int i = 0; i < m_componentCount; i++)
        m_components[i]->draw();
}

void Actor::end()
{
    m_started = false;

    for (int i = 0; i < m_componentCount; i++)
        m_components[i]->start();
}

void Actor::onDestroy()
{
    //Removes this actor from its parent if it has one
    if (getTransform()->getParent())
        getTransform()->getParent()->removeChild(getTransform());

    for (int i = 0; i < m_componentCount; i++)
        m_components[i]->onDestroy();
}

bool Actor::checkForCollision(Actor* other)
{
    //Call check collision if there is a collider attached to this actor
    if (m_collider)
        return m_collider->checkCollision(other);

    return false;
}