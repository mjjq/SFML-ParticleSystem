vec3 colorA = vec3(0.0,0.0,0.0);
vec3 colorB = vec3(1.0,1.0,1.0);

in vec4 colorOut;
in vec4 TexCoord;

float circle(in vec2 _st, in float _radius){
    vec2 dist = _st-vec2(0.5);
	return 1.-smoothstep(_radius-(_radius*0.01),
                         _radius+(_radius*0.01),
                         dot(dist,dist)*4.0);
}

void main() {


    //gl_FragColor = vec4(colorB, 1.0);

    vec2 st = TexCoord.xy;

    float pct = pow(1.064 - distance(st, vec2(0.5)), 3.848);

    float colorThreshold = circle(st, 0.9);

    gl_FragColor = vec4(colorOut.rgb, pct*colorOut.a);
    //y = pow(st.y, 1.0);// + distance(st.x, 0.5);
    //gl_FragColor = vec4(st.y, 1.0-st.y, 0.0, 1.0);
    //gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
}
