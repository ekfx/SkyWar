#include "Shader.h"

Shader::Shader() 
{
}

Shader::~Shader() 
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Config

// Make a Basic shaders from default directories
void Shader::CreateBasicShaders(const std::string& path_vertex, const std::string& path_fragment) {
    ProcessVertexShader(path_vertex);
    CompileVertexShader(GetVertexShader().c_str());

    ProcessFragmentShader(path_fragment);
    CompileFragmentShader(GetFragmentShader().c_str());

    AttachShaderProgram();
    LinkShaderProgram();
    ReleaseShaders();
}

// Proccess vertex shader source code
void Shader::ProcessVertexShader(std::string path) 
{
    vertexShader.str("");
    vertexShader.clear();

    std::ifstream file;

    file.open(path);
        if (file.is_open()) {
            vertexShader << file.rdbuf();
            std::cout << "VERTEX_SHADER::OPENED_SUCCESSFULLY" << std::endl;

        } else {
            std::cout << "VERTEX_SHADER::COULD_NOT_OPEN_ARCHIVE\nSHADER_MUST_BE::project_name/shader/shader.vert";
        }
    file.close(); 
}

// Compiles vertex shader
void Shader::CompileVertexShader(const char* vertexShaderSourceCode) {
    // vertex Shader
    vShaderID = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vShaderID, 1, &vertexShaderSourceCode, NULL);
    glCompileShader(vShaderID);

    glGetShaderiv(vShaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vShaderID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    } else {
        std::cout << "VERTEX_SHADER::COMPILED_SUCCESSFULLY" << std::endl;
    }
}

// Proccess fragment shader source code
void Shader::ProcessFragmentShader(std::string path) 
{
    fragmentShader.str("");
    fragmentShader.clear();

    std::ifstream file;

    file.open(path);
        if (file.is_open()) {
            fragmentShader  << file.rdbuf();
            std::cout << "FRAGMENT_SHADER::OPENED_SUCCESSFULLY" << std::endl;

        } else {
            std::cout << "FRAGMENT_SHADER::COULD_NOT_OPEN_ARCHIVE\nSHADER_MUST_BE::project_name/shader/shader.frag";
        }
    file.close(); 
}

// Compiles fragment shader
void Shader::CompileFragmentShader(const char* fragmentShaderSourceCode) {
    // Fragment shader 
    // relacionado a saida de cores do vertex
    
    fShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShaderID, 1, &fragmentShaderSourceCode, NULL);
    glCompileShader(fShaderID);

    glGetShaderiv(fShaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fShaderID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    } else {
        std::cout << "FRAGMENT_SHADER::COMPILED_SUCCESSFULLY" << std::endl;
    }
}

// Attaches created shaders to the shader program
void Shader::AttachShaderProgram() {
    // shader programs
    ShaderProgID = glCreateProgram();
    glAttachShader(ShaderProgID, vShaderID);
    glAttachShader(ShaderProgID, fShaderID);
}

// Links shaders
void Shader::LinkShaderProgram() {
    // shader programs
    glLinkProgram(ShaderProgID);

    glGetProgramiv(ShaderProgID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ShaderProgID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    } else {
        std::cout << "SHADER_PROGRAM::LINKED_SUCCESSFULLY" << std::endl;
    }
}

// Deletes shaders
void Shader::ReleaseShaders() 
{
    glDeleteShader(vShaderID);   // os objetos do shader não são mais necessários, 
    vShaderID = 0;               // DeleteShader ignora IDs com valor zero, evita erro de memoria

    glDeleteShader(fShaderID); // ja foram vinculados e compilados   
    fShaderID = 0;
}

void Shader::ReleaseShaderProgram() {
    if (ShaderProgID != 0)
        glDeleteProgram(GetShaderProgramID());
}

