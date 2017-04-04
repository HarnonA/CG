// Ultima alteração 04 Abril 2017 15:34

/*
 * Teclas usadas na navegação
 * w/s : frente/tras
 * a/d : esquerda/direita
 * z/x : cima/baixo
 * u/i : rotação equerda/direita
 */


/* -> todo
 * 1 deixa todo programa dependendo apenas de escalas e nao de pontos
 * 2 altura dos galpoes em relaçao ao solo
 * 3 portas, janelas, escadas e rampas
 */


#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <stdio.h>

/* Global variables */
char title[] = "3D Shapes";
int abc = 1;
float zoom=0;
float lx=0, ly=0,lz=0, angle = 2*1.8, up = 0, left=0;
double size = 0.5;
int t=0,u=0,v=0;

/* Initialize OpenGL Graphics */
void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

void cubo(double x, double y, double z);
void plataforma(double x, double y, double z){
	glBegin(GL_QUADS);
	glColor3f(1,0.8,0.2);
	// up face
	glVertex3f( 0, y, 0);
	glVertex3f(x, y, 0);
	glVertex3f(x, y,  z);
	glVertex3f( 0, y,  z);


	// Bottom face
	glVertex3f( x, 0,  z);
	glVertex3f(0, 0,  z);
	glVertex3f(0, 0, 0);
	glVertex3f( x, 0, 0);

	glEnd();


	glColor3f(1,1,1);
	glTranslated(0.45, 0, 0);
	int i = 0;
	for(i = 0; i < 6; i++){

	   cubo(0.1,1,0.1);
	   glTranslated(0, 0, 1);
	}
	glTranslated(-0.45,0,-6);


	// ##############################################
	glutPostRedisplay();
}

void cubo(double x, double y, double z){

	glBegin(GL_QUADS);
	//glColor3f(1,0.8,0.2);

	//baixo
	//glColor3f(tam,0,tam);     // up face
	glVertex3f( 0, 0, 0);
	glVertex3f( 0, 0, z);
	glVertex3f( x, 0, z);
	glVertex3f( x, 0, 0);

	//cima
	glVertex3f( 0, y, 0);
	glVertex3f( 0, y, z);
	glVertex3f( x, y, z);
	glVertex3f( x, y, 0);

	//atras
	glVertex3f( 0, 0, 0);
	glVertex3f( x, 0, 0);
	glVertex3f( x, y, 0);
	glVertex3f( 0, y, 0);

	//frente
	glVertex3f( 0, 0, z);
	glVertex3f( x, 0, z);
	glVertex3f( x, y, z);
	glVertex3f( 0, y, z);

	//esq
	glVertex3f( 0, 0, 0);
	glVertex3f( 0, 0, z);
	glVertex3f( 0, y, z);
	glVertex3f( 0, y, 0);

	//dir
	glVertex3f( x, 0, 0);
	glVertex3f( x, 0, z);
	glVertex3f( x, y, z);
	glVertex3f( x, y, 0);


	glEnd();

}


/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
   glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

   // Render a color-cube consisting of 6 quads with different colors
   glLoadIdentity();                 // Reset the model-view matrix
   gluLookAt(left,1,zoom+8,
   		   left,0,zoom,
   		   0,1,0);

   glRotatef(angle,t,u,v);
   glTranslatef(0,up,0);


   glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
      // Top face (y = 1.0f)
      // Define vertices in counter-clockwise (CCW) order with normal pointing out


   //===
   glColor3f(0.0f, 1, 0.0f); //grama na entrada
   glVertex3f( 4*size, -size,  4*size);
   glVertex3f(-4*size, -size,  4*size);
   glVertex3f(-4*size, -size, -4*size);
   glVertex3f( 4*size, -size, -4*size);


   glColor3f(0.8f, 0.8, 0.8f); //brita no final
   glVertex3f(-4*size, -size, -4*size);
   glVertex3f( 4*size, -size, -4*size);
   glVertex3f( 4*size, -size, -5*4*size);
   glVertex3f(-4*size, -size, -5*4*size);

   //===
   glEnd();  // fim do chao

