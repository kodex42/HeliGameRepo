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
uniform float explodeTime;
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
	float fullTime = 5.5;
	acttime = mod(time,fullTime);
	float modTime = acttime - explodeTime;

	color_interp = colorin;
	uv_interp = uv;

	if(acttime<explodeTime){
		ppos = vec4(vertex.x+dir.x*0.25 , vertex.y+dir.y*0.25 + 0.5*gravity*acttime + acttime*speed, 0.0, 1.0);
	}
	else if(acttime < explodeTime+3){
		uv_interp.y = 1-modTime/3;
		ppos = vec4(vertex.x/(modTime+1)+dir.x*modTime*speed , vertex.y/(modTime+1)+dir.y*modTime*speed + 0.5*gravity*explodeTime + explodeTime*speed, 0.0, 1.0);
	}
	else{
		uv_interp.y = 0;
		ppos = vec4(vertex.x/(modTime+1)+dir.x*modTime*speed , vertex.y/(modTime+1)+dir.y*modTime*speed + 0.5*gravity*explodeTime + explodeTime*speed, 0.0, 1.0);
	}

    gl_Position = viewMatrix*transformationMatrix*ppos;
	
}