// Use shader program
void Shader::Use(i32 unbind) {
    (unbind == 0) ? glUseProgram(unbind) : glUseProgram(ShaderProgID);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Getters

std::string Shader::GetVertexShader() {
    return vertexShader.str();
}

u32 Shader::GetVertexShaderID() {
    return vShaderID;   
}

std::string Shader::GetFragmentShader() {
    return fragmentShader.str();
}

u32 Shader::GetFragmentShaderID() {
    return fShaderID;   
}

std::string Shader::GetShaderProgram() {
    return shaderProgram.str();
}

u32 Shader::GetShaderProgramID() {
    return ShaderProgID;   
}

std::string Shader::GetError() {
    return error.str();
}

i32 Shader::GetSuccessStatus() {
    return success;
}

char* Shader::GetInfoLog() {
    return infoLog; // retorna ponteiro para array
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Setters
void Shader::SetEssentialUniforms(glm::mat4 view, glm::mat4 projection, glm::mat4 model) {
    Use();
    SetMat4("projection", projection);
    SetMat4("view", view);
    SetMat4("model", model);
}

void Shader::SetFloat(const char* name_var, float value) {
    auto it = UniformArray.find(name_var);  // Iterador, especie de ponteiro
                                            // Find pelo nome do uniform
    
    if (it != UniformArray.end()) {
        glUniform1f(it->second, value);
        // id->second é o GLint
    } else {  
        auto it_ = UniformArray.insert({name_var, glGetUniformLocation(ShaderProgID, name_var)});
        glUniform1f(it_.first->second, value);
        // insert retorna um pair<pair<first, second>, status_operac>
    }
}
void Shader::SetInt(const char* name_var, int value) {
    auto it = UniformArray.find(name_var);

    if (it != UniformArray.end()) {
        glUniform1i(it->second, value);
    } else {  
        auto it_ = UniformArray.insert({name_var, glGetUniformLocation(ShaderProgID, name_var)});
        glUniform1i(it_.first->second, value);
    }
}
void Shader::SetBool(const char*  name_var, bool value) {
    auto it = UniformArray.find(name_var);

    if (it != UniformArray.end()) {
        glUniform1i(it->second, (int)value);
    } else {  
        auto it_ = UniformArray.insert({name_var, glGetUniformLocation(ShaderProgID, name_var)});
        glUniform1i(it_.first->second, (int)value);
    }
}

void Shader::SetVec2Float(const char* name_var, float value_1, float value_2) {
    auto it = UniformArray.find(name_var);

    if (it != UniformArray.end()) {
        glUniform2f(it->second, value_1, value_2);
    } else {  
        auto it_ = UniformArray.insert({name_var, glGetUniformLocation(ShaderProgID, name_var)});
        glUniform2f(it_.first->second, value_1, value_2);
    }
}
void Shader::SetVec3Float(const char* name_var, float value_1, float value_2, float value_3) {
    auto it = UniformArray.find(name_var);

    if (it != UniformArray.end()) {
        glUniform3f(it->second, value_1, value_2, value_3);
    } else {  
        auto it_ = UniformArray.insert({name_var, glGetUniformLocation(ShaderProgID, name_var)});
        glUniform3f(it_.first->second, value_1, value_2, value_3);
    }
}
void Shader::SetVec4Float(const char* name_var, float value_1, float value_2, float value_3, float value_4) {
    auto it = UniformArray.find(name_var);

    if (it != UniformArray.end()) {
        glUniform4f(it->second, value_1, value_2, value_3, value_4);
    } else {  
        auto it_ = UniformArray.insert({name_var, glGetUniformLocation(ShaderProgID, name_var)});
        glUniform4f(it_.first->second, value_1, value_2, value_3, value_4);
    }
}
void Shader::SetVec2Int(const char* name_var, int value_1, int value_2) {
    auto it = UniformArray.find(name_var);

    if (it != UniformArray.end()) {
        glUniform2i(it->second, value_1, value_2);
    } else {  
        auto it_ = UniformArray.insert({name_var, glGetUniformLocation(ShaderProgID, name_var)});
        glUniform2i(it_.first->second, value_1, value_2);
    }
}
void Shader::SetVec3Int(const char* name_var, int value_1, int value_2, int value_3) {
    auto it = UniformArray.find(name_var);

    if (it != UniformArray.end()) {
        glUniform3i(it->second, value_1, value_2, value_3);
    } else {  
        auto it_ = UniformArray.insert({name_var, glGetUniformLocation(ShaderProgID, name_var)});
        glUniform3i(it_.first->second, value_1, value_2, value_3);
    }
}
void Shader::SetVec4Int(const char* name_var, int value_1, int value_2, int value_3, int value_4) {
    auto it = UniformArray.find(name_var);

    if (it != UniformArray.end()) {
        glUniform4i(it->second, value_1, value_2, value_3, value_4);
    } else {  
        auto it_ = UniformArray.insert({name_var, glGetUniformLocation(ShaderProgID, name_var)});
        glUniform4i(it_.first->second, value_1, value_2, value_3, value_4);
    }
}

void Shader::SetMat3(const char* name_var, glm::mat3 matrix_3) {
    auto it = UniformArray.find(name_var);

    if (it != UniformArray.end()) {
        glUniformMatrix3fv(it->second, 1, GL_FALSE, glm::value_ptr(matrix_3));
    } else {  
        auto it_ = UniformArray.insert({name_var, glGetUniformLocation(ShaderProgID, name_var)});
        glUniformMatrix3fv(it->second, 1, GL_FALSE, glm::value_ptr(matrix_3));
    }
}

void Shader::SetMat4(const char* name_var, glm::mat4 matrix_4) {
    auto it = UniformArray.find(name_var);

    if (it != UniformArray.end()) {
        glUniformMatrix4fv(it->second, 1, GL_FALSE, glm::value_ptr(matrix_4));
    } else {  
        auto it_ = UniformArray.insert({name_var, glGetUniformLocation(ShaderProgID, name_var)});
        glUniformMatrix4fv(it->second, 1, GL_FALSE, glm::value_ptr(matrix_4));
    }
}

/////////////////////////////////////////////////////////////////////////////////
// Getters
u32 Shader::GetUniformLocation(const char* name_uniform) {
    auto it = UniformArray.find(name_uniform);
    return it->second;
}


