#include "MyApp.h"
#include "GLUtils.hpp"

//#include <GL/GLU.h>
#include <math.h>

CMyApp::CMyApp(void)
{
	m_vaoID = 0;
	m_vboID = 0;
	m_programID = 0;
	m_waterTextureID = 0;

	m_mesh = 0;
}


CMyApp::~CMyApp(void)
{
}

bool CMyApp::Init()
{
	glClearColor(0.125f, 0.25f, 0.5f, 1.0f);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK); 

	Vertex vert[] =
	{ 
		//          x,  y, z               nx,ny,nz			 s, t
		{glm::vec3(-10, 0, -10), glm::vec3( 0, 1, 0), glm::vec2(0, 0)},
		{glm::vec3(-10, 0,  10), glm::vec3( 0, 1, 0), glm::vec2(0, 1)},
		{glm::vec3( 10, 0, -10), glm::vec3( 0, 1, 0), glm::vec2(1, 0)},
		{glm::vec3( 10, 0,  10), glm::vec3( 0, 1, 0), glm::vec2(1, 1)},
	};

    GLushort indices[]=
    {
        0,1,2,
        2,1,3,
    };

	glGenVertexArrays(1, &m_vaoID);
	glBindVertexArray(m_vaoID);
	
	glGenBuffers(1, &m_vboID); 
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	glBufferData( GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0 ); 

	glEnableVertexAttribArray(1); 
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)) );

	glEnableVertexAttribArray(2); 
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2*sizeof(glm::vec3)) );

	glGenBuffers(1, &m_ibID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//
	// shaders
	//
	GLuint vs_ID = loadShader(GL_VERTEX_SHADER,		"myVert.vert");
	GLuint fs_ID = loadShader(GL_FRAGMENT_SHADER,	"myFrag.frag");

	m_programID = glCreateProgram();

	glAttachShader(m_programID, vs_ID);
	glAttachShader(m_programID, fs_ID);

	glBindAttribLocation(	m_programID, 0, "vs_in_pos");
	glBindAttribLocation( m_programID, 1, "vs_in_col");
	glBindAttribLocation( m_programID, 2, "vs_in_tex0");

	glLinkProgram(m_programID);

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
	// 
	//

	m_matProj = glm::perspective( 45.0f, 640/480.0f, 1.0f, 1000.0f );

	m_loc_mvp = glGetUniformLocation( m_programID, "MVP");
	m_loc_texture = glGetUniformLocation( m_programID, "texture" );

	// load texture
	m_waterTextureID = TextureFromFile("texture.bmp");

	// load mesh
	m_mesh = ObjParser::parse("Suzanne.obj");
	m_mesh->initBuffers();

	return true;
}

void CMyApp::Clean()
{
	delete m_mesh;
	glDeleteTextures(1, &m_waterTextureID);

	glDeleteBuffers(1, &m_vboID);
	glDeleteVertexArrays(1, &m_vaoID);

	glDeleteProgram( m_programID );
}

void CMyApp::Update()
{
	m_matView = glm::lookAt(glm::vec3(0, -10, 20),		// eye
							glm::vec3( 0,  0,  0),		// center
							glm::vec3( 0,  1,  0));		// up
}


void CMyApp::DrawGround()
{
	glUseProgram( m_programID );

	m_matWorld = glm::mat4(1.0f);
	glm::mat4 mvp = m_matProj * m_matView * m_matWorld;

	glUniformMatrix4fv( m_loc_mvp, 1, GL_FALSE, &(mvp[0][0]) );
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_waterTextureID);
	glUniform1i(	m_loc_texture, 0);

	glBindVertexArray(m_vaoID);

	glDrawElements(	GL_TRIANGLES,		// primitive type
					6,					// vertex count
					GL_UNSIGNED_SHORT,	// index type
					0);					// index address

	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0);

	glUseProgram( 0 );
}

void CMyApp::DrawMesh()
{
	glUseProgram( m_programID );

	const float r = 10;
	for (int i = 0; i < 5; i++) {


		float t = 2 * M_PI / 5 * i 
			+ SDL_GetTicks() / 5000.0;

		float t2 = SDL_GetTicks() / 1000.0;
		//this is where the rotation happens
		float x = r * cosf(t);
		float y = r * sinf(t);
		float z = 0;//4 * sin(t + t2);//* r 

		m_matWorld =
			glm::translate<float>(glm::vec3(x, y, z));
		
		glm::mat4 mvp = m_matProj * m_matView * m_matWorld;

		glUniformMatrix4fv(m_loc_mvp, 1, GL_FALSE, &(mvp[0][0]));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_waterTextureID);
		glUniform1i(m_loc_texture, 0);

		m_mesh->draw();
	}

	glUseProgram( 0 );
}

void CMyApp::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawGround();
	DrawMesh();
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

	m_matProj = glm::perspective(  45.0f, _w/(float)_h,	0.01f, 100.0f);
}
