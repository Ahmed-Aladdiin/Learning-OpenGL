#version 330 core
// The output of this pixel calculation.
out vec4 frag_color;
in vec2 v_TextCoord;

// uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main() {
    vec4 textColor = texture(u_Texture, v_TextCoord);
    frag_color = textColor;
}
