#version 330 core
layout (location = 0) in vec3 position;

uniform mat4 modelView;

void main()
{
    gl_Position = modelView * vec4(position, 1.0f);
}
