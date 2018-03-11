#version 450

// VBO-ból érkezõ változók
layout(location = 0) in vec3 vs_in_pos;
layout(location = 1) in vec3 vs_in_col;

// a pipeline-ban tovább adandó értékek
out vec4 vs_out_col;
out vec4 vs_out_pos;

// shader külsõ paraméterei - most a három transzformációs mátrixot külön-külön vesszük át
uniform mat4 world;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	vs_out_pos = gl_Position = proj * view * world * vec4( vs_in_pos, 1 );
	vs_out_col = vec4(vs_in_col, 1);
}