#include <GL/glut.h>
#include <stdlib.h>

float angleX = 0.0f, angleY = 0.0f;
int colorFace = -1;

void init() {

    /*Bật kiểm tra chiều sâu*/
   glEnable(GL_DEPTH_TEST);
}
float color[][3] = {
    {1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {0.0, 0.0, 1.0},
    {1.0, 1.0, 0.0},
    {1.0, 0.0, 1.0},
    {0.0, 1.0, 1.0}
};

void changeColor(int face) {
    float r = (float)(rand()) / (float)(RAND_MAX);
    float g = (float)(rand()) / (float)(RAND_MAX);
    float b = (float)(rand()) / (float)(RAND_MAX);

    color[face][0] = r;
    color[face][1] = g; 
    color[face][2] = b;

}
void endChangeColor()
{
    colorFace = -1;
}
void setColor(int face)
{
    if(colorFace == face)
    {
        changeColor(face);
        endChangeColor();
        
    }
    glColor3f(color[face][0], color[face][1], color[face][2]);
    

}

void drawCube() {
    glBegin(GL_QUADS);
    GLfloat vertices[][3] = {
        {-1.0, -1.0, -1.0},
        { 1.0, -1.0, -1.0},
        { 1.0,  1.0, -1.0},
        {-1.0,  1.0, -1.0},
        {-1.0, -1.0,  1.0},
        { 1.0, -1.0,  1.0},
        { 1.0,  1.0,  1.0},
        {-1.0,  1.0,  1.0}
    };

    // Các mặt của hình lập phương
    GLubyte faces[][4] = {
        {0, 1, 2, 3}, // Mặt sau
        {4, 5, 6, 7}, // Mặt trước
        {0, 1, 5, 4}, // Mặt dưới
        {2, 3, 7, 6}, // Mặt trên
        {0, 3, 7, 4}, // Mặt trái
        {1, 2, 6, 5}  // Mặt phải
    };

    
    for (int i = 0; i < 6; i++) {
        setColor(i);
        
        for (int j = 0; j < 4; j++) {
            glVertex3fv(vertices[faces[i][j]]);
        }
    }

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    // lui khung hinh 
    glTranslatef(0.0f, 0.0f, -5.0f);
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);

    drawCube();
    
    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    float ratio = 1.0f * w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, ratio, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, w, h);
}

void keyboard(unsigned char key, int x, int y) {
    if (key >= '1' && key <= '6') {
        colorFace = key - '1';
    }
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_RIGHT:
            angleY += 5;
            break;
        case GLUT_KEY_LEFT:
            angleY -= 5;
            break;
        case GLUT_KEY_UP:
            angleX -= 5;
            break;
        case GLUT_KEY_DOWN:
            angleX += 5;
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Cube with OpenGL");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);

    glutMainLoop();
    return 0;
}
