#version 130
// Fragment shader operates on each pixel of poly

// Recieve color from vertex shader
in vec4 fragmentColor;

// vector3 of RGB color that gets output for each pixel
out vec4 color;

// Uniform variables are global variables used by all vertex of the mesh
uniform float time;

void main()
{
	// set color to the recieved fragment color
	color = fragmentColor + vec4(1.0 * (cos(time) + 1.0) * 0.5, 
								1.0 * (cos(time + 2.0) + 1.0) * 0.5,
								1.0 * (sin(time + 1.0) + 1.0) * 0.5, 0.0);
}