#version 330 core
// The output of this pixel calculation.
out vec4 frag_color;

in vec2 v_TextCoord;
in vec3 v_Normals;
in vec3 currPos;
// uniform vec4 u_Color;
uniform sampler2D u_Texture;
uniform vec4 u_lightColor;
uniform vec3 u_lightPos;

void main() {

    float ambient = 0.1f;

    vec3 normal = normalize(v_Normals);
    vec3 light = normalize(u_lightPos - currPos);
    float diff = max(dot(normal, light), 0.0f);
    // float diff = dot(normal, light);

    vec4 textColor = texture(u_Texture, v_TextCoord);
    vec4 frag_color_pre = textColor * u_lightColor * (diff + ambient);
    frag_color = vec4(frag_color_pre.x, frag_color_pre.y, frag_color_pre.z, 1.0f);
}
// * (diff + ambient)