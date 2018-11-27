#version 130
// Fragment shader operates on each pixel of poly

// Recieve color from vertex shader
in vec4 fragmentColor;

// vector3 of RGB color that gets output for each pixel
out vec4 color;

void main()
{
	// set color to the recieved fragment color
	color = fragmentColor;
}