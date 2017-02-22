#include "SavingData.h"
#include "Scene.h"


XMLError eResult;

XMLError saveScene(GameObject* worldObject, string TempName)
{
	XMLDocument* xmlDoc = new XMLDocument();

	XMLNode * pRoot = xmlDoc->NewElement("root");

	xmlDoc->InsertFirstChild(pRoot);

	XMLElement * worldElement = xmlDoc->NewElement("worldObject");

	saveObject(worldObject, worldElement, xmlDoc);

	pRoot->InsertEndChild(worldElement);

	xmlDoc->InsertEndChild(pRoot);

	string filePath = ASSET_PATH + SCENE_PATH + "/" + TempName + ".banana";
	XMLError eResult = xmlDoc->SaveFile(filePath.c_str());
	XMLCheckResult(eResult);
}

XMLError saveObject(GameObject* tempObject, XMLElement* parentNode, XMLDocument* doc)
{	
	XMLElement * objectElement = doc->NewElement("object");

	XMLElement * nameElement = doc->NewElement("name");
	nameElement->SetText(tempObject->getName().c_str());
	objectElement->InsertEndChild(nameElement);

	nameElement = doc->NewElement("world");
	nameElement->SetText(tempObject->getActive());
	objectElement->InsertEndChild(nameElement);

	nameElement = doc->NewElement("active");
	nameElement->SetText(tempObject->getActive());
	objectElement->InsertEndChild(nameElement);

	nameElement = doc->NewElement("model");
	if (tempObject->getModel() != NULL)
	{
		nameElement->SetText(tempObject->getModel()->getName().c_str());
	}
	objectElement->InsertEndChild(nameElement);

	nameElement = doc->NewElement("texture");
	if (tempObject->getTexture() != NULL)
	{
		nameElement->SetText(tempObject->getTexture()->getName().c_str());
	}
	objectElement->InsertEndChild(nameElement);

	nameElement = doc->NewElement("shader");
	if (tempObject->getShader() != NULL)
	{
		nameElement->SetText(tempObject->getShader()->getName().c_str());
	}
	objectElement->InsertEndChild(nameElement);

	nameElement = doc->NewElement("localPos");
	nameElement->SetAttribute("x", tempObject->getLocalPos().x);
	nameElement->SetAttribute("y", tempObject->getLocalPos().y);
	nameElement->SetAttribute("z", tempObject->getLocalPos().z);
	objectElement->InsertEndChild(nameElement);

	nameElement = doc->NewElement("scale");
	nameElement->SetAttribute("x", tempObject->getScale().x);
	nameElement->SetAttribute("y", tempObject->getScale().y);
	nameElement->SetAttribute("z", tempObject->getScale().z);
	objectElement->InsertEndChild(nameElement);


	nameElement = doc->NewElement("rotation");
	nameElement->SetAttribute("x", tempObject->getRotation().x);
	nameElement->SetAttribute("y", tempObject->getRotation().y);
	nameElement->SetAttribute("z", tempObject->getRotation().z);
	objectElement->InsertEndChild(nameElement);


	nameElement = doc->NewElement("components");
	for (auto i = tempObject->getCompMap()->begin(); i != tempObject->getCompMap()->end(); i++)
	{
		XMLElement * loopElement = doc->NewElement("component");
		//TODO fix editor loopElement->SetText(i->first);
		nameElement->InsertEndChild(loopElement);
	}
	objectElement->InsertEndChild(nameElement);

	nameElement = doc->NewElement("children");
	for (auto i = tempObject->getChildrenMap()->begin(); i != tempObject->getChildrenMap()->end(); i++)
	{
		XMLElement * loopElement = doc->NewElement("child");
		saveObject(i->second, loopElement, doc);
		nameElement->InsertEndChild(loopElement);
	}
	objectElement->InsertEndChild(nameElement);

	parentNode->InsertEndChild(objectElement);
	
	XMLCheckResult(eResult);
}

