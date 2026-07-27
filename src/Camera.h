#ifndef CAMERA_H
#define CAMERA_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>
#include <glm/common.hpp>
#include <string>

#include "Types.h"
#include "Core.h"

class Camera {
private:
    // Attributes
    f32 cameraX;
    f32 cameraY;
    f32 cameraZ;
    f32 cameraVel;
    
    // Render Distance
    f32 nearDistance;
    f32 farDistance;

    // Vision
    f32 fieldOfView;
    f32 sensitivityMultiplier ;

    // Matrices
    glm::mat4 cameraView;
    glm::mat4 cameraProjection;

    // Logs
    std::string infoLog;

public:
    Camera();
    ~Camera();

    // Config
    void Reset();

    // Camera
    void TranslateAxis(int axis, int movement, f32 delta_time); 
    void Translate(f32 x_inc = 1, f32 y_inc = 1, f32 z_inc = 1);
    void Rotate(f32 degrees, bool x_axis, bool y_axis, bool z_axis);
    void RotateVision(f32 degrees_x, f32 degrees_y);
    void Zoom(f32 scalar);
    
    // Projection
    void SetProjection(int projection, f32 width, f32 height);
    
    // Getters
    glm::mat4 GetCameraMat4();
    glm::mat4 GetProjectionMat4();
    std::string GetInfoLog();
    f32 GetX();
    f32 GetY();
    f32 GetZ();
    
    // Setters
    void SetFieldOfView(f32 degrees);
    void SetRenderDistance(f32 NearDistance_, f32 FarDistance_);
    void SetSensitivity(f32 decimal);
    void SetCameraVelocity(f32 vel);

};

#endif  //CAMERA_H