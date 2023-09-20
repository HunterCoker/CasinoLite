#version 330 core

out vec4 FragColor;

in vec4 v_PositionColor;

void main() {
	FragColor = v_PositionColor;
}