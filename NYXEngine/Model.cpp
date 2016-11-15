#include "pch.h"
#include "Model.h"



#include "vgl.h"
int VertLength;
GLuint location;
Model::Model()
{
}
void Model::MakeShape(PrimitiveShapes Type) {
	switch (Type) {
	case PrimitiveShapes::Cube:
		VertLength = 24;
		//front
		Verts[0] = glm::vec3(-1, 1, 0);
		Verts[1] = glm::vec3(-1, -1, 0);
		Verts[2] = glm::vec3(1, -1, 0);
		Verts[3] = glm::vec3(1, 1, 0);

		ColorData[0] = glm::vec3(1, 0, 0);
		ColorData[1] = glm::vec3(1, 0, 0);
		ColorData[2] = glm::vec3(1, 0, 0);
		ColorData[3] = glm::vec3(1, 0, 0);
		//right
		Verts[4] =glm::vec3(1, 1, 0);
		Verts[5] =glm::vec3(1, -1, 0);
		Verts[6] =glm::vec3(1, -1, -1);
		Verts[7] =glm::vec3(1, 1, -1);


		ColorData[4] = glm::vec3(0, 1, 0);
		ColorData[5] = glm::vec3(0, 1, 0);
		ColorData[6] = glm::vec3(0, 1, 0);
		ColorData[7] = glm::vec3(0, 1, 0);
		//back
		Verts[8] =glm::vec3(-1, 1, -1);
		Verts[9] =glm::vec3(-1, -1, -1);
		Verts[10] =glm::vec3(1, -1, -1);
		Verts[11] =glm::vec3(1, 1, -1);

		ColorData[8] = glm::vec3(0, 0, 1);
		ColorData[9] = glm::vec3(0, 0, 1);
		ColorData[10] = glm::vec3(0, 0, 1);
		ColorData[11] = glm::vec3(0, 0, 1);
		//left
		Verts[12] =glm::vec3(-1, 1, 0);
		Verts[13] =glm::vec3(-1, -1, 0);
		Verts[14] =glm::vec3(-1, -1, -1);
		Verts[15] =glm::vec3(-1, 1, -1);

		ColorData[12] = glm::vec3(1, 1, 0);
		ColorData[13] = glm::vec3(1, 1, 0);
		ColorData[14] = glm::vec3(1, 1, 0);
		ColorData[15] = glm::vec3(1, 1, 0);
		//top
		Verts[16] =glm::vec3(-1, 1, 0);
		Verts[17] =glm::vec3(1, 1, 0);
		Verts[18] =glm::vec3(1, 1, -1);
		Verts[19] =glm::vec3(-1, 1, -1);

		ColorData[16] = glm::vec3(1, 0, 1);
		ColorData[17] = glm::vec3(1, 0, 1);
		ColorData[18] = glm::vec3(1, 0, 1);
		ColorData[19] = glm::vec3(1, 0, 1);
		//bottom
		Verts[20] =glm::vec3(-1, -1, 0);
		Verts[21] =glm::vec3(1, -1, 0);
		Verts[22] =glm::vec3(1, -1, -1);
		Verts[23] =glm::vec3(-1, -1, -1);

		ColorData[20] = glm::vec3(1, 1, 1);
		ColorData[21] = glm::vec3(1, 1, 1);
		ColorData[22] = glm::vec3(1, 1, 1);
		ColorData[23] = glm::vec3(1, 1, 1);
		break;

	case PrimitiveShapes::Primide:
		VertLength = 9;
		Verts[0] =glm::vec3(0, 1, 0);
		Verts[1] =glm::vec3(-1, -1, 1);
		Verts[2] =glm::vec3(1, -1, 1);

		ColorData[0] = glm::vec3(0, 1, 0);
		ColorData[1] = glm::vec3(0, 1, 0);
		ColorData[2] = glm::vec3(0, 1, 0);

		Verts[3] =glm::vec3(0, 1, 0);
		Verts[4] =glm::vec3(-1, -1, 1);
		Verts[5] =glm::vec3(0, -1, -1);
		ColorData[3] = glm::vec3(1, 0, 0);
		ColorData[4] = glm::vec3(1, 0, 0);
		ColorData[5] = glm::vec3(1, 0, 0);

		Verts[6] =glm::vec3(0, 1, 0);
		Verts[7] =glm::vec3(0, -1, -1);
		Verts[8] =glm::vec3(1, -1, 1);
		ColorData[6] = glm::vec3(0, 0, 1);
		ColorData[7] = glm::vec3(0, 0, 1);
		ColorData[8] = glm::vec3(0, 0, 1);
		break;
	}
	
}
void Model::MakeShape(glm::vec3 P_Verts[], glm::vec3 P_ColorData[]) {}

void Model::LoadBuffer(ShaderInfo shaders[]){ 
	glBufferData(GL_ARRAY_BUFFER, sizeof(Verts), Verts, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, VertLength, ColorData);
	
}
void Model::Draw(GLuint location) {
	glm::mat4 model_view = glm::translate(glm::mat4(1.0), glm::vec3(0.0, 0.0, 0.0));
	glUniformMatrix4fv(location, 1, GL_FALSE, &model_view[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}