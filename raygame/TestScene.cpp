#include "TestScene.h"
#include "Player.h"
#include "Transform2D.h"
#include "Component.h"

void TestScene::start()
{
	const char* name = "Christian";

	Component* comp = new Component(nullptr, name);

	//equivalent of base.Start() in c#.
	Scene::start();

	Player* player = new Player();

	MathLibrary::Vector2 scale = MathLibrary::Vector2(50, 50);
	player->getTransform()->setScale(scale);

	addActor(player);
}
