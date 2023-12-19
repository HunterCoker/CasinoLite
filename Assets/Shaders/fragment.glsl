#version 330 core

out vec4 FragColor;
uniform sampler2D u_Textures[32];

in vec4 v_PositionColor;
in vec2 v_TextureCoord;
in float v_TextureIndex;
in float v_TilingFactor;

void main() {
	switch (int(v_TextureIndex)) {
		case  0: FragColor = texture(u_Textures[ 0], v_TextureCoord * v_TilingFactor); break;
		case  1: FragColor = texture(u_Textures[ 1], v_TextureCoord * v_TilingFactor); break;
		case  2: FragColor = texture(u_Textures[ 2], v_TextureCoord * v_TilingFactor); break;
		case  3: FragColor = texture(u_Textures[ 3], v_TextureCoord * v_TilingFactor); break;
		case  4: FragColor = texture(u_Textures[ 4], v_TextureCoord * v_TilingFactor); break;
		case  5: FragColor = texture(u_Textures[ 5], v_TextureCoord * v_TilingFactor); break;
		case  6: FragColor = texture(u_Textures[ 6], v_TextureCoord * v_TilingFactor); break;
		case  7: FragColor = texture(u_Textures[ 7], v_TextureCoord * v_TilingFactor); break;
		case  8: FragColor = texture(u_Textures[ 8], v_TextureCoord * v_TilingFactor); break;
		case  9: FragColor = texture(u_Textures[ 9], v_TextureCoord * v_TilingFactor); break;
		case 10: FragColor = texture(u_Textures[10], v_TextureCoord * v_TilingFactor); break;
		case 11: FragColor = texture(u_Textures[11], v_TextureCoord * v_TilingFactor); break;
		case 12: FragColor = texture(u_Textures[12], v_TextureCoord * v_TilingFactor); break;
		case 13: FragColor = texture(u_Textures[13], v_TextureCoord * v_TilingFactor); break;
		case 14: FragColor = texture(u_Textures[14], v_TextureCoord * v_TilingFactor); break;
		case 15: FragColor = texture(u_Textures[15], v_TextureCoord * v_TilingFactor); break;
	}

	if (FragColor.a == 0.0)
		discard;

	FragColor *= v_PositionColor;
}