// glsl.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include "glee.h"
#include <gl/glu.h>
#include <gl/glut.h>

using namespace std;

void init();
void render();
void reshape(int width, int height);
void setShaders();
char* readShaderSource(const char* fileName);

GLhandleARB programObject;
GLfloat lightPosition[] = {30.0f, 30.0f, 30.0f};
GLfloat eyePosition[] = {0.0f, 0.0f, 3.0f};
GLfloat ambient[] = {1.0f, 0.0f, 0.0f, 1.0f};
GLfloat lightColor[] = {1.0f, 1.0f, 1.0f};
GLfloat Ns = 80.0f;
GLfloat attenuation = 0.1f;

int _tmain(int argc, _TCHAR* argv[])
{
	glutInit(&argc, (char**)argv);
	glutInitWindowPosition(400, 200);
	glutInitWindowSize(800, 480);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("glsl test");
	init();
	glutDisplayFunc(render);
	glutReshapeFunc(reshape);
	glutIdleFunc(render);
	glutMainLoop();

	system("pause");
	return 0;
}

void init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	setShaders();
}

void setShaders()
{
	// ��ȡԴ�ļ�constdf
	char *vertexShader = readShaderSource("sample.vert");
	char *fragShader = readShaderSource("sample.frag");

	// ����������ɫ��Ƭ����ɫ�����󲢷�������
	GLhandleARB vertexShaderObject, fragShaderObject;
	
	vertexShaderObject = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	fragShaderObject = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);

	//// �����հ׳�����󲢷�������
	programObject = glCreateProgramObjectARB();

	// glShaderSourceARB() ������:
    // GLhandleARB shader        --- ��ɫ��
    // GLuint nstrings           --- �ַ��������ж��ٸ�Ԫ�� �����Ӿ�ֻ��1���ַ���
    // const GLcharARB **strings --- �ַ�������
    // GLint *lengths            --- ��Ӧ�ַ�������ĳ������� NULL��ʾ�����ַ�����null����
	// ����ɫ���ַ����ύ���հ���ɫ��
	const char* constVertexShader = vertexShader;
	const char* constFragShader = fragShader;
	glShaderSourceARB(vertexShaderObject, 1, &constVertexShader, NULL);
	glShaderSourceARB(fragShaderObject, 1, &constFragShader, NULL);

	// ����Դ��
	glCompileShaderARB(vertexShaderObject);
	glCompileShaderARB(fragShaderObject);

	// ����ɫ��������ӵ��������
	glAttachObjectARB(programObject, vertexShaderObject);
	glAttachObjectARB(programObject, fragShaderObject);

	// ���ӳ������
	glLinkProgramARB(programObject);

	// ��װ�������
	glUseProgramObjectARB(programObject);

	// �ͷ��ַ���
	free(vertexShader);
	free(fragShader);
}

//GLfloat lightPosition[] = {30.0f, 30.0f, 30.0f};
//GLfloat eyePosition[] = {0.0f, 10.0f, 3.0f};
//GLfloat ambient[] = {1.0f, 0.0f, 0.0f, 1.0f};
//GLfloat lightColor[] = {1.0f, 1.0f, 1.0f};
//GLfloat Ns = 8.0f;
//GLfloat attenuation = 0.1f;

void render()
{
	cout << "render" << endl;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	
	// �����shader���и�ֵ
	glUseProgram(programObject);
	glUniform3f(glGetUniformLocation(programObject, "lightPosition"), lightPosition[0], lightPosition[1], lightPosition[2]);
	glUniform3f(glGetUniformLocation(programObject, "eyePosition"), eyePosition[0], eyePosition[1], eyePosition[2]);
	glUniform4f(glGetUniformLocation(programObject, "ambient"), ambient[0], ambient[1], ambient[2], ambient[3]);
	glUniform4f(glGetUniformLocation(programObject, "lightColor"), lightColor[0], lightColor[1], lightColor[2], lightColor[3]);
	glUniform1f(glGetUniformLocation(programObject, "Ns"), Ns);
	glUniform1f(glGetUniformLocation(programObject, "attenuation"), attenuation);

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -20.0f);
	glutSolidTeapot(4.0f);
	glPopMatrix();

	glutSwapBuffers();
}

char* readShaderSource(const char* fileName)
{
	FILE *filePointer;
    char *content = nullptr;
    int count=0;

	if(fileName == nullptr) return nullptr;

    fopen_s(&filePointer, fileName, "rt");
	if(filePointer == nullptr) return nullptr;

    fseek(filePointer, 0, SEEK_END);
    count = ftell(filePointer);
    rewind(filePointer);
    if (count > 0)
    {
        content = (char *)malloc(sizeof(char) * (count + 1));
        count = fread(content,sizeof(char), count, filePointer);
        content[count] = '\0';
    }
    fclose(filePointer);
    return content;
}

void reshape(int width, int height)
{
	cout << "reshape" << endl;
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(57, (GLfloat)width / height, 0.1f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(eyePosition[0], eyePosition[1], eyePosition[2], 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}








