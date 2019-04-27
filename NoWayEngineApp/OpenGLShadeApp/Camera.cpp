#include "Camera.h"
#include <iostream>
#include <GLFW/glfw3.h> // GLFW helper library
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Camera::Camera()
	: target(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVTY), fieldOfView(ZOOM)
{
	//camera
	GLfloat posX = -10.0f;
	GLfloat posY = 10.0f;
	GLfloat posZ = 0.0f;
	GLfloat upX = 0.0f;
	GLfloat upY = 1.0f;
	GLfloat upZ = 0.0f;
	GLfloat yaw = 0.0f;
	GLfloat pitch = 0.0f;

	this->position = glm::vec3(posX, posY, posZ);
	this->worldUpDirection = glm::vec3(upX, upY, upZ);
	this->pitchYawRoll.y = yaw;
	this->pitchYawRoll.x = pitch;

	this->updateCameraVectors();
}


Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch)
	: target(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVTY), fieldOfView(ZOOM)
{
	this->position = glm::vec3(posX, posY, posZ);
	this->worldUpDirection = glm::vec3(upX, upY, upZ);
	this->pitchYawRoll.y = yaw;
	this->pitchYawRoll.x = pitch;

	this->updateCameraVectors();
}

Camera::~Camera()
{

}

void Camera::updateCameraVectors()
{
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(this->getYaw())) * cos(glm::radians(this->getPitch()));
	front.y = sin(glm::radians(this->getPitch()));
	front.z = sin(glm::radians(this->getYaw())) * cos(glm::radians(this->getPitch()));
	this->target = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	this->rightDirection = glm::normalize(glm::cross(this->target, this->worldUpDirection));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	this->upDirection = glm::normalize(glm::cross(this->rightDirection, this->target));
}

void Camera::processMouseScroll(GLfloat yOffset)
{
	if (this->fieldOfView >= 1.0f && this->fieldOfView <= 45.0f)
		this->fieldOfView -= yOffset ;
	if (this->fieldOfView <= 1.0f)
		this->fieldOfView = 1.0f;
	if (this->fieldOfView >= 45.0f)
		this->fieldOfView = 45.0f;
	

}

void Camera::processMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch)
{
	xOffset *= this->mouseSensitivity;
	yOffset *= this->mouseSensitivity;

	//set pitch
	this->pitchYawRoll.x += yOffset;
	//set Yaw
	this->pitchYawRoll.y += xOffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (this->pitchYawRoll.x > 89.0f)
			this->pitchYawRoll.x = 89.0f;
		if (this->pitchYawRoll.x < -89.0f)
			this->pitchYawRoll.x = -89.0f;
	}

	// Update Front, Right and Up Vectors using the updated Eular angles
	this->updateCameraVectors();
}

void Camera::processKeyboard(CameraMovement direction, GLfloat deltaTime)
{
	GLfloat velocity = this->movementSpeed * deltaTime;
	if (direction == FORWARD)
		this->position += this->target * velocity;
	if (direction == BACKWARD)
		this->position -= this->target * velocity;
	if (direction == LEFT)
		this->position -= this->rightDirection * velocity;
	if (direction == RIGHT)
		this->position += this->rightDirection * velocity;
	if (direction == TOP)
		this->position -= this->worldUpDirection * velocity;
	if (direction == DOWN)
		this->position += this->worldUpDirection * velocity;
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(this->position, this->position + this->target, this->upDirection);
}
