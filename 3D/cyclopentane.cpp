#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string>
#include <cmath>
#include <iostream>
#include <GL/glut.h>
#include <string>
using namespace std;

// Global Variables
GLfloat cyclopentane_coords[6][3] = {
    {-6.25, 0, 0},
    {-5.25, 1.299038106, 0},
    {-4.25, 0, 0},
    {-4.25, -1.5, 0},
    {-6.25, -1.5, 0},
    {-3.25,1.299038106, 0}}; 

GLfloat HBr_coords[2][3] = {
    {-0.25, -0.9, 0},
    {-0.25, 0.9, 0},
};

GLfloat bromocyclopentane_coords[7][3] = {
    {3.75, 0, 0},
    {4.75, 1.299038106, 0},
    {5.75, 0, 0},
    {5.75, -1.5, 0},
    {3.75, -1.5, 0},
    {6.4,0.8, 0.5},
    {6.75,-0.599038106, -0.3}}; 

GLfloat pa_coords[9][3] = {
    {-3, 0, 0},
    {-2, 0, 0},
    {-2.5, -0.5, 0},
    {-2.5, 0.5, 0},
    {1.5, 0, 0},
    {2.5, 0, 0},
    {2.146446609, 0.353553391, 0},
    {2.146446609, -0.353553391, 0}};

GLfloat cyclopentane_orig_coords[6][3] = {
    {-6.25, 0, 0},
    {-5.25, 1.299038106, 0},
    {-4.25, 0, 0},
    {-4.25, -1.5, 0},
    {-6.25, -1.5, 0},
    {-3.25,1.299038106, 0}}; 

GLfloat HBr_orig_coords[2][3] = {
    {-0.25, -0.9, 0},
    {-0.25, 0.9, 0},
};

int selectedObject = 3;
bool drawThatAxis = 0;
bool lightEffect = 1;
int drawLegend = 1;
GLdouble sphereRadius = 0.4;
GLdouble cylinderRadius = 0.2;
GLint resolution = 100;
GLint slices = resolution, stacks = resolution;


// defining time counters for the animation.
int time_cnt = 0;
int t1 = 135, t2 = 160, t3 = 600;

// Animation variables
int camera = 1;
int animation = 0, merging = 0, merge_cnt = 0, merge_pause = 20, to_print = 1, calc = 1, is_rotate = 0;
GLdouble rot_angle = 0;
GLdouble HbrcylinderRadius = 0;
GLdouble CCcylinderRadius = 0.2;
GLdouble delta_CC = cylinderRadius / (t2 - t1);
GLdouble delta_HBr = delta_HBr;

// Viewer options (GluLookAt)
float fovy = 60.0, aspect = 1.0, zNear = 1.0, zFar = 100.0;

// Mouse modifiers
float depth = 8;
float phi = 0, theta = 0;
float downX, downY;
bool leftButton = false, middleButton = false;

// colors
GLfloat oxygen[3] = {1.0, 0.5, 0.0};    // (O - Golden)
GLfloat nitrogen[3] = {0.5, 0.3, 0.5};  // (N - Blue)
GLfloat phosphate[3] = {1.0, 0.5, 0.0}; // (P - Orange)
GLfloat carbon[3] = {0.7, 0.5, 0.7};    // (C - Grey)
GLfloat flourine[3] = {1, 0, 0};         //  (S - Red)
GLfloat hydrogen[3] = {0.0, 0.0, 1.0};  // (H - Blue)
GLfloat white[3] = {1.0, 1.0, 1.0};
GLfloat black[3] = {1.0, 1.0, 1.0};

/* Prototypes */
void draw_atom(GLfloat color[3]);
void setLightColor(GLfloat light_color[3]);
void renderCylinder(float x1, float y1, float z1, float x2, float y2, float z2, float radius, GLUquadricObj *quadrilc);
void drawAxis();
void reshape(int w, int h);
void mouseCallback(int button, int state, int x, int y);
void motionCallback(int x, int y);
void keyboardCallback(unsigned char ch, int x, int y);
void displayCallback(void);
void buildDisplayList();
void options_menu(int input);
void initMenu();

