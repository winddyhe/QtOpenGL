precision mediump int;
precision mediump float;

uniform mat4 u_projectionMatrix;
uniform mat4 u_modelViewMatrix;

attribute vec2  a_position;
attribute float a_height;
attribute vec2  a_texcoord;

uniform vec2 u_startPos;

varying vec2 v_texcoord;

void main()
{
    vec4 position = vec4(a_position.x, a_height, a_position.y, 1.0);
    mat4 mvpMatrix = u_projectionMatrix * u_modelViewMatrix;

    position.x += u_startPos.x;
    position.y += u_startPos.y;

    gl_Position = mvpMatrix * position;
    v_texcoord = a_texcoord;
}
