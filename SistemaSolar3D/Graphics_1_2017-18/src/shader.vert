#version 330
 
//Del planeta tierra
in vec3 a_vertex;	
in vec2 a_uv;		
in vec3 a_normal;




uniform mat4 u_model;
uniform mat4 u_projection;
uniform mat4 u_view;

uniform mat3 u_normal_matrix;


out vec3 v_world_vertex_pos;

//Del planeta tierra
out vec3 v_normal;
out vec2 v_uv;

void main()
{
	// position of the vertex
	gl_Position = u_projection *u_view* u_model * vec4( a_vertex , 1.0 );
	v_uv = a_uv;
	v_normal = u_normal_matrix*a_normal;
	
	v_world_vertex_pos = (u_model * vec4(a_vertex,1.0)).xyz;
}

