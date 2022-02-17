
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <iostream>
#include <vector>


//窗口属性
unsigned int WINDOW_WIDTH = 1600;					//窗口宽度
unsigned int WINDOW_HEIGHT = 1200;				//窗口高度
GLFWwindow* window;
int setupWindow();

//初始化
int setupGlad();
void initDrawSetup();

//顶点数据
GLfloat points[10000][3];
int tot = 0;

//模式管理
enum class ModeType
{
    FPS_WORK_MODE = 0,
};
ModeType workMode = ModeType::FPS_WORK_MODE;

//鼠标键盘控制
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_move_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_press_callback(GLFWwindow* window, GLint button, GLint action, GLint mod);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);


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

        //绘制点
        glPointSize(10.0f);
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_POINTS);
        for(int i = 0;i < tot;++ i)
        {
            //std::cerr << "Draw\n";
            glVertex2fv(&points[i][0]);
        }
        glEnd();

        //绘制Bezier曲线
        if (tot >= 4)
        {
            for (int begin = 0; begin + 3 < tot; begin += 3)
            {
                //begin,begin+3为端点，begin+1，begin+2为控制点
                glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &points[begin][0]);
                glEnable(GL_MAP1_VERTEX_3);
                glColor3f(0.0, 0.0, 1.0f);
                glLineWidth(2.0);
                glMapGrid1f(100, 0.0, 1.0);
                glEvalMesh1(GL_LINE, 0, 100);
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
   // glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
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
    nowX = float((xpos - WINDOW_WIDTH / 2.0) / WINDOW_WIDTH) * 2.0;
    nowY = float(0 - (ypos - WINDOW_HEIGHT / 2.0) / WINDOW_HEIGHT) * 2.0;
    //std::cerr << "(" << nowX << ", " << nowY << ")\n";
}
void mouse_press_callback(GLFWwindow* window, GLint button, GLint action, GLint mod)
{
    if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT)
    {
        points[tot][0] = nowX;
        points[tot][1] = nowY;
        points[tot][2] = 0;
        ++tot;
        //std::cerr << "Add Point: " << "(" << nowX << ", " << nowY << ")\n";
    }
}
void scroll_callback(GLFWwindow* window, GLdouble xoffset, GLdouble yoffset)
{

}