void displayLegend()
{

    glPushMatrix();
    glRotatef(40, 0, 0, 1);
    setLightColor(white);
    string legend_disp_1 = "Use W/A (along X), S/D(along Y), 5/8(along Z) to Translate";
    string legend_disp_2 = "Use Mouse: Hold Scroll and Drag to Zoom In/Out";
    string legend_disp_3 = "Use Mouse: Left Click and Drag to Rotate Axis";
    string legend_disp_4 = "Press Enter to Start/Pause animation";
    string legend_disp_5 = "Press Space to Start/Pause rotation";
    string legend_disp_6 = "Press R to Reset animation";
    string legend_disp_7 = "Press + to Add/Remove Axis";
    // string legend_disp_8 = "Press - to Change Lighting effect";
    string legend_disp_9 = "Press Esc to Close Window";
    string legend_disp_10 = "Press L to Toggle Legend";

    glRasterPos3f(4, 4.1, 0);
    for (int i = 0; i < legend_disp_1.size(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, legend_disp_1[i]);
    }
    glRasterPos3f(4, 3.8, 0);
    for (int i = 0; i < legend_disp_2.size(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, legend_disp_2[i]);
    }
    glRasterPos3f(4, 3.5, 0);
    for (int i = 0; i < legend_disp_3.size(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, legend_disp_3[i]);
    }
    glRasterPos3f(4, 3.2, 0);
    for (int i = 0; i < legend_disp_4.size(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, legend_disp_4[i]);
    }
    glRasterPos3f(4, 2.9, 0);
    for (int i = 0; i < legend_disp_5.size(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, legend_disp_5[i]);
    }
    glRasterPos3f(4, 2.6, 0);
    for (int i = 0; i < legend_disp_6.size(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, legend_disp_6[i]);
    }
    glRasterPos3f(4, 2.3, 0);
    for (int i = 0; i < legend_disp_7.size(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, legend_disp_7[i]);
    }
    glRasterPos3f(4, 2, 0);
    for (int i = 0; i < legend_disp_9.size(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, legend_disp_9[i]);
    }
    glRasterPos3f(4, 1.7, 0);
    for (int i = 0; i < legend_disp_10.size(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, legend_disp_10[i]);
    }
    glPopMatrix();
}

void draw_plus_arrow()
{
    // plus
    GLUquadric *myQuad;
    myQuad = gluNewQuadric();

    setLightColor(nitrogen);
    renderCylinder(pa_coords[0][0], pa_coords[0][1], pa_coords[0][2], pa_coords[1][0], pa_coords[1][1], pa_coords[1][2], 0.1, myQuad);
    renderCylinder(pa_coords[2][0], pa_coords[2][1], pa_coords[2][2], pa_coords[3][0], pa_coords[3][1], pa_coords[3][2], 0.1, myQuad);

    // arrow
    setLightColor(nitrogen);
    renderCylinder(pa_coords[4][0], pa_coords[4][1], pa_coords[4][2], pa_coords[5][0], pa_coords[5][1], pa_coords[5][2], 0.1, myQuad);
    renderCylinder(pa_coords[6][0], pa_coords[6][1], pa_coords[6][2], pa_coords[5][0], pa_coords[5][1], pa_coords[5][2], 0.1, myQuad);
    renderCylinder(pa_coords[7][0], pa_coords[7][1], pa_coords[7][2], pa_coords[5][0], pa_coords[5][1], pa_coords[5][2], 0.1, myQuad);
}
void draw_cyclopentane(GLfloat center[3])
{
    for (int i = 0; i < 6; i++)
    {
        glPushMatrix();
        glTranslatef(cyclopentane_coords[i][0], cyclopentane_coords[i][1], cyclopentane_coords[i][2]);
        draw_atom(carbon);
        glPopMatrix();
    }

    GLUquadric *myQuad;
    myQuad = gluNewQuadric();

    for(int i=0;i<5;i++){
        setLightColor(white);
        if(i==0){
            renderCylinder(cyclopentane_coords[0][0], cyclopentane_coords[0][1], cyclopentane_coords[0][2],cyclopentane_coords[4][0], cyclopentane_coords[4][1], cyclopentane_coords[4][2],
                   cylinderRadius, myQuad);
        }
        else if(i==1 || i==2){
            renderCylinder(cyclopentane_coords[i-1][0], cyclopentane_coords[i-1][1], cyclopentane_coords[i-1][2],cyclopentane_coords[i][0], cyclopentane_coords[i][1], cyclopentane_coords[i][2],
                   cylinderRadius, myQuad);
        }
        else{
            renderCylinder(cyclopentane_coords[i][0], cyclopentane_coords[i][1], cyclopentane_coords[i][2],
                   cyclopentane_coords[i-1][0], cyclopentane_coords[i-1][1], cyclopentane_coords[i-1][2],
                   cylinderRadius, myQuad);
        }
    }
    renderCylinder(cyclopentane_coords[2][0], cyclopentane_coords[2][1], cyclopentane_coords[2][2],
                   cyclopentane_coords[5][0], cyclopentane_coords[5][1], cyclopentane_coords[5][2],
                   cylinderRadius, myQuad);
}

