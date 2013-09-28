 
uniform sampler2DRect tex0;
uniform sampler2DRect maskTex;
uniform sampler2DRect mensajesText;
void main (void){
	vec2 pos = gl_TexCoord[0].st;
	 
	vec4 Txt = texture2DRect(tex0, pos);
	vec4 mask = texture2DRect(maskTex, pos);
	vec4 msg = texture2DRect(mensajesText, pos);
	// vec4 color = vec4(0,0,0,0);
	vec4 color = vec4(Txt.r,Txt.g,Txt.b,mask.a);
	color +=msg;
	//color = sin(pos.s);
	 
	 //color = mix(color, Txt, mask);
	 
	 
	gl_FragColor = color;
}