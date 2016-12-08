//////////////////////////////////////////////////////////////////////////////
//
//  --- LoadShaders.cxx ---
//
//////////////////////////////////////////////////////////////////////////////

#include <cstdlib>
#include <iostream>

//#define GLEW_STATIC
#include "OpenGL\include\glew.h"
#include "LoadShaders.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	FILE _iob[] = { *stdin, *stdout, *stderr };

	extern "C" FILE * __cdecl __iob_func(void)
	{
		return _iob;
	}
	//----------------------------------------------------------------------------

	static const GLchar*
		ReadShader(const char* filename)
	{
#ifdef WIN32
		FILE* infile;
		fopen_s(&infile, filename, "rb");// open the file
#else
		FILE* infile;
		fopen_s(&infile, filename, "rb");
#endif // WIN32

		if (!infile) {// if the file is not found
#ifdef _DEBUG
			std::cout << "Unable to open file '" << filename << "'" << std::endl;
#endif /* DEBUG */
			return NULL;
		}

		fseek(infile, 0, SEEK_END);
		int len = ftell(infile);
		fseek(infile, 0, SEEK_SET);

		GLchar* source = new GLchar[len + 1];// set up the array to be the length of the file

		fread(source, 1, len, infile);//read the file
		fclose(infile);// close the file

		source[len] = 0;// set the last char slot to 0

		return const_cast<const GLchar*>(source); // return the char array
	}

	//----------------------------------------------------------------------------

	GLuint
		LoadShaders(ShaderInfo* shaders)
	{
		if (shaders == NULL) { return 0; }

		GLuint program = glCreateProgram(); //make the return

		ShaderInfo* entry = shaders; //make a temp
		while (entry->type != GL_NONE) {//run till the last is null
			GLuint shader = glCreateShader(entry->type);//make shader of type(frag or vert)

			entry->shader = shader; // make the shader of the temp equal to the type

			const GLchar* source = ReadShader(entry->filename); // read shader and conver it to a char array (see above function)
			if (source == NULL) { // if the array is equal to nothing return 0
				for (entry = shaders; entry->type != GL_NONE; ++entry) {
					glDeleteShader(entry->shader);
					entry->shader = 0;
				}

				return 0;
			}

			glShaderSource(shader, 1, &source, NULL); // link the shader to its source
			delete[] source;// delet the char array

			glCompileShader(shader); //compile the shader

			GLint compiled;//this is to set up a check to see if the shaders compile 
			glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
			if (!compiled) {
#ifdef _DEBUG
				GLsizei len;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

				GLchar* log = new GLchar[len + 1];
				glGetShaderInfoLog(shader, len, &len, log);
				std::cout << "Shader compilation failed: " << log << std::endl;
				delete[] log;
#endif /* DEBUG */
				return 0;
			}

			glAttachShader(program, shader); // attach the shader to the program

			++entry; // move to the next shader file
		}

#ifdef GL_VERSION_4_1
		if (GLEW_VERSION_4_1) {
			// glProgramParameteri( program, GL_PROGRAM_SEPARABLE, GL_TRUE );
		}
#endif /* GL_VERSION_4_1 */

		glLinkProgram(program); // link the shader program

		GLint linked;//chack if its linked
		glGetProgramiv(program, GL_LINK_STATUS, &linked);
		if (!linked) {
#ifdef _DEBUG
			GLsizei len;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);

			GLchar* log = new GLchar[len + 1];
			glGetProgramInfoLog(program, len, &len, log);
			std::cout << "Shader linking failed: " << log << std::endl;
			delete[] log;
#endif /* DEBUG */

			for (entry = shaders; entry->type != GL_NONE; ++entry) {
				glDeleteShader(entry->shader);
				entry->shader = 0;
			}

			return 0;
		}

		return program; // return the working shader program
	}

	//----------------------------------------------------------------------------
#ifdef __cplusplus
}
#endif // __cplusplus


