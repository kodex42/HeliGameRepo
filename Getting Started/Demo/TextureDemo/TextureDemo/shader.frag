// Source code of fragment shader
#version 130

// Attributes passed from the vertex shader
in vec4 color_interp;
in vec2 uv_interp;

out vec4 FragColor;

uniform sampler2D onetex;
uniform vec4 color_base;

void main()
{
	vec4 color = texture2D(onetex, uv_interp);
	
	if (color_base.a != 0) {
		FragColor = vec4(
			(color_base.r*0.5) + (color.r*0.5),
			(color_base.g*0.5) + (color.g*0.5),
			(color_base.b*0.5) + (color.b*0.5),
			1
		);
	}
	else {
		FragColor = vec4(color.r,color.g,color.b,color.a);
	}

    if(color.a == 0) {
 		discard;
	}
//	 FragColor = color_interp;
}