void draw_HBr(GLfloat center[3])
{
    glPushMatrix();
    glTranslatef(HBr_coords[0][0], HBr_coords[0][1], HBr_coords[0][2]);
    draw_atom(hydrogen);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(HBr_coords[1][0], HBr_coords[1][1], HBr_coords[1][2]);
    draw_atom(flourine);
    glPopMatrix();

    GLUquadric *myQuad;
    myQuad = gluNewQuadric();

    glColor3fv(white);
    setLightColor(white);
    renderCylinder(HBr_coords[1][0], HBr_coords[1][1], HBr_coords[1][2],
                   HBr_coords[0][0], HBr_coords[0][1], HBr_coords[0][2],
                   cylinderRadius, myQuad);
}

void draw_bromocyclopentane(GLfloat center[3])
{
    for (int i = 0; i < 6; i++)
    {
        glPushMatrix();
        glTranslatef(bromocyclopentane_coords[i][0], bromocyclopentane_coords[i][1], bromocyclopentane_coords[i][2]);
        draw_atom(carbon);
        glPopMatrix();
    }
    glPushMatrix();
    glTranslatef(bromocyclopentane_coords[6][0], bromocyclopentane_coords[6][1], bromocyclopentane_coords[6][2]);
    draw_atom(flourine);
    glPopMatrix();

    GLUquadric *myQuad;
    myQuad = gluNewQuadric();

    for(int i=0;i<5;i++){
        setLightColor(white);
        if(i==0){
            renderCylinder(bromocyclopentane_coords[0][0], bromocyclopentane_coords[0][1], bromocyclopentane_coords[0][2],bromocyclopentane_coords[4][0], bromocyclopentane_coords[4][1], bromocyclopentane_coords[4][2],
                   cylinderRadius, myQuad);
        }
        else if(i==1 || i==2){
            renderCylinder(bromocyclopentane_coords[i-1][0], bromocyclopentane_coords[i-1][1], bromocyclopentane_coords[i-1][2],bromocyclopentane_coords[i][0], bromocyclopentane_coords[i][1], bromocyclopentane_coords[i][2],
                   cylinderRadius, myQuad);
        }
        else{
            renderCylinder(bromocyclopentane_coords[i][0], bromocyclopentane_coords[i][1], bromocyclopentane_coords[i][2],
                   bromocyclopentane_coords[i-1][0], bromocyclopentane_coords[i-1][1], bromocyclopentane_coords[i-1][2],
                   cylinderRadius, myQuad);
        }
    }
    renderCylinder(bromocyclopentane_coords[2][0], bromocyclopentane_coords[2][1], bromocyclopentane_coords[2][2],
                   bromocyclopentane_coords[5][0], bromocyclopentane_coords[5][1], bromocyclopentane_coords[5][2],
                   cylinderRadius, myQuad);
    renderCylinder(bromocyclopentane_coords[2][0], bromocyclopentane_coords[2][1], bromocyclopentane_coords[2][2],
                   bromocyclopentane_coords[6][0], bromocyclopentane_coords[6][1], bromocyclopentane_coords[6][2],
                   cylinderRadius, myQuad);
}

void translate_cyclopentane(char key)
{
    int n = 6;
    GLfloat delta = 0.25;
    if (key == 'w')
    {
        for (int i = 0; i < n; i++)
        {
            cyclopentane_coords[i][1] += delta;
        }
    }
    else if (key == 'a')
    {
        for (int i = 0; i < n; i++)
        {
            cyclopentane_coords[i][0] -= delta;
        }
    }
    else if (key == 's')
    {
        for (int i = 0; i < n; i++)
        {
            cyclopentane_coords[i][1] -= delta;
        }
    }
    else if (key == 'd')
    {
        for (int i = 0; i < n; i++)
        {
            cyclopentane_coords[i][0] += delta;
        }
    }
    else if (key == '8')
    {
        for (int i = 0; i < n; i++)
        {
            cyclopentane_coords[i][2] += delta;
        }
    }
    else if (key == '5')
    {
        for (int i = 0; i < n; i++)
        {
            cyclopentane_coords[i][2] -= delta;
        }
    }
}

