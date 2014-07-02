varying vec3 normal;
uniform vec3 lightDir;
uniform vec4 ambientColor;
uniform vec4 diffuseColor;
uniform vec4 specularColor;         

void main(void) {

    float diffuse = max(0.0, dot(normalize(normal), normalize(lightDir)));
    float diffuse2 = max(0.0, dot(normalize(-normal), normalize(lightDir)));
    vec4 flagColor = diffuse * diffuseColor;
    flagColor += diffuse2 * diffuseColor * 0.5;
    flagColor += ambientColor;
    vec3 vReflection = normalize(reflect(-normalize(lightDir), normalize(normal)));
    float specular = pow(max(0.0, dot(normalize(normal), vReflection)), 128.0);
    flagColor += specular * specularColor;
    flagColor.a = 1.0;
    gl_FragColor = flagColor;
}