#version 330

out vec4 fragColor;

in vec2 v_uv;
uniform sampler2D u_texture;


void main(void)
{
	vec4 texture_color = texture2D(u_texture, v_uv);
	vec3 final_color = texture_color.xyz;
	fragColor = vec4(final_color, 1.0);
}