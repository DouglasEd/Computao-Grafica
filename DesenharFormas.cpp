#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>

#define PI 3.14159265358979323846

void desenharCilindroHori(float x, float y, float z, float radius, float height, float r, float g, float b, int slices) {
    float angleStep = 2.0f * PI / slices;

    // Definir a cor do cilindro
    glColor3f(r, g, b);

    // Transladar para a posição desejada
    glPushMatrix();
    glTranslatef(x, y, z);

    // Desenhar a lateral do cilindro
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= slices; i++) {
        float angle = i * angleStep;
        float xCoord = radius * cos(angle);
        float zCoord = radius * sin(angle);

        glVertex3f(xCoord, 0.0f, zCoord);           // Ponto na base inferior
        glVertex3f(xCoord, height, zCoord);         // Ponto na base superior
    }
    glEnd();

    // Desenhar a base inferior
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, 0.0f); // Centro da base inferior
    for (int i = 0; i <= slices; i++) {
        float angle = i * angleStep;
        float xCoord = radius * cos(angle);
        float zCoord = radius * sin(angle);

        glVertex3f(xCoord, 0.0f, zCoord); // Ponto na circunferência
    }
    glEnd();

    // Desenhar a base superior
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, height, 0.0f); // Centro da base superior
    for (int i = 0; i <= slices; i++) {
        float angle = i * angleStep;
        float xCoord = radius * cos(angle);
        float zCoord = radius * sin(angle);

        glVertex3f(xCoord, height, zCoord); // Ponto na circunferência
    }
    glEnd();

    glPopMatrix(); // Reverter a translação
}
void desenharCilindroVert(float x, float y, float z, float radius, float height, float r, float g, float b, int slices) {
    float angleStep = 2.0f * PI / slices;

    // Definir a cor do cilindro
    glColor3f(r, g, b);

    // Transladar para a posição desejada
    glPushMatrix();
    glTranslatef(x, y, z);

    // Desenhar a lateral do cilindro
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= slices; i++) {
        float angle = i * angleStep;
        float xCoord = radius * cos(angle);
        float yCoord = radius * sin(angle);

        glVertex3f(xCoord, yCoord, 0.0f);           // Ponto na base inferior
        glVertex3f(xCoord, yCoord, height);         // Ponto na base superior
    }
    glEnd();

    // Desenhar a base inferior
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, 0.0f); // Centro da base
    for (int i = 0; i <= slices; i++) {
        float angle = i * angleStep;
        float xCoord = radius * cos(angle);
        float yCoord = radius * sin(angle);

        glVertex3f(xCoord, yCoord, 0.0f); // Ponto na circunferência
    }
    glEnd();

    // Desenhar a base superior
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, height); // Centro da base
    for (int i = 0; i <= slices; i++) {
        float angle = i * angleStep;
        float xCoord = radius * cos(angle);
        float yCoord = radius * sin(angle);

        glVertex3f(xCoord, yCoord, height); // Ponto na circunferência
    }
    glEnd();

    glPopMatrix(); // Reverter a translação
}
void desenharCubo(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax, float r, float g, float b) {
    glColor3f(r, g, b);  
    glBegin(GL_QUADS);
        // Frente
        glVertex3f(xMin, yMin, zMax);
        glVertex3f(xMax, yMin, zMax);
        glVertex3f(xMax, yMax, zMax);
        glVertex3f(xMin, yMax, zMax);
        // Trás
        glVertex3f(xMin, yMin, zMin);
        glVertex3f(xMax, yMin, zMin);
        glVertex3f(xMax, yMax, zMin);
        glVertex3f(xMin, yMax, zMin);
        // Topo
        glVertex3f(xMin, yMax, zMax);
        glVertex3f(xMax, yMax, zMax);
        glVertex3f(xMax, yMax, zMin);
        glVertex3f(xMin, yMax, zMin);
        // Fundo
        glVertex3f(xMin, yMin, zMax);
        glVertex3f(xMax, yMin, zMax);
        glVertex3f(xMax, yMin, zMin);
        glVertex3f(xMin, yMin, zMin);
        // Lado direito
        glVertex3f(xMax, yMin, zMax);
        glVertex3f(xMax, yMin, zMin);
        glVertex3f(xMax, yMax, zMin);
        glVertex3f(xMax, yMax, zMax);
        // Lado esquerdo
        glVertex3f(xMin, yMin, zMax);
        glVertex3f(xMin, yMin, zMin);
        glVertex3f(xMin, yMax, zMin);
        glVertex3f(xMin, yMax, zMax);
    glEnd();
}