#version 330

in vec2 v_uv;
in vec3 v_normal;
in vec3 v_world_vertex_pos;

uniform sampler2D u_texture;

uniform vec3 u_light_dir;
uniform vec3 u_light_color;
uniform vec3 u_cam_pos;
uniform float u_shininess;
uniform vec3 u_ambient;

out vec4 fragColor;

void main(void)
{
	vec3 texture_color = texture2D(u_texture, v_uv).xyz;

	vec3 L = normalize(u_light_dir);
	vec3 N = normalize(v_normal);

	//Calculamos el diffuse color teniendo en cuenta la luz. Usamos Phong.
	float NdotL = max( dot(N,L) , 0.0 );
	vec3 diffuse_color =  texture_color * NdotL * u_light_color;

	//Calculamos el ambient color
	vec3 ambient_color = texture_color * u_ambient;

	
	//Calculamos el color especular
	vec3 R = reflect(L,N);
	vec3 E = normalize(u_cam_pos - v_world_vertex_pos);
	float RdotE = pow(max(dot(R,-E),0.0),u_shininess);
	vec3 specular_color = texture_color * u_light_color *RdotE;//

	vec3 final_color =  ambient_color + diffuse_color + specular_color;
	fragColor = vec4(final_color, 1.0);
}