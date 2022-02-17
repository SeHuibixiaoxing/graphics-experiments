
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <iostream>
#include <vector>

const GLfloat pi = 3.1415926535898;

//划分精度
const int eps = 500;

// 视角变换
GLfloat theta;

//窗口属性
unsigned int WINDOW_WIDTH = 1600;					//窗口宽度
unsigned int WINDOW_HEIGHT = 1200;				//窗口高度
GLFWwindow* window;
int setupWindow();

//初始化
int setupGlad();
void initDrawSetup();

//顶点数据
GLfloat points1[10000][3], points2[10000][3];
int tot1 = 0, tot2 = 0;

//模式管理
enum class ModeType
{
    DRAW_MODE_LINE1 = 0,
    DRAW_MODE_LINE2 = 1,
    SHOW_MODE = 2,
};
ModeType workMode = ModeType::DRAW_MODE_LINE1;

//鼠标键盘控制
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_move_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_press_callback(GLFWwindow* window, GLint button, GLint action, GLint mod);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

//光照设置
GLfloat position[4] = { 2.0f, 0.0f, 0.0f, 1.0f };
GLfloat ambient[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat diffuse[4] = { 0.9f, 0.9f, 0.9f, 1.0f };
GLfloat specular[4] = { 0.5f, 0.5f, 0.5f, 1.0f };


int main()
{
    if (setupWindow() == -1) return -1;
    if (setupGlad() == -1) return -1;
    initDrawSetup();

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.47843f, 0.50196f, 0.56470f, 0.05f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (workMode == ModeType::DRAW_MODE_LINE1)
        {
            glLoadIdentity();

            //绘制点
            glPointSize(10.0f);
            glColor3f(1.0, 0.0, 0.0);
            glBegin(GL_POINTS);
            for (int i = 0; i < tot1; ++i)
                glVertex2fv(&points1[i][0]);
            glEnd();

            //绘制线
            glBegin(GL_LINE_STRIP);
            for (int i = 0; i < tot1; ++i)
                glVertex2fv(&points1[i][0]);
            glEnd();

        }
        else if (workMode == ModeType::DRAW_MODE_LINE2)
        {
            glLoadIdentity();

            //绘制点
            glPointSize(10.0f);
            glColor3f(1.0, 0.0, 0.0);
            glBegin(GL_POINTS);
            for (int i = 0; i < tot1; ++i)
                glVertex2fv(&points1[i][0]);
            glEnd();

            //绘制线
            glBegin(GL_LINE_STRIP);
            for (int i = 0; i < tot1; ++i)
                glVertex2fv(&points1[i][0]);
            glVertex2fv(&points1[0][0]);
            glEnd();

            //绘制点
            glPointSize(10.0f);
            glColor3f(0.0, 1.0, 0.0);
            glBegin(GL_POINTS);
            for (int i = 0; i < tot2; ++i)
                glVertex2fv(&points2[i][0]);
            glEnd();

            //绘制线
            glBegin(GL_LINE_STRIP);
            for (int i = 0; i < tot2; ++i)
                glVertex2fv(&points2[i][0]);
            glEnd();
        }
        else if (workMode == ModeType::SHOW_MODE)
        {
            //设置投影矩阵
            glMatrixMode(GL_PROJECTION);
            glLoadMatrixf(glm::value_ptr(glm::perspective(90.0f, 1.0f, 0.3f, 1000.0f)));

            //设置Model矩阵
            glMatrixMode(GL_MODELVIEW);
            glLoadMatrixf(glm::value_ptr(glm::lookAt(glm::vec3(0.0, 1.0, -1.0),
                glm::vec3(0.0, 0.0, 0.0),
                glm::vec3(0.0, 1.0, 0.0)) * glm::rotate(glm::mat4(1.0f), theta, glm::vec3(1, 0, 0))));

            //设置Phong模型
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);
            glLightfv(GL_LIGHT0, GL_POSITION, position);
            glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
            glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
            glLightfv(GL_LIGHT0, GL_SPECULAR, specular);


            //绘制
            glColor3f(0.0f, 0.0f, 1.0f);
            for (int i = 0; i < tot1; ++i)
            {
                glBegin(GL_TRIANGLE_STRIP);
                for (int j = 0; j < tot2; ++j)
                {
                    int nxt = (i + 1) % tot1;
                    GLfloat radian1 = atan2(points1[i][1], points1[i][0]);
                    GLfloat radian2 = atan2(points1[nxt][1], points1[nxt][0]);
                    glVertex3f(points1[i][0] + cos(radian1) * points2[j][0], points2[j][1], points1[i][1] + points2[j][0] * sin(radian1));
                    glVertex3f(points1[nxt][0] + cos(radian2) * points2[j][0], points2[j][1], points1[nxt][1] + points2[j][0] * sin(radian2));
                }
                glEnd();
            }

        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}


int setupWindow()
{
    glfwInit();

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_move_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_press_callback);

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
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
    glEnable(GL_BLEND);
}


/*键盘控制*/
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
void framebuffer_size_callback(GLFWwindow* window, GLint width, GLint height)
{
    WINDOW_WIDTH = width;
    WINDOW_HEIGHT = height;
    glViewport(0, 0, width, height);
}
/*鼠标控制*/
GLdouble nowX, nowY;
void mouse_move_callback(GLFWwindow* window, GLdouble xpos, GLdouble ypos)
{
    GLfloat nowX_t = float((xpos - WINDOW_WIDTH / 2.0) / WINDOW_WIDTH) * 2.0;
    GLfloat nowY_t = float(0 - (ypos - WINDOW_HEIGHT / 2.0) / WINDOW_HEIGHT) * 2.0;
    if (workMode == ModeType::SHOW_MODE)
    {
        theta += (nowY_t - nowY);
    }
    nowX = nowX_t;
    nowY = nowY_t;
}
void mouse_press_callback(GLFWwindow* window, GLint button, GLint action, GLint mod)
{
    if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (workMode == ModeType::DRAW_MODE_LINE1)
        {
            points1[tot1][0] = nowX;
            points1[tot1][1] = nowY;
            points1[tot1][2] = 0;
            ++tot1;
        }
        else if (workMode == ModeType::DRAW_MODE_LINE2)
        {
            points2[tot2][0] = nowX;
            points2[tot2][1] = nowY;
            points2[tot2][2] = 0;
            ++tot2;
        }
    }
    if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        if (workMode == ModeType::DRAW_MODE_LINE1)
        {
            workMode = ModeType::DRAW_MODE_LINE2;
        }
        else if (workMode == ModeType::DRAW_MODE_LINE2)
        {
            workMode = ModeType::SHOW_MODE;
        }
    }
}
void scroll_callback(GLFWwindow* window, GLdouble xoffset, GLdouble yoffset)
{

}
