#version 330 core

in vec3 ourColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    //FragColor = texture(texture1,TexCoord)*vec4(ourColor,1.0);
    FragColor = mix(texture(texture1,TexCoord),
                    texture(texture2,TexCoord),0.2); // that is 80 % of 1st input color and 20% of 2nd input color
}