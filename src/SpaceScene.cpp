
#include "SpaceScene.h"
#include "Editor.h"
#include "OpenGL.h"

SpaceScene::SpaceScene()
{
	debugMode = false;
	worldObject = new GameObject("world Object");
}

SpaceScene::SpaceScene(string tempName)
{
	debugMode = false;
	name = tempName;
	worldObject = new GameObject("world Object");
}

SpaceScene::~SpaceScene()
{
}

void SpaceScene::render()
{

	//set the clear colour background 
	glClearColor(0.0f, 0.0f, 1.0f, 0.5f);

	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObject);
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	//clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//blend alpha channel
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//backface culling
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);


	//glUseProgram(shaders["shadowMap"]->getShader());
	//update();


	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, &input->getMVPmatrix()[0][0]);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &ModelMatrix[0][0]);
	glUniform1f(materialShininessLoc, materialShininess);
	glUniform3f(materialSPecularLoc, materialSpecularColor.x, materialSpecularColor.y, materialSpecularColor.z);
	glUniform3f(gLightPosLoc, gLight.position.x, gLight.position.y, gLight.position.z);
	glUniform3f(gLightIntensitiesLoc, gLight.intensities.x, gLight.intensities.y, gLight.intensities.z);
	glUniform1f(gLightAttenuationLoc, gLight.attenuation);
	glUniform1f(gLightAmbientCoeLoc, gLight.ambientCoefficient);
	glUniform3f(cameraPosLoc, input->getWorldPoint().x, input->getWorldPoint().y, input->getWorldPoint().z);

	glUniform1i(textureSamplerLocation, 0);

	glDepthMask(GL_TRUE);

	worldObject->render(fustrum);

	CHECK_GL_ERROR();
}



void SpaceScene::update()
{
	GLenum err = GL_NO_ERROR;
	input->Update();

	bulPhys->updatePhysics();
	
	
	worldObject->update(input->getMVPmatrix());

	CHECK_GL_ERROR();

	mat4 biasMatrix(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
	);

	depthBias = biasMatrix * depthMVP;
}

void SpaceScene::createScene()
{
	//CreateFrameBuffer(); ENable for post processing
	glEnable(GL_DEPTH_TEST);

	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	//editor = new Editor(this);
	debugMode = true;

	input = new PlayerController();
	Object *tea = new Object();
	tea->createBuffer("/utah-teapot.fbx");

	//bullet physics
	bulPhys = new BulletPhys();
	bulPhys->CreateGroundPlane();

	//create cubemap texture
	skyMaterial = new CubeTexture("skybox");
	string skyBoxFront = ASSET_PATH + TEXTURE_PATH + "/skybox/Space_front.png";
	string skyBoxBack = ASSET_PATH + TEXTURE_PATH + "/skybox/Space_back.png";
	string skyBoxLeft = ASSET_PATH + TEXTURE_PATH + "/skybox/Space_left.png";
	string skyBoxRight = ASSET_PATH + TEXTURE_PATH + "/skybox/Space_right.png";
	string skyBoxTop = ASSET_PATH + TEXTURE_PATH + "/skybox/Space_top.png";
	string skyBoxBottom = ASSET_PATH + TEXTURE_PATH + "/skybox/Space_bottom.png";
	skyMaterial->loadSkyBoxTextures(skyBoxFront, skyBoxBack, skyBoxLeft, skyBoxRight, skyBoxTop, skyBoxBottom);

	//create objects
	objects.insert(pair<string, Object*>("teapot", new Object("teapot")));
	objects["teapot"]->createBuffer("/utah-teapot.FBX");

	objects.insert(pair<string, Object*>("cubeMesh", new Cube("cubeMesh")));
	objects["cubeMesh"]->createBuffer();

	//create textures
	textures.insert(pair<string, Texture*>("sun", new Texture("sun")));
	textures["sun"]->createTexture("/SunTexture.png");

	//create shaders
	Shader * s = new Shader("main");
	s->attatchVertexShader("/textureVS.glsl");
	s->attatchFragmentShader("/textureFS.glsl");
	s->createShader();
	shaders.insert(pair<string, Shader*>("main", s));

	shaders.insert(pair<string, Shader*>("toonMaterial", new Shader("toonMaterial")));
	shaders["toonMaterial"]->attatchVertexShader("/specularVS.glsl");
	shaders["toonMaterial"]->attatchFragmentShader("/toonSpecularFS.glsl");
	shaders["toonMaterial"]->createShader();

	shaders.insert(pair<string, Shader*>("sky", new Shader("sky")));
	shaders["sky"]->attatchVertexShader("/skyboxVS.glsl");
	shaders["sky"]->attatchFragmentShader("/skyboxFS.glsl");
	shaders["sky"]->createShader();

	//create player/debug cam
	input = new PlayerController();
	fustrum = new Fustrum(input);
	fustrum->setUpCamera();
	fustrum->updateCamera();
	worldObject->setScene(this);

	//loadScene(worldObject, name, this);

	//uncomment for world reset
	GameObject *tempObj;

	//player
	worldObject->addChild(new GameObject("player", worldObject, input));
	worldObject->getChild("player")->addComponent(new InputComponent(worldObject->getChild("player")));

	//teapot room node done
	worldObject->addChild(new GameObject("SpaceNode", worldObject));	//creating node
	tempObj = worldObject->getChild("SpaceNode"); //setting temp object for easy access
	tempObj->setPosition(vec3(0, 0, 0));
	tempObj->setActive(true);

	tempObj->addChild(new GameObject("sun", tempObj, objects["teapot"], textures["sun"], shaders["main"]));	//creating object
	tempObj->getChild("sun")->addComponent(new Renderer(tempObj->getChild("sun")));	//adding render comp
	tempObj->getChild("sun")->addComponent(new physicsComponent(tempObj->getChild("sun"), bulPhys->CreatePhysSphere(btVector3(0, 100, 0), 1, 5.0))); //adding physics comp
	tempObj->getChild("sun")->setPosition(vec3(0, 100, 0));	//changing postiion
	tempObj->getChild("sun")->setRotation(vec3(0, 0, 0));	//change rotaion
	tempObj->getChild("sun")->setScale(vec3(1, 1, 1));	//change scele
	tempObj->getChild("sun")->setForceRender(true);

																//set skybox
	//worldObject->addChild(new GameObject("skybox", worldObject, objects["cubeMesh"], skyMaterial, shaders["main"]));
	//worldObject->getChild("skybox")->addComponent(RENDER_COMPONENT);
	//worldObject->getChild("skybox")->setForceRender(true);
	//worldObject->getChild("skybox")->setScale(vec3(20, 20, 20));	//change scele

	cout << "world: " << worldObject->getName() << " components: ";
	worldObject->printComponents();
	worldObject->printChildern();

	GLenum err = GL_NO_ERROR;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		//Process/log the error.
		cout << "error in creating scene " << err << endl;
	}

	materialShininess = 100;
	gLight.position = glm::vec3(10, 50, 10);
	gLight.intensities = glm::vec3(1.0f, 1.0f, 1.0f); //white
	gLight.attenuation = 1.0f;
	gLight.ambientCoefficient = 0.305f;
}


