// classic Phong vertex shader
#version 450

layout(location = 0) in vec4 local_position;
layout(location = 1) in vec4 normal;
//layout(location = 1) in vec2 texture_coordinates;

uniform mat4 projection_view_matrix;
uniform mat4 model_matrix;

out vec4 vPosition;
out vec3 vNormal;

// we need this matrix to transform the normal
uniform mat3 NormalMatrix;

void main()
{
    vPosition = model_matrix * local_position;
    vNormal = NormalMatrix * normal.xyz;
    gl_Position = (projection_view_matrix * model_matrix) * local_position;
}