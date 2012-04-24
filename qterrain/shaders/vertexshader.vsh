precision mediump int;
precision mediump float;

attribute vec2  a_position;
attribute float a_height;
attribute vec2  a_texcoord;
attribute vec3  a_normal;

uniform vec2 u_startPos;
uniform mat4 u_mvpMatrix;

varying vec2 v_texcoord;
varying vec3 v_normal;

void main()
{
    vec4 position = vec4(a_position.x, a_height, a_position.y, 1.0);

    position.x += u_startPos.x;
    position.z += u_startPos.y;

    gl_Position = u_mvpMatrix * position;
    v_texcoord = a_texcoord;
    v_normal = a_normal;
}
