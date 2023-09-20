#include "Texture.hpp"

#include <stb_image.h>

Texture::Texture(const std::string& filepath) {
	glGenTextures(1, &handle_);
	glBindTexture(GL_TEXTURE_2D, handle_);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 4);
	glBindTexture(GL_TEXTURE_2D, handle_);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
}

Texture::~Texture() {
	glDeleteTextures(1, &handle_);
}

std::shared_ptr<Texture> Texture::Create(const std::string& filepath) {
    return std::make_shared<Texture>(filepath);
}

void Texture::Bind(uint32_t slot) const {
	glBindTexture(GL_TEXTURE_2D, handle_);
}

bool Texture::operator==(const Texture &other) const {
    return handle_ == other.handle_;
}
