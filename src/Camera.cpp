#include "Camera.h"
#include <iostream>

Camera::Camera() {
    cameraX = -87.373f;
    cameraY = -13.0033f;
    cameraZ = -2.49943f;
    cameraVel = 60.0f;
    
    nearDistance = 0.01f;
    farDistance = 1000.0f;
    
    fieldOfView = 60.0f;
    sensitivityMultiplier = 0.05f;
}

Camera::~Camera() {

}

void Camera::Reset() {
    cameraProjection = glm::mat4(1.0f);
    cameraView = glm::mat4(1.0f);
}

// CAMERA
void Camera::TranslateAxis(int axis, int movement, f32 delta_time) {
    /*
        Apenas uma constante que segura um numero que é lido pela função,
        vai indicar qual eixo aplicar, e outra constante que indica movimento
        multiplicando por um valor positivo ou negativo. veja constantes em Core.h
    */

    if (axis == ENGINE::AXIS::X_AXIS) {
        cameraX = cameraX + ((cameraVel * delta_time)*movement);
        //camera recebe velocidade por tempo, multiplicado pelo movimento
        Translate(cameraX, cameraY, cameraZ); // 1 mantem no mesmo valor
    }
    
    if (axis == ENGINE::AXIS::Y_AXIS) {
        cameraY = cameraY + ((cameraVel * delta_time)*movement);
        Translate(cameraX, cameraY, cameraZ);
    }
    
    if (axis == ENGINE::AXIS::Z_AXIS) {
        cameraZ = cameraZ + ((cameraVel * delta_time)*movement);
        Translate(cameraX, cameraY, cameraZ);
    }

    //Camera.zView = Camera.zView + ((Camera.ViewVel) * Delta);        
}

void Camera::Translate(f32 x_inc, f32 y_inc, f32 z_inc) {
    cameraView = glm::translate(cameraView, glm::vec3(x_inc, y_inc, z_inc));
}

void Camera::Rotate(f32 degrees, bool x_axis, bool y_axis, bool z_axis) {
    // true for which axis will become fixed
    cameraView = glm::rotate(cameraView, glm::radians(degrees*sensitivityMultiplier), glm::vec3(x_axis, y_axis, z_axis));
}

void Camera::RotateVision(f32 degrees_x, f32 degrees_y) {
    // Ordem invertida: zyx
    cameraView = glm::rotate(cameraView, glm::radians(degrees_y*sensitivityMultiplier), glm::vec3(1.0f, 0.0f, 0.0f));
    cameraView = glm::rotate(cameraView, glm::radians(degrees_x*sensitivityMultiplier), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::Zoom(f32 scalar) {
    cameraView = glm::scale(cameraView, glm::vec3(scalar, scalar, scalar));
}



// PROJECTION
void Camera::SetProjection(int projection, f32 width, f32 height) {
    f32 aspect_ratio = width/height;
    // aspect ratio é a proporção da tela, evita achatar formas.

    if (projection == ENGINE::CAMERA::PERSPECTIVE) {
        cameraProjection = glm::perspective(glm::radians(fieldOfView), width/height, nearDistance, farDistance);
    } else if (projection == ENGINE::CAMERA::ORTHOGRAPHIC) {
        cameraProjection = glm::ortho(-aspect_ratio, aspect_ratio, -1.0f, 1.0f, nearDistance, farDistance);
        /*
            learnopengl.com: 
                The first two parameters specify the left 
                and right coordinate of the frustum and 
                the third and fourth parameter specify 
                the bottom and top part of the frustum. 

                colocar valores normalizados dá o mesmo efeito 
                que em perspective, por isso é plausivel
                colocar em aspect ratio para proporção correta.
        */
    }
}

void Camera::SetRenderDistance(f32 nearDistance_, f32 farDistance_) {
    if ((farDistance_ - nearDistance_) < 20) {
        infoLog = "WARNING::SetRenderDistance::TOO_SMALL_VALUE\n";
    }
    nearDistance = nearDistance_;
    farDistance = farDistance_;
}

glm::mat4 Camera::GetProjectionMat4() {
    return cameraProjection;
}

// GETTERS
std::string Camera::GetInfoLog() { return infoLog; }
glm::mat4 Camera::GetCameraMat4() { return cameraView; }

f32 Camera::GetX() { return cameraX; };
f32 Camera::GetY() { return cameraY; };
f32 Camera::GetZ() { return cameraZ; };

// SETTERS
void Camera::SetFieldOfView(f32 degrees) {
    if (degrees < 40) {
        infoLog = "WARNING::SetfieldOfView::TOO_SMALL_VALUE\n";
    }
    fieldOfView = degrees;
}

void Camera::SetSensitivity(f32 decimal) {
    sensitivityMultiplier = decimal;
}

void Camera::SetCameraVelocity(f32 vel) {
    cameraVel = vel;
}
