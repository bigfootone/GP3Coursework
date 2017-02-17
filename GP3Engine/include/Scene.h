#ifndef _SCENE_H
#define _SCENE_H

#include "Common.h"
#include "Vertex.h"
#include "Texture.h"
#include "Shader.h"
#include "Mesh.h"
#include "FBXLoader.h"
#include "Object.h"
#include "GameObject.h"
#include "Components\Components.h"
#include "SDL2.h"
#include "KeyboardListener.h"
#include "PlayerController.h"
#include "Window.h"
#include "ViewFrustumCulling.h"
#include <map>
#include "Cube.h"
#include "CubeTexture.h"
#include "OutlineMaterial.h"
#include "ToonMaterial.h"

class Editor;

class Scene : public IkeyboardListener
{
public:
	Scene(){};
	Scene(string tempName){};
	virtual ~Scene(){};
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void createScene() = 0;
	virtual void destroyScene() = 0;
	virtual void SceneLoop() = 0;

	//debug stuff
	virtual GameObject *getGameObject(string command) = 0;
	virtual GameObject *getWorldObject() = 0;
	virtual Object *getObject(string command) = 0;
	virtual Texture *getTexture(string command) = 0;
	virtual Shader *getShader(string command) = 0;
	virtual string getName() = 0;

	virtual void onKeyDown(SDL_Keycode key) = 0;
	virtual void onkeyUp(SDL_Keycode key) = 0;

	Fustrum *getFustrum(){ return fustrum; };
	PlayerController *getInput(){ return input; };
	GLuint getActiveShader(){ return activeShader; };
	GLuint getActiveTexture(){ return activeTexture; };
	bool getDebug(){ return debugMode; };

	void setActiveShader(GLuint tempShader){ activeShader = tempShader; };
protected:
	string name;

	GLuint activeShader;
	GLuint activeTexture;

	PlayerController *input;
	Fustrum* fustrum;

	//main gameobject 
	GameObject *worldObject;
	
	//game objects
	map<string, Object*> objects;
	
	//textures 
	map<string, Texture*> textures;
	
	//shaders
	map<string, Shader*> shaders;

	//debug mode stuff
	Editor *editor;
	bool debugMode;

};

#endif
