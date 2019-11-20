#pragma once

#include <string>
#include <unordered_map>
#include "glm\glm.hpp"

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& filepath);
	~Shader();
	void Bind() const;
	void Unbind() const;

	//Set uniforms
	void setUniform4f(const std::string& name, float v0, float v1, float f2, float f3);
	void setUniform1i(const std::string& name, int value);
	void setUniformMat4f(const std::string& name, glm::mat4& matrix);

private:
	unsigned int CompileShader(unsigned int type, const std::string& source);
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	int GetUniformLocation(const std::string& name);
};