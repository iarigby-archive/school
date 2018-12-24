#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <GL/glew.h>

#include <SDL_image.h>

/* 

Based on http://www.opengl-tutorial.org/ 

*/
GLuint loadShader(GLenum _shaderType, const char* _fileName)
{
	// create shader resource ID
	GLuint loadedShader = glCreateShader( _shaderType );

	if ( loadedShader == 0 )
	{
		fprintf(stderr, "[loadShader] glCreateShader failed", _fileName);
		return 0;
	}
	
	// load the shader code (text file)
	std::string shaderCode = "";

	std::ifstream shaderStream(_fileName);

	if ( !shaderStream.is_open() )
	{
		fprintf(stderr, "[shaderStream] Cannot open shader file", _fileName);
		return 0;
	}

	std::string line = "";
	while ( std::getline(shaderStream, line) )
	{
		shaderCode += line + "\n";
	}

	shaderStream.close();

	// attach the code to the shader resource
	const char* sourcePointer = shaderCode.c_str();
	glShaderSource( loadedShader, 1, &sourcePointer, NULL );

	// compile the shader
	glCompileShader( loadedShader );

	// check compilation status
	GLint result = GL_FALSE;
    int infoLogLength;

	glGetShaderiv(loadedShader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(loadedShader, GL_INFO_LOG_LENGTH, &infoLogLength);

	if ( GL_FALSE == result )
	{
		// compilation failed
		std::vector<char> VertexShaderErrorMessage(infoLogLength);
		glGetShaderInfoLog(loadedShader, infoLogLength, NULL, &VertexShaderErrorMessage[0]);

		fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);
	}

	return loadedShader;
}

GLuint loadProgramVSGSFS(const char* _fileNameVS, const char* _fileNameGS, const char* _fileNameFS)
{
	GLuint vs_ID = loadShader(GL_VERTEX_SHADER,		_fileNameVS);
	GLuint gs_ID = loadShader(GL_GEOMETRY_SHADER,	_fileNameGS);
	GLuint fs_ID = loadShader(GL_FRAGMENT_SHADER,	_fileNameFS);

	if ( vs_ID == 0 || gs_ID == 0 || fs_ID == 0 )
	{
		return 0;
	}

	GLuint program_ID = glCreateProgram();

	fprintf(stdout, "Linking program\n");
	glAttachShader(program_ID, vs_ID);
	glAttachShader(program_ID, gs_ID);
	glAttachShader(program_ID, fs_ID);

	glLinkProgram(program_ID);

	GLint infoLogLength = 0, result = 0;

	glGetProgramiv(program_ID, GL_LINK_STATUS, &result);
	glGetProgramiv(program_ID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if ( GL_FALSE == result)
	{
		std::vector<char> ProgramErrorMessage( infoLogLength );
		glGetProgramInfoLog(program_ID, infoLogLength, NULL, &ProgramErrorMessage[0]);
		fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);
	}

	glDeleteShader( vs_ID );
	glDeleteShader( gs_ID );
	glDeleteShader( fs_ID );

	return program_ID;
}

GLuint TextureFromFile(const char* filename)
{
	SDL_Surface* loaded_img = IMG_Load(filename);  

	int img_mode = 0;
	
	if ( loaded_img == 0 )
	{
		std::cout << "[TextureFromFile] Hiba a kép betöltése közben: " << filename << std::endl;
		return 0;
	}

	#if SDL_BYTEORDER == SDL_LIL_ENDIAN
		if ( loaded_img->format->BytesPerPixel == 4 )
			img_mode = GL_BGRA;
		else
			img_mode = GL_BGR;
	#else
		if ( loaded_img->format->BytesPerPixel == 4 )
			img_mode = GL_RGBA;
		else
			img_mode = GL_RGB;
	#endif

    GLuint tex;
    glGenTextures(1, &tex);
  
    glBindTexture(GL_TEXTURE_2D, tex);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, loaded_img->w, loaded_img->h, img_mode, GL_UNSIGNED_BYTE, loaded_img->pixels);
  
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  
	SDL_FreeSurface( loaded_img );

    return tex;
}