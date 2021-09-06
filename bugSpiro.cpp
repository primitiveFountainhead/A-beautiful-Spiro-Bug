
#include <GL/glut.h>
#include <math.h>
#include<stdlib.h>
#include <iostream>

using namespace std; 

#define H .0175
#define MAXITR 1000  

 double R, r, a;

void display();
void reshape(int, int);
void init()
{
    glClearColor(0, 0, 0, 1.0); //Deafault at clear color
}

int main(int argc, char **argv)
{
   
    cout << "Enter outer radius\n";
    cin >> R;
    cout << "Enter inner radius \n";
    cin >> r;
    cout << "Enter the distance of hole from inner circle\n";
    cin >> a;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowPosition(200, 150);
    glutInitWindowSize(1000, 1000);



    glutCreateWindow("This is a window");
    
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    init(); //initialisation

    glutMainLoop();
}

void display()
{

    double A,  sk1, sw1, ck1, ck2, cw1, ck, cw, sk, sw, temp;
    sk1 = 0;
    sk =  sin(r*H/R);
    sw1 = 0;
    sw =  sin((R-r)*H/R);

    ck1 = 1;
    ck  = cos(r*H/R);
    cw1 = 1;
    cw = cos((R - r)*H/R);

    //int X, Y;
    double X, Y;
    A = R - r;
    //X = round(A + a);
    X = A+a;
    Y = 0;

    //int Step = round(2*MAXITR*M_PI*R/(H*min(r, R-r))) +1;
    int Step = 1000000000;
    //cout << ck2  << " " << cw2; 

    glClear(GL_COLOR_BUFFER_BIT);//Clears buffer to deafault bgc
    glLoadIdentity(); //Reset cordinate system

    int i = 0;
    glPointSize(1.0);
    //draw
   
    
    do{
        if(X >= A+a || Y >=A+a){
            cout << "_________\n";
            cout << "!XY:    \n";
            cout << "sk1:" << sk1 << "  ck1:" << ck1 << "\n";
            cout << "sw1:" << sw1 << "  cw1:" << cw1 << "\n";
            
        
        }

        
        cout << "X: " << X << "\n Y:" << Y << "\n"; 
         glBegin(GL_POINTS);
        glVertex2f(X,Y);
        temp = sk1;
        sk1 = sk*ck1 + ck*sk1;
        ck1 = ck*ck1 - sk*temp;

        temp = sw1;
        sw1 = sw*cw1 + ck*sw1;
        cw1 = cw*cw1 - sw*temp;

        //X =round(A*ck1 + a*cw1);
        //Y = round(A*sk1 - a*sw1);
        X =A*ck1 + a*cw1;
        Y = A*sk1 - a*sw1;
        
        glEnd();

    glFlush();

    }while(/*(X <= A+a && Y <= A+a) && */(++i) <= Step );

    cout << "STEP: " << Step << "\n";

    

    
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);//Projection mode only to change projection
    glLoadIdentity();
    gluOrtho2D(-50, 50, -50, 50); //To set 2D cordinate space
    glMatrixMode(GL_MODELVIEW); //Always be in this mode, for drawing
}