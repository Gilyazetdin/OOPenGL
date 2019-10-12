#version 460 core
layout (location = 0) in vec3 position; // Устанавливаем позиция переменной с координатами в 0
uniform mat4 MVP;
void main()
{
    gl_Position = MVP * vec4(position, 1);
}   