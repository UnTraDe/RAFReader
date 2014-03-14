#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Camera
{
public: 
    Camera();
    Camera(const glm::vec3 &position);
    glm::mat4 getView();
    void moveAhead(float speed);
    void moveBack(float speed);
    void moveLeft(float speed);
    void moveRight(float speed);
    void addHorizontalAngle(float amount);
    void addVerticalAngle(float amount);
    void calculateVectors();

    glm::vec3 getPosition();
    void setPosition(const glm::vec3 &position);
    float getHorizontalAngle();
    float getVerticalAngle();

    void setIsFPSCamera(bool value);

private:
    void init();

    float horizontalAngle;
    float verticalAngle;
    
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 up;
    glm::vec3 right;

    bool isFPSCamera;
};
