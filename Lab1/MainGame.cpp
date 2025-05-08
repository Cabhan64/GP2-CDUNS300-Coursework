#include "MainGame.h"
#include <iostream>
#include <string>


unsigned int indices[] = { 0, 1, 2 };
Transform transform1;
Transform transform2;
Transform transform3;
Transform transform4;
Transform transform5;
bool Press1 = false;
bool Flipcounter;
bool Init = false;


MainGame::MainGame()
{
	
	_gameState = GameState::PLAY;
	Display* _gameDisplay = new Display(); //new display
	Mesh* mesh1 = new Mesh();
	Mesh* mesh2 = new Mesh();
	Mesh* mesh3 = new Mesh();
	Mesh* mesh4 = new Mesh();
	Camera* myCamera = new Camera();

	//Shader* shader;
	//Shader* shader2;
	counter = 0.0f;

}

MainGame::~MainGame()
{
}

void MainGame::run()
{
	initSystems(); 
	gameLoop();
}

void MainGame::initSystems()
{
	_gameDisplay.initDisplay();
	mesh1.loadModel("..//res//monkey3.obj");
	mesh2.loadModel("..//res//Sting.obj");
	mesh3.loadModel("..//res//Sting.obj");
	mesh4.loadModel("..//res//Satellite.obj");


	myCamera.initCamera(glm::vec3(0, 0, -10), 70.0f, (float)_gameDisplay.getWidth() / _gameDisplay.getHeight(), 0.01f, 1000.0f);
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput();
		drawGame();
	}
}

void MainGame::processInput()
{
	SDL_Event evnt;

	while(SDL_PollEvent(&evnt)) //get and process events
	{




		switch (evnt.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
			case SDL_KEYDOWN:
				switch (evnt.key.keysym.sym)
				{
					case SDLK_RIGHT:
						myCamera.MoveRight(-0.1);
						break;
					case SDLK_LEFT:
						myCamera.MoveRight(0.1);
						break;
					case SDLK_UP:
						myCamera.MoveForward(0.1);
						break;
					case SDLK_DOWN:
						myCamera.MoveForward(-0.1);
						break;


					case SDLK_w:
						myCamera.Pitch(-0.1);
						break;
					case SDLK_s:
						myCamera.Pitch(0.1);
						break;
					case SDLK_d:
						myCamera.RotateY(-0.1);
						break;
					case SDLK_a:
						myCamera.RotateY(0.1);
						break;

					case SDLK_1:
						Press1 = !Press1;
						Flipcounter = !Flipcounter;
						break;

				}
				break;

		}
	}
	
}


