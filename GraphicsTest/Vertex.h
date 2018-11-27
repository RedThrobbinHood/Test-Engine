#pragma once

#include <GL\glew.h>

// Vertext struct should be a multiple of 4 bytes for alignment reasons

struct Vertex {

	// Struct for x/y position of the vertex, lowercase position at the end is naming the struct
	struct Position {
		float x;
		float y;
	} position;

	struct Color {
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	} color;

};