void SpaceScene::UpdateLightPerspMVP()
{
	// Compute the MVP matrix from the light's point of view
	mat4 depthProjectionMatrix = glm::ortho<float>(-10, 10, -10, 10, -10, 20);
	mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	mat4 depthModelMatrix = glm::mat4(1.0);
	depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;

}

void SpaceScene::destroyScene()
{
	shaders["main"]->cleanUp();
	shaders["sky"]->cleanUp();
	objects["teapot"]->cleanUp();
	objects["cubeMesh"]->cleanUp();
}

void SpaceScene::SceneLoop()
{
	windowLoop();
	update();
	render();
}

GameObject *SpaceScene::getGameObject(string command)
{
	GameObject * tempGameObject;
	tempGameObject = worldObject->findChild(command);
	if (tempGameObject != NULL)
	{
		cout << "game object assigned " << tempGameObject->getName() << endl;
	}
	else
	{
		cout << "game object assigned NULL" << endl;
	}
	return tempGameObject;
}

GameObject *SpaceScene::getWorldObject()
{
	return worldObject;
}

Object *SpaceScene::getObject(string command)
{
	Object * tempObject;
	tempObject = objects[command];
	if (tempObject != NULL)
	{
		cout << "mesh assigned " << tempObject->getName() << endl;
	}
	else
	{
		cout << "mesh assigned NULL" << endl;
	}
	return tempObject;
}

Texture *SpaceScene::getTexture(string command)
{
	Texture * tempTexture;
	tempTexture = textures[command];
	if (tempTexture != NULL)
	{
		cout << "texture assigned " << tempTexture->getName() << endl;
	}
	else
	{
		cout << "texture assigned NULL" << endl;
	}
	return tempTexture;
}

Shader *SpaceScene::getShader(string command)
{
	Shader * tempShader;
	tempShader = shaders[command];
	if (tempShader != NULL)
	{
		cout << "shader assigned " << tempShader->getName() << endl;
	}
	else
	{
		cout << "shader assigned NULL" << endl;
	}
	return tempShader;
}

void SpaceScene::onKeyDown(SDL_Keycode key)
{
	//cout << "Key down " << key << endl;
	fustrum->updateCamera();
	switch (key)
	{
	case SDLK_p:
		if (debugMode)
		{
			cout << "debug mode off" << endl;
			debugMode = false;
		}
		else
		{
			cout << "debug mode on" << endl;
			debugMode = true;
		}
		input->setDebug(debugMode);
		break;
	case SDLK_ESCAPE:
		GameRunning = false;
	case SDLK_e:
		bulPhys->getRidgidBody(1)->applyForce(btVector3(0, 1000, 0), btVector3(0, 0, 0));
	default:
		break;
	}
}

void SpaceScene::onkeyUp(SDL_Keycode key)
{
	//cout << "Key up " << key << endl;
}

void SpaceScene::mouseMove(SDL_MouseMotionEvent motion)
{

}

string SpaceScene::getName()
{
	return name;
}


