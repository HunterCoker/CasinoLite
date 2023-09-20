#pragma once

#include <glad/glad.h>

#include <string>
#include <memory>

class Texture {
public:
	Texture(const std::string& filepath);
	Texture(const Texture&) = delete;
	~Texture();

    static std::shared_ptr<Texture> Create(const std::string& filepath);

	void Bind(uint32_t slot = 0) const;

    bool operator==(const Texture& other) const;
private:
	GLuint handle_;
};