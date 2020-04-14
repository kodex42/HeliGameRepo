// Source code of vertex shader for particle system
#version 130

// Vertex buffer
in vec2 vertex;
in vec2 dir;
in float t; //phase
in vec2 uv;

// Uniform (global) buffer
uniform mat4 transformationMatrix;
uniform mat4 viewMatrix;
uniform float time;
uniform vec4 colorin;

// Attributes forwarded to the fragment shader
out vec4 color_interp;
out vec2 uv_interp;

void main()
{
	vec4 ppos;
	float acttime;
	float speed = 4.0;
	float gravity = 2.8;
	acttime = mod(time + t*2.0, 2.0);
	color_interp = colorin;
	uv_interp = uv;

	ppos = vec4(vertex.x/(acttime+1)+dir.x*acttime*speed , vertex.y/(acttime+1)+dir.y*acttime*speed + 0.5*gravity*acttime*acttime, 0.0, 1.0);

    gl_Position = viewMatrix*transformationMatrix*ppos;
}
