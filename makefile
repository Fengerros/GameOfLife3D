run: main.cpp
	g++ -o main main.cpp src/shaders.cpp -lglfw -lGL -lGLEW -lGLU -lglut -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl
	./main

clean:
	rm main