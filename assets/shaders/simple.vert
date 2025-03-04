#version 330 core
layout(location = 0) in vec4 positions;
void main() {
    // Create a constant array of data and fill it with data.
    // Use the vertexID 
    gl_Position = positions;
}
