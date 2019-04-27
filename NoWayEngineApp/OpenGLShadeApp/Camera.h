#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h> // include GLEW and new version of GL on Windows

class Camera
{
private:
	

	// Default camera values
	const GLfloat YAW = -90.0f;
	const GLfloat PITCH = 0.0f;
	const GLfloat SPEED = 3.0f;
	const GLfloat SENSITIVTY = 0.25f;
	const GLfloat ZOOM = 72.0f;
	const GLuint WINDOW_WIDTH = 800;
	const GLuint WINDOW_HEIGHT = 600;

	// Camera position vec3(x, y, z)
	glm::vec3 position;
	// Camera target vec3(x, y, z)
	glm::vec3 target;
	// Camera vector to right direction related to the camera view vec3(x, y, z)
	glm::vec3 rightDirection;
	// World큦 vector to up direction related to the camera vec3(x, y, z)
	glm::vec3 upDirection;
	// World큦 vector to up direction related to the world vec3(x, y, z)
	glm::vec3 worldUpDirection;
	// Camera rotate vec3(pitch, yaw, roll) pitch = x axis, yaw = y axis and roll = z axis
	glm::vec3 pitchYawRoll;
	//last position of the camera related to the update
	glm::vec3 lastPosition;
	// field of view, camera angle of vision
	GLfloat fieldOfView;
	//  how close a vetice can be drawn to the camera
	GLfloat zNear;
	// how far a vetice can be drawn to the camera
	GLfloat zFar;
	// how far a vetice can be drawn to the camera
	GLfloat mouseSensitivity;
	// how far a vetice can be drawn to the camera
	GLfloat movementSpeed;
	// model - maps from an object's local coordinate space into world space



public:
	// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
	enum CameraMovement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		TOP,
		DOWN
	};

	// Constructors
	Camera();
	Camera(glm::vec3 position, glm::vec3 target, glm::vec3 upDirection, GLfloat fieldOfView);
	Camera(GLfloat fieldOfView, glm::vec2 windowSize, GLfloat zNear, GLfloat zFar);
	// Constructor with scalar values
	Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch);
	// Destructor
	~Camera();


	// Calculates the front vector from the Camera's (updated) Eular Angles
	void updateCameraVectors();
	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis 
	// - Default action zoom
	void processMouseScroll(GLfloat yOffset);
	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void processMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch = true);
	// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void processKeyboard(CameraMovement direction, GLfloat deltaTime);
	// Returns the view matrix calculated using Eular Angles and the LookAt Matrix
	glm::mat4 getViewMatrix();

	//----------------------Inline Getters and Setters----------------------//
	glm::vec3 getPosition() { return position; }
	void  setPosition(glm::vec3 value) { position = value; }

	glm::vec3 getTarget() { return target; }
	void  setTarget(glm::vec3 value) { target = value; }

	glm::vec3 getRightDirection() { return rightDirection; }
	void  setRightDirection(glm::vec3 value) { rightDirection = value; }

	glm::vec3 getUpDirection() { return upDirection; }
	void  setUpDirection(glm::vec3 value) { upDirection = value; }

	glm::vec3 getWorldUpDirection() { return worldUpDirection; }
	void  setWorldUpDirection(glm::vec3 value) { worldUpDirection = value; }

	glm::vec3 getPitchYawRoll() { return pitchYawRoll; }
	void  setPitchYawRoll(glm::vec3 value) { pitchYawRoll = value; }

	glm::vec3 getLastPosition() { return lastPosition; }
	void  setLastPosition(glm::vec3 value) { lastPosition = value; }

	GLfloat getFieldOfView() { return fieldOfView; }
	void  setFieldOfView(GLfloat value) { fieldOfView = value; }

	GLfloat getZNear() { return zNear; }
	void  setzNear(GLfloat value) { zNear = value; }

	GLfloat getZFar() { return zFar; }
	void  setZFar(GLfloat value) { zFar = value; }

	GLfloat getMouseSensitivity() { return mouseSensitivity; }
	void  setMouseSensitivity(GLfloat value) { mouseSensitivity = value; }

	GLfloat getMovementSpeed() { return movementSpeed; }
	void  setMovementSpeed(GLfloat value) { movementSpeed = value; }

	//----------------------Inline Getters and Setters Conversions----------------------//
	// breaking down the camera큦 position vector getters and setters
	GLfloat getPositionX() { return position.x; }
	void  setPositionX(GLfloat xValue) { position.x = xValue; }
	GLfloat getPositionY() { return position.y; }
	void  setPositionY(GLfloat yValue) { position.y = yValue; }
	GLfloat getPositionZ() { return position.z; }
	void  setPositionZ(GLfloat zValue) { position.z = zValue; }

	// breaking down the camera큦 target vector getters and setters
	GLfloat getTargetX() { return target.x; }
	void  setTargetX(GLfloat xValue) { target.x = xValue; }
	GLfloat getTargetY() { return target.y; }
	void  setTargetY(GLfloat yValue) { target.y = yValue; }
	GLfloat getTargetZ() { return target.z; }
	void  setTargetZ(GLfloat zValue) { target.z = zValue; }

	// breaking down the camera큦 rightDirection vector getters and setters
	GLfloat getRightDirectionX() { return rightDirection.x; }
	void  setRightDirectionX(GLfloat xValue) { rightDirection.x = xValue; }
	GLfloat getRightDirectionY() { return rightDirection.y; }
	void  setRightDirectionY(GLfloat yValue) { rightDirection.y = yValue; }
	GLfloat getRightDirectionZ() { return rightDirection.z; }
	void  setRightDirectionZ(GLfloat zValue) { rightDirection.z = zValue; }

	// breaking down the camera큦 upDirection vector getters and setters
	GLfloat getUpDirectionX() { return upDirection.x; }
	void  setUpDirectionX(GLfloat xValue) { upDirection.x = xValue; }
	GLfloat getUpDirectionY() { return upDirection.y; }
	void  setUpDirectionY(GLfloat yValue) { upDirection.y = yValue; }
	GLfloat getUpDirectionZ() { return upDirection.z; }
	void  setUpDirectionZ(GLfloat zValue) { upDirection.z = zValue; }

	// breaking down the camera큦 worldUpDirection vector getters and setters
	GLfloat getWorldUpDirectionX() { return worldUpDirection.x; }
	void  setWorldUpDirectionX(GLfloat xValue) { worldUpDirection.x = xValue; }
	GLfloat getWorldUpDirectionY() { return worldUpDirection.y; }
	void  setWorldUpDirectionY(GLfloat yValue) { worldUpDirection.y = yValue; }
	GLfloat getWorldUpDirectionZ() { return worldUpDirection.z; }
	void  setWorldUpDirectionZ(GLfloat zValue) { worldUpDirection.z = zValue; }

	// breaking down the camera큦 pitchYawRoll vector getters and setters
	GLfloat getPitch() { return pitchYawRoll.x; }
	void  setPitch(GLfloat pitch) { pitchYawRoll.x = pitch; }
	GLfloat getYaw() { return pitchYawRoll.y; }
	void  setYaw(GLfloat yaw) { pitchYawRoll.y = yaw; }
	GLfloat getRoll() { return pitchYawRoll.z; }
	void  setRoll(GLfloat roll) { pitchYawRoll.z = roll; }

	// breaking down the camera큦 lastPosition vector getters and setters
	GLfloat getLastPositionX() { return lastPosition.x; }
	void  setLastPositionX(GLfloat xValue) { lastPosition.x = xValue; }
	GLfloat getLastPositionY() { return lastPosition.y; }
	void  setLastPositionY(GLfloat yValue) { lastPosition.y = yValue; }
	GLfloat getLastPositionZ() { return lastPosition.z; }
	void  setLastPositionZ(GLfloat zValue) { lastPosition.z = zValue; }


	
};

