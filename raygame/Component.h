#pragma once

//forward declaration
//saying Actor exists without definiting it *yet*.
//helps avoid circular dependency
class Actor;

class Component
{
public:
	/// <summary>
	/// constructs a default Component with null values
	/// </summary>
	Component();
	/// <summary>
	/// constructs a Component with a name and an owner
	/// </summary>
	/// <param name="owner">the owner of this Component</param>
	/// <param name="name">the name of the Component</param>
	Component(Actor* owner, const char* name);

	//destructor, called upon "delete 'class name'"
	
	/// <summary>
	/// destructor, deletes Component data upon the deletion of Component.
	/// </summary>
	virtual ~Component();

	/// <summary>
	/// called upon the start of an Actor that this Component is attached to
	/// </summary>
	virtual void start() {};
	/// <summary>
	/// called every time the game loop updates the Actor that this is attached to
	/// </summary>
	/// <param name="deltaTime">the amount of time passed between each update</param>
	virtual void update(float deltaTime) {};
	/// <summary>
	/// called every time the Actor that this is attached to is drawn on the screen.
	/// </summary>
	virtual void draw() {};
	/// <summary>
	/// called when the Actor that this is attached to dies or needs to end for some reason.
	/// </summary>
	virtual void end() {};

	/// <summary>
	/// called when an Actor collides with the Actor that this is attached to
	/// </summary>
	/// <param name="other">the Actor that collided with this Component's owner.</param>
	virtual void onCollision(Actor* other) {};

	/// <summary>
	/// called when this Component is destroyed. 
	/// </summary>
	virtual void onDestroy() {};

	/// <summary>
	/// gets the name of this Component
	/// </summary>
	/// <returns>the name of this Component</returns>
	const char* getName() { return m_name;  }

	/// <summary>
	/// gets a reference to the Owner of this Component
	/// </summary>
	/// <returns>returns a reference to the Owner of this Component</returns>
	Actor* getOwner() { return m_owner; }

private:
	const char* m_name;

	//when using forward declaration, the fowarded class's variables
	//must be declared as pointer-type because we dont yet know how
	//much memory an "Actor" has, but with a pointer, we do know.
	//Actor m_owner; - incorrect [error] (with forward declaration)
	Actor* m_owner;// - correct (with forward declaration)
};

