#include "Mesh.h"

/////////////////////////////////////////////////////////////////////////////////
// Constructor and Destructor

Mesh::Mesh() {
    NumberAttributes = 0;
};

Mesh::~Mesh() {

};

/////////////////////////////////////////////////////////////////////////////////
// Abstract

void Mesh::CreateMesh(vertex YourVertex[], size_t vertex_size, u32 ebo_array[], size_t size_ebo_array, bool position, bool color, bool normal, bool uv) 
{
    unsigned int counter = 0;

    StartVAORecording();
        CreateVBO(YourVertex, vertex_size);
        if (position == true) {
            SetAttrib(counter, 3);
            counter = counter + 3;
        }

        if (color == true) {
            SetAttrib(counter, 3);
            counter = counter + 3;
        }
        
        if (normal == true) {
            SetAttrib(counter, 3);
            counter = counter + 3;
        }

        if (uv == true) {
            SetAttrib(counter, 2);
            counter = counter + 2;
        }
        CreateEBO(ebo_array, size_ebo_array);
    DeactiveBuffers();
}

/////////////////////////////////////////////////////////////////////////////////
// Start

void Mesh::StartVAORecording() {
    glGenVertexArrays(1, &VAO);     // VAO -> genVertexArrays
    glBindVertexArray(VAO);         // VAO -> bindVertexArray
}

void Mesh::CreateVBO(vertex YourVertex[], size_t vertex_size) {
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertex_size, YourVertex, GL_STATIC_DRAW);
}

void Mesh::CreateEBO(u32 ebo_array[], size_t size_ebo_array) {
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_ebo_array, ebo_array, GL_STATIC_DRAW);
}

/////////////////////////////////////////////////////////////////////////////////
// Config

void Mesh::SetAttrib(i32 offset_float_multiplier, i32 component_number) {
    glVertexAttribPointer(NumberAttributes, component_number, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*) (offset_float_multiplier*sizeof(float)));
    glEnableVertexAttribArray(NumberAttributes);
    NumberAttributes = NumberAttributes + 1;
}

/////////////////////////////////////////////////////////////////////////////////
// Deletes

void Mesh::DeactiveBuffers() {
    glBindVertexArray(0);                       // Desativa VAO sempre primeiro
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::ReleaseBuffers() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

/////////////////////////////////////////////////////////////////////////////////
// Getters

GLuint Mesh::GetVAO() {
    return VAO;
}

i32 Mesh::GetNumberOfAttributes() {
    return NumberAttributes;
}