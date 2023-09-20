#pragma once

#include <glad/glad.h>

#include <glm/mat4x4.hpp>

#include <string>

class Shader {
public:
	Shader(const std::string& vertex_path, const std::string& fragment_path);
	Shader(const Shader&) = delete;
	~Shader();

	void Bind();
	void Unbind();

	void SetUniform1f(const std::string& name, float value) const;
	void SetUniform3f(const std::string& name, float value[3]) const;
	void SetUniformm4fv(const std::string& name, const glm::mat4& value) const;
private:
	GLuint program_;
};