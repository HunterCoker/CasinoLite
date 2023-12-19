#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec2 a_TextureCoord;
layout (location = 3) in float a_TextureIndex;
layout (location = 4) in float a_TilingFactor;

out vec4 v_PositionColor;

out vec2 v_TextureCoord;
out float v_TextureIndex;
out float v_TilingFactor;

uniform float u_Aspect;

void main() {
    v_PositionColor = a_Color;
    v_TextureCoord = a_TextureCoord;
    v_TextureIndex = a_TextureIndex;
    v_TilingFactor = a_TilingFactor;

    gl_Position = vec4(a_Position.x * u_Aspect, a_Position.yz, 1.0);
}