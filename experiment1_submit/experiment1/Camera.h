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

//初始属性
const GLfloat YAW = -90.0f;					//偏航角，绕y轴旋转
const GLfloat PITCH = 0.0f;					//俯仰角，绕x轴旋转
const GLfloat SPEED = 10.0f;
const GLfloat SENSITIVITY = 0.1f;
const GLfloat ZOOM = 45.0f;

class Camera
{
public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH);
	Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch);

	glm::mat4 GetViewMatrix();		//获得变换矩阵

	void ProcessKeyboard(CameraMovement direction, GLfloat deltaTime);	//处理键盘按键移动指令

	void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = GL_TRUE);	//处理鼠标移动旋转指令

	void ProcessMouseScroll(GLfloat yoffset);	//处理滚轮移动放缩指令


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
	glm::vec3 position;						//相机位置
	glm::vec3 front;						//相机注视位置方向向量
	glm::vec3 up;							//相机上轴（y轴）
	glm::vec3 right;						//相机右轴（x轴）
	glm::vec3 worldUp;						//世界坐标系上向量

	GLfloat yaw;							//偏航角，绕y轴旋转
	GLfloat pitch;							//俯仰角，绕x轴旋转

	GLfloat movementSpeed;					//移动速度
	GLfloat mouseSensitivity;				//旋转速度
	GLfloat zoom;							//放缩比率

	void updateCameraVectors();				//更新摄像机各个向量
};

