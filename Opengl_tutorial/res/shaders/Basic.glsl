//#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

out vec4 colour;

void main()
{
gl_Position = position;
colour = color;
};





//#shader fragment
#version 330 core



layout(location = 0) out vec4 color;

uniform vec4 u_Color;

in vec4 colour;

void main()
{
    color = colour;
};
    