#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include <stdio.h>

#define ROZ_X 100
#define ROZ_Y 100

static double surface[ROZ_X][ROZ_Y] = {0};

GLint vertices[8][3] = {
        {0, 0, 0},
        {0, 0, 3},
        {0, 1, 0},
        {0, 1, 3},
        {3, 0, 0},
        {3, 0, 3},
        {3, 1, 0},
        {3, 1, 3}
};

GLint vertices2[8][3] = {
        {1, 1, 1},
        {1, 1, 2},
        {1, 2, 1},
        {1, 2, 2},
        {2, 1, 1},
        {2, 1, 2},
        {2, 2, 1},
        {2, 2, 2}
};

GLint vertices3[8][3] = {
        {1, 2, 1},
        {1, 2, 2},
        {1, 3, 1},
        {1, 3, 1},
        {2, 2, 1},
        {2, 2, 2},
        {1, 3, 1},
        {1, 3, 1}
};


GLint faces[6][4] = {
        {1, 5, 7, 3},
        {5, 4, 6, 7},
        {4, 0, 2, 6},
        {3, 7, 6, 2},
        {0, 1, 3, 2},
        {0, 4, 5, 1}
};

GLfloat vertexColors[8][3] = {
        {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 1.0, 0.0}, {0.0, 1.0, 1.0},
        {1.0, 0.0, 0.0}, {1.0, 0.0, 1.0}, {1.0, 1.0, 0.0}, {1.0, 1.0, 1.0}
};

GLfloat KAT = 0, PI = 3.14, PX = -ROZ_X / 2, PY = -2, PZ = -ROZ_Y / 2;

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

void EnableOpenGL(HWND hwnd, HDC *, HGLRC *);

void DisableOpenGL(HWND, HDC, HGLRC);

void init();

void drawSurface(HDC);

void mountain(int, int, int, int, int);

void initSurface(int, int, int);


void initTexture(char *);

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow) {
    WNDCLASSEX wcex;
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

/* register window class */
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


    if (!RegisterClassEx(&wcex))
        return 0;

/* create main window */
    hwnd = CreateWindowEx(0,
                          "GLSample",
                          "OpenGL Sample",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          1024,
                          720,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hwnd, nCmdShow);

/* enable OpenGL for the window */
    EnableOpenGL(hwnd, &hDC, &hRC);

/* program main loop */
    init();
    initSurface(120,25,5);
    while (!bQuit) {
/* check for messages */
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
/* handle or dispatch messages */
            if (msg.message == WM_QUIT) {
                bQuit = TRUE;
            } else {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        } else {
/* OpenGL animation code goes here */
            drawSurface(hDC);
        }
    }

/* shutdown OpenGL */
    DisableOpenGL(hwnd, hDC, hRC);

/* destroy the window explicitly */
    DestroyWindow(hwnd);

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CLOSE:
            PostQuitMessage(0);
            break;

        case WM_DESTROY:
            return 0;

        case WM_KEYDOWN: {
            switch (wParam) {
                case VK_ESCAPE:
                    PostQuitMessage(0);
                    break;
                case VK_UP:
                    PX += sin(PI * KAT / 180);
                    PY = (surface[(int) PX * -1][(int) PZ * -1] + 2) * -1;
                    PZ += cos(PI * KAT / 180);
                    break;
                case VK_DOWN:
                    PX -= sin(PI * KAT / 180);
                    PY = (surface[(int) PX * -1][(int) PZ * -1] + 2) * -1;
                    PZ -= cos(PI * KAT / 180);
                    break;
                case VK_LEFT:
                    KAT += 4;
                    if (KAT > 360)
                        KAT -= 360;
                    break;
                case VK_RIGHT:
                    KAT -= 4;
                    if (KAT < 0)
                        KAT += 360;
                    break;
            }
        }
            break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void EnableOpenGL(HWND hwnd, HDC *hDC, HGLRC *hRC) {
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC(hwnd);

    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL(HWND hwnd, HDC hDC, HGLRC hRC) {
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}

void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,1,1,160);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    initTexture("../texture.bmp");
}

void drawSurface(HDC hDC) {
    glLoadIdentity();
    glRotatef(-KAT, 0, 1, 0);
    glTranslatef(PX, PY, PZ);
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0, 0, 0);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    for (int x = 0; x < ROZ_X - 1; x++)
        for (int y = 0; y < ROZ_Y - 1; y++) {
            glTexCoord2f(0, 0);
            glVertex3f(x,   surface[x][y], y);
            glTexCoord2f(0, 1);
            glVertex3f(x, surface[x][y + 1], y + 1);
            glTexCoord2f(1, 1);
            glVertex3f(x + 1, surface[x + 1][y + 1], y + 1);
            glTexCoord2f(1, 0);
            glVertex3f(x + 1, surface[x + 1][y], y);
        }
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glDisable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            glColor3fv((GLfloat*)&vertexColors[faces[i][j]]);
            glVertex3iv((GLint *) &vertices[faces[i][j]]);
            // which face
        }
    }
    glEnd();

    glBegin(GL_QUADS);
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            glColor3fv((GLfloat*)&vertexColors[faces[i][j]]);
            glVertex3iv((GLint *) &vertices2[faces[i][j]]);
            // which face
        }
    }
    glEnd();

    glBegin(GL_QUADS);
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            glColor3fv((GLfloat*)&vertexColors[faces[i][j]]);
            glVertex3iv((GLint *) &vertices3[faces[i][j]]);
            // which face
        }
    }
    glEnd();

    SwapBuffers(hDC);
}
void mountain(int px, int py, int r1, int r2, int wys){
    int i,j;
    for(i = -r1/2;i<r1/2;i++){
        for(j = -r1/2;j<r1/2;j++){
            if(2*sqrt(i*i+j*j)<r1){
                surface[(i+px+ROZ_X)%ROZ_X][(j+py+ROZ_Y)%ROZ_Y]+= min(wys, (r1 - 2*sqrt(i*i+j*j))*wys/(r1-r2));
            }
        }
    }
}


void initSurface(int quantity, int max_radius, int max_height){
    int a,r1,r2,px,py,height;
    for(a=0;a<quantity;a++){
        r1 = rand()*max_radius/RAND_MAX;
        r2 = rand()*(r1/2)/RAND_MAX;
        height = rand()*max_height/RAND_MAX;
        px = rand()*ROZ_X/RAND_MAX;
        py = rand()*ROZ_Y/RAND_MAX;
        if((px - r1) < 10) px+=10;
        if((py - r1) < 10) py+=10;

        mountain(px,py,r1,r2,height);
    }
}


void initTexture(char name[]){
    long i, size = 256 * 256 * 3;
    unsigned char buf[size];
    FILE *ws;
    if((ws = fopen(name,"rb")) == NULL){
        printf("ERROR");
        return;
    }
    fseek(ws,-size,SEEK_END);
    for(i = 0; i < size;i+=3){
        buf[i + 2] = getc(ws);
        buf[i + 1] = getc(ws);
        buf[i] = getc(ws);
    }
    fclose(ws);

    glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, buf);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glEnable(GL_TEXTURE_2D);
}
