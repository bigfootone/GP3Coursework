#include "Editor.h"
#include "Scene.h"

Editor::Editor()
{

}

Editor::Editor(Scene *tempScene)
{
	curScene = tempScene;
	curName = "";
	curGameObject = NULL;
	curMesh = NULL;
	curTexture = NULL;
	curShader = NULL;
}

Editor::~Editor()
{

}

void Editor::readCommand()
{
	string com;
	do
	{
		cout << "insert command" << endl;
		cin >> com;
		if (com == "assignObjectName")
		{
			assignName();
		}
		else if (com == "assignGameObject")
		{
			assignGameObject();
		}
		else if (com == "assignMesh")
		{
			assignObject();
		}
		else if (com == "assignTexture")
		{
			assignTexture();
		}
		else if (com == "assignShader")
		{
			assignShader();
		}
		else if (com == "spawnObject")
		{
			spawnObject();
		}
		else if (com == "spawnLight")
		{
			spawnLight();
		}
		else if (com == "spawnNode")
		{
			spawnNode();
		}
		else if (com == "transform")
		{
			if (curGameObject == NULL)
			{
				cout << "no object" << endl;
			}
			else
			{
				cout << "curent pos " << curGameObject->getLocalPos().x << " " << curGameObject->getLocalPos().y << " " << curGameObject->getLocalPos().z << endl;
				cout << "curent scale " << curGameObject->getScale().x << " " << curGameObject->getScale().y << " " << curGameObject->getScale().z << endl;
				cout << "curent rotation " << curGameObject->getRotation().x << " " << curGameObject->getRotation().y << " " << curGameObject->getRotation().z << endl;
				do
				{
					cout << "adjust transform" << endl;
					cin >> com;
					if (com == "setPos")
					{
						setPos();
					}
					else if (com == "movePos")
					{
						movePos();
					}
					else if (com == "setRotation")
					{
						setRotation();
					}
					else if (com == "setScale")
					{
						setScale();
					}
				} while (com != "doneTransform");
			}
		}
		else if (com == "save")
		{
			//atm just one scene to keep it easy
			cout << "saving" << endl;
			//saveScene(curScene->getWorldObject(), curScene->getName());
		}
		else if (com == "load")
		{
			cout << "select scene" << endl;
			cin >> com;
			cout << "loading" << endl;
			//loadScene(curScene->getWorldObject(), com, curScene);
		}
		else
		{
			cout << "unknown command" << endl;
		}
		curScene->render();
	} while (com != "done");
}

void Editor::assignName()
{
	cout << "assign name" << endl;
	string com;
	cin >> com;
	curName = com;
	cout << "name assigned " << curName << endl;
}

void Editor::assignGameObject()
{
	cout << "get gameObject name" << endl;
	string com;
	cin >> com;
	curGameObject = curScene->getGameObject(com);
}

void Editor::assignObject()
{
	cout << "get mesh name" << endl;
	string com;
	cin >> com;
	curMesh = curScene->getObject(com);
}

void Editor::assignTexture()
{
	cout << "get texture name" << endl;
	string com;
	cin >> com;
	curTexture = curScene->getTexture(com);
}

void Editor::assignShader()
{
	cout << "get shader name" << endl;
	string com;
	cin >> com;
	curShader = curScene->getShader(com);
}

void Editor::spawnObject()
{
	if (curName != "" && curGameObject != NULL && curMesh != NULL && curTexture != NULL && curShader != NULL)
	{
		cout << "spawning object" << endl;
		curGameObject->addChild(new GameObject(curName, curGameObject, curMesh, curTexture, curShader));
		curGameObject = curGameObject->findChild(curName);
		curGameObject->addComponent(new Renderer());
	}
	else
	{
		if (curName == "")
		{
			cout << "no name" << endl;
		}
		else
		{
			cout << "cur name: " << curName << endl;
		}
		if (curGameObject == NULL)
		{
			cout << "no Game object" << endl;
		}
		else
		{
			cout << "cur Game Object " << curGameObject->getName() << endl;
		}
		if (curMesh == NULL)
		{
			cout << "no object" << endl;
		}
		else
		{
			cout << "cur object " << curMesh->getName() << endl;
		}
		if (curTexture == NULL)
		{
			cout << "no texture" << endl;
		}
		else
		{
			cout << "cur texture " << curTexture->getName() << endl;
		}
		if (curShader == NULL)
		{
			cout << "no texture" << endl;
		}
		else
		{
			cout << "cur Shader " << curShader->getName() << endl;
		}
	}
}

