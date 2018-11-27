#pragma once

#include <GL\glew.h>

// Struct for x/y position of the vertex, lowercase position at the end is naming the struct
struct Position {
	float x;
	float y;
};

struct Color {
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

// Vertext struct should be a multiple of 4 bytes for alignment reasons
struct Vertex {

	// Vertex stores position and color
	Position position;
	Color color;
};