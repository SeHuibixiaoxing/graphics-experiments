#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
{
	this->position = position;
	this->worldUp = up;
	this->yaw = yaw;
	this->pitch = pitch;
	updateCameraVectors();
}

Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
{
	this->position = glm::vec3(posX, posY, posZ);
	this->worldUp = glm::vec3(upX, upY, upZ);
	this->yaw = yaw;
	this->pitch = pitch;
	updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(this->position, this->position + this->front, this->up);
}

void Camera::ProcessKeyboard(CameraMovement direction, GLfloat deltaTime)
{
	GLfloat velocity = this->movementSpeed * deltaTime;
	if (direction == CameraMovement::FORWARD)
	{
		this->position += this->front * velocity;
	}
	if (direction == CameraMovement::BACKWARD)
	{
		this->position -= this->front * velocity;
	}
	if (direction == CameraMovement::LEFT)
	{
		this->position -= this->right * velocity;
	}
	if (direction == CameraMovement::RIGHT)
	{
		this->position += this->right * velocity;
	}
}

void Camera::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch)
{
	xoffset *= mouseSensitivity;
	yoffset *= mouseSensitivity;

	this->yaw += xoffset;
	this->pitch += yoffset;

	if (constrainPitch == GL_TRUE)
	{
		if (this->pitch > 89.0f)
		{
			this->pitch = 89.0f;
		}
		if (this->pitch < -89.0f)
		{
			this->pitch = -89.0f;
		}
	}
	updateCameraVectors();
}

void Camera::ProcessMouseScroll(GLfloat yoffset)
{
	this->zoom -= (GLfloat)yoffset;
	if (this->zoom < 1.0f)
	{
		this->zoom = 1.0f;
	}
	if (this->zoom > 45.0f)
	{
		this->zoom = 45.0f;
	}
}

void Camera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	front.y = sin(glm::radians(this->pitch));
	front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->front = glm::normalize(front);

	this->right = glm::normalize(glm::cross(this->front, this->worldUp));
	this->up = glm::normalize(glm::cross(this->right, this->front));
}

glm::vec3 Camera::getPosition()
{
	return this->position;
}

glm::vec3 Camera::getFront()
{
	return this->front;
}

glm::vec3 Camera::getUp()
{
	return this->up;
}

glm::vec3 Camera::getRight()
{
	return this->right;
}

glm::vec3 Camera::getWorldUp()
{
	return this->worldUp;
}

GLfloat Camera::getYaw()
{
	return this->yaw;
}

GLfloat Camera::getPitch()
{
	return this->pitch;
}

GLfloat Camera::getMovementSpeed()
{
	return this->movementSpeed;
}

GLfloat Camera::getMouseSensitivity()
{
	return this->mouseSensitivity;
}

GLfloat Camera::getZoom()
{
	return this->zoom;
}
