#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>
#include <glm/common.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <random>

#include "Types.h"
#include "Core.h"

class ObjectManager {
public:
    struct Object {
        glm::vec3 position = glm::vec3(1.0f);
        glm::vec3 velocity = glm::vec3(1.0f);
        glm::vec4 color = glm::vec4(1.0f);
        f32 weight = 0;
    };

public:
    std::vector<Object> ObjectArray;

    ObjectManager();
    ~ObjectManager();

    // Utility
    void SetObjectVelocity(u32 index, glm::vec3 velocity);
    void MoveObject(i32 axis, i32 movement, f32 delta_time, u32 index);
    void JumpObject(f32 delta_time, u32 index);
    
    // Generators
    u32 CreateOneObject(glm::vec3 position = glm::vec3(10.0f,  10.0f,  10.0f), 
                        f32 weight = 10.0f, 
                        glm::vec3 velocity = glm::vec3(50.0f,  0.0f,  50.0f), 
                        glm::vec4 color = glm::vec4(1.0f,  0.8f,  0.6f, 1.0f));

    void CreateNewObjects(i32 quantity, 
                          f32 interval_xa, f32 interval_xb, 
                          f32 interval_ya, f32 interval_yb, 
                          f32 interval_za, f32 interval_zb, 
                          f32 weight, 
                          glm::vec4 color);

    void CreateLineObjects(i32 quantity);

    void CreatePlan(i32 start_x, i32 end_x, 
                    i32 start_y, i32 end_y, 
                    i32 start_z, i32 end_z, 
                    glm::vec4 color);
};

#endif // OBJECT_H