#version 330 core
out vec4 fragColor;

in vec4 vertexColor;

uniform vec4 outColor; //uniform simulate to global, can set by CPU for GPU

void main()
{
    //fragColor = vertexColor;
    fragColor = outColor;
}

