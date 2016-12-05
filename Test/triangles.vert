#version 430 core
/*layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vertexColor;

uniform mat4 model_matrix;
uniform mat4 proj_matrix;
uniform mat4 camera_matrix;

out vec4 myColor;

void main()
{
	myColor = vertexColor;
	gl_Position = proj_matrix * camera_matrix * model_matrix * vPosition;
}
*/
layout (location = 0) in vec3 position;

void main()
{
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
}