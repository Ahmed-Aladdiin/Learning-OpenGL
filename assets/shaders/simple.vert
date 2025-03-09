#version 330 core
layout(location = 0) in vec4 positions;
layout(location = 1) in vec2 textureCoord;

out vec2 v_TextCoord;
void main() {
    // Create a constant array of data and fill it with data.
    // Use the vertexID 
    gl_Position = positions;
    v_TextCoord = textureCoord;
}
