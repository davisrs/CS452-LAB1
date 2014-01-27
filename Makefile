run: lab1.cpp
	g++ dots.cpp -lglut -lGLU -lGL -lGLEW -g
	
clean: 
	rm -f *.out *~ run
	
