#version 120
uniform sampler2D ColorCorrMap;
uniform sampler2D fbo_texture;
varying vec2 f_texcoord;
 
void main(void) {
  
	vec3 InColor = texture2D(fbo_texture, f_texcoord).xyz;
	vec3 OutColor;
	OutColor.r = texture2D(ColorCorrMap, vec2(InColor.r,1.0)).r;
	OutColor.g = texture2D(ColorCorrMap, vec2(InColor.g,1.0)).g;
	OutColor.b = texture2D(ColorCorrMap, vec2(InColor.b,1.0)).b;
    
	
	gl_FragColor = vec4(OutColor , 1.0);
}

