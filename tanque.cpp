#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

// Funções para desenhar as formas básicas
void desenharCubo(float x, float y, float z, float r, float g, float b);
void desenharCilindro(float x, float y, float z, float r, float g, float b);

// Funções para desenhar as partes do tanque
void desenharCorpoPrincipal();
void desenharTorre(float anguloTorre);
void desenharCano(float anguloTorre);
void desenharEsteiras();
void desenharRodas();
/*
// Shaders
const char* vertexShaderSource = R"(
#version 330 core
layout(location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
)";

const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;

uniform vec3 objectColor;

void main() {
    FragColor = vec4(objectColor, 1.0);
}
)";
*/
// Variáveis globais
float anguloTorre = 0.0f;
/*
// Função para inicializar shaders
GLuint criarShaderProgram(const char* vertexSource, const char* fragmentSource) {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}
*/
// Funções de desenho
void desenharCubo(float x, float y, float z, float r, float g, float b) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glBegin(GL_QUADS);
    glColor3f(r, g, b);

    // Face frontal
    glVertex3f(-0.5f, -0.5f,  0.5f);
    glVertex3f( 0.5f, -0.5f,  0.5f);
    glVertex3f( 0.5f,  0.5f,  0.5f);
    glVertex3f(-0.5f,  0.5f,  0.5f);

    // Face traseira
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f, -0.5f);
    glVertex3f( 0.5f,  0.5f, -0.5f);
    glVertex3f(-0.5f,  0.5f, -0.5f);

    // Face superior
    glVertex3f(-0.5f,  0.5f, -0.5f);
    glVertex3f( 0.5f,  0.5f, -0.5f);
    glVertex3f( 0.5f,  0.5f,  0.5f);
    glVertex3f(-0.5f,  0.5f,  0.5f);

    // Face inferior
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f,  0.5f);
    glVertex3f(-0.5f, -0.5f,  0.5f);

    // Face lateral esquerda
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f,  0.5f, -0.5f);
    glVertex3f(-0.5f,  0.5f,  0.5f);
    glVertex3f(-0.5f, -0.5f,  0.5f);

    // Face lateral direita
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f,  0.5f, -0.5f);
    glVertex3f(0.5f,  0.5f,  0.5f);
    glVertex3f(0.5f, -0.5f,  0.5f);

    glEnd();
    glPopMatrix();
}

void desenharCilindro(float x, float y, float z, float r, float g, float b) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glColor3f(r, g, b);
    GLUquadric* quad = gluNewQuadric();
    gluCylinder(quad, 0.5, 0.5, 1.0, 32, 32);
    gluDeleteQuadric(quad);
    glPopMatrix();
}

void desenharCorpoPrincipal() {
    glPushMatrix();
    glScalef(3.0f, 1.0f, 2.0f); // Escalonamento para criar o formato retangular alongado
    desenharCubo(0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 0.5f); // Cor: vermelho
    glPopMatrix();
}

void desenharTorre(float anguloTorre) {
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f); // Posiciona a torre em cima do corpo principal
    glRotatef(anguloTorre, 0.0f, 1.0f, 0.0f); // Rotação para simular o giro da torre
    glScalef(1.0f, 0.5f, 1.0f); // Escalonamento para robustez
    desenharCilindro(0.0f, 0.0f, 0.0f, 0.8f, 0.8f, 0.8f); // Cor: cinza
    glPopMatrix();
}

void desenharCano(float anguloTorre) {
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f); // Posiciona o cano na torre
    glRotatef(anguloTorre, 0.0f, 1.0f, 0.0f); // Alinha com a torre
    glTranslatef(1.0f, 0.0f, 0.0f); // Posiciona o cano à frente da torre
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f); // Rotação para alinhar com a direção correta
    glScalef(0.1f, 0.1f, 2.0f); // Escalonamento para o comprimento do cano
    desenharCilindro(0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f); // Cor: cinza claro
    glPopMatrix();
}

void desenharEsteiras() {
    glPushMatrix();
    glTranslatef(1.5f, -0.5f, 1.0f); // Posiciona a esteira à direita
    glScalef(3.0f, 0.2f, 0.5f); // Escalonamento para o comprimento das esteiras
    desenharCubo(0.0f, 0.0f, 0.0f, 0.2f, 0.2f, 0.2f); // Cor: cinza escuro
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5f, -0.5f, -1.0f); // Posiciona a esteira à esquerda
    glScalef(3.0f, 0.2f, 0.5f);
    desenharCubo(0.0f, 0.0f, 0.0f, 0.2f, 0.2f, 0.2f);
    glPopMatrix();
}

void desenharRodas() {
    for (int i = 0; i < 4; ++i) {
        glPushMatrix();
        glTranslatef(1.5f - i, -0.7f, 1.0f); // Posiciona as rodas à direita
        glScalef(0.5f, 0.5f, 0.1f); // Escalonamento para ajustar o tamanho das rodas
        desenharCilindro(0.0f, 0.0f, 0.0f, 0.1f, 0.1f, 0.1f); // Cor: preto
        glPopMatrix();

        glPushMatrix();
        glTranslatef(1.5f - i, -0.7f, -1.0f); // Posiciona as rodas à esquerda
        glScalef(0.5f, 0.5f, 0.1f);
        desenharCilindro(0.0f, 0.0f, 0.0f, 0.1f, 0.1f, 0.1f);
        glPopMatrix();
    }
}

void desenharTanque(float anguloTorre) {
    desenharCorpoPrincipal();
    desenharTorre(anguloTorre);
    desenharCano(anguloTorre);
    desenharEsteiras();
    desenharRodas();
}
void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 0.1, 100.0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Aplicar rotações
    glRotatef(anguloX, 1.0f, 0.0f, 0.0f); 
    glRotatef(anguloY, 0.0f, 1.0f, 0.0f); 
    glRotatef(anguloZ, 0.0f, 0.0f, 1.0f); 

    desenharCorpo();
    desenharEsteiras();
    desenharTorre();
    desenharCanhao();

    glutSwapBuffers();
}
void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_RIGHT:
            anguloY += 5.0f; // Rotaciona em torno do eixo Y
            break;
        case GLUT_KEY_LEFT:
            anguloY -= 5.0f; // Rotaciona em torno do eixo Y
            break;
        case GLUT_KEY_UP:
            anguloX -= 5.0f; // Rotaciona em torno do eixo X
            break;
        case GLUT_KEY_DOWN:
            anguloX += 5.0f; // Rotaciona em torno do eixo X
            break;
    }
    glutPostRedisplay(); 
}
// Função principal
int main(int argc, char** argv) {
    /*if (!glfwInit()) {
        std::cerr << "Erro ao inicializar o GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Tanque em OpenGL", NULL, NULL);
    if (!window) {
        std::cerr << "Erro ao criar a janela" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewInit();

    GLuint shaderProgram = criarShaderProgram(vertexShaderSource, fragmentShaderSource);
    glUseProgram(shaderProgram);

    // Configurações de câmera e projeção (simples)
    glm::mat4 view = glm::lookAt(glm::vec3(5.0f, 3.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
    GLint projLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Desenho do tanque
        glPushMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
        desenharTanque(anguloTorre);
        glPopMatrix();

        glfwSwapBuffers(window);
        glfwPollEvents();

        // Atualização da rotação da torre
        anguloTorre += 0.5f;
        if (anguloTorre > 360.0f) anguloTorre -= 360.0f;
    }

    glfwTerminate();
    return 0;*/
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Tanque 3D");
    glewInit();
    init();
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    return 0;
}