//this is kinda bad tidy at some point
XMLError loadScene(GameObject* worldObject, string TempName, Scene* curScene)
{
	XMLDocument* xmlDoc = new XMLDocument();

	string filePath = ASSET_PATH + SCENE_PATH + "/" + TempName + ".banana";
	eResult = xmlDoc->LoadFile(filePath.c_str());
	XMLCheckResult(eResult);

	XMLNode * pRoot = xmlDoc->FirstChild();
	if (pRoot == nullptr) return XML_ERROR_PARSING_ELEMENT;

	XMLElement * worldElement = pRoot->FirstChildElement("worldObject");
	if (worldElement == nullptr) return XML_ERROR_PARSING_ELEMENT;

	XMLElement * objectElement = worldElement->FirstChildElement("object");
	if (objectElement == nullptr) return XML_ERROR_PARSING_ELEMENT;

	//fill up the world object
	worldObject->setWord(true);
	worldObject->setActive(true);
	XMLElement * nameElement = objectElement->FirstChildElement("localPos");
	if (nameElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
	vec3 outVec3;
	eResult = nameElement->QueryFloatAttribute("x", &outVec3.x);
	XMLCheckResult(eResult);
	eResult = nameElement->QueryFloatAttribute("y", &outVec3.y);
	XMLCheckResult(eResult);
	eResult = nameElement->QueryFloatAttribute("z", &outVec3.z);
	XMLCheckResult(eResult);
	worldObject->setPosition(outVec3);
	
	nameElement->FirstChildElement("scale");
	if (nameElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
	eResult = nameElement->QueryFloatAttribute("x", &outVec3.x);
	XMLCheckResult(eResult);
	eResult = nameElement->QueryFloatAttribute("y", &outVec3.y);
	XMLCheckResult(eResult);
	eResult = nameElement->QueryFloatAttribute("z", &outVec3.z);
	XMLCheckResult(eResult);
	worldObject->setScale(outVec3);

	nameElement->FirstChildElement("rotation");
	if (nameElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
	eResult = nameElement->QueryFloatAttribute("x", &outVec3.x);
	XMLCheckResult(eResult);
	eResult = nameElement->QueryFloatAttribute("y", &outVec3.y);
	XMLCheckResult(eResult);
	eResult = nameElement->QueryFloatAttribute("z", &outVec3.z);
	XMLCheckResult(eResult);
	worldObject->setRotation(outVec3);

	//nameElement->FirstChildElement("children");
	XMLElement *listElement = objectElement->FirstChildElement("children");
	if (listElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
	XMLElement * loopElement = listElement->FirstChildElement("child");
	if (nameElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
	while (loopElement != nullptr)
	{
		loadObject(worldObject, loopElement, curScene);
		loopElement = loopElement->NextSiblingElement("child");
	}
	return XML_SUCCESS;
}

XMLError loadObject(GameObject* tempParent, XMLElement* parentNode, Scene* curScene)
{
	XMLElement * objectElement = parentNode->FirstChildElement("object");
	string outName;
	XMLElement * nameElement = objectElement->FirstChildElement("name");
	if (nameElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
	outName = nameElement->GetText();

	string outModel;
	nameElement = objectElement->FirstChildElement("model");
	if (nameElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
	if (nameElement->GetText() != NULL){ outModel = nameElement->GetText(); }

	string outTexture;
	nameElement = objectElement->FirstChildElement("texture");
	if (nameElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
	if (nameElement->GetText() != NULL){ outTexture = nameElement->GetText(); }

	string outShader;
	nameElement = objectElement->FirstChildElement("shader");
	if (nameElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
	if (nameElement->GetText() != NULL){ outShader = nameElement->GetText(); }

	tempParent->addChild(new GameObject(outName, tempParent, curScene->getObject(outModel), curScene->getTexture(outTexture), curScene->getShader(outShader)));
	
	bool outBool;
	nameElement = objectElement->FirstChildElement("active");
	if (nameElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
	eResult = nameElement->QueryBoolText(&outBool);
	XMLCheckResult(eResult);
	tempParent->getChild(outName)->setActive(outBool);

	vec3 outVec3;
	XMLElement *attribElement = objectElement->FirstChildElement("localPos");
	if (attribElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
	eResult = attribElement->QueryFloatAttribute("x", &outVec3.x);
	XMLCheckResult(eResult);
	eResult = attribElement->QueryFloatAttribute("y", &outVec3.y);
	XMLCheckResult(eResult);
	eResult = attribElement->QueryFloatAttribute("z", &outVec3.z);
	XMLCheckResult(eResult);
	tempParent->getChild(outName)->setPosition(outVec3);

	attribElement = objectElement->FirstChildElement("scale");
	if (attribElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
	eResult = attribElement->QueryFloatAttribute("x", &outVec3.x);
	XMLCheckResult(eResult);
	eResult = attribElement->QueryFloatAttribute("y", &outVec3.y);
	XMLCheckResult(eResult);
	eResult = attribElement->QueryFloatAttribute("z", &outVec3.z);
	XMLCheckResult(eResult);
	tempParent->getChild(outName)->setScale(outVec3);

	attribElement = objectElement->FirstChildElement("rotation");
	if (attribElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
	eResult = attribElement->QueryFloatAttribute("x", &outVec3.x);
	XMLCheckResult(eResult);
	eResult = attribElement->QueryFloatAttribute("y", &outVec3.y);
	XMLCheckResult(eResult);
	eResult = attribElement->QueryFloatAttribute("z", &outVec3.z);
	XMLCheckResult(eResult);
	tempParent->getChild(outName)->setRotation(outVec3);

	int outInt;
	XMLElement *listElement = objectElement->FirstChildElement("components");
	if (listElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
	XMLElement * loopElement = listElement->FirstChildElement("component");
	if (loopElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
	while (loopElement != nullptr)
	{
		eResult = loopElement->QueryIntText(&outInt);
		//TODO fix editor tempParent->getChild(outName)->addComponent((Components)outInt);
		if (outInt == INPUT_COMPONENT)
		{
			tempParent->getChild(outName)->setInput(curScene->getInput());
			curScene->getInput()->setWorldPoint(tempParent->getChild(outName)->getLocalPos());
		}
		loopElement = loopElement->NextSiblingElement("component");
	}

	listElement = objectElement->FirstChildElement("children");
	if (listElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
	loopElement = listElement->FirstChildElement("child");
	if (loopElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
	while (loopElement != nullptr)
	{
		loadObject(tempParent->getChild(outName), loopElement, curScene);
		loopElement = loopElement->NextSiblingElement("child");
	}
	return XML_SUCCESS;

}