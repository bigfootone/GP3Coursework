
#include "SpaceScene.h"
#include "Editor.h"
#include "OpenGL.h"
#include "AL\alut.h"

SpaceScene::SpaceScene()
{
	debugMode = false;
	worldObject = new GameObject("world Object");
	musicState = true;
}

SpaceScene::SpaceScene(string tempName)
{
	debugMode = false;
	name = tempName;
	worldObject = new GameObject("world Object");
	musicState = true;
}

SpaceScene::~SpaceScene()
{
}

void SpaceScene::render()
{
	CHECK_GL_ERROR();
	//set the clear colour background 
	glClearColor(0.0f, 0.0f, 1.0f, 0.5f);
	CHECK_GL_ERROR();

	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObject);
	CHECK_GL_ERROR();
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	CHECK_GL_ERROR();

	//clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//blend alpha channel
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//backface culling
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);


	glUseProgram(shaders["main"]->getShader());
	//update();

	CHECK_GL_ERROR();
	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, &input->getMVPmatrix()[0][0]);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &ModelMatrix[0][0]);
	glUniform1f(materialShininessLoc, materialShininess);
	glUniform3f(materialSPecularLoc, materialSpecularColor.x, materialSpecularColor.y, materialSpecularColor.z);
	glUniform3f(gLightPosLoc, gLight.position.x, gLight.position.y, gLight.position.z);
	glUniform3f(gLightIntensitiesLoc, gLight.intensities.x, gLight.intensities.y, gLight.intensities.z);
	glUniform1f(gLightAttenuationLoc, gLight.attenuation);
	glUniform1f(gLightAmbientCoeLoc, gLight.ambientCoefficient);
	glUniform3f(cameraPosLoc, input->getWorldPoint().x, input->getWorldPoint().y, input->getWorldPoint().z);
	CHECK_GL_ERROR();

	glUniform1i(textureSamplerLocation, 0);
	CHECK_GL_ERROR();

	glDepthMask(GL_TRUE);
	CHECK_GL_ERROR();

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
	cout << "creating space scene" << endl;

	//CreateFrameBuffer(); ENable for post processing
	glEnable(GL_DEPTH_TEST);
	CHECK_GL_ERROR();

	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	CHECK_GL_ERROR();

	//editor = new Editor(this);
	debugMode = true;

	input = new GamePlayerController();

	//bullet physics
	bulPhys = new BulletPhys();
	//bulPhys->CreateGroundPlane();
	groundBoxID = bulPhys->CreateBoxShape(btVector3(2, 3, 2));
	missileBoxID = bulPhys->CreateBoxShape(btVector3(5, 3, 3));

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
	objects.insert(pair<string, Object*>("ground", new Object("ground")));
	objects["ground"]->createBuffer("/SpaceFloor.FBX");

	objects.insert(pair<string, Object*>("fireball", new Object("fireball")));
	objects["fireball"]->createBuffer("/Fireball.FBX");

	objects.insert(pair<string, Object*>("iceball", new Object("iceball")));
	objects["iceball"]->createBuffer("/iceball2.FBX");

	objects.insert(pair<string, Object*>("target", new Object("target")));
	objects["target"]->createBuffer("/training-doll.FBX");

	//objects.insert(pair<string, Object*>("cubeMesh", new Cube("cubeMesh")));
	//objects["cubeMesh"]->createBuffer();

	//create textures
	textures.insert(pair<string, Texture*>("ground", new Texture("ground")));
	textures["ground"]->createTexture("/wallTexture.png");

	textures.insert(pair<string, Texture*>("targetFire", new Texture("targetFire")));
	textures["targetFire"]->createTexture("/NeptuneTexture.png");

	textures.insert(pair<string, Texture*>("targetIce", new Texture("targetIce")));
	textures["targetIce"]->createTexture("/VenusTexture.png");

	textures.insert(pair<string, Texture*>("fireball", new Texture("fireball")));
	textures["fireball"]->createTexture("/SunTexture.png");

	//create shaders
	Shader * currentShader = new Shader("main");
	currentShader->attatchVertexShader("/final Shaders/textureSpecularVS.glsl");
	currentShader->attatchFragmentShader("/final Shaders/textureSpecularFS.glsl");
	currentShader->createShader();
	shaders.insert(pair<string, Shader*>("main", currentShader));

	shaders.insert(pair<string, Shader*>("toonMaterial", new Shader("toonMaterial")));
	shaders["toonMaterial"]->attatchVertexShader("/specularVS.glsl");
	shaders["toonMaterial"]->attatchFragmentShader("/toonSpecularFS.glsl");
	shaders["toonMaterial"]->createShader();

	shaders.insert(pair<string, Shader*>("sky", new Shader("sky")));
	shaders["sky"]->attatchVertexShader("/skyboxVS.glsl");
	shaders["sky"]->attatchFragmentShader("/skyboxFS.glsl");
	shaders["sky"]->createShader();

	//create player/debug cam
	input = new GamePlayerController();
	fustrum = new Fustrum(input);
	fustrum->setUpCamera();
	fustrum->updateCamera();
	worldObject->setScene(this);

	//loadScene(worldObject, name, this);

	//uncomment for world reset
	GameObject *tempObj;

	//teapot room node done
	worldObject->addChild(new GameObject("SpaceNode", worldObject));	//creating node
	tempObj = worldObject->getChild("SpaceNode"); //setting temp object for easy access
	tempObj->setPosition(vec3(0, 0, 0));
	tempObj->setActive(true);

	/*player
	tempObj->addChild(new GameObject("player", tempObj, input));
	GameInputComponent *inputComp = new GameInputComponent(tempObj->getChild("player"));
	inputComp->assignMissile(objects["fireball"], shaders["main"], textures["sun"], missileBoxID, bulPhys);
	tempObj->getChild("player")->addComponent(inputComp);*/

	
	playerObject = new GameObject("player", tempObj, input);
	tempObj->addChild(playerObject);
	GameInputComponent *inputComp = new GameInputComponent(tempObj->getChild("player"));
	inputComp->assignFireball(objects["fireball"], shaders["main"], textures["fireball"], missileBoxID, bulPhys);
	inputComp->assignIceball(objects["iceball"], shaders["main"], textures["targetFire"], missileBoxID, bulPhys);
	playerObject->addComponent(inputComp);
	playerObject->setPosition(vec3(0, 0, 0));
	playerObject->setScale(vec3(1, 1, 1));

	
	GameObject *go = new GameObject("ground", tempObj, objects["ground"], textures["ground"], shaders["main"]);
	go->addComponent(new Renderer(go));	//adding render comp
	go->setPosition(vec3(0, -105, 75));	//changing postiion
	go->setRotation(vec3(-180, 0, 0));	//change rotaion
	go->setScale(vec3(5, 5, 5));	//change scale
	go->setForceRender(true);
	tempObj->addChild(go);	//creating object
	

	tempObj->addChild(new GameObject("targetFire", tempObj, objects["target"], textures["targetFire"], shaders["main"]));	//creating object
	tempObj->getChild("targetFire")->addComponent(new Renderer(tempObj->getChild("targetFire")));	//adding render comp
	tempObj->getChild("targetFire")->addComponent(new physicsComponent(tempObj->getChild("targetFire"), bulPhys->CreatePhysBox(btVector3(0, 0, 20), 500000000, groundBoxID), bulPhys)); //adding physics comp
	//tempObj->getChild("targetFire")->setPosition(vec3(0, 0, 20));	//changing postiion
	tempObj->getChild("targetFire")->setRotation(vec3(-90, 0, 0));	//change rotaion
	tempObj->getChild("targetFire")->setScale(vec3(1, 1, 1));	//change scale
	tempObj->getChild("targetFire")->setForceRender(true);

																//set skybox
	//worldObject->addChild(new GameObject("skybox", worldObject, objects["cubeMesh"], skyMaterial, shaders["main"]));
	//worldObject->getChild("skybox")->addComponent(RENDER_COMPONENT);
	//worldObject->getChild("skybox")->setForceRender(true);
	//worldObject->getChild("skybox")->setScale(vec3(20, 20, 20));	//change scele

	//music
	backgroundAudio = new Audio();
	backgroundAudio->createBuffer("/bgMusic.wav");
	//backgroundAudio->playAudio();


	cout << "world: " << worldObject->getName() << " components: ";
	worldObject->printComponents();
	worldObject->printChildern();

	GLenum err = GL_NO_ERROR;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		//Process/log the error.
		cout << "error in creating scene " << err << endl;
	}
	GLuint shaderID = shaders["main"]->getShader();

	textureSamplerLocation = glGetUniformLocation(shaderID, "texture0");
	MVPLocation = glGetUniformLocation(shaderID, "MVP");
	materialShininessLoc = glGetUniformLocation(shaderID, "materialShininess");
	materialSPecularLoc = glGetUniformLocation(shaderID, "materialSpecularColor");
	gLightPosLoc = glGetUniformLocation(shaderID, "light.position");
	gLightIntensitiesLoc = glGetUniformLocation(shaderID, "light.intensities");
	gLightAttenuationLoc = glGetUniformLocation(shaderID, "light.attenuation");
	gLightAmbientCoeLoc = glGetUniformLocation(shaderID, "light.ambientCoefficient");
	cameraPosLoc = glGetUniformLocation(shaderID, "cameraPosition");
	modelLocation = glGetUniformLocation(shaderID, "M");


	CHECK_GL_ERROR();
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
	objects["ground"]->cleanUp();
	//objects["cubeMesh"]->cleanUp();
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
		if (musicState == true)
		{
			backgroundAudio->stopAudio();
			musicState = false;
		}
		else
		{
			backgroundAudio->playAudio();
			musicState = true;
		}
		break;
	case SDLK_ESCAPE:
		GameRunning = false;
		break;
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

void SpaceScene::controllerStickInput(SDL_ControllerAxisEvent motion)
{

}

string SpaceScene::getName()
{
	return name;
}


