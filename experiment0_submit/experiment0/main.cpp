/* 按键说明
W / A / S / D:移动摄像机 / 物体
P：切换模式。（FPS模式，选中模式，移动模式）FPS模式下按P，切换到选中模式。选中模式按P，切换到移动模式。移动模式按P，切换到FPS模式。
J：选中模式下，确定为起始状态
K：选中模式下，确定为结束状态
X：选中模式下，按住Z左右旋转，将绕X轴旋转
*/

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Shader.h"
#include "Camera.h"
#include "Model.h"

#include <iostream>

//窗口属性
const unsigned int WINDOW_WIDTH = 1600;					//窗口宽度
const unsigned int WINDOW_HEIGHT = 1200;				//窗口高度


//模式名称
enum class ModeType
{
    FPS_WORK_MODE = 0,
    PICKED_WORK_MODE = 1,
    MOVE_WORK_MODE = 2
};

ModeType workMode = ModeType::FPS_WORK_MODE;

const GLfloat MOVE_DISTANCE_PER_SECOND = 0.05;
glm::vec3 deltaPos;
GLint moveTimes = 0;
GLint nowTimes = 0;
GLboolean beginMove = GL_FALSE;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);


Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WINDOW_WIDTH / 2.0f;
GLfloat lastY = WINDOW_HEIGHT / 2.0f;
GLboolean firstMouse = true;

glm::vec3 lightPos(20.0f, 40.0f, 30.0f);

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;


struct ModelMat
{
    glm::quat rotate;
    glm::mat4 translate;
    glm::mat4 zoom;
    glm::mat4 value()
    {
        return translate * glm::toMat4(rotate) * zoom;
    }
};

ModelMat model_now, model_start, model_end;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "LearnOpenGL", NULL, NULL);
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


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    stbi_set_flip_vertically_on_load(true);

    glEnable(GL_DEPTH_TEST);

    Shader ourShader("1.vs", "1.fs");
    Shader lightShader("light.vs", "light.fs");


    //模型读取
    Model ourModel("nanosuit/nanosuit.obj", GL_STATIC_DRAW);

    //设置光照
    float lightBoxVertices[] = { -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
    };
    GLuint lightVAO1, lightVBO1;
    glGenVertexArrays(1, &lightVAO1);
    glGenBuffers(1, &lightVBO1);

    glBindVertexArray(lightVAO1);
    glBindBuffer(GL_ARRAY_BUFFER, lightVBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lightBoxVertices), lightBoxVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    //初始化model变换矩阵
    model_now.translate = model_now.zoom = glm::mat4(1.0f);
    model_now.rotate = glm::quat(1, 0, 0, 0);

    model_now.translate = glm::translate(model_now.translate, glm::vec3(0.0f, 0.0f, 0.0f));
    model_now.zoom = glm::scale(model_now.zoom, glm::vec3(1.0f, 1.0f, 1.0f));

    model_start = model_end = model_now;

    while (!glfwWindowShouldClose(window))
    {
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.05f, 0.05f, 0.05f, 0.05f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.use();

        glm::mat4 projection = glm::perspective(glm::radians(camera.getZoom()), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 1000.0f);
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);
        ourShader.setVec3("lighgPos", lightPos);
        ourShader.setVec3("viewPos", camera.getPosition());

        //model move
        if (workMode == ModeType::MOVE_WORK_MODE)
        {
            if (beginMove == GL_FALSE)
            {
                beginMove = GL_TRUE;


                glm::vec3 beginPos(model_start.translate[3][0], model_start.translate[3][1], model_start.translate[3][2]);
                glm::vec3 endPos(model_end.translate[3][0], model_end.translate[3][1], model_end.translate[3][2]);


                moveTimes = glm::l2Norm(endPos - beginPos) / MOVE_DISTANCE_PER_SECOND + 1;

                nowTimes = 0;
                deltaPos = (endPos - beginPos) * (1.0f / moveTimes);

                model_now = model_start;
            }
            else
            {
                ++nowTimes;
                model_now.translate = glm::translate(model_now.translate, deltaPos);
                model_now.rotate = glm::mix(model_start.rotate, model_end.rotate, (GLfloat)nowTimes / moveTimes);
                if (nowTimes == moveTimes)
                {
                    model_now = model_end;
                    beginMove = GL_FALSE;
                }
            }
        }

        auto model_now_mat = model_now.value();
        ourShader.setMat4("model", model_now_mat);
        ourShader.setMat4("normModel", glm::transpose(glm::inverse(model_now_mat)));   

        ourShader.setVec3("light.ambient", 0.4f, 0.4f, 0.4f);
        ourShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
        ourShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
        ourShader.setFloat("light.constant", 1.0f);
        ourShader.setFloat("light.linear", 0.0f);
        ourShader.setFloat("light.quadratic", 0.0f);
        ourShader.setFloat("shininess", 32.0f);

        ourModel.Draw(ourShader);

        //光源绘制
        lightShader.use();
        lightShader.setMat4("projection", projection);
        lightShader.setMat4("view", view);
        auto lightModel = glm::mat4(1.0f);
        lightModel = glm::translate(lightModel, lightPos);
        lightModel = glm::scale(lightModel, glm::vec3(5.0f));
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

