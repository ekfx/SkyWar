#ifndef MESH_H
#define MESH_H

#include <GLAD/glad.h>    
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <map>
#include <string>
#include <vector>
#include <random>
#include "Types.h"

class Mesh {
private:
    GLuint VAO, VBO, EBO;
    i32 NumberAttributes;
    std::string ErrorMessages;

public:
    struct vertex {
        f32 x,y,z;
        f32 r,g,b;
        f32 u,v;
    };

    Mesh();
    ~Mesh();

    /////////////////////////////////////////////////////////////////////////////////
    // Buffers

    // Abstract
    // You can set your own Attributes with SetAttrib and do the Manual Initialization
    void CreateMesh(vertex YourVertex[], size_t struct_size, 
                    u32 ebo_array[], size_t size_ebo_array, 
                    bool position, bool color, bool normal, bool uv);

    // Start
    void StartVAORecording();
    void CreateVBO(vertex YourVertex[], size_t struct_size);
    void CreateEBO(u32 ebo_array[], size_t size_ebo_array);

    // Config
    void SetAttrib(i32 offset_float_multiplier, i32 component_number);

    // Deletes
    void DeactiveBuffers();
    void ReleaseBuffers();

    /////////////////////////////////////////////////////////////////////////////////
    // Getters
    GLuint GetVAO();
    i32 GetNumberOfAttributes();
};

#endif // MESH_H
