varying vec3 normal;
void main(void) {
 	normal = normalize(gl_NormalMatrix * gl_Normal).xyz;
    gl_Position = ftransform();
}