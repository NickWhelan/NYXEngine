#include "pch.h"
#include "OpenGLRenderer.h"
#include "glm\glm\glm.hpp"
#include "glm\glm\gtc\matrix_transform.hpp"

#include "Model.h"

static const GLfloat bg[] = { .10f, 0.0f, .20f, 1.0f };
static const int NumVertices = 9;
float angle;
Model model;
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
void OpenGLRenderer::renderPrimitive(PRIMITIVETYPE prim)
{
	
	glEnable(GL_DEPTH_TEST);
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
	
	model.LoadBuffer(shaders);
}

void OpenGLRenderer::PreRender()
{
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
	glDrawArrays(GL_TRIANGLES, 0, 9);
}
void OpenGLRenderer::PostRender()
{
	//glDrawArrays(GL_TRIANGLES, 0, NumVertices);
	//glFlush();
}