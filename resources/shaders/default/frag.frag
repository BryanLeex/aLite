#version 330

out vec4 FragColor;


in vec2 TexCoord;


uniform float time;
uniform sampler2D aTexture;


void main() {

    const float M_PI = 3.1416;

    FragColor = vec4(0.5 * sin(2 * time), cos(time + M_PI / 2.f), pow(cos(time), 2), 1.);

    FragColor = texture(aTexture, TexCoord);

}