GLboolean pressKeyP = GL_FALSE;
void processInput(GLFWwindow* window)
{
    if (workMode == ModeType::FPS_WORK_MODE || workMode == ModeType::MOVE_WORK_MODE)
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
        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        {
            pressKeyP = GL_TRUE;
        }
        if (pressKeyP && glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE)
        {
            pressKeyP = GL_FALSE;
            if (workMode == ModeType::FPS_WORK_MODE)
            {
                workMode = ModeType::PICKED_WORK_MODE;
            }
            else if (workMode == ModeType::MOVE_WORK_MODE)
            {
                workMode = ModeType::FPS_WORK_MODE;
                beginMove = GL_FALSE;
            }
        }
        
    }
    else if (workMode == ModeType::PICKED_WORK_MODE)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
            {
                GLfloat velocity = SPEED * deltaTime;
                model_now.translate = glm::translate(model_now.translate, camera.getUp() * velocity);
            }
            else
            {
                GLfloat velocity = SPEED * deltaTime;
                model_now.translate = glm::translate(model_now.translate, camera.getFront() * velocity);
            }
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
            {
                GLfloat velocity = -SPEED * deltaTime;
                model_now.translate = glm::translate(model_now.translate, camera.getUp() * velocity);
            }
            else
            {
                float velocity = -SPEED * deltaTime;
                model_now.translate = glm::translate(model_now.translate, camera.getFront() * velocity);
            }
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            GLfloat velocity = -SPEED * deltaTime;
            model_now.translate = glm::translate(model_now.translate, camera.getRight() * velocity);
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            GLfloat velocity = SPEED * deltaTime;
            model_now.translate = glm::translate(model_now.translate, camera.getRight() * velocity);
        }
        if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        {
            model_start = model_now;
        }
        if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        {
            model_end = model_now;
        }

        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        {
            pressKeyP = GL_TRUE;
        }
        if (pressKeyP && glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE)
        {
            pressKeyP = GL_FALSE;
            workMode = ModeType::MOVE_WORK_MODE;
            model_end = model_now;
        }
    }
}
void framebuffer_size_callback(GLFWwindow* window, GLint width, GLint height)
{
    glViewport(0, 0, width, height);
}
void mouse_callback(GLFWwindow* window, GLdouble xpos, GLdouble ypos)
{
    if (firstMouse == GL_TRUE)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = GL_FALSE;
    }

    if (workMode == ModeType::FPS_WORK_MODE || workMode == ModeType::MOVE_WORK_MODE)
    {
        GLfloat xoffset = xpos - lastX;
        GLfloat yoffset = lastY - ypos;


        lastX = xpos;
        lastY = ypos;

        camera.ProcessMouseMovement(xoffset, yoffset);
    }
    else if (workMode == ModeType::PICKED_WORK_MODE)
    {
        GLfloat xoffset = xpos - lastX;
        GLfloat yoffset = lastY - ypos;

        lastX = xpos;
        lastY = ypos;

        xoffset *= SENSITIVITY;
        yoffset *= SENSITIVITY;

        GLfloat RotationAngleY = glm::radians(xoffset);
        glm::quat rotateQuatY;
        if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
        {
            glm::quat rotateQuatT(1 * sin(RotationAngleY / 2),
                0 * sin(RotationAngleY / 2),
                0 * sin(RotationAngleY / 2),
                cos(RotationAngleY / 2));
            rotateQuatY = rotateQuatT;
        }
        else
        {
            glm::quat rotateQuatT(0 * sin(RotationAngleY / 2),
                1 * sin(RotationAngleY / 2),
                0 * sin(RotationAngleY / 2),
                cos(RotationAngleY / 2));
            rotateQuatY = rotateQuatT;
        }
        
        GLfloat RotationAngleZ = glm::radians(yoffset);
        glm::quat rotateQuatZ(0 * sin(RotationAngleZ / 2),
            0 * sin(RotationAngleZ / 2),
            1 * sin(RotationAngleZ / 2),
            cos(RotationAngleZ / 2));
                
        model_now.rotate = model_now.rotate * rotateQuatZ * rotateQuatY;
    }

}
void scroll_callback(GLFWwindow* window, GLdouble xoffset, GLdouble yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

