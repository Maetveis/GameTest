#version 450

in vec4 vs_out_col;
in vec3 vs_out_pos;
layout(location = 0) out vec4 fs_out_col;

uniform float time;

void main()
{
	fs_out_col = sin(length(vs_out_col) * time) * vs_out_col;
}