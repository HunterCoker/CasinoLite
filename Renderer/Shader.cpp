#include "Shader.hpp"

#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string& vertex_path, const std::string& fragment_path) {
	std::ifstream vertex_file;
	std::stringstream vertex_stream;
	vertex_file.exceptions(std::ios::failbit | std::ios::badbit);
	try {
		vertex_file.open(vertex_path);
		vertex_stream << vertex_file.rdbuf();
        vertex_file.close();
	}
	catch(std::ifstream::failure& e) {
		std::cerr << "error: failed to read vertex Shader file\n";
	}

	std::ifstream fragment_file;
	std::stringstream fragment_stream;
	fragment_file.exceptions(std::ios::failbit | std::ios::badbit);
	try {
		fragment_file.open(fragment_path);
		fragment_stream << fragment_file.rdbuf();
        fragment_file.close();
	}
	catch(std::ifstream::failure& e) {
		std::cerr << "error: failed to read fragment Shader file\n";
	}

	std::string t_vertex = vertex_stream.str();
	const char* vertex_shader_code = t_vertex.c_str();
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_code, nullptr);
	glCompileShader(vertex_shader);

	std::string t_fragment =  fragment_stream.str();
	const char* fragment_shader_code = t_fragment.c_str();
	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_code, nullptr);
	glCompileShader(fragment_shader);

	int  success;
	char infoLog[512];
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if(!success) {
		glGetShaderInfoLog(vertex_shader, 512, nullptr, infoLog);
		std::cerr << "error: vertex Shader failed to compile!\n" << infoLog << '\n';
	}

	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if(!success) {
		glGetShaderInfoLog(fragment_shader, 512, nullptr, infoLog);
		std::cerr << "error: fragment Shader failed to compile!" << infoLog << '\n';
	}

	program_ = glCreateProgram();
	glAttachShader(program_, vertex_shader);
	glAttachShader(program_, fragment_shader);
	glLinkProgram(program_);

	glGetShaderiv(program_, GL_LINK_STATUS, &success);
	if(!success) {
		glGetShaderInfoLog(program_, 512, nullptr, infoLog);
		std::cerr << "error: fragment Shader failed to compile!" << infoLog << '\n';
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

Shader::~Shader() {
	glDeleteProgram(program_);
}

Ref<Shader> Shader::Create(const std::string& vert_filepath, const std::string& frag_filepath) {
    return std::make_shared<Shader>(vert_filepath, frag_filepath);
}

void Shader::Bind() {
	glUseProgram(program_);
}

void Shader::Unbind() {
    glUseProgram(0);
}

void Shader::SetUniformFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(program_, name.c_str()), value);
}

void Shader::SetUniformFloat3(const std::string& name, float value[3]) const {
	glUniform3f(glGetUniformLocation(program_, name.c_str()), value[0], value[1], value[2]);
}

void Shader::SetUniformIntArray(const std::string &name, GLsizei count, GLint* values) const {
    glUniform1iv(glGetUniformLocation(program_, name.c_str()), count, values);
}

void Shader::SetUniformMat4(const std::string& name, const glm::mat4& value) const {
	glUniformMatrix4fv(glGetUniformLocation(program_, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
