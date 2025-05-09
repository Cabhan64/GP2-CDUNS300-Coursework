#pragma once
#include <string>
#include <GL\glew.h>

class Texture
{
public:
	Texture(const std::string& fileName);
	void loadNormals(const std::string& fileName);
	void Bind(unsigned int unit); // bind upto 32 textures
	GLuint getID() { return textureHandler; }
	GLuint getNID() { return textureNHandler; }
	~Texture();

protected:
private:

	GLuint textureHandler;
	GLuint textureNHandler;
};

