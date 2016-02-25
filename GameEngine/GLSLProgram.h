#pragma once
#include <gl\glew.h>
#include <string>

namespace GameEngine {

	// This class handles the compiletion, linking nad usage of a GLSL shader progarm.
	// Reference: https://www.opengl.org/wiki/Shader_Compilation
	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();

		void CompileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
		void AddAttribute(const std::string& attributeName);
		void LinkShaders();

		GLint GetUniformLocation(const std::string& UniformName);

		void UseShader();
		void UnuseShader();
	private:
		void Compileshader(GLuint& ID, const std::string& ShaderFilePath);

		int _numberOfAttribute;

		GLuint _programID;
		GLuint _verterxShaderID;
		GLuint _fragmentShaderID;
	};
}

