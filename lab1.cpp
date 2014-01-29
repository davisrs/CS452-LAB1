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

const int numpoints=4000; //4000 dots
//int counter=0; //I have no idea (Hint:from shapes.cpp)

GLuint vaoID, vboID;// these are the buffers that are going to be linked too

//initialize the polygons
void init(){
	//Generate random points for the dots
	
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
	
	/*
	glGenVertexArrays(1,&vaoID);//Tried doing it like dots.cpp did - didn't help'
	glBindVertexArray(vaoID);
	
	glGenBuffers(1,&vboID);
	glBindBuffer(GL_ARRAY_BUFFER,vboID);
	*/
	
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
        
}

//Draw Functions
void points(){
	glClear(GL_COLOR_BUFFER_BIT);//clear screen
	glDrawArrays(GL_POINTS,0,numpoints);//draws the points
	glFlush();//make sure the processes finish
}

//mouse control function
void mousepress(int button, int state, int x, int y){
	if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)//If right click
		exit(0);//exit the program
}

int main(int argc, char **argv){
        
	//intialize the window adn contex mangament library your using
	glutInit(&argc,argv);
	glutCreateWindow("dots");
        
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
        
      //initialize polygons
      init();
        
      //draw polygons
      glutDisplayFunc(points);
              
      //mouse controls
      glutMouseFunc(mousepress);
      
      //glut main loop
      glutMainLoop();
        
      return 0;
}
