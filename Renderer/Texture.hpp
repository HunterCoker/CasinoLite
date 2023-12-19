#pragma once

#include <glad/glad.h>

#include "../Core/Util.hpp"

#include <string>

class Texture {
public:
	explicit Texture(const std::string& filepath);
	Texture(const Texture&) = delete;
	~Texture();

    static Ref<Texture> Create(const std::string& filepath);

	void Bind(uint32_t slot = 0) const;

    bool operator==(const Texture& other) const;
private:
	GLuint handle_;
};