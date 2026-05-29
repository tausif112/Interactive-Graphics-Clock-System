#include <GL/glut.h>
#include <cmath>
#include <ctime>
#include <string>

#define PI 3.14159265358979323846

int W = 800, H = 600;
int cx = 400, cy = 300;
int R = 210;

float theme = 0;

// ---------------- Pixel ----------------
void putPixel(int x, int y)
{
    if (x >= 0 && x <= W && y >= 0 && y <= H)
    {
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
    }
}

// ---------------- Bresenham Line Algorithm ----------------
void bresenhamLine(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while (true)
    {
        putPixel(x1, y1);

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;

        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }

        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

// ---------------- Thick Line using Bresenham ----------------
void thickLine(int x1, int y1, int x2, int y2, int thickness)
{
    for (int i = -thickness; i <= thickness; i++)
    {
        bresenhamLine(x1 + i, y1, x2 + i, y2);
        bresenhamLine(x1, y1 + i, x2, y2 + i);
    }
}

// ---------------- Midpoint Circle Algorithm ----------------
void circlePoints(int xc, int yc, int x, int y)
{
    putPixel(xc + x, yc + y);
    putPixel(xc - x, yc + y);
    putPixel(xc + x, yc - y);
    putPixel(xc - x, yc - y);
    putPixel(xc + y, yc + x);
    putPixel(xc - y, yc + x);
    putPixel(xc + y, yc - x);
    putPixel(xc - y, yc - x);
}

void midpointCircle(int xc, int yc, int r)
{
    int x = 0;
    int y = r;
    int d = 1 - r;

    circlePoints(xc, yc, x, y);

    while (x < y)
    {
        x++;

        if (d < 0)
        {
            d += 2 * x + 1;
        }
        else
        {
            y--;
            d += 2 * (x - y) + 1;
        }

        circlePoints(xc, yc, x, y);
    }
}

// ---------------- Filled Circle by Scan Conversion ----------------
void filledCircle(int xc, int yc, int r)
{
    for (int y = -r; y <= r; y++)
    {
        int xLimit = (int)sqrt(r * r - y * y);
        bresenhamLine(xc - xLimit, yc + y, xc + xLimit, yc + y);
    }
}

// ---------------- Circular Clipping ----------------
bool insideClock(int x, int y)
{
    int dx = x - cx;
    int dy = y - cy;
    return dx * dx + dy * dy <= R * R;
}

void clippedPixel(int x, int y)
{
    if (insideClock(x, y))
        putPixel(x, y);
}

// ---------------- Text ----------------
void drawText(float x, float y, std::string text)
{
    glRasterPos2f(x, y);
    for (char c : text)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
}

// ---------------- Background ----------------
void drawBackground()
{
    glColor3f(0.02, 0.025, 0.05);

    for (int y = 40; y <= 560; y++)
        bresenhamLine(90, y, 710, y);
}

// ---------------- Clock Face ----------------
void drawClockFace()
{
    drawBackground();

    if (theme == 0)
    {
        glColor3f(0.25, 0.04, 0.55);
        filledCircle(cx, cy, 210);

        glColor3f(0.20, 0.10, 0.70);
        filledCircle(cx, cy, 175);

        glColor3f(0.05, 0.32, 0.75);
        filledCircle(cx, cy, 135);

        glColor3f(0.00, 0.60, 0.75);
        filledCircle(cx, cy, 85);
    }
    else
    {
        glColor3f(0.10, 0.35, 0.45);
        filledCircle(cx, cy, 210);

        glColor3f(0.08, 0.45, 0.55);
        filledCircle(cx, cy, 160);

        glColor3f(0.02, 0.65, 0.70);
        filledCircle(cx, cy, 100);
    }

    // Concentric boundary circles using Midpoint Circle Algorithm
    glColor3f(1.0, 0.55, 0.0);
    glPointSize(3);
    midpointCircle(cx, cy, 212);
    midpointCircle(cx, cy, 208);
    midpointCircle(cx, cy, 204);

   // glColor3f(1.0, 1.0, 1.0);
   // glPointSize(2);
   // midpointCircle(cx, cy, 185);
   // midpointCircle(cx, cy, 145);
   // midpointCircle(cx, cy, 105);

    // Hour and minute markings
    for (int i = 0; i < 60; i++)
    {
        double angle = PI / 2 - i * 2 * PI / 60;

        int outerX = cx + 195 * cos(angle);
        int outerY = cy + 195 * sin(angle);

        int innerR = (i % 5 == 0) ? 165 : 180;

        int innerX = cx + innerR * cos(angle);
        int innerY = cy + innerR * sin(angle);

        if (i % 5 == 0)
        {
            glColor3f(1.0, 1.0, 1.0);
            thickLine(innerX, innerY, outerX, outerY, 2);
        }
        else
        {
            glColor3f(0.90, 0.75, 1.0);
            thickLine(innerX, innerY, outerX, outerY, 0);
        }
    }

    // Clock numbers
    glColor3f(1.0, 1.0, 1.0);

    for (int i = 1; i <= 12; i++)
    {
        double angle = PI / 2 - i * 2 * PI / 12;

        int tx = cx + 145 * cos(angle);
        int ty = cy + 145 * sin(angle);

        std::string num = std::to_string(i);

        if (i >= 10)
            drawText(tx - 10, ty - 8, num);
        else
            drawText(tx - 5, ty - 8, num);
    }
}

// ---------------- Clock Hands ----------------
void drawClockHands()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

    int hour = ltm->tm_hour % 12;
    int minute = ltm->tm_min;
    int second = ltm->tm_sec;

    double secondAngle = PI / 2 - second * 2 * PI / 60;
    double minuteAngle = PI / 2 - (minute + second / 60.0) * 2 * PI / 60;
    double hourAngle = PI / 2 - (hour + minute / 60.0) * 2 * PI / 12;

    int hourX = cx + 85 * cos(hourAngle);
    int hourY = cy + 85 * sin(hourAngle);

    int minuteX = cx + 135 * cos(minuteAngle);
    int minuteY = cy + 135 * sin(minuteAngle);

    int secondX = cx + 165 * cos(secondAngle);
    int secondY = cy + 165 * sin(secondAngle);

    // Hour hand - thickest
    glColor3f(1.0, 1.0, 1.0);
    thickLine(cx, cy, hourX, hourY, 5);

    // Minute hand - medium
    glColor3f(0.80, 0.95, 1.0);
    thickLine(cx, cy, minuteX, minuteY, 3);

    // Second hand - thinnest
    glColor3f(1.0, 0.0, 0.0);
    thickLine(cx, cy, secondX, secondY, 1);

    // Center point
    glColor3f(1.0, 0.0, 0.0);
    filledCircle(cx, cy, 9);

    glColor3f(1.0, 1.0, 1.0);
    filledCircle(cx, cy, 4);
}

// ---------------- Display ----------------
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawClockFace();
    drawClockHands();

    glFlush();
}

// ---------------- Animation Timer ----------------
void timer(int value)
{
    glutPostRedisplay();
    glutTimerFunc(1000, timer, 0);
}

// ---------------- Keyboard Interaction ----------------
void keyboard(unsigned char key, int x, int y)
{
    if (key == '1')
        theme = 0;

    if (key == '2')
        theme = 1;

    if (key == 27)
        exit(0);

    glutPostRedisplay();
}

// ---------------- Initialization ----------------
void init()
{
    glClearColor(0.93, 0.93, 0.93, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0, W, 0, H);

    glPointSize(2);
}

// ---------------- Main ----------------
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(W, H);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Interactive Graphics Clock System");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(1000, timer, 0);

    glutMainLoop();

    return 0;
}
