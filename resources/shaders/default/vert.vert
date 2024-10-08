#version 330

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCorrd;

out vec2 TexCoord;

uniform mat4 aModel;

void main() {

    gl_Position = aModel * vec4(aPos.xyz, 1.0);

    TexCoord = aTexCorrd;

}