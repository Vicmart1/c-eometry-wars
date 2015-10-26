CXX = gcc
CXXFLAGS = -std=c99 -pedantic -Wall -Wextra -O -g -Wno-deprecated -framework OpenGL -framework GLUT
game: main.o Input.o NeonObj.o Player.o Diamond.o Pinwheel.o Bullet.o Particle.o Vector3.o Vector2.o
	$(CXX) $(CXXFLAGS) -o game main.o Input.o NeonObj.o Player.o Diamond.o Pinwheel.o Bullet.o Particle.o Vector3.o Vector2.o

main.o: main.c Input.h Vector2.h Vector3.h Player.h 
	$(CXX) $(CXXFLAGS) -c main.c

Particle.o: Particle.c Particle.h
	$(CXX) $(CXXFLAGS) -c Particle.c

Bullet.o: Bullet.c Bullet.h
	$(CXX) $(CXXFLAGS) -c Bullet.c

Pinwheel.o: Pinwheel.c Pinwheel.h
	$(CXX) $(CXXFLAGS) -c Pinwheel.c

Diamond.o: Diamond.c Diamond.h
	$(CXX) $(CXXFLAGS) -c Diamond.c

Input.o: Input.c Input.h Player.h
	$(CXX) $(CXXFLAGS) -c Input.c

Player.o: Player.c Player.h
	$(CXX) $(CXXFLAGS) -c Player.c

NeonObj.o: NeonObj.c NeonObj.h
	$(CXX) $(CXXFLAGS) -c NeonObj.c

Vector3.o: Vector3.c Vector3.h
	$(CXX) $(CXXFLAGS) -c Vector3.c

Vector2.o: Vector2.c Vector2.h
	$(CXX) $(CXXFLAGS) -c Vector2.c
