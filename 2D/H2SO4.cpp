#include <bits/stdc++.h>
#include <GL/glut.h>
using namespace std;

double FinalX = 0.0;
double FinalY = 0.0;

struct color
{
    double r, g, b;
};

color red = {1, 0, 0};
color green = {0, 1, 0};
color blue = {0, 0, 1};
color yellow = {1, 1, 0};
color cyan = {0, 1, 1};
color magenta = {1, 0, 1};
color white = {1, 1, 1};
color black = {0, 0, 0};

double H2SO4_centers[7][2] = {{ -150, 0}, {0, 0}, {150, 0}, { -106.06, 106.06}, {106.06, 106.06}, {106.06, -106.06}, { -106.06, -106.06}};
color H2SO4_colors[7] = {red, blue, red, green, green, green, green};
double H2SO4_radii[7] = {25, 50, 25, 25, 25, 25, 25};

void draw_circle(double x, double y, double r, color c)
{
    glColor3f(c.r, c.g, c.b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++)
    {
        double angle = 2 * 3.1416 * i / 360;
        double x1 = x + r * cos(angle);
        double y1 = y + r * sin(angle);
        glVertex2f(x1, y1);
    }
    glEnd();
}
void draw_H2SO4(double centers[7][2], double radii[7], color colors[7])
{
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);

    for (int k = 0; k < 7; k++) {
        glVertex2f(centers[1][0], centers[1][1]);
        glVertex2f(centers[k][0], centers[k][1]);
    }

    glEnd();

    for (int k = 0; k < 7; k++)
    {
        draw_circle(centers[k][0], centers[k][1], radii[k], colors[k]);
    }
}

void translate_H2SO4(char key)
{
    int n = 7;
    glClear(GL_COLOR_BUFFER_BIT);
    double delta = 10;

    if (key == 'w')
    {
        for (int i = 0; i < n; i++)
        {
            H2SO4_centers[i][1] += delta;
        }
    }
    else if (key == 'a')
    {
        for (int i = 0; i < n; i++)
        {
            H2SO4_centers[i][0] -= delta;
        }
    }
    else if (key == 's')
    {
        for (int i = 0; i < n; i++)
        {
            H2SO4_centers[i][1] -= delta;
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            H2SO4_centers[i][0] += delta;
        }
    }
    draw_H2SO4(H2SO4_centers, H2SO4_radii, H2SO4_colors);

    glFlush();
}

// scale_h2so4 Polygon along its center
void scale_h2so4(char zoom)
{
    double scale_h2so4;
    glClear(GL_COLOR_BUFFER_BIT);

    if (zoom == 'i')
    {
        scale_h2so4 = 1.05;
    }
    else
        scale_h2so4 = 0.95;

    double d_old_1 = sqrt(pow(H2SO4_centers[0][0] - H2SO4_centers[1][0], 2) + pow(H2SO4_centers[0][1] - H2SO4_centers[1][1], 2));
    double d_old_2 = sqrt(pow(H2SO4_centers[1][0] - H2SO4_centers[3][0], 2) + pow(H2SO4_centers[1][1] - H2SO4_centers[3][1], 2));
    double d_new_1 = scale_h2so4 * d_old_1;
    double d_new_2 = scale_h2so4 * d_old_2;

    double m1 = abs((H2SO4_centers[0][1] - H2SO4_centers[1][1]) / (H2SO4_centers[0][0] - H2SO4_centers[1][0]));
    double m2 = abs((H2SO4_centers[2][1] - H2SO4_centers[1][1]) / (H2SO4_centers[2][0] - H2SO4_centers[1][0]));
    double m3 = abs((H2SO4_centers[3][1] - H2SO4_centers[1][1]) / (H2SO4_centers[3][0] - H2SO4_centers[1][0]));
    double m4 = abs((H2SO4_centers[4][1] - H2SO4_centers[1][1]) / (H2SO4_centers[4][0] - H2SO4_centers[1][0]));
    double m5 = abs((H2SO4_centers[5][1] - H2SO4_centers[1][1]) / (H2SO4_centers[5][0] - H2SO4_centers[1][0]));
    double m6 = abs((H2SO4_centers[6][1] - H2SO4_centers[1][1]) / (H2SO4_centers[6][0] - H2SO4_centers[1][0]));

    int flags[12];
    for (int k = 0; k < 12; k++) {
        flags[k] = 1;
    }
    if (H2SO4_centers[0][0] < H2SO4_centers[1][0])
        flags[0] = -1;
    if (H2SO4_centers[0][1] < H2SO4_centers[1][1])
        flags[1] = -1;
    if (H2SO4_centers[2][0] < H2SO4_centers[1][0])
        flags[2] = -1;
    if (H2SO4_centers[2][1] < H2SO4_centers[1][1])
        flags[3] = -1;
    if (H2SO4_centers[3][0] < H2SO4_centers[1][0])
        flags[4] = -1;
    if (H2SO4_centers[3][1] < H2SO4_centers[1][1])
        flags[5] = -1;
    if (H2SO4_centers[4][0] < H2SO4_centers[1][0])
        flags[6] = -1;
    if (H2SO4_centers[4][1] < H2SO4_centers[1][1])
        flags[7] = -1;
    if (H2SO4_centers[5][0] < H2SO4_centers[1][0])
        flags[8] = -1;
    if (H2SO4_centers[5][1] < H2SO4_centers[1][1])
        flags[9] = -1;
    if (H2SO4_centers[6][0] < H2SO4_centers[1][0])
        flags[10] = -1;
    if (H2SO4_centers[6][1] < H2SO4_centers[1][1])
        flags[11] = -1;

    H2SO4_centers[0][0] = H2SO4_centers[1][0] + flags[0] * d_new_1 / (sqrt(1 + m1 * m1));
    H2SO4_centers[0][1] = H2SO4_centers[1][1] + flags[1] * m1 * d_new_1 / (sqrt(1 + m1 * m1));
    H2SO4_centers[2][0] = H2SO4_centers[1][0] + flags[2] * d_new_1 / (sqrt(1 + m2 * m2));
    H2SO4_centers[2][1] = H2SO4_centers[1][1] + flags[3] * m2 * d_new_1 / (sqrt(1 + m2 * m2));
    H2SO4_centers[3][0] = H2SO4_centers[1][0] + flags[4] * d_new_2 / (sqrt(1 + m3 * m3));
    H2SO4_centers[3][1] = H2SO4_centers[1][1] + flags[5] * m3 * d_new_2 / (sqrt(1 + m3 * m3));
    H2SO4_centers[4][0] = H2SO4_centers[1][0] + flags[6] * d_new_2 / (sqrt(1 + m4 * m4));
    H2SO4_centers[4][1] = H2SO4_centers[1][1] + flags[7] * m4 * d_new_2 / (sqrt(1 + m4 * m4));
    H2SO4_centers[5][0] = H2SO4_centers[1][0] + flags[8] * d_new_2 / (sqrt(1 + m5 * m5));
    H2SO4_centers[5][1] = H2SO4_centers[1][1] + flags[9] * m5 * d_new_2 / (sqrt(1 + m5 * m5));
    H2SO4_centers[6][0] = H2SO4_centers[1][0] + flags[10] * d_new_2 / (sqrt(1 + m6 * m6));
    H2SO4_centers[6][1] = H2SO4_centers[1][1] + flags[11] * m6 * d_new_2 / (sqrt(1 + m6 * m6));

    for (int i = 0; i < 7; i++)
    {
        H2SO4_radii[i] *= scale_h2so4;
    }
    draw_H2SO4(H2SO4_centers, H2SO4_radii, H2SO4_colors);
    glFlush();
}

