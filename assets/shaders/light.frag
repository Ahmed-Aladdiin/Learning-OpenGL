#version 330 core
// The output of this pixel calculation.
out vec4 frag_color;
uniform vec4 u_lightColor;
        
void main() {
    frag_color = u_lightColor;
}