#version 130
// Shader that opeerates on each vertex

// input data from the VBO, grabs the vector2 vertex
in vec2 vertexPosition;
in vec4 vertexColor;

// Sends this data to frag file
out vec4 fragmentColor;

void main() {
	// Set the x/y postion on screen
	gl_Position.xy = vertexPosition;
	
	// Set z to 0 (2D game)
	gl_Position.z = 0.0;
	
	// Normalize coordinates
	gl_Position.w = 1.0;
	
	fragmentColor = vertexColor;
}