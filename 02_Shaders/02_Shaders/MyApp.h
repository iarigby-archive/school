#pragma once

// GLEW
#include <GL/glew.h>

// SDL
#include <SDL.h>
#include <SDL_opengl.h>

// GLM
#include <glm/glm.hpp>

class CMyApp
{
public:
	CMyApp(void);
	~CMyApp(void);

	bool Init();
	void Clean();

	void Update();
	void Render();

	void KeyboardDown(SDL_KeyboardEvent&);
	void KeyboardUp(SDL_KeyboardEvent&);
	void MouseMove(SDL_MouseMotionEvent&);
	void MouseDown(SDL_MouseButtonEvent&);
	void MouseUp(SDL_MouseButtonEvent&);
	void MouseWheel(SDL_MouseWheelEvent&);
	void Resize(int, int);
protected:
	GLuint m_vaoID; // vertex array object resource identifier
	GLuint m_vboID; // vertex buffer object resource identifier
	GLuint m_programID; // shader program ID

	// structure which contains all the data that is stored in a single vertex
	struct Vertex
	{
		glm::vec3 p;		// position; glm::vec3 is a 3 dimensional vector with float coordinates
		glm::vec3 c;		// color
	};
};

