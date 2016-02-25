#include "GLSLProgram.h"
#include "ErrorMessage.h"

#include <fstream>
#include <vector>

namespace GameEngine {

	GLSLProgram::GLSLProgram() :
		// These all just an initialization list.
		// Its a a better way to initialize variables, since it avoides an extra copy.
		_numberOfAttribute(0),
		_programID(0),
		_verterxShaderID(0),
		_fragmentShaderID(0)
	{
	}

	GLSLProgram::~GLSLProgram()
	{
	}

	void GLSLProgram::CompileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) {
		// Get a program object.
		_programID = glCreateProgram();

		// Create the vertex shader object, and store its ID.
		_verterxShaderID = glCreateShader(GL_VERTEX_SHADER);
		if (_verterxShaderID == 0) {
			FatalError("Vertex shader failed to be created.");
		}

		// Create the fragment shader object, and store its ID.
		_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		if (_fragmentShaderID == 0) {
			FatalError("Fragment shader failed to be created.");
		}

		// Compile each shader.
		Compileshader(_verterxShaderID, vertexShaderFilePath);
		Compileshader(_fragmentShaderID, fragmentShaderFilePath);
	}

	// Compile a signle shader file.
	void GLSLProgram::Compileshader(GLuint& ID, const std::string& ShaderFilePath) {
		// Open the file using ifstream.
		std::ifstream vertexShaderFile(ShaderFilePath);
		if (vertexShaderFile.fail()) {
			FatalError("Failed to open " + ShaderFilePath);
		}
		// File contents stores all the text contents in the file.
		std::string fileContents = "";
		// Line is used to grab each line of text in the file.
		std::string line = "";

		// Get all the lines in the file and add it into the contents.
		while (std::getline(vertexShaderFile, line)) {
			fileContents += line + "\n";
		}

		vertexShaderFile.close();

		// Get a pointer to our file contents c string.
		const char* contentsPtr = fileContents.c_str();
		// Tell opengl that we wanr to use fileContent as the contents of the shader file.
		glShaderSource(ID, 1, &contentsPtr, nullptr);

		// Compile the shaders, easy enough.
		glCompileShader(ID);

		// Check if any errors.
		GLint success = 0;
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE) {
			GLint maxLength = 0;
			glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxlength includes the NULL character.
			std::vector<char> errorLog(maxLength);
			glGetShaderInfoLog(ID, maxLength, &maxLength, &errorLog[0]);

			// Provide the info log in whatever manor you deem best.
			// Exit with failure.
			glDeleteShader(ID);

			std::printf("%s\n", &(errorLog[0]));
			FatalError("Shader " + ShaderFilePath + " failed to compile");
		}
	}

	void GLSLProgram::LinkShaders() {
		// Attach our shaders to out program.
		glAttachShader(_programID, _verterxShaderID);
		glAttachShader(_programID, _fragmentShaderID);

		// Link our program.
		// Remenber you have to detach those shaders which has been attached to the program.
		glLinkProgram(_programID);

		// Note the different functions here: glGetProgram* instead of glGetShader*
		GLint isLinked = 0;
		glGetProgramiv(_programID, GL_LINK_STATUS, &isLinked);

		if (isLinked == GL_FALSE) {
			GLint maxLength = 0;
			glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxlength includes the NULL character.
			std::vector<char> errorLog(maxLength);
			glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(_programID);
			// Don't leak the shader either.
			glDeleteShader(_verterxShaderID);
			glDeleteShader(_fragmentShaderID);

			std::printf("%s\n", &(errorLog[0]));
			FatalError("Shader failed to link.");
		}

		// Always detach shaders after a succesful link.
		glDetachShader(_programID, _verterxShaderID);
		glDetachShader(_programID, _fragmentShaderID);

		// Make sure to reless all the resouce.
		glDeleteShader(_verterxShaderID);
		glDeleteShader(_fragmentShaderID);
	}

	// Adds an attribute to our shader. 
	// Should be called between compiling and linking.
	void GLSLProgram::AddAttribute(const std::string& attributeName) {
		glBindAttribLocation(_programID, _numberOfAttribute++, attributeName.c_str());
	}

	GLint GLSLProgram::GetUniformLocation(const std::string& UniformName) {
		GLint location = glGetUniformLocation(_programID, UniformName.c_str());
		// If the uniform we looking for is not exist then it will return 0Xffffffff
		if (location == GL_INVALID_INDEX) {
			FatalError("Uniform " + UniformName + " not found in shader!");
		}
		return location;
	}


	// Enbale the shader, and all its attributes.
	void GLSLProgram::UseShader() {
		glUseProgram(_programID);
		// Enable all the attributes we added with addAttribute.
		for (int i = 0; i < _numberOfAttribute; i++)
		{
			glEnableVertexAttribArray(i);
		}
	}

	// Disbale the shader and all its attributes.
	void GLSLProgram::UnuseShader() {
		glUseProgram(0);
		for (int i = 0; i < _numberOfAttribute; i++)
		{
			glDisableVertexAttribArray(i);
		}
	}
}