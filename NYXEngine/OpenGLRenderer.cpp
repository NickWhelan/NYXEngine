#include "pch.h"
#include "OpenGLRenderer.h"
#include "glm\glm\glm.hpp"
#include "glm\glm\gtc\matrix_transform.hpp"

#include "Model.h"

static const GLfloat bg[] = { .10f, 0.0f, .20f, 1.0f };
static const int NumVertices = 9;
float angle;
Model model;


GLuint shaderProgram;
GLuint VBO, VAO;
OpenGLRenderer::OpenGLRenderer()
{
	CameraOne = new Camera();
}

bool OpenGLRenderer::loadOBJ(const char* path, std::vector<glm::vec3> &out_vertices, std::vector<glm::vec2> &out_uvs, std::vector<glm::vec3> &out_normals)
{
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;

	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	FILE* file;

	file = fopen(path, "r");
	if (file == NULL)
	{
		printf("CANNOT OPEN THE FILE\n");
		return false;
	}

	while (1)
	{
		char lineHeader[128];

		//read first word of line
		int res = fscanf_s(file, "%s", lineHeader);

		if (res == EOF)
			break;

		if (strcmp(lineHeader, "v") == 0)
		{
			glm::vec3 vertex;
			fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0)
		{
			glm::vec2 uv;
			fscanf_s(file, "%f, %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0)
		{
			glm::vec3 normal;
			fscanf_s(file, "%f, %f, %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf_s(file, "%d%d%d %d%d%d %d%d%d\n",
				&vertexIndex[0], &uvIndex[0], &normalIndex[0],
				&vertexIndex[1], &uvIndex[1], &normalIndex[1],
				&vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9)
			{
				printf("File can't be read by simple parser... :( try exporting with different options!");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
			for (unsigned int i = 0; i < vertexIndices.size(); i++)
			{
				unsigned int vertexIndex = vertexIndices[i];

				glm::vec3 vertex = temp_vertices[vertexIndex - 1];

				out_vertices.push_back(vertex);
			}
		}
	}
	fclose(file);

}

OpenGLRenderer::~OpenGLRenderer()
{
}
void OpenGLRenderer::BufferSetUp()
{
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	///Shaders
	//define the shader types and loactions
	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "triangles.vert" },
		{ GL_FRAGMENT_SHADER, "triangles.frag" }
	};

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
	//same for FragmentShader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//Make the ShaderProgram and link it to engine
	shaderProgram = glCreateProgram();
	//attach shaders to the shaderProgram
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//link and use the defined shaderProgram
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	//deleting the shaders because they are linked at this point;
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	///Buffers
	glEnable(GL_DEPTH_TEST);
	//define vertex buffer objects
	
	// Define the number of buffers and vertex buffer objects attached
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);
	//build a buffer for a VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// add verts to a buffer using the type of data then length and actull data
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	// Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
	
	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	// Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
	glBindVertexArray(0); 

	




	/*
	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "triangles.vert" },
		{ GL_FRAGMENT_SHADER, "triangles.frag" },
		{ GL_NONE, NULL }
	};

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
	
	model.LoadBuffer(shaders);
	*/
}

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
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
}
void OpenGLRenderer::Render() {
	//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	//glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
void OpenGLRenderer::PostRender()
{
	glBindVertexArray(0);
	//glDrawArrays(GL_TRIANGLES, 0, NumVertices);
	//glFlush();
}