#include "bsp5.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

static qboolean gl_initialized = false;
GLFWwindow* window;

void InitGL() {
    /* Initialize the library */
    glfwInit();

    /* Create a windowed mode window and its OpenGL context */
	int width = 640;
	int height = 480;
	glfwWindowHint(GLFW_DOUBLEBUFFER, 0);
    window = glfwCreateWindow(width, height, "qbsp debug draw", NULL, NULL);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

	double right = width / 4;
	double bottom = height / 4;
	glOrtho(-right, right, -bottom, bottom, -1000, 1000);
	gluLookAt(100, 100, 100, 0, 0, 0, 0, 0, 1);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.2, 0.4, 0.6, 1.0);
	glColor3ub(0xFF, 0xFF, 0xFF);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwSwapBuffers(window);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	gl_initialized = true;
}

void Draw_ClearBounds (void)
{
}

void Draw_AddToBounds (vec3_t v)
{
}

void Draw_DrawFace (face_t *f)
{
	if (!gl_initialized) InitGL();

	glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
	int i;
	for (i = 2; i < f->numpoints; i++) {
		DrawTri(f->pts[0], f->pts[i-1], f->pts[i]);
	}

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	for (i = 0; i < f->numpoints; i++) {
		glVertex3fv(f->pts[i]);
		glVertex3fv(f->pts[(i+1)%f->numpoints]);
	}
	glEnd();

	glfwSwapBuffers(window);
}

void Draw_ClearWindow (void)
{
	if (!gl_initialized) InitGL();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwSwapBuffers(window);
}

void Draw_SetRed (void)
{
	glColor3ub(0xFF, 0x00, 0x00);
}

void Draw_SetGrey (void)
{
	glColor3ub(0x80, 0x80, 0x80);
}

void Draw_SetBlack (void)
{
	glColor3ub(0x00, 0x00, 0x00);
}

void DrawPoint (vec3_t v)
{
	glBegin(GL_POINTS);
	glVertex3fv(v);
	glEnd();
}

void DrawLeaf (node_t *l, int color)
{
	face_t *f;
	for (f = l->faces; f; f = f->next) {
		Draw_DrawFace(f);
	}
}

void DrawBrush (brush_t *b)
{
}

void DrawWinding (winding_t *w)
{
}

void DrawTri (vec3_t p1, vec3_t p2, vec3_t p3)
{
	glBegin(GL_TRIANGLES);
	glVertex3fv(p1);
	glVertex3fv(p2);
	glVertex3fv(p3);
	glEnd();
}

void DrawPortal (portal_t *portal)
{
}
