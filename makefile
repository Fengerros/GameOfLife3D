run: main.cpp
	g++ -o main main.cpp src/shaders.cpp src/VBO.cpp src/VAO.cpp src/EBO.cpp src/camera.cpp -lglfw -lGL -lGLEW -lGLU -lglut -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl
	./main

clean:
	rm main