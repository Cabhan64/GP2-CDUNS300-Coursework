#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "Display.h" 
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "transform.h"

enum class GameState { PLAY, EXIT };

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:

	void initSystems();
	void processInput();
	void gameLoop();
	void drawGame();
	void linkFog(Shader shader);
	void linkToon(Shader shader,Transform transform);
	void linkRim(Shader shader,Transform transform);
	void linkBump(Shader shader, Transform transform, Texture texture, Texture bump);
	void linkPlaid(Shader shader, Transform transform);
	void linkFlat(Shader shader, Transform transform);

	Display _gameDisplay;
	GameState _gameState;
	Mesh mesh1;
	Mesh mesh2;
	Mesh mesh3;
	Mesh mesh4;
	Camera myCamera;
	//Shader shader;

	float counter;

};