//============================================
    /* fachada de 2 andares */

   glColor3f(1,0.8,0.2);
   // faixada 2 andares
   glTranslated(-1.5,0,0);
   cubo(3,2,1);

   // salao interior
   glTranslated(-1,0,-1);
   cubo(5,1,1);

   // plataformas
   glTranslated(0, 0, -6);
   plataforma(1,1,6);
   glTranslated(2, 0, 0);
   plataforma(1,1,6);
   glTranslated(2, 0, 0);
   plataforma(1,1,6);




   glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
}
void GerenciaMouse(int button, int state, int x, int y)
{
	//cout << "mouse" << endl;

   if (button == GLUT_LEFT_BUTTON)
      if (state == GLUT_DOWN) {  // Zoom-in

        	 abc += 5;


         //glutIdleFunc(spinDisplay);
      }
   if (button == GLUT_RIGHT_BUTTON)
      if (state == GLUT_DOWN) {  // Zoom-out
         abc -= 5;

      }

   glutPostRedisplay();
}


/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;

   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);

   // Set the aspect ratio of the clipping volume to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset
   // Enable perspective projection with fovy, aspect, zNear and zFar
   gluPerspective(45.0f, aspect, 0.1f, 100.0f);



}

void keyboard(int key, int a, int c){
	  float fraction = 0.1f;

	  switch(key) {
	  		case 'w':
	  			zoom -= 1;
	  			glutPostRedisplay();
	  			break;
	  		case 's':
	  			zoom += 1;
	  			glutPostRedisplay();
	  			break;
//	  		case 'a':
//	  			//left +=1;
//	  			angle -= 0.2f;
//	  			lx = sin(angle);
//	  			lz = -cos(angle);
//	  			glutPostRedisplay();
//	  			break;
//	  		case 'd':
//	  			//left -=1;
//	  			angle += 0.2f;
//	  			lx = sin(angle);
//	  			lz = -cos(angle);
//	  			glutPostRedisplay();
//	  			break;
	  		case 'z':
	  			up += 0.5;
	  			glutPostRedisplay();
	  			break;
	  		case 'x':
	  			up -= 0.5;
	  			glutPostRedisplay();
	  			break;
	  		case 'a':
//	  			angle+=15;
//	  			if(angle >= 360)
//	  				angle = 0;
//	  			u=1;
	  			left -=0.25;
	  			glutPostRedisplay();
	  			break;
	  		case 'd':
//	  			angle-=15;
//	  			if(angle <= 0)
//	  				angle = 360;
//	  			u=1;
	  			left += 0.25;
	  			glutPostRedisplay();
	  			break;

	  		case 'u':
	  			angle+=15;
	  			if(angle >= 360)
	  				angle = 0;
	  			u=1;
	  			glutPostRedisplay();
	  			break;

	  		case 'i':
	  			angle-=15;
	  			if(angle <= 0)
	  				angle = 360;
	  			u=1;
	  			glutPostRedisplay();
	  			break;

	  		case 27:
	  			exit(8);
	  			break;
	  		default:
	  			break;
	  	}


}

/* Main function: GLUT runs as a console application starting at main() */
int mainX(int argc, char** argv) {
   glutInit(&argc, argv);            // Initialize GLUT
   //glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
   glutInitWindowSize(640, 480);   // Set the window's initial width & height
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   glutCreateWindow(title);          // Create window with the given title

   glutDisplayFunc(display);       // Register callback handler for window re-paint event
   glutReshapeFunc(reshape);       // Register callback handler for window re-size event
   //glutMouseFunc(GerenciaMouse);
   glutKeyboardFunc(keyboard);

   initGL();                       // Our own OpenGL initialization
   glutMainLoop();                 // Enter the infinite event-processing loop
   return 0;
}
