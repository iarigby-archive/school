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
	// blue-ish clear color
	glClearColor(0.125f, 0.25f, 0.5f, 1.0f);

	glEnable(GL_CULL_FACE);		// enable back-face culling
	glCullFace(GL_BACK);		// cull the back-faces: GL_BACK; cull front faces: GL_FRONT
	glEnable(GL_DEPTH_TEST);	// enable depth test

	//
	// geometry
	//

	Vertex vert[] =
	{ 
		// 1st triangle
		//          x,  y, z             R, G, B
		{glm::vec3(-1, -1, 0), glm::vec3(1, 0, 0)},
		{glm::vec3( 1, -1, 0), glm::vec3(0, 1, 0)},
		{glm::vec3(-1,  1, 0), glm::vec3(0, 0, 1)},

		// 2nd triangle
		{glm::vec3(-1,  1, 0), glm::vec3(0, 0, 1)},
		{glm::vec3( 1, -1, 0), glm::vec3(0, 1, 0)},
		{glm::vec3( 1,  1, 0), glm::vec3(1, 1, 1)},
	};

	//
	// allocate VAO, VBO, fill the latter with the geometry, set attributes
	//
	glGenVertexArrays(1, &m_vaoID);
	glBindVertexArray(m_vaoID);
	
	glGenBuffers(1, &m_vboID); 
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID); 
	glBufferData( GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),	0); 

	glEnableVertexAttribArray(1); 
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)) );

	glBindVertexArray(0); 
	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	//
	// load shaders
	//
	GLuint vs_ID = loadShader(GL_VERTEX_SHADER,		"myVert.vert");
	GLuint fs_ID = loadShader(GL_FRAGMENT_SHADER,	"myFrag.frag");

	// create shader program
	m_programID = glCreateProgram();

	// attach the two shaders to the program object
	glAttachShader(m_programID, vs_ID);
	glAttachShader(m_programID, fs_ID);

	// bind the attribute channels and the vertex shader in variables
	glBindAttribLocation( m_programID, 0, "vs_in_pos");
	glBindAttribLocation( m_programID, 1, "vs_in_col");

	// link the shaders
	glLinkProgram(m_programID);

	// check link status
	GLint infoLogLength = 0, result = 0;

	glGetProgramiv(m_programID, GL_LINK_STATUS, &result);
	glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if ( GL_FALSE == result )
	{
		std::vector<char> ProgramErrorMessage( infoLogLength );
		glGetProgramInfoLog(m_programID, infoLogLength, NULL, &ProgramErrorMessage[0]);
		fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);
		
		char* aSzoveg = new char[ProgramErrorMessage.size()];
		memcpy( aSzoveg, &ProgramErrorMessage[0], ProgramErrorMessage.size());

		std::cout << "[app.Init()] Sáder Huba panasza: " << aSzoveg << std::endl;

		delete aSzoveg;
	}

	glDeleteShader( vs_ID );
	glDeleteShader( fs_ID );

	//
	// rest of the init
	//

	// projection matrix
	m_matProj = glm::perspective( 45.0f, 640/480.0f, 1.0f, 1000.0f );

	// find the uniform variables' location
	m_loc_world = glGetUniformLocation( m_programID, "world");
	m_loc_view  = glGetUniformLocation( m_programID, "view" );
	m_loc_proj  = glGetUniformLocation( m_programID, "proj" );

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
	// view transform
	m_matView = glm::lookAt(glm::vec3( 0,  0,  5),		// eye position
							glm::vec3( 0,  0,  0),		// look at point
							glm::vec3( 0,  1,  0));		// vector pointing upwards
}


void CMyApp::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// shader on
	glUseProgram( m_programID );

	// set shader uniforms' values
	/*

	GLM transformation matrices
		glm::rotate<float>( angle, axis_x, axis_y, axis_z) 
		glm::translate<float>( d_x, d_y, d_z) 
		glm::scale<float>( s_x, s_y, s_z )

	*/
	// <float> is needed because vec  is int and pi is float and results in error
	int t = SDL_GetTicks();
	m_matWorld = glm::rotate<float>(2*M_PI *t/ 1000.0f, glm::vec3(0, 0, 1)) *  glm::translate(glm::vec3(2, 3, 1))
		;

	glUniformMatrix4fv( m_loc_world,// uniform's location
						1,			// send 1 matrix
						GL_FALSE,	// do no transpose the matrix
						&(m_matWorld[0][0]) ); // read data from here, 16 x sizeof(float) 
	glUniformMatrix4fv( m_loc_view,  1, GL_FALSE, &( m_matView[0][0]) );
	glUniformMatrix4fv( m_loc_proj,  1, GL_FALSE, &( m_matProj[0][0]) );

	// VAO on
	glBindVertexArray(m_vaoID);

	// draw
	glDrawArrays(GL_TRIANGLES, 0, 6);

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

void CMyApp::Resize(int _w, int _h)
{
	glViewport(0, 0, _w, _h);

	m_matProj = glm::perspective(  45.0f, _w/(float)_h, 0.01f, 100.0f);
}