void translate_plus_arrow(char key)
{
    int n = 8;
    GLfloat delta = 0.25;
    if (key == 'w')
    {
        for (int i = 0; i < n; i++)
        {
            pa_coords[i][1] += delta;
        }
    }
    else if (key == 'a')
    {
        for (int i = 0; i < n; i++)
        {
            pa_coords[i][0] -= delta;
        }
    }
    else if (key == 's')
    {
        for (int i = 0; i < n; i++)
        {
            pa_coords[i][1] -= delta;
        }
    }
    else if (key == 'd')
    {
        for (int i = 0; i < n; i++)
        {
            pa_coords[i][0] += delta;
        }
    }
    else if (key == '8')
    {
        for (int i = 0; i < n; i++)
        {
            pa_coords[i][2] += delta;
        }
    }
    else if (key == '5')
    {
        for (int i = 0; i < n; i++)
        {
            pa_coords[i][2] -= delta;
        }
    }
}

void translate_HBr(char key)
{
    int n = 2;
    GLfloat delta = 0.25;
    if (key == 'w')
    {
        for (int i = 0; i < n; i++)
        {
            HBr_coords[i][1] += delta;
        }
    }
    else if (key == 'a')
    {
        for (int i = 0; i < n; i++)
        {
            HBr_coords[i][0] -= delta;
        }
    }
    else if (key == 's')
    {
        for (int i = 0; i < n; i++)
        {
            HBr_coords[i][1] -= delta;
        }
    }
    else if (key == 'd')
    {
        for (int i = 0; i < n; i++)
        {
            HBr_coords[i][0] += delta;
        }
    }
    else if (key == '8')
    {
        for (int i = 0; i < n; i++)
        {
            HBr_coords[i][2] += delta;
        }
    }
    else if (key == '5')
    {
        for (int i = 0; i < n; i++)
        {
            HBr_coords[i][2] -= delta;
        }
    }
}

void translate_bromocyclopentane(char key)
{
    int n = 7;
    GLfloat delta = 0.25;
    if (key == 'w')
    {
        for (int i = 0; i < n; i++)
        {
            bromocyclopentane_coords[i][1] += delta;
        }
    }
    else if (key == 'a')
    {
        for (int i = 0; i < n; i++)
        {
            bromocyclopentane_coords[i][0] -= delta;
        }
    }
    else if (key == 's')
    {
        for (int i = 0; i < n; i++)
        {
            bromocyclopentane_coords[i][1] -= delta;
        }
    }
    else if (key == 'd')
    {
        for (int i = 0; i < n; i++)
        {
            bromocyclopentane_coords[i][0] += delta;
        }
    }
    else if (key == '8')
    {
        for (int i = 0; i < n; i++)
        {
            bromocyclopentane_coords[i][2] += delta;
        }
    }
    else if (key == '5')
    {
        for (int i = 0; i < n; i++)
        {
            bromocyclopentane_coords[i][2] -= delta;
        }
    }
}


GLdouble width, height; /* window width and height */
int wd;                 /* GLUT window handle */

void init(void)
{
    width = 1280.0;
    height = 800.0;
}

void reshape(int w, int h)
{
    /* save new screen dimensions */
    width = (GLdouble)w;
    height = (GLdouble)h;

    /* tell OpenGL to use the whole window for drawing */
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);

    /* do an orthographic parallel projection with the coordinate
     system set to first quadrant, limited by screen/window size */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, width, 0.0, height);

    aspect = width / height;
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    init(); // Initialization

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DEPTH);

    glutInitWindowSize((int)width, (int)height);

    wd = glutCreateWindow("cyclopentane + HBr -> bromocyclopentane" /* title */);

    glutReshapeFunc(reshape);

    setLightColor(white);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glutDisplayFunc(displayCallback);

    // motion
    glutMouseFunc(mouseCallback);
    glutMotionFunc(motionCallback);

    // keyboard functions
    glutKeyboardFunc(keyboardCallback);

    /* start the GLUT main loop */
    glutMainLoop();

    return 0;
}

// Sphere
void draw_atom(GLfloat color[3])
{

    // Set Sphere Color
    glColor3fv(color);
    setLightColor(color);

    GLUquadric *myQuad;
    myQuad = gluNewQuadric();

    // Draw sphere
    gluSphere(myQuad, sphereRadius, slices, stacks);
}

void setLightColor(GLfloat light_color[3])
{
    // Light Options
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat shine[] = {100.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_color);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
    glMaterialfv(GL_FRONT, GL_SHININESS, shine);
}

