//Designed to see if you can draw things.

//Create and draw three different 2D objects.
//Examples are star, points (at least 1500), square, triangle, trapezoid, lines (at least 6), any kind of polygon, and etc. Stick with 2D.
//Use mouse controls: left click cycles through drawing the different objects and right click to exit the program.

//Use different GLenum modes aka OpenGL primitives along with GL_QUADS and etc.

//run command: 
//	g++ lab1.cpp -lglut -lGL -lGLEW -g
//	./a.out

//Lab1

//INCLUDES
#include "initShaders.h"
#include "vec.h"
#include <cstdlib>
#include <ctime>
using namespace std;

const int numpoints=4000; //4000 dots = shape 1
int counter=0; //used for cycling through the shapes

//vertexIDs
GLuint vaoID, vboID;// these are the buffers that are going to be linked too

//vertices for shape 2 = triangle
GLfloat vertexarray[]={0.5f,-0.5f,0.0f,0.0f,0.5f,0.0f,-0.5f,-0.5f,0.0f};// vertices that are drawn x,y,z ...
//indices of the triangle (shape 2)
GLubyte indices[3]={0,1,2};


//initialize the polygons

//Draw Functions

void points(){//4000 points = shape 1
	glClear(GL_COLOR_BUFFER_BIT);//clear screen
	
	vec2 points[numpoints];
	float k;
	float j;
	srand(time(0)); //Sees the random
	
	for(int i=0;i<numpoints;i++){
		switch(i%4){
			case 0:
			j=((float) rand()/RAND_MAX);
			k=((float) rand()/RAND_MAX-1);
			//cout << " j: "<< j << " k: " << k << endl;
			points[i]=vec2(j,k);
			break;
			case 1:
			j=((float) rand()/RAND_MAX-1);
			k=((float) rand()/RAND_MAX-1);
			//cout << " j: "<< j << " k: " << k << endl;
			points[i]=vec2(j,k);
			break;
			case 2:
			j=((float) rand()/RAND_MAX);
			k=((float) rand()/RAND_MAX);
			//cout << " j: "<< j << " k: " << k << endl;
			points[i]=vec2(j,k);
			break;
			case 3:
			j=((float) rand()/RAND_MAX-1);
			k=((float) rand()/RAND_MAX);
			//cout << " j: "<< j << " k: " << k << endl;
			points[i]=vec2(j,k);
			break;
			}
	}
	
	//Generation of vao's and vbo's
	glGenVertexArrays(1,&vaoID);
	glGenBuffers(1,&vboID);

	//binding of voa's and vbo's
	glBindVertexArray(vaoID);
	glBindBuffer(GL_ARRAY_BUFFER,vboID);
	
	//allocate buffer and fill with vertice data
	glBufferData(GL_ARRAY_BUFFER,sizeof(points),points,GL_STATIC_DRAW);  
	
	//ShaderInfo shaders[]={shaders GLenum, filename}, {...} ,{end with GL_NONE, null};
	ShaderInfo shaders[]={
  { GL_VERTEX_SHADER , "vertexshader.glsl"} ,
  { GL_FRAGMENT_SHADER , "fragmentshader.glsl"},
  { GL_NONE , NULL} 
  };
        
	//initShaders(shaders);
	initShaders(shaders);
        
	//Enable Vertex Attribute
	glEnableVertexAttribArray(0);
	//setup vertex pointers
	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,(void*)0);
        
	glDrawArrays(GL_POINTS,0,numpoints);//draws the points
	glFlush();//make sure the processes finish
}

void triangle1(){//Triangle = shape 2
  glClear(GL_COLOR_BUFFER_BIT);//clears the screen
  
  glGenVertexArrays(1, &vaoID);//generates object name for Vertex Array Objects
  glBindVertexArray(vaoID);//bind the object to the array

  glGenBuffers(1, &vboID);//generates object name for the Vertex Buffer Object
  glBindBuffer(GL_ARRAY_BUFFER, vboID);//bind the object to the array
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexarray), vertexarray, GL_STATIC_DRAW);//allocates the memory of the vertices

 ShaderInfo shaders[]={//create the shader specified by my initshaders 
  { GL_VERTEX_SHADER , "vertexshader1.glsl"} ,
  { GL_FRAGMENT_SHADER , "fragmentshader1.glsl"},
  { GL_NONE , NULL} 
  };

  initShaders(shaders);//creates shaders
  
  glEnableVertexAttribArray(0);//enables the vertex attribute index 
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);//specified the start the vertice array used to the draw

  glDrawArrays(GL_TRIANGLES, 0, 3);//draws array
  glFlush();//makes sure the prcesses finish
}

void drawscene(){
  switch(counter%3){//easy way to switch throw functions
    case 0:
      //cout << " points ";
      glutDisplayFunc(triangle1);
      glutPostRedisplay();//sets flags for opengl to redraw the display
      break;
    case 1:
      //cout << " triangle ";
      glutDisplayFunc(points);
      glutPostRedisplay();
      break;
    case 2:
      //cout << " triangle ";
      glutDisplayFunc(triangle1);
      glutPostRedisplay();
      break;
  }
}

//mouse control function
void mousepress(int button, int state, int x, int y){
	if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)//If right click
		exit(0);//exit the program
	else if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
		counter++;
		//cout << " leftclicked " << counter%3;
		drawscene();
	}//left click changes the shape color
		
}

void idle(void){
  glutPostRedisplay();
}

int main(int argc, char **argv){
        
	//intialize the window adn contex mangament library your using
	glutInit(&argc,argv);
	glutCreateWindow("Lab 1");
        
      //specify with version of GL you are using
      glewExperimental=GL_TRUE;
	if(glewInit()){
		fprintf(stderr,"unable to initialize GLEW");
		exit(EXIT_FAILURE);
	}
	
	glutInitContextVersion(4, 3);
  glutInitContextProfile(GLUT_CORE_PROFILE|GLUT_COMPATIBILITY_PROFILE);
 
  const GLubyte* version=glGetString(GL_SHADING_LANGUAGE_VERSION);
  fprintf(stderr,"Opengl glsl version %s\n", version);

  version=glGetString(GL_VERSION);
  fprintf(stderr,"Opengl version %s\n", version);
        
              
      //mouse controls
      glutMouseFunc(mousepress);
              
      //draw polygons
      glutDisplayFunc(drawscene);

      //glut main loop
      glutMainLoop();//sets opengl state in a neverending loop
        
      return 0;
}
