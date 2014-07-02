uniform sampler2DRect tex;
uniform sampler2DRect noise;


uniform int numSample;
uniform int numSteps;
uniform float stepDist;
uniform float influence;
uniform float edge;
uniform float power;
uniform float noiseLev;
uniform float colorNoise;
uniform vec4 paintColor;

vec4 threshold(vec4 col) {
	vec4 ret;
	if (col.r > 0.5) {
		ret = vec4(vec3(0.9), 1.0);
	} else if (col.r > 0.3) {
		ret = vec4(vec3(0.2), 1.0);
	} else if (col.r > 0.2) {
		ret = vec4(vec3(0.0), 1.0);
	} else {
		ret = vec4(vec3(0.3), 1.0);
	}
	if (col.r < 0.5 && col.b > 0.5) {
		ret = vec4(vec3(1.0), 1.0);
	}
	return ret;
}

vec2 rotate(vec2 v, float a) {
	return vec2(v.x * cos(a) - v.y * sin(a), v.x * sin(a) + v.y * cos(a));
}

void main (void){
	float PI = 3.14159265359;
	vec4 outCol = vec4(0.0);

	for (int j = 0; j < numSample; j ++) {
		vec4 mixCol = vec4(0.0);
		float influenceRatio = 1.0;
		float angle = PI * 2.0 / float(j) * float(numSample);
		vec2 vec = vec2(cos(angle) * stepDist, sin(angle) * stepDist);
		vec2 sampCoord = gl_TexCoord[0].st;
		vec4 prevSamp  = vec4(0.0);
		float edgeLev = -1.0;
		
		for (int i = 0; i < numSteps; i ++) {
			vec4 sample = threshold(texture2DRect(tex, sampCoord));
			vec4 noiseSample = texture2DRect(noise, sampCoord);

			if (prevSamp != sample) {
				edgeLev += (1.0 - influenceRatio);
			}
			prevSamp = sample;


			if (sample.r != 1.0) {
				sample -= noiseSample * noiseSample * noiseLev;
				sample.a = 1.0;
			}

			mixCol = sample * influenceRatio + mixCol * (1.0 - influenceRatio);

			sampCoord += vec;
			vec += rotate((noiseSample.st - vec2(0.5, 0.5)), angle) * stepDist * 4.0;
			vec = normalize(vec) * stepDist;
			influenceRatio *= influence;
		}
		outCol += mixCol - vec4(max(vec3(0.0), vec3(edgeLev * edge)), 0.0);
	}

	outCol /= float(numSample);
	float lev = pow(outCol.r, power);
	outCol = outCol * colorNoise + min(vec4(1.0), vec4(vec3(lev), 1.0)) * (1.0 - colorNoise);
	outCol = outCol * (1.0 - paintColor) + paintColor;
	gl_FragColor = outCol;
}







