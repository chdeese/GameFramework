#pragma once

//forward declaration
//saying Actor exists without definiting it *yet*.
//helps avoid circular dependency
class Actor;

class Component
{
public:

	virtual void start() {};
	virtual void update(float deltaTime) {};
	virtual void draw() {};
	virtual void end() {};

	virtual void onCollision() {};

	virtual void onDestroy() {};

	const char* getName() { return m_name;  }

private:
	const char* m_name;

	//when using forward declaration, the fowarded class's variables
	//must be declared as pointer-type because we dont yet know how
	//much memory an "Actor" has, but with a pointer, we do know.
	//Actor m_owner; - incorrect [error] (with forward declaration)
	//Actor* m_owner; - correct (with forward declaration)
};

