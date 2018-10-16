#include "MyApp.h"
#include "GLUtils.hpp"

#include <math.h>

CMyApp::CMyApp(void)
{
	m_vaoID = 0;
	m_vboID = 0;
	m_programID = 0;
}


CMyApp::~CMyApp(void)
{
}

bool CMyApp::Init()
{
	// set the clear color (background color)
	glClearColor(0.125f, 0.25f, 0.5f, 1.0f);

	glEnable(GL_CULL_FACE);		// enable backface culling
	glEnable(GL_DEPTH_TEST);	// enable depth test (z-buffer)

	//
	// create the geometry
	//

	Vertex vert[] =
	{ 
		// position x,  y, z;  color     r, g, b
		{glm::vec3(-1, -1, 0), glm::vec3(1, 0, 0)},
		{glm::vec3( 1, -1, 0), glm::vec3(0, 1, 0)},
		{glm::vec3(-1,  1, 0), glm::vec3(0, 0, 1)},
		{glm::vec3( 1,  1, 0), glm::vec3(1, 1, 1)},
	};

	// generate a VAO ID
	glGenVertexArrays(1, &m_vaoID);
	// activate the generated VAO
	glBindVertexArray(m_vaoID);
	
	// generate a VBO ID
	glGenBuffers(1, &m_vboID); 
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID); // activate the new VBO
	// allocate the VBO (in the onboard GPU memory) and fill it with data from system RAM (vert[])
	glBufferData( GL_ARRAY_BUFFER,	// which activated buffer object to allocate
				  sizeof(vert),		// how many bytes should be allocated
				  vert,				// copy data from system RAM from this memory address
				  GL_STATIC_DRAW);	// usage flags
	

	// register in the VAO that general attribute index 0 is activated and it contains 3 floats per vertex
	glEnableVertexAttribArray(0); // enable channel 0 (position)
	glVertexAttribPointer(
		(GLuint)0,		// we set the descriptor (pointer) of channel 0`s attributes
		3,				// it contains 3
		GL_FLOAT,		// floats
		GL_FALSE,		// not normalized
		sizeof(Vertex),	// stride (0=tightly packed)
		0				// first data at the beginning of the buffer
	); 

	// register in the VAO that general attribute index 3 is activated and it contains 3 floats per vertex
	glEnableVertexAttribArray(1); // enable channel 3 (color)
	glVertexAttribPointer(
		(GLuint)1,
		3, 
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)(sizeof(glm::vec3)) ); // stride = 3*sizeof(float) i.e. skip 3 floats at the beginning

	glBindVertexArray(0); // deactivate the VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0); // deactiviate the VBO

	//
	// load the shaders
	//
	GLuint vs_ID = loadShader(GL_VERTEX_SHADER,		"myVert.vert");
	GLuint fs_ID = loadShader(GL_FRAGMENT_SHADER,	"myFrag.frag");

	// create the shader program object
	m_programID = glCreateProgram();

	// attach the loaded shaders to the program object
	glAttachShader(m_programID, vs_ID);
	glAttachShader(m_programID, fs_ID);

	// connect the VAO general attribute channels and vertex shader input variables
	glBindAttribLocation(	m_programID,	// program ID
							0,				// attribute channel
							"vs_in_pos");	// shader 'in' variable
	glBindAttribLocation( m_programID, 1, "vs_in_col");

	// link the shader program
	glLinkProgram(m_programID);

	// check link status
	GLint infoLogLength = 0, result = 0;

	glGetProgramiv(m_programID, GL_LINK_STATUS, &result);
	glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if ( infoLogLength > 1)
	{
		std::vector<char> ProgramErrorMessage( infoLogLength );
		glGetProgramInfoLog(m_programID, infoLogLength, NULL, &ProgramErrorMessage[0]);
		fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);
		
		char* aSzoveg = new char[ProgramErrorMessage.size()];
		memcpy( aSzoveg, &ProgramErrorMessage[0], ProgramErrorMessage.size());

		std::cout << "[app.Init()] Shader problem: " << aSzoveg << std::endl;

		delete aSzoveg;
	}

	glDeleteShader( vs_ID );
	glDeleteShader( fs_ID );

	return true;
}

void CMyApp::Clean()
{
	glDeleteBuffers(1, &m_vboID);
	glDeleteVertexArrays(1, &m_vaoID);

	glDeleteProgram( m_programID );
}

void CMyApp::Update()
{
}


void CMyApp::Render()
{
	// clear the frame buffer (GL_COLOR_BUFFER_BIT) and z-buffer (GL_DEPTH_BUFFER_BIT)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// shader on
	glUseProgram( m_programID );

	// VAO on
	glBindVertexArray(m_vaoID);

	// draw
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	// VAO off
	glBindVertexArray(0);

	// shader off
	glUseProgram( 0 );
}

void CMyApp::KeyboardDown(SDL_KeyboardEvent& key)
{
}

void CMyApp::KeyboardUp(SDL_KeyboardEvent& key)
{
}

void CMyApp::MouseMove(SDL_MouseMotionEvent& mouse)
{

}

void CMyApp::MouseDown(SDL_MouseButtonEvent& mouse)
{
}

void CMyApp::MouseUp(SDL_MouseButtonEvent& mouse)
{
}

void CMyApp::MouseWheel(SDL_MouseWheelEvent& wheel)
{
}

// _w: new width, _h: new height
void CMyApp::Resize(int _w, int _h)
{
	glViewport(0, 0, _w, _h );
}