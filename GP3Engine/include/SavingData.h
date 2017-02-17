#ifndef _SAVINGDATA_H
#define _SAVINGDATA_H


#define XMLCheckResult(a_eResult) if(a_eResult !=XML_SUCCESS) { cout << "Error: " <<a_eResult <<endl; return a_eResult; }

#include "Common.h"
#include "tinyxml2.h"
#include "GameObject.h"

class Scene;

using namespace tinyxml2;

XMLError saveScene(GameObject* worldObject, string tempName);
XMLError saveObject(GameObject* tempObject, XMLElement* parentNode, XMLDocument* doc);
XMLError loadScene(GameObject* worldObject, string TempName, Scene* curScene);
XMLError loadObject(GameObject* tempObject, XMLElement* parentNode, Scene* curScene);

#endif