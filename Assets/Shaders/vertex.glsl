#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec2 a_TextureCoord;
layout (location = 3) in float a_TextureIndex;
layout (location = 3) in float a_TilingFactor;

out vec4 v_PositionColor;

void main() {
    gl_Position = vec4(a_Position, 1.0);
    v_PositionColor = a_Color;
}