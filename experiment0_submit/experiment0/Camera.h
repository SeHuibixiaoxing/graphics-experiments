#pragma once
#include <vector>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class CameraMovement {
	FORWARD = 0,
	BACKWARD = 1,
	LEFT = 2,
	RIGHT = 3,
};

//��ʼ����
const GLfloat YAW = -90.0f;					//ƫ���ǣ���y����ת
const GLfloat PITCH = 0.0f;					//�����ǣ���x����ת
const GLfloat SPEED = 10.0f;
const GLfloat SENSITIVITY = 0.1f;
const GLfloat ZOOM = 45.0f;

class Camera
{
public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH);
	Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch);

	glm::mat4 GetViewMatrix();		//��ñ任����

	void ProcessKeyboard(CameraMovement direction, GLfloat deltaTime);	//������̰����ƶ�ָ��

	void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = GL_TRUE);	//��������ƶ���תָ��

	void ProcessMouseScroll(GLfloat yoffset);	//��������ƶ�����ָ��


	glm::vec3 getPosition();
	glm::vec3 getFront();
	glm::vec3 getUp();
	glm::vec3 getRight();
	glm::vec3 getWorldUp();
	GLfloat getYaw();
	GLfloat getPitch();
	GLfloat getMovementSpeed();
	GLfloat getMouseSensitivity();
	GLfloat getZoom();


private:
	glm::vec3 position;						//���λ��
	glm::vec3 front;						//���ע��λ�÷�������
	glm::vec3 up;							//������ᣨy�ᣩ
	glm::vec3 right;						//������ᣨx�ᣩ
	glm::vec3 worldUp;						//��������ϵ������

	GLfloat yaw;							//ƫ���ǣ���y����ת
	GLfloat pitch;							//�����ǣ���x����ת

	GLfloat movementSpeed;					//�ƶ��ٶ�
	GLfloat mouseSensitivity;				//��ת�ٶ�
	GLfloat zoom;							//��������

	void updateCameraVectors();				//�����������������
};

