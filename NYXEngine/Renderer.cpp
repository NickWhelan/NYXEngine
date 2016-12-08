#include "Renderer.h"

float roateY=0;

Renderer::Renderer()
{
}

void Renderer::BufferSetUp(GLuint const Program) {
	//glEnable(GL_DEPTH_TEST);
	///creat the vao and makes and adress (uuid) for it
	glGenVertexArrays(1, &VAO);
	///Inables the VAO Set thats as a current and open and then the lines bellow are added to this vao
	glBindVertexArray(VAO);
	///Generate the numbers and returns an array of units at that adress
	///Passing the fist valuse of the array defines the starting point in ram
	glGenBuffers(NumberOfBuffers, &Buffers[0]);
	///open that buffer (type of buffer and location
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
	///binds the buffer to the variable in shader;
	glBindAttribLocation(Program, 0, "vPosition");
	///Id of AttribLocation , How many Attris it is, then type, dynmaic or const, how may bites you will skip, and that start of the buffer
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	///unbind the buffer array
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);
	glBindAttribLocation(Program, 1, "vertexColor");
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
	///this is used to close the buffer
	glBindVertexArray(0);
}
void  Renderer::BindDataToBuffers(Mesh* mesh) {
	///open Buffer
	glBindVertexArray(VAO);
	///select buffer and bind it to a type of buffer;
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
	///select type of buffer, pass how many bytes of data, point to the first element of the array, wither u are changing adress of values
	glBufferData(GL_ARRAY_BUFFER, mesh->Vertices.size() * sizeof(glm::vec3), &mesh->Vertices.at(0), GL_STATIC_DRAW);
	//glBufferSubData(GL_ARRAY_BUFFER, BufferLength, mesh->Vertices.size() * sizeof(glm::vec3), &mesh->Vertices.at(0));
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, mesh->Colors.size() * sizeof(glm::vec3), &mesh->Colors.at(0), GL_STATIC_DRAW);
	//glBufferSubData(GL_ARRAY_BUFFER, BufferLength, mesh->Colors.size() * sizeof(glm::vec3), &mesh->Colors.at(0));
	BufferLength += glm::min(mesh->Vertices.size(), mesh->Colors.size());
	///this is used to close the buffer
	glBindVertexArray(0);

	modelMatrix = glGetUniformLocation(Program, "model_matrix");
}
void Renderer::SetupShader() {
	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "triangles.vert" },
		{ GL_FRAGMENT_SHADER, "triangles.frag" },
		{ GL_NONE, NULL }
	};

	Program = LoadShaders(shaders);
	glUseProgram(Program);
}
void Update() {
	roateY +=0.001;
}
void Renderer::Draw() {
	Update();
	glBindVertexArray(VAO);
	modelOrigin = glm::translate(glm::mat4(1.0), glm::vec3(0, 0,0));
	modelOrigin = glm::rotate(glm::mat4(1.0), roateY, glm::vec3(0, roateY, 0));
	glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, &modelOrigin[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, BufferLength);
	glBindVertexArray(0);
}
Renderer::~Renderer()
{
	glBindVertexArray(VAO);
	glDeleteBuffers(NumberOfBuffers, &Buffers[0]);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO);
}
