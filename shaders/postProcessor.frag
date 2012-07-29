varying vec2 texcoord;
uniform sampler2D Texture[4];

void main(void)
{
    vec3 fogCol = vec3(0.0, 0.5, 0.8);
    vec3 col = texture2D(Texture[0], texcoord).xyz;
    vec3 d = texture2D(Texture[1], texcoord).xyz;
    col *= (fogCol * d);
    gl_FragColor = vec4(col.r, col.g, col.b, 1.0);
}
