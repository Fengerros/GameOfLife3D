#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN,
    SPRINT
};


const float YAW = -90.0f; 
const float PITCH = 0.0f;
const float SPEED = 2.f;
const float SPRINT_SPEED = 12.f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 1.0f;

class Camera
{
    public:
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;
        glm::vec3 right;
        
        glm::vec3 worldUp;
        glm::vec3 worldDown;
        glm::vec3 worldRight;
        glm::vec3 worldLeft;
        glm::vec3 worldFront;
        glm::vec3 worldBack;

        float yaw;
        float pitch;

        float movementSpeed;
        float mouseSensitivity;
        float zoom;

        Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
               glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
               glm::vec3 down = glm::vec3(0.0f, -1.0f, 0.0f),
               glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f),
               glm::vec3 back = glm::vec3(0.0f, 0.0f, 1.0f),
               glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f),
               glm::vec3 left = glm::vec3(-1.0f, 0.0f, 0.0f),
               float yaw = YAW,
               float pitch = PITCH) : front(glm::vec3(0.0f, 0.0f, -1.0f)),
                                      movementSpeed(SPEED),
                                      mouseSensitivity(SENSITIVITY),
                                      zoom(ZOOM)
        {
            this->position = position;
            this->worldUp = up;
            this->worldDown = down;
            this->worldFront = front;
            this->worldBack = back;
            this->worldRight = right;
            this->worldLeft = left;
            this->yaw = yaw;
            this->pitch = pitch;
            this->updateCameraVectors();
        }

        Camera(float posX, float posY, float posZ,
               float upX, float upY, float upZ,
               float yaw, float pitch) : front(glm::vec3(0.0f, 0.0f, -1.0f)),
                                         movementSpeed(SPEED),
                                         mouseSensitivity(SENSITIVITY),
                                         zoom(ZOOM)
        {
            this->position = glm::vec3(posX, posY, posZ);
            this->worldUp = glm::vec3(upX, upY, upZ);
            this->yaw = yaw;
            this->pitch = pitch;
            this->updateCameraVectors();
        }

        glm::mat4 GetViewMatrix()
        {
            return glm::lookAt(this->position, this->position + this->front, this->up);
        }

        void ProcessKeyboard(CameraMovement direction, float deltaTime)
        {
            float velocity = this->movementSpeed * deltaTime;
            if (direction == FORWARD)
                this->position += glm::normalize(glm::vec3(this->front.x, 0.0f, this->front.z)) * velocity;
            if (direction == BACKWARD)
                this->position -= glm::normalize(glm::vec3(this->front.x, 0.0f, this->front.z)) * velocity;
            if (direction == LEFT)
                this->position -= this->right * velocity;
            if (direction == RIGHT)
                this->position += this->right * velocity;
            if (direction == UP)
                this->position += this->worldUp * velocity;
            if (direction == DOWN)
                this->position -= this->worldUp * velocity;            

            if (direction == SPRINT)
                this->movementSpeed = SPRINT_SPEED;
            else
                this->movementSpeed = SPEED;
        }

        void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
        {
            xoffset *= this->mouseSensitivity;
            yoffset *= this->mouseSensitivity;

            this->yaw += xoffset;
            this->pitch += yoffset;

            if (constrainPitch)
            {
                if (this->pitch > 89.0f)
                    this->pitch = 89.0f;
                if (this->pitch < -89.0f)
                    this->pitch = -89.0f;
            }

            this->updateCameraVectors();
        }

        void ProcessMouseScroll(float yoffset)
        {
            if (this->zoom >= 1.0f && this->zoom <= 45.0f)
                this->zoom -= yoffset;
            if (this->zoom <= 1.0f)
                this->zoom = 1.0f;
            if (this->zoom >= 45.0f)
                this->zoom = 45.0f;
        }

    private:
        void updateCameraVectors()
        {
            // calculate the new front vector
            glm::vec3 front;
            front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
            front.y = sin(glm::radians(this->pitch));
            front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
            this->front = glm::normalize(front);

            // also re-calculate the right and up vector
            this->right = glm::normalize(glm::cross(this->front, this->worldUp));
            this->up = glm::normalize(glm::cross(this->right, this->front));
        }
};