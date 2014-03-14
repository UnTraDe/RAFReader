#include "Camera.h"

Camera::Camera()
{
    init();
}

Camera::Camera(const glm::vec3 &position)
{
    init();
    setPosition(position);
}

void Camera::init()
{
    this->position = glm::vec3(0.0f, 0.0f, 0.0f);
    this->direction = glm::vec3(0.0f, 0.0f, -1.0f);
    this->up = glm::vec3(0.0f, -1.0f, 0.0f);
    horizontalAngle = 0;
    verticalAngle = 0;
    isFPSCamera = false;
}

glm::mat4 Camera::getView()
{
    return glm::lookAt(position, position + direction, up);
}

void Camera::moveAhead(float speed)
{
    position += direction * speed;
}

void Camera::moveBack(float speed)
{
    position -= direction * speed;
}

void Camera::moveLeft(float speed)
{
    position += glm::cross(up, direction) * speed;
}

void Camera::moveRight(float speed)
{
    position -= glm::cross(up, direction) * speed;
}

void Camera::addHorizontalAngle(float amount)
{
    horizontalAngle += amount;
}

void Camera::addVerticalAngle(float amount)
{
    verticalAngle += amount;

        if(isFPSCamera)
        verticalAngle = glm::clamp(verticalAngle, -1.0f, 1.0f);
}

void Camera::calculateVectors()
{
    direction.x = glm::cos(verticalAngle) * glm::sin(horizontalAngle);
    direction.y = glm::sin(verticalAngle);
    direction.z = glm::cos(verticalAngle) * glm::cos(horizontalAngle);
    right = glm::vec3(glm::sin(horizontalAngle - 3.14f/2.0f), 0, glm::cos(horizontalAngle - 3.14f/2.0f));
    up = glm::cross(right, direction);
}

glm::vec3 Camera::getPosition()
{
    return position;
}

void Camera::setPosition(const glm::vec3 &position)
{
    this->position = position;
}

float Camera::getHorizontalAngle()
{
    return horizontalAngle;
}

float Camera::getVerticalAngle()
{
    return verticalAngle;    
}

void Camera::setIsFPSCamera(bool value)
{
    isFPSCamera = value;
}
