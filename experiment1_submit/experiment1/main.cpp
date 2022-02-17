/* ����˵��
W / A / S / D:�ƶ������ / ����
P���л�ģʽ����FPSģʽ��ѡ��ģʽ���ƶ�ģʽ��FPSģʽ�°�P���л���ѡ��ģʽ��ѡ��ģʽ��P���л����ƶ�ģʽ���ƶ�ģʽ��P���л���FPSģʽ��
J��ѡ��ģʽ�£�ȷ��Ϊ��ʼ״̬
K��ѡ��ģʽ�£�ȷ��Ϊ����״̬
X��ѡ��ģʽ�£���סZ������ת������X����ת
*/
#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Shader.h"
#include "Camera.h"
#include "ModelMat.h"
#include "Box.h"
#include "datadefs.h"
#include "node.h"

#include <iostream>

//��������
const unsigned int WINDOW_WIDTH = 1600;					//���ڿ��
const unsigned int WINDOW_HEIGHT = 1200;				//���ڸ߶�
GLFWwindow* window;
int setupWindow();

//��ʼ��
int setupGlad();
void initDrawSetup();


//ģʽ����
enum class ModeType
{
    FPS_WORK_MODE = 0,
};
ModeType workMode = ModeType::FPS_WORK_MODE;

//�����̿���
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

//������ƶ�����
Camera camera(glm::vec3(0.0f, -5.0f, 20.0f));
GLfloat lastX = WINDOW_WIDTH / 2.0f;
GLfloat lastY = WINDOW_HEIGHT / 2.0f;
GLboolean firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

//���չ���
glm::vec3 lightPos(8.0f, -3.0f, 8.0f);
GLuint lightVAO1, lightVBO1;
void initLightBoxSetup();

//����˶�������
enum class MoveState
{
    NONE = 0,
    LEFT_ARM_RIGHT_LEG_FORWARD = 1,
    LEFT_ARM_RIGHT_LEG_BACKWARD = 2,
};

MoveState moveState;

const GLfloat maxAngleArmUp = 45;      //�ϱ����Ƕ�
const GLfloat maxAngleArmDown = 45;    //�±����Ƕ�
const GLfloat maxAngleLegUp = 30;      //�������Ƕ�
const GLfloat maxAngleLegDown = 30;    //�������Ƕ�
const GLint timePerTwoStep = 4000;     //ÿ��������ʱ��
const GLint timePerState = timePerTwoStep / 4; //ÿ��״̬����ʱ��
const GLint timePrecision = 1000;      //ʱ�侫��

GLint beginTime;                     //��ʼʱ��
GLint lastTime;                      //��һ�δ���ʱ��
GLint nowTime;                       //��ǰʱ��
GLint endTime;                       //����ʱ��

GLint timeCnt;                       //ʱ�����

GLboolean firstBegin = GL_TRUE;      //��ʼ��־


