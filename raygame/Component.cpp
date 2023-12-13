#include "Component.h"

Component::Component()
{
	m_name = nullptr;
	m_owner = nullptr;
}

Component::Component(Actor* owner, const char* name)
{
	m_owner = owner;
	m_name = name;
}

Component::~Component()
{
	//for character arrays, or strings, use delete[].
	delete[] m_name;
}
