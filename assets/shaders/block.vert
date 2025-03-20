#version 330 core
layout(location = 0) in vec4 positions;
layout(location = 1) in vec2 textureCoord;
layout(location = 2) in vec3 normals;

uniform mat4 model;
uniform mat4 view;
uniform mat4 perspective;

out vec2 v_TextCoord;
out vec3 v_Normals;
out vec3 currPos;

void main() {
    // Create a constant array of data and fill it with data.
    // Use the vertexID 
    currPos = vec3(model * positions);
    gl_Position = perspective * view * vec4(currPos, 1.0f);
    v_TextCoord = textureCoord;
    v_Normals = vec3(model * vec4(normals, 0));
}
