#pragma once

#include <glad/glad.h>
#include <glm/mat4x4.hpp>

#include "../Core/Util.hpp"

#include <string>

class Shader {
public:
	Shader(const std::string& vertex_path, const std::string& fragment_path);
	Shader(const Shader&) = delete;
	~Shader();

    static Ref<Shader> Create(const std::string& vert_filepath, const std::string& frag_filepath);

	void Bind();
	void Unbind();

	void SetUniformFloat(const std::string& name, float value) const;
	void SetUniformFloat3(const std::string& name, float value[3]) const;
    void SetUniformIntArray(const std::string &name, GLsizei count, GLint* values) const;
	void SetUniformMat4(const std::string& name, const glm::mat4& value) const;
private:
	GLuint program_;
};