void MainGame::drawGame()
{
	_gameDisplay.clearDisplay(0.0f, 0.0f, 0.0f, 1.0f);
	
	Vertex Vert[] = { Vertex(glm::vec3(-5.0,0.0,0),glm::vec2(counter,0.0)),
					Vertex(glm::vec3(-5.0,5.0,0.0),glm::vec2(0.0,counter)),
					Vertex(glm::vec3(5.0,5.0,0),glm::vec2(-counter,0.0)),
					Vertex(glm::vec3(5.0,-5.0,0),glm::vec2(0.0,-counter))
	};

	Mesh SquareMesh;
	SquareMesh.initPlane(Vert, sizeof(Vert) / sizeof(Vert[0])); // needed new function for plane /

	
	Shader shader("..//res//shader"); //new shader
	Shader shader2("..//res//fog");
	Shader shader3("..//res//Rim");
	Shader shader4("..//res//Test");
	Shader shader5("..//res//Plaid");
	Shader shader6("..//res//Flat");
	Shader shader7("..//res//Toon");
	Shader shader8("..//res//Bump"); // not using due to lag
	Texture texture1("..//res//bricks.jpg"); //load texture
	Texture texture2("..//res//water.jpg"); //load texture
	Texture texture3("..//res//Doom.jpg"); //load texture
	Texture texture4("..//res//Rainbow.jpg"); //load texture
	Texture texture5("..//res//Metal.jpg");//load texture
	Texture textureB("..//res//Normal.jpg");
	//textureB.loadNormals("..//res//Normal.jpg"); not using due to lag
	//due to not having a empty default consturctor, must be set here, but causes lag as scope increses


	transform1.SetPos(glm::vec3(0.0));
	transform1.SetRot(glm::vec3(0.0, counter *0.1,0.0));
	transform1.SetScale(glm::vec3(1.0, 1.0, 1.0));
	texture1.Bind(0);
	if(Press1){
	shader5.Bind();
	
	shader5.Update(transform1, myCamera);
		}
	if (!Press1) {
		shader.Bind();
	
	shader.Update(transform1, myCamera);
	}
	mesh1.draw();

	

	transform2.SetPos(glm::vec3(5.0, 0.0, 0.0));
	transform2.SetScale(glm::vec3(0.1, 0.1, 0.1));
	texture2.Bind(0);
	if (Press1) {
		transform2.SetRot(glm::vec3(-counter, -counter, -counter));
		shader3.Bind();
		linkRim(shader3, transform2);
		shader3.Update(transform2, myCamera);
	}
	if (!Press1) {


	 glm::vec3 CAMPOS = *myCamera.GetPos();
	 glm::vec3 ROTPOS = *transform2.GetPos();
	 glm::vec3 TRAROT = *transform2.GetRot();
	 glm::vec3 CAMUP = *myCamera.GetUp();
	 glm::mat4 LOOK = (inverse(glm::lookAt(CAMPOS, ROTPOS, CAMUP)));
	 glm::vec4 LOOKF = LOOK * glm::vec4(*myCamera.GetRot(), 1.0);
	 transform2.SetRot(glm::vec3(LOOKF));
	 //to make object face camera, causes object ot move in relation to cam position

		shader7.Bind();
		linkToon(shader7, transform2);
		shader7.Update(transform2, myCamera);
	}
	mesh2.draw();


	transform3.SetPos(glm::vec3(-5.0, 0.0, -0.3));
	transform3.SetRot(glm::vec3(counter, counter, counter));
	transform3.SetScale(glm::vec3(0.1, 0.1, 0.1));
	texture3.Bind(0);
	if (Press1) {
		shader6.Bind();
		linkFlat(shader6, transform3);
		shader6.Update(transform3, myCamera);
	}
	if (!Press1) {
		shader.Bind();
		shader.Update(transform3, myCamera);
	}
	mesh3.draw();
	
	transform5.SetPos(glm::vec3(3.0));
	transform5.SetRot(glm::vec3(0.0, counter * 0.1, 0.0));
	transform5.SetScale(glm::vec3(1.0, 1.0, 1.0));
	texture5.Bind(0);
	if (Press1) {
		shader5.Bind();
		
		shader5.Update(transform5, myCamera);
	}
	if (!Press1) {
		shader3.Bind();
		linkRim(shader3 ,transform5);
		shader3.Update(transform5, myCamera);
	}
	mesh4.draw();




	transform4.SetPos(glm::vec3(0.0, -3.0, -3));
	transform4.SetRot(glm::vec3(1.5, 0, 0));
	transform4.SetScale(glm::vec3(10, 10, 10));
	texture4.Bind(0);
	shader.Bind();
	shader.Update(transform4, myCamera);
	SquareMesh.drawPlane();

	//transform 5

	
	if(Flipcounter){
	counter = counter + 0.05f;
		}
	if (!Flipcounter) {
		counter = counter - 0.05f;
	}

	glEnableClientState(GL_COLOR_ARRAY);
	glEnd();

	_gameDisplay.swapBuffer();
}


void MainGame::linkRim(Shader shader, Transform transform)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	shader.setMat4("modelMatrix", transform.GetModel());
	//rimShader.setMat4("viewMatrix", *myCamera.getView());
	shader.setFloat("rimPower", 3.0f);
	shader.setVec3("rimColor", glm::vec3(0.8f, 0.0f, 0.0f));
	shader.setVec3("camPos", *myCamera.GetPos());


	transform.SetPos(glm::vec3(1.0, 0.0, 0.0));
	transform.SetRot(glm::vec3(0.0, counter * 0.5, 0.0));
	transform.SetScale(glm::vec3(1.0, 1.0, 1.0));


}

void MainGame::linkFog(Shader shader)
{
	
	shader.setFloat("maxDist", 20.0f);
	shader.setFloat("minDist", 0.0f);
	shader.setVec3("fogColor", glm::vec3(0.0f, 0.0f, 0.0f));
}

void MainGame::linkToon(Shader shader, Transform transform)
{
	shader.setMat4("modelMatrix", transform.GetModel());
	shader.setVec3("lightDir", glm::vec3(0.5f, 0.5f, 0.5f));
}

void MainGame::linkBump(Shader shader, Transform transform, Texture texture, Texture bump)
{
	GLuint t1L = glGetUniformLocation(shader.getID(), "diffuse"); //texture 1 location
	GLuint t2L = glGetUniformLocation(shader.getID(), "normalT");

	//set textures
	glActiveTexture(GL_TEXTURE0); //set acitve texture unit
	glBindTexture(GL_TEXTURE_2D, texture.getID());
	glUniform1i(t1L, 0);

	glActiveTexture(GL_TEXTURE1); //set acitve texture unit
	glBindTexture(GL_TEXTURE_2D, bump.getNID());
	glUniform1i(t2L, 1);
}

void MainGame::linkPlaid(Shader shader, Transform transform)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//shader.setMat4("modelMatrix", transform.GetModel());
	//rimShader.setMat4("viewMatrix", *myCamera.getView());

	//shader.setVec3("camPos", *myCamera.GetPos());

}

void MainGame::linkFlat(Shader shader, Transform transform)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//shader.setMat4("modelMatrix", transform.GetModel());
	//rimShader.setMat4("viewMatrix", *myCamera.getView());
	
	//shader.setVec3("camPos", *myCamera.GetPos());

}