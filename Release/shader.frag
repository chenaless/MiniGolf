varying vec3 N;
varying vec3 L;
varying vec3 E;

void main()
{
    vec3 Normal = normalize(N);
    vec3 Light = normalize(L);
    vec3 Eye = normalize(E);
    vec3 Half = normalize(Eye+Light);
    float f = 1.0;
    
    float Kd = max(dot(Normal, Light), 0.0);
    float Ks = pow(max(dot(Half, Normal), 0.0),
                   gl_FrontMaterial.shininess);
                   
    vec4 diffuse = Kd * gl_FrontLightProduct[0].diffuse;
    if (dot(Normal, Light) < 0.0) f = 0.0;
    vec4 specular = f * Ks * gl_FrontLightProduct[0].specular;
    vec4 ambient = gl_FrontLightProduct[0].ambient;
    
    gl_FragColor = ambient + diffuse + specular + gl_Color;
}
