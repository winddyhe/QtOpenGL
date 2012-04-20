precision mediump int;
precision mediump float;

attribute vec4  a_posXY;
attribute float a_posHeight;
attribute vec2  a_texCoord;
attribute vec3  a_normal;

uniform mat4 u_mvpMatrix;
uniform vec4 u_posOffset;

varying vec2 v_texCoord;
varying vec3 v_normal;

void main()
{
    vec4 combinePos = vec4(a_posXY.x, a_posHeight, a_posXY.y, 1);

    combinePos.x += u_posOffset.x;
    combinePos.z += u_posOffset.y;

    gl_Position = combinePos * u_mvpMatrix;

    v_texCoord = a_texCoord;
    v_normal = a_normal;
}