void Editor::spawnNode()
{
	if (curName != "" && curGameObject != NULL)
	{
		cout << "spawning node" << endl;
		curGameObject->addChild(new GameObject(curName, curGameObject));
		curGameObject = curGameObject->findChild(curName);
	}
	else
	{
		if (curName == "")
		{
			cout << "no name" << endl;
		}
		else
		{
			cout << "cur name: " << curName << endl;
		}
		if (curGameObject == NULL)
		{
			cout << "no Game object" << endl;
		}
		else
		{
			cout << "cur Game Object " << curGameObject->getName() << endl;
		}
	}
}

void Editor::spawnLight()
{
	if (curName != "" && curGameObject != NULL)
	{
		cout << "spawning node" << endl;
		curGameObject->addChild(new GameObject(curName, curGameObject));
		curGameObject = curGameObject->findChild(curName);
		//add light comp
		//curGameObject->addComponent(RENDER_COMPONENT);
		//add to light vector
	}
	else
	{
		if (curName == "")
		{
			cout << "no name" << endl;
		}
		else
		{
			cout << "cur name: " << curName << endl;
		}
		if (curGameObject == NULL)
		{
			cout << "no Game object" << endl;
		}
		else
		{
			cout << "cur Game Object " << curGameObject->getName() << endl;
		}
	}

}

void Editor::setPos()
{
	if (curGameObject != NULL)
	{
		cout << "cur Game Object " << curGameObject->getName() << endl;
		float xCoord;
		cout << "set X" << endl;
		cin >> xCoord;
		
		float yCoord;
		cout << "set Y" << endl;
		cin >> yCoord;

		float zCoord;
		cout << "set z" << endl;
		cin >> zCoord;

		curGameObject->setPosition(vec3(xCoord, yCoord, zCoord));
	}
	else
	{
		cout << "no object" << endl;
	}
}

void Editor::movePos()
{
	if (curGameObject != NULL)
	{
		cout << "cur Game Object " << curGameObject->getName() << endl;
		float xCoord;
		cout << "set X" << endl;
		cin >> xCoord;

		float yCoord;
		cout << "set Y" << endl;
		cin >> yCoord;

		float zCoord;
		cout << "set z" << endl;
		cin >> zCoord;

		curGameObject->changePosition(vec3(xCoord, yCoord, zCoord));
	}
	else
	{
		cout << "no object" << endl;
	}

}

void Editor::setScale()
{
	if (curGameObject != NULL)
	{
		cout << "cur Game Object " << curGameObject->getName() << endl;
		float xCoord;
		cout << "set X" << endl;
		cin >> xCoord;

		float yCoord;
		cout << "set Y" << endl;
		cin >> yCoord;

		float zCoord;
		cout << "set z" << endl;
		cin >> zCoord;

		curGameObject->setScale(vec3(xCoord, yCoord, zCoord));
	}
	else
	{
		cout << "no object" << endl;
	}

}

void Editor::setRotation()
{
	if (curGameObject != NULL)
	{
		cout << "cur Game Object " << curGameObject->getName() << endl;
		float xCoord;
		cout << "set X" << endl;
		cin >> xCoord;

		float yCoord;
		cout << "set Y" << endl;
		cin >> yCoord;

		float zCoord;
		cout << "set z" << endl;
		cin >> zCoord;

		curGameObject->setRotation(vec3(xCoord, yCoord, zCoord));
	}
	else
	{
		cout << "no object" << endl;
	}

}