int main()
{
    if (setupWindow() == -1) return -1;
    if (setupGlad() == -1) return -1;
    initDrawSetup();
        
    //��Դģ������
    Shader ourShader("shader.vs", "shader.fs");
    Shader lightShader("light.vs", "light.fs");
    initLightBoxSetup();

    //�������
    Box::loadTexture("container2.png", "container2_specular.png");

    Node body(boxVertices, sizeof(boxVertices));

    Node head(boxVertices, sizeof(boxVertices));

    Node leftArmUp(boxVertices, sizeof(boxVertices));
    Node leftArmDown(boxVertices, sizeof(boxVertices));
    Node leftHand(boxVertices, sizeof(boxVertices));

    Node rightArmUp(boxVertices, sizeof(boxVertices));
    Node rightArmDown(boxVertices, sizeof(boxVertices));
    Node rightHand(boxVertices, sizeof(boxVertices));


    Node leftLegUp(boxVertices, sizeof(boxVertices));
    Node leftLegDown(boxVertices, sizeof(boxVertices));
    Node leftFoot(boxVertices, sizeof(boxVertices));

    Node rightLegUp(boxVertices, sizeof(boxVertices));
    Node rightLegDown(boxVertices, sizeof(boxVertices));
    Node rightFoot(boxVertices, sizeof(boxVertices));

    head.insertChild(&body);
    body.insertChild(&leftArmUp);
    leftArmUp.insertChild(&leftArmDown);
    leftArmDown.insertChild(&leftHand);
    body.insertChild(&rightArmUp);
    rightArmUp.insertChild(&rightArmDown);
    rightArmDown.insertChild(&rightHand);
    body.insertChild(&leftLegUp);
    leftLegUp.insertChild(&leftLegDown);
    leftLegDown.insertChild(&leftFoot);
    body.insertChild(&rightLegUp);
    rightLegUp.insertChild(&rightLegDown);
    rightLegDown.insertChild(&rightFoot);



    //����
    body.translate(glm::vec3(0.0f, -2.5f, 0.0f));
    body.zoom(glm::vec3(2.0, 4.0, 1.0));

    //���ϱ�
    leftArmUp.translate(glm::vec3(-1.25f, 0.875f, 0.0f));
    leftArmUp.zoom(glm::vec3(0.5f, 2.25f, 1.0f));
    //���±�
    leftArmDown.translate(glm::vec3(0.0f, -2.25f, 0.0f));
    leftArmDown.zoom(glm::vec3(0.5f, 2.25f, 1.0f));
    //����
    leftHand.translate(glm::vec3(0.0f, -1.25f, 0.0f));
    leftHand.zoom(glm::vec3(0.40f, 0.5f, 0.40f));
    //���ϱ�
    rightArmUp.translate(glm::vec3(1.25f, 0.875f, 0.0f));
    rightArmUp.zoom(glm::vec3(0.5f, 2.25f, 1.0f));
    //���±�
    rightArmDown.translate(glm::vec3(0.0f, -2.25f, 0.0f));
    rightArmDown.zoom(glm::vec3(0.5f, 2.25f, 1.0f));
    //����
    rightHand.translate(glm::vec3(0.0f, -1.25f, 0.0f));
    rightHand.zoom(glm::vec3(0.40f, 0.5f, 0.40f));

    //������
    leftLegUp.translate(glm::vec3(-0.45f, -3.125f, 0.0f));
    leftLegUp.zoom(glm::vec3(0.6f, 2.25f, 1.0f));
    //������
    leftLegDown.translate(glm::vec3(0.0f, -2.25f, 0.0f));
    leftLegDown.zoom(glm::vec3(0.6f, 2.25f, 1.0f));
    //���
    leftFoot.translate(glm::vec3(0.0f, -1.25f, 0.5f));
    leftFoot.zoom(glm::vec3(0.40f, 0.2f, 1.5f));
    //������
    rightLegUp.translate(glm::vec3(0.45f, -3.125f, 0.0f));
    rightLegUp.zoom(glm::vec3(0.6f, 2.25f, 1.0f));
    //������
    rightLegDown.translate(glm::vec3(0.0f, -2.25f, 0.0f));
    rightLegDown.zoom(glm::vec3(0.6f, 2.25f, 1.0f));
    //�ҽ�
    rightFoot.translate(glm::vec3(0.0f, -1.25f, 0.5f));
    rightFoot.zoom(glm::vec3(0.40f, 0.2f, 1.5f));

    while (!glfwWindowShouldClose(window))
    {
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.47843f, 0.50196f, 0.56470f, 0.05f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //���ù�Դλ�ú͹۲���λ��
        ourShader.use();
        ourShader.setVec3("light.position", lightPos);
        ourShader.setVec3("viewPos", camera.getPosition());
        //����projection matrix��view matrix
        glm::mat4 projection = glm::perspective(glm::radians(camera.getZoom()), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 1000.0f);
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        //�������˲��ж���
        if (firstBegin)
        {
            firstBegin = false;
            beginTime = currentFrame * timePrecision;
            nowTime = beginTime;
            endTime = currentFrame * timePrecision + timePerTwoStep;
            lastTime = beginTime;
            timeCnt = 0;

            moveState = MoveState::LEFT_ARM_RIGHT_LEG_FORWARD;
        }
        else
        {   
            nowTime = currentFrame * timePrecision;
            timeCnt = std::min(timePerState, nowTime - lastTime);
            if (moveState == MoveState::LEFT_ARM_RIGHT_LEG_FORWARD)
            {
                //���������ҽ�
                leftArmUp.setRotate(glm::radians(maxAngleArmUp - maxAngleArmUp * 2 / timePerState * timeCnt), glm::vec3(1.0f, 0.0f, 0.0f));
                leftArmDown.setRotate(glm::radians(maxAngleArmDown  -maxAngleArmDown * 2 / timePerState * timeCnt), glm::vec3(1.0f, 0.0f, 0.0f));
                rightLegUp.setRotate(glm::radians(maxAngleLegUp  -maxAngleLegUp * 2 / timePerState * timeCnt), glm::vec3(1.0f, 0.0f, 0.0f));
                rightLegDown.setRotate(glm::radians(maxAngleLegDown  -maxAngleLegDown * 2 / timePerState * timeCnt), glm::vec3(1.0f, 0.0f, 0.0f));
                       

                //�ջ��������
                rightArmUp.setRotate(glm::radians(-maxAngleArmUp + maxAngleArmUp * 2 / timePerState * timeCnt), glm::vec3(1.0f, 0.0f, 0.0f));
                rightArmDown.setRotate(glm::radians(-maxAngleArmDown + maxAngleArmDown * 2 / timePerState * timeCnt), glm::vec3(1.0f, 0.0f, 0.0f));
                leftLegUp.setRotate(glm::radians(-maxAngleLegUp + maxAngleLegUp * 2 / timePerState * timeCnt), glm::vec3(1.0f, 0.0f, 0.0f));
                leftLegDown.setRotate(glm::radians(-maxAngleLegDown + maxAngleLegDown * 2 / timePerState * timeCnt), glm::vec3(1.0f, 0.0f, 0.0f));

                if (timeCnt == timePerState)
                {
                    moveState = MoveState::LEFT_ARM_RIGHT_LEG_BACKWARD;
                    timeCnt = 0;
                    lastTime = nowTime;
                }
            }
            else if (moveState == MoveState::LEFT_ARM_RIGHT_LEG_BACKWARD)
            {
                //�ջ������ҽ�
                leftArmUp.setRotate(glm::radians(-maxAngleArmUp + maxAngleArmUp * 2 / timePerState * timeCnt), glm::vec3(1.0f, 0.0f, 0.0f));
                leftArmDown.setRotate(glm::radians(-maxAngleArmDown + maxAngleArmDown * 2/ timePerState * timeCnt), glm::vec3(1.0f, 0.0f, 0.0f));
                rightLegUp.setRotate(glm::radians(-maxAngleLegUp + maxAngleLegUp * 2 / timePerState * timeCnt), glm::vec3(1.0f, 0.0f, 0.0f));
                rightLegDown.setRotate(glm::radians(-maxAngleLegDown + maxAngleLegDown * 2 / timePerState * timeCnt), glm::vec3(1.0f, 0.0f, 0.0f));

                //�����������
                rightArmUp.setRotate(glm::radians(maxAngleArmUp - maxAngleArmUp * 2 / timePerState * timeCnt), glm::vec3(1.0f, 0.0f, 0.0f));
                rightArmDown.setRotate(glm::radians(maxAngleArmDown - maxAngleArmDown * 2 / timePerState * timeCnt), glm::vec3(1.0f, 0.0f, 0.0f));
                leftLegUp.setRotate(glm::radians(maxAngleLegUp - maxAngleLegUp * 2 / timePerState * timeCnt), glm::vec3(1.0f, 0.0f, 0.0f));
                leftLegDown.setRotate(glm::radians(maxAngleLegDown - maxAngleLegDown * 2 / timePerState * timeCnt), glm::vec3(1.0f, 0.0f, 0.0f));

                if (timeCnt == timePerState)
                {
                    moveState = MoveState::LEFT_ARM_RIGHT_LEG_FORWARD;
                    timeCnt = 0;
                    lastTime = nowTime;
                }
            }
        }

        //�������Ȧ��ת
        GLfloat r = glm::distance(glm::vec3(0, 0, 0), lightPos);
        GLfloat theta = currentFrame / 5;
        head.setTranslate(glm::vec3(-2 * r * sin(theta) * cos(theta), 0.0f, -2 * r * sin(theta) * sin(theta)));
        head.setRotate(glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        head.rotate(- 2 * theta, glm::vec3(0.0f, 1.0f, 0.0f));
        
        //���ƻ����
        head.draw(ourShader);

        //��Դ����
        lightShader.use();
        lightShader.setMat4("projection", projection);
        lightShader.setMat4("view", view);
        auto lightModel = glm::mat4(1.0f);
        lightModel = glm::translate(lightModel, lightPos);
        lightModel = glm::scale(lightModel, glm::vec3(1.0f));
        lightShader.setMat4("model", lightModel);
        glBindVertexArray(lightVAO1);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &lightVAO1);
    glDeleteBuffers(1, &lightVBO1);
    glfwTerminate();
    return 0;
}

int setupWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
      
    return 1;
}
int setupGlad()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    return 1;
}
void initDrawSetup()
{
    stbi_set_flip_vertically_on_load(true);
    glEnable(GL_DEPTH_TEST);
}

/*��������*/
void initLightBoxSetup()
{
    glGenVertexArrays(1, &lightVAO1);
    glGenBuffers(1, &lightVBO1);

    glBindVertexArray(lightVAO1);
    glBindBuffer(GL_ARRAY_BUFFER, lightVBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lightBoxVertices), lightBoxVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

/*���̿���*/
void processInput(GLFWwindow* window)
{
    if (workMode == ModeType::FPS_WORK_MODE)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.ProcessKeyboard(CameraMovement::FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.ProcessKeyboard(CameraMovement::BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.ProcessKeyboard(CameraMovement::LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.ProcessKeyboard(CameraMovement::RIGHT, deltaTime);
    }
}
void framebuffer_size_callback(GLFWwindow* window, GLint width, GLint height)
{
    glViewport(0, 0, width, height);
}
/*������*/
void mouse_callback(GLFWwindow* window, GLdouble xpos, GLdouble ypos)
{
    if (firstMouse == GL_TRUE)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = GL_FALSE;
    }
    if (workMode == ModeType::FPS_WORK_MODE)
    {
        GLfloat xoffset = xpos - lastX;
        GLfloat yoffset = lastY - ypos;


        lastX = xpos;
        lastY = ypos;

        camera.ProcessMouseMovement(xoffset, yoffset);
    }

}
void scroll_callback(GLFWwindow* window, GLdouble xoffset, GLdouble yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}