void renderCylinder(float x1, float y1, float z1, float x2, float y2, float z2, float radius, GLUquadricObj *quadric)
{
    float vx = x2 - x1;
    float vy = y2 - y1;
    float vz = z2 - z1;
    float ax, rx, ry, rz;
    float len = sqrt(vx * vx + vy * vy + vz * vz);

    glPushMatrix();
    glTranslatef(x1, y1, z1);
    if (fabs(vz) < 0.0001)
    {
        glRotatef(90, 0, 1, 0);
        ax = 57.2957795 * -atan(vy / vx);
        if (vx < 0)
        {
        }
        rx = 1;
        ry = 0;
        rz = 0;
    }
    else
    {
        ax = 57.2957795 * acos(vz / len);
        if (vz < 0.0)
            ax = -ax;
        rx = -vy * vz;
        ry = vx * vz;
        rz = 0;
    }
    glRotatef(ax, rx, ry, rz);
    gluQuadricOrientation(quadric, GLU_OUTSIDE);
    gluCylinder(quadric, radius, radius, len, slices, stacks);
    glPopMatrix();
}

void drawAxis()
{

    float originAxis[3] = {-4, -4, -4};
    float xAxis[3] = {-2, -4, -4};
    float yAxis[3] = {-4, -2, -4};
    float zAxis[3] = {-4, -4, -2};

    glDisable(GL_LIGHTING);
    glPushMatrix();
    glLineWidth(10.0);

    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3fv(originAxis);
    glVertex3fv(xAxis);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3fv(originAxis);
    glVertex3fv(yAxis);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3fv(originAxis);
    glVertex3fv(zAxis);
    glEnd();

    glPopMatrix();
    glEnable(GL_LIGHTING);
}

/* Callbacks */
void mouseCallback(int button, int state, int x, int y)
{
    downX = x;
    downY = y;
    leftButton = ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN));
    middleButton = ((button == GLUT_MIDDLE_BUTTON) && (state == GLUT_DOWN));
}

void motionCallback(int x, int y)
{
    if (leftButton) // Rotate
    {
        phi += (x - downX) / 4.0;
        theta += (downY - y) / 4.0;
    }
    if (middleButton) // Scale
    {
        if (depth + (downY - y) / 10.0 < zFar - 10 && depth + (downY - y) / 10.0 > zNear + 3)
            depth += (downY - y) / 10.0;
    }
    downX = x;
    downY = y;

    glutPostRedisplay();
}

void keyboardCallback(unsigned char key, int x, int y)
{
    if (key == 'a' || key == 'A')
    {
        // cout << "Key pressed: A\n";
        translate_bromocyclopentane('a');
        translate_cyclopentane('a');
        translate_HBr('a');
        translate_plus_arrow('a');
    }
    if (key == 'w' || key == 'W')
    {
        // cout << "Key pressed: W\n";
        translate_bromocyclopentane('w');
        translate_cyclopentane('w');
        translate_HBr('w');
        translate_plus_arrow('w');
    }
    if (key == 's' || key == 'S')
    {
        // cout << "Key pressed: S\n";
        translate_bromocyclopentane('s');
        translate_cyclopentane('s');
        translate_HBr('s');
        translate_plus_arrow('s');
    }
    if (key == 'd' || key == 'D')
    {
        // cout << "Key pressed: D\n";
        translate_bromocyclopentane('d');
        translate_cyclopentane('d');
        translate_HBr('d');
        translate_plus_arrow('d');
    }
    if (key == '8')
    {
        // cout << "Key pressed: D\n";
        translate_bromocyclopentane('8');
        translate_cyclopentane('8');
        translate_HBr('8');
        translate_plus_arrow('8');
    }
    if (key == '5')
    {
        // cout << "Key pressed: D\n";
        translate_bromocyclopentane('5');
        translate_cyclopentane('5');
        translate_HBr('5');
        translate_plus_arrow('5');
    }
    if (key == '+')
    {
        drawThatAxis = 1 - drawThatAxis;
    }
    glutPostRedisplay();
}

void displayCallback(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovy, aspect, zNear, zFar);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // gluLookAt(eyex, eyey, eyez, atx, aty, atz, upx, upy, upz);
    gluLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0);

    // Motion Options
    glTranslatef(0.0, 0.0, -depth);
    glRotatef(-theta, 1.0, 0.0, 0.0);
    glRotatef(phi, 0.0, 1.0, 0.0);

    // Axis x, y and z Toggle
    if (drawThatAxis)
    {
        drawAxis();
    }

    // Light Effect Toggle :)
    if (lightEffect)
    {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
    }
    else
    {
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
    }

    // glCallList(3);
    GLfloat all_center[3] = {0, 0, 0};

    draw_cyclopentane(all_center);
    draw_bromocyclopentane(all_center);
    draw_HBr(all_center);
    draw_plus_arrow();
    glFlush();
}