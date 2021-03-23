uniform mat4 qt_ModelViewProjectionMatrix;

attribute vec4 qt_Vertex;
varying vec2 qt_TexCoord0;

void main(void)
{
    //qt_Vertex.x/=128;
    //qt_Vertex.y/=128;
    //qt_Vertex.x-=1;
    //qt_Vertex.y-=1;
    gl_Position = qt_ModelViewProjectionMatrix * qt_Vertex;
    qt_TexCoord0 = vec2(gl_MultiTexCoord0);//qt_Vertex/vec2(256,256);
}
