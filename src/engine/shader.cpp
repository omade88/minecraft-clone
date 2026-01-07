#include "shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>

Shader::Shader() : shaderID(0) {
}

Shader::~Shader() {
    if (shaderID != 0) {
        glDeleteProgram(shaderID);
    }
}

std::string Shader::readFile(const std::string& filePath) {
    std::string content;
    std::ifstream file(filePath);
    
    if (file) {
        std::stringstream stream;
        stream << file.rdbuf();
        content = stream.str();
        file.close();
    } else {
        std::cerr << "ERROR::SHADER::FILE_NOT_FOUND: " << filePath << std::endl;
    }
    
    return content;
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source) {
    unsigned int shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    
    // Check for compilation errors
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    return shader;
}

bool Shader::load(const std::string& vertexPath, const std::string& fragmentPath) {
    // Read shader source files
    std::string vertexCode = readFile(vertexPath);
    std::string fragmentCode = readFile(fragmentPath);
    
    if (vertexCode.empty() || fragmentCode.empty()) {
        return false;
    }
    
    // Compile shaders
    unsigned int vertex = compileShader(GL_VERTEX_SHADER, vertexCode);
    unsigned int fragment = compileShader(GL_FRAGMENT_SHADER, fragmentCode);
    
    // Create shader program
    shaderID = glCreateProgram();
    glAttachShader(shaderID, vertex);
    glAttachShader(shaderID, fragment);
    glLinkProgram(shaderID);
    
    // Check for linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderID, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    
    // Delete shaders as they're linked into our program now
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    
    return success;
}

void Shader::use() {
    glUseProgram(shaderID);
}