void displayMe(void)
{

    glClear(GL_COLOR_BUFFER_BIT);
    //glClearColor(1.0, 1.0, 1.0, 0.0);

    draw_H2SO4(H2SO4_centers, H2SO4_radii, H2SO4_colors);

    glFlush();
}

void rotate_H2SO4(double angle)
{
    glClear(GL_COLOR_BUFFER_BIT);

    double xc = H2SO4_centers[1][0];
    double yc = H2SO4_centers[1][1];

    for (int i = 0; i < 7; i++)
    {
        H2SO4_centers[i][0] -= xc;
        H2SO4_centers[i][1] -= yc;
    }

    for (int i = 0; i < 7; i++)
    {
        double x = H2SO4_centers[i][0];
        double y = H2SO4_centers[i][1];

        H2SO4_centers[i][0] = x * cos(angle) - y * sin(angle);
        H2SO4_centers[i][1] = x * sin(angle) + y * cos(angle);
    }

    for (int i = 0; i < 7; i++)
    {
        H2SO4_centers[i][0] += xc;
        H2SO4_centers[i][1] += yc;
    }

    draw_H2SO4(H2SO4_centers, H2SO4_radii, H2SO4_colors);
    glFlush();
}

// Get Co-Ordinates after Mouse Click
void mouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN)
    {
        FinalX = x;
        FinalY = y;
    }
}

// Mouse Rotation function
void mouse_move(int x, int y)
{
    // Calculate mouse position change
    int delta_x = x - FinalX;

    // Rotate the figure
    double angle = delta_x * 0.05f;
    rotate_H2SO4(angle);

    // Change Final Mouse Position
    FinalX = x;
    FinalY = y;
}

void keyUser(unsigned char key, int x, int y)
{
    if (key == 'a' || key == 'A')
    {
        cout << "Key pressed: A\n";
        translate_H2SO4('a');
    }
    if (key == 'w' || key == 'W')
    {
        cout << "Key pressed: W\n";
        translate_H2SO4('w');
    }
    if (key == 's' || key == 'S')
    {
        cout << "Key pressed: S\n";
        translate_H2SO4('s');
    }
    if (key == 'd' || key == 'D')
    {
        cout << "Key pressed: D\n";
        translate_H2SO4('d');
    }
    if (key == 'i' || key == 'I')
    {
        cout << "Key pressed: I\n";
        scale_h2so4('i');
    }
    if (key == 'o' || key == 'O')
    {
        cout << "Key pressed: O\n";
        scale_h2so4('o');
    }
}

signed main(int argc, char **argv)
{
    cout << "Menu: \n";
    cout << "Key     Action \n";
    cout << "D:      Right Translation\n";
    cout << "A:      Left Translation\n";
    cout << "W:      Up Translation\n";
    cout << "S:      Down Translation\n";
    cout << "I:      Zoom In\n";
    cout << "O:      Zoom Out\n\n";

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Window");
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-500, 500, -500, 500);
    glutDisplayFunc(displayMe);
    glutKeyboardFunc(keyUser);
    glutMotionFunc(mouse_move);
    glutMouseFunc(mouse);
    glutMainLoop();
}