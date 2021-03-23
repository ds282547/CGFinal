uniform sampler2D qt_Texture0;
varying vec2 qt_TexCoord0;

void main(void)
{
    gl_FragColor = vec4(texture2D(qt_Texture0, qt_TexCoord0).xxx,1.0);
}
