 
uniform sampler2DRect tex0;
uniform sampler2DRect maskTex;

void main (void){
	vec2 pos = gl_TexCoord[0].st;
	 
	vec4 rTxt = texture2DRect(tex0, pos);
	//vec4 gTxt = texture2DRect(tex1, pos);
	// vec4 bTxt = texture2DRect(tex2, pos);
	vec4 mask = texture2DRect(maskTex, pos);
	 
	vec4 color = vec4(rTxt.r,rTxt.g,rTxt.b,mask.a);
	//color = mix(color, rTxt, mask );
	//color = mix(color, gTxt, mask.g );
	//color = mix(color, bTxt, mask.b );
	 /*color = rTxt * mask;
	 
	 color.r = rTxt.r * mask.r;
	 color.a = rTxt.a * mask.a;*/
	 //color = mix(color, rTxt, mask);
	 
	 color = rTxt;
	 color.a *= mask.a;
	 
	gl_FragColor = color;
}