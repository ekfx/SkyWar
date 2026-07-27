#include "Object.h"

ObjectManager::ObjectManager() 
{
}

ObjectManager::~ObjectManager() 
{
}

u32 ObjectManager::CreateOneObject(glm::vec3 position, f32 weight, glm::vec3 velocity, glm::vec4 color) {
    Object temp;
    temp.position = position;
    temp.weight = weight;
    temp.velocity = velocity;
    temp.color = color;
    ObjectArray.push_back(temp);
    return ObjectArray.size()-1;
}

void ObjectManager::SetObjectVelocity(u32 index, glm::vec3 velocity) {
    ObjectArray.at(index).velocity = velocity;
}

void ObjectManager::MoveObject(i32 axis, i32 movement, f32 delta_time, u32 index) {
    if (axis == ENGINE::AXIS::X_AXIS) {
        ObjectArray.at(index).position.x += (ObjectArray.at(index).velocity.x*delta_time)*movement;
    }

    if (axis == ENGINE::AXIS::Y_AXIS) {
        ObjectArray.at(index).position.y += (ObjectArray.at(index).velocity.y*delta_time)*movement;
    }

    if (axis == ENGINE::AXIS::Z_AXIS) {
        ObjectArray.at(index).position.z += (ObjectArray.at(index).velocity.z*delta_time)*movement;
    }
}

void ObjectManager::JumpObject(f32 delta_time, u32 index) {
    ObjectArray.at(index).velocity.y += 75.0f*delta_time;
}

void ObjectManager::CreateNewObjects(i32 quantity, f32 interval_xa, f32 interval_xb, f32 interval_ya, f32 interval_yb, f32 interval_za, f32 interval_zb, f32 weight, glm::vec4 color) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<f32> Nx(interval_xa, interval_xb);
    std::uniform_real_distribution<f32> Ny(interval_ya, interval_yb);
    std::uniform_real_distribution<f32> Nz(interval_za, interval_zb);
    f32 x = Nx(mt);
    f32 y = Ny(mt);
    f32 z = Nz(mt);
    Object temp;

    for (int i = 1; i <= quantity; i++) {
        temp.position = glm::vec3(x,y,z);
        temp.weight = weight;
        temp.color = color;
        ObjectArray.push_back(temp);
        x = Nx(mt);
        y = Ny(mt);
        z = Nz(mt);
    }
}

void ObjectManager::CreateLineObjects(i32 quantity) {
    Object temp;
    temp.position = glm::vec3(0.0f);

    for (int i = 0; i < quantity; i++) {
        temp.position = glm::vec3((f32)i/10, 0.0f, 0.0f);
        ObjectArray.push_back(temp);
    }
}

void ObjectManager::CreatePlan(i32 start_x, i32 end_x, i32 start_y, i32 end_y, i32 start_z, i32 end_z, glm::vec4 color) {
    Object temp;
    temp.position = glm::vec3(1.0f, 0.0f, 1.0f);

    for (int i = start_x; i <= end_x; i++) {
        for (int j = start_y; j <= end_y; j++) {
            for (int k = start_z; k <= end_z; k++) {
                temp.position = glm::vec3((f32)i, (f32)j, (f32)k);
                if (i % 2 == 0) {
                    temp.color = glm::vec4(0.0118f, 0.3686f, 0.0f, 1.0f);
                } 
                if (j % 2 == 0) {
                    temp.color = glm::vec4(0.0118f, 0.9f, 0.0f, 1.0f);
                }
                
                ObjectArray.push_back(temp);
            }
        }
        /*
            coluna i = 0: j0, j1, j2, j3, ...
            coluna i = 1: j0, j1, j2, j3, ...
            não sao necessarios dois push_back()
        */
    }
}
