class Shader {
public:
    Shader();
    ~Shader();
    
    bool load(const std::string& vertexPath, const std::string& fragmentPath);
    void use();
    
private:
    unsigned int shaderID;
    
    std::string readFile(const std::string& filePath);
    unsigned int compileShader(unsigned int type, const std::string& source);
};