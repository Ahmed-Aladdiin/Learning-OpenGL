#version 330 core
layout(location = 0) in vec4 positions;
layout(location = 1) in vec2 textureCoord;
layout(location = 2) in vec3 normals;

uniform mat4 model;
uniform mat4 view;
uniform mat4 perspective;


void main() {
    // Create a constant array of data and fill it with data.
    // Use the vertexID 
    gl_Position = perspective * view * model * positions;
}
