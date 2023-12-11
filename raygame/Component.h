#pragma once

//forward declaration
class Actor;
//saying Actor exists without definiting it *yet*.

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
};

