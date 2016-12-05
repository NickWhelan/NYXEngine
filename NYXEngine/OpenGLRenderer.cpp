#include "pch.h"
#include "OpenGLRenderer.h"
#include "glm\glm\glm.hpp"
#include "glm\glm\gtc\matrix_transform.hpp"
#include <iostream>
#include "Model.h"

static const GLfloat bg[] = { .10f, 0.0f, .20f, 1.0f };
static const int NumVertices = 9;
float angle;

OpenGLRenderer::OpenGLRenderer()
{
	//CameraOne = new Camera();
}

OpenGLRenderer::~OpenGLRenderer()
{
}
void OpenGLRenderer::renderPrimitive(PRIMITIVETYPE prim)
{

	///Shaders
	//define the shader types and loactions
	
	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "triangles.vert" },
		{ GL_FRAGMENT_SHADER, "triangles.frag" }
	};
	/*
	const GLchar* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 position;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
		"}\0";
	const GLchar* fragmentShaderSource = "#version 330 core\n"
		"out vec4 color;\n"
		"void main()\n"
		"{\n"
		"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";

	//make and define the vertexShader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//the location of the shader and other values that i dont understand
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//compile the shader and attach it program; 
	glCompileShader(vertexShader);
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	else {
		std::cout << "Loaded Shader\n";
	}
	//same for FragmentShader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	else {
		std::cout << "Loaded Shader\n";
	}
	//Make the ShaderProgram and link it to engine
	shaderProgram = glCreateProgram();
	//attach shaders to the shaderProgram
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//link and use the defined shaderProgram
	glLinkProgram(shaderProgram);
	//glUseProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	//deleting the shaders because they are linked at this point;
	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);
	*/

	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	///Buffers
	glEnable(GL_DEPTH_TEST);
	//define vertex buffer objects
	
	// Define the number of buffers and vertex buffer objects attached
	//glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &VBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	//glBindVertexArray(VAO);
	//build a buffer for a VBO
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// add verts to a buffer using the type of data then length and actull data
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	// Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	// Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
	glBindVertexArray(0); 

	/*
=======
	
	glEnable(GL_DEPTH_TEST);
>>>>>>> origin/master
	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "triangles.vert" },
		{ GL_FRAGMENT_SHADER, "triangles.frag" },
		{ GL_NONE, NULL }
	};
	/*
	glm::vec3 Verts[255];
	glm::vec3 ColorData[255];
	int VertLength = 9;
	Verts[0] = glm::vec3(0, 1, 0);
	Verts[1] = glm::vec3(-1, -1, 1);
	Verts[2] = glm::vec3(1, -1, 1);

	ColorData[0] = glm::vec3(0, 1, 0);
	ColorData[1] = glm::vec3(0, 1, 0);
	ColorData[2] = glm::vec3(0, 1, 0);

	Verts[3] = glm::vec3(0, 1, 0);
	Verts[4] = glm::vec3(-1, -1, 1);
	Verts[5] = glm::vec3(0, -1, -1);
	ColorData[3] = glm::vec3(1, 0, 0);
	ColorData[4] = glm::vec3(1, 0, 0);
	ColorData[5] = glm::vec3(1, 0, 0);

	Verts[6] = glm::vec3(0, 1, 0);
	Verts[7] = glm::vec3(0, -1, -1);
	Verts[8] = glm::vec3(1, -1, 1);
	ColorData[6] = glm::vec3(0, 0, 1);
	ColorData[7] = glm::vec3(0, 0, 1);
	ColorData[8] = glm::vec3(0, 0, 1);
	*/
	
	//model.MakeShape(Model::PrimitiveShapes::Primide);

	GLuint program = LoadShaders(shaders);
	glUseProgram(program);

	glGenBuffers(2, Buffers);

	glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, 255, 0, GL_DYNAMIC_DRAW);
	//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(ColorData), ColorData);
	//model.LoadBuffer(true);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(Verts), Verts, GL_DYNAMIC_DRAW);
	glBindAttribLocation(program, 0, "vPosition");
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, 255, 0, GL_DYNAMIC_DRAW);
	//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(ColorData), ColorData);
	//model.LoadBuffer(false);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(ColorData), ColorData, GL_DYNAMIC_DRAW);
	glBindAttribLocation(program, 1, "vertexColor");
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(1);

	location = glGetUniformLocation(program, "model_matrix");
	location2 = glGetUniformLocation(program, "camera_matrix");
	location3 = glGetUniformLocation(program, "proj_matrix");
	
}

void OpenGLRenderer::BufferSetUpBeta() {
	glEnable(GL_DEPTH_TEST);
	
	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "triangles.vert" },
		{ GL_FRAGMENT_SHADER, "triangles.frag" },
		{ GL_NONE, NULL }
	};

	GLuint program = LoadShaders(shaders);
	glUseProgram(program);
	glGenVertexArrays(1, &ChunkVAO);
	glBindVertexArray(ChunkVAO);

	glGenBuffers(BufferCount, &ChunkBuffers[0]);
	glBindBuffer(GL_ARRAY_BUFFER, ChunkBuffers[0]);
	glBindAttribLocation(program, 0, "vPosition");
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, ChunkBuffers[1]);
	glBindAttribLocation(program, 1, "vertexColor");
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	modelMatrix = glGetUniformLocation(program, "model_matrix");
}
void OpenGLRenderer::AddToBuffer(const std::vector<glm::vec3>* const Points, const std::vector<glm::vec3>* const Colors) {
	glBindVertexArray(ChunkVAO);
	glBindBuffer(GL_ARRAY_BUFFER, ChunkBuffers[0]);
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(glm::vec3), &Points[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, ChunkBuffers[1]);
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(glm::vec3), &Colors[0], GL_STATIC_DRAW);
	length = glm::min(Points->size(), Colors->size());
	glBindVertexArray(0);
}
/*
void GLChunkRenderer::Render(Window* window)
{
window->renderPrimitive(Window::PrimativeType::QUAD, ChunkVAO, 0, length);
}
*/
void OpenGLRenderer::PreRender()
{
	/*
	angle+= 0.005;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	CameraOne->RenderCam();
	glm::mat4 camera_matrix = *CameraOne->camera_matrix;
	glUniformMatrix4fv(location2, 1, GL_FALSE, &camera_matrix[0][0]);

	glm::mat4 projection_matrix = glm::perspective(45.0f, 1.0f, 1.0f, 100.0f);
	glUniformMatrix4fv(location3, 1, GL_FALSE, &projection_matrix[0][0]);

	//model.Draw(location);
	glm::mat4 model_view = glm::translate(glm::mat4(1.0), glm::vec3(0.0, 0.0, 0.0));
	model_view = glm::rotate(glm::mat4(1.0), angle, glm::vec3(0.0, 1.0, 0.0));
	glUniformMatrix4fv(location, 1, GL_FALSE, &model_view[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, 9);*/
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glUseProgram(shaderProgram);
}
void OpenGLRenderer::Render() {
	//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	//glBindVertexArray(VAO);
	glBindVertexArray(VAO);
	glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, &glm::mat4(1.0)[0][0]);

	glDrawArrays(GL_QUADS, 0, length);
	glBindVertexArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 9);
}
void OpenGLRenderer::PostRender()
{
	//glDrawArrays(GL_TRIANGLES, 0, NumVertices);
	glFlush();
}