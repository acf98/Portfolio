/*  by Alun Evans 2016 LaSalle (aevanss@salleurl.edu) */

//include some standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include<math.h>
#include "glfunctions.h" //include all OpenGL stuff
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h" // class to compile shaders
#include "imageloader.h"
#include <glm/gtc/matrix_inverse.hpp>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

using namespace std;
using namespace glm;

// Default window size, in pixels
int g_ViewportWidth = 512; int g_ViewportHeight = 512;

// background colour - a GLM 3-component vector
const vec3 g_backgroundColor(0.2f, 0.2f, 0.2f);

GLuint g_ShaderProgram[] = {0,0,0}; //shader identifier
GLuint g_Vao = 0; //vao for sphere
GLuint g_Vao2 = 0; //vao for starship
GLuint g_NumTriangles = 0; //  Numbre of triangles we are painting.

						   //global variables used for camera movement
int key_flags[] = { 0, 0, 0, 0 }; //w, a, s, d
float mouse_coords[] = { 0.0, 0.0 }; // x, y
vec3 cam_pos(0,0, 0); //camera always starts at center of world
vec3 cam_target(0, 0, -1); //camera always starts looking down z-axis
float cam_pitch = 0; // up/down
float cam_yaw = 0; //left/right

				   //you may need to change these variables, depending on your system
float MOVE_SPEED = 0.1f;
float LOOK_SPEED = 0.01f;



//Global for light
vec3 g_light_dir(0, 0,0);

//Globales de movimiento de la tierra (referencia)
float movimiento= 0;
float radio_tierra = 10;
float velocitat_terra = 0.01;
float tamany_terra = 1;

//Global for texture object
GLuint texture_id_earth[] = { 0,0,0 };
GLuint texture_id_skybox[] = { 0 };
GLuint texture_id_planetas[] = {0,0,0,0,0,0,0,0,0};
GLuint texture_nave[] = { 0,0,0,0 }; //IOZ-501 Starship(https://sketchfab.com/models/666833e1eda84d86a95deecb0aba3c47) by Links_Even(https://sketchfab.com/links_even) is licensed under CC Attribution(http://creativecommons.org/licenses/by/4.0/)

//Textures
Image* image = loadBMP("earthmap1k.bmp");
Image* universo = loadBMP("milkyway.bmp");
Image* earth_normal = loadBMP("earthnormal.bmp");
Image* earth_spec = loadBMP("earthspec.bmp");

Image* mercurio = loadBMP("mercurymap.bmp"); //0
Image* venus = loadBMP("venusmap.bmp");		//1
Image* marte = loadBMP("mars_1k_color.bmp");//2
Image* jupiter = loadBMP("jupitermap.bmp"); //3
Image* saturno = loadBMP("saturnmap.bmp");	//4
Image* uranus = loadBMP("uranusmap.bmp");	//5
Image* neptuno = loadBMP("neptunemap.bmp");	//6
Image* sol = loadBMP("sunmap.bmp");			//7

void cargarTexturas() {
	//We load the images
	glGenTextures((sizeof(texture_id_earth) + sizeof(texture_id_skybox)+sizeof(texture_id_planetas)) / sizeof(GLuint), texture_id_earth);


	//PLaneta tierra
	glBindTexture(GL_TEXTURE_2D, texture_id_earth[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,//target
		0, //level, = 0 base, no mipmap
		GL_RGB, //the way opengl stores the data
		image->width, //width
		image->height, //height
		0, //border, must be 0
		GL_RGB, //the format of the original data
		GL_UNSIGNED_BYTE, //type of data
		image->pixels //pointer to start of data
	);

	glBindTexture(GL_TEXTURE_2D, texture_id_earth[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,//target
		0, //level, = 0 base, no mipmap
		GL_RGB, //the way opengl stores the data
		earth_normal->width, //width
		earth_normal->height, //height
		0, //border, must be 0
		GL_RGB, //the format of the original data
		GL_UNSIGNED_BYTE, //type of data
		earth_normal->pixels //pointer to start of data
	);

	glBindTexture(GL_TEXTURE_2D, texture_id_earth[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,//target
		0, //level, = 0 base, no mipmap
		GL_RGB, //the way opengl stores the data
		earth_spec->width, //width
		earth_spec->height, //height
		0, //border, must be 0
		GL_RGB, //the format of the original data
		GL_UNSIGNED_BYTE, //type of data
		earth_spec->pixels //pointer to start of data
	);

	
	//Skybox
	glBindTexture(GL_TEXTURE_2D, texture_id_skybox[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,//target
		0,				//level, = 0 base, no mipmap
		GL_RGB,			//the way opengl stores the data
		universo->width, //width
		universo->height, //height
		0,				 //border, must be 0
		GL_RGB,			 //the format of the original data
		GL_UNSIGNED_BYTE, //type of data
		universo->pixels //pointer to start of data
	);


	//De los planetas
	
	
	glBindTexture(GL_TEXTURE_2D, texture_id_planetas[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,//target
		0,				//level, = 0 base, no mipmap
		GL_RGB,			//the way opengl stores the data
		mercurio->width, //width
		mercurio->height, //height
		0,				 //border, must be 0
		GL_RGB,			 //the format of the original data
		GL_UNSIGNED_BYTE, //type of data
		mercurio->pixels //pointer to start of data
	);
	
	glBindTexture(GL_TEXTURE_2D, texture_id_planetas[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,//target
		0,				//level, = 0 base, no mipmap
		GL_RGB,			//the way opengl stores the data
		venus->width, //width
		venus->height, //height
		0,				 //border, must be 0
		GL_RGB,			 //the format of the original data
		GL_UNSIGNED_BYTE, //type of data
		venus->pixels //pointer to start of data
	);

	glBindTexture(GL_TEXTURE_2D, texture_id_planetas[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,//target
		0,				//level, = 0 base, no mipmap
		GL_RGB,			//the way opengl stores the data
		marte->width, //width
		marte->height, //height
		0,				 //border, must be 0
		GL_RGB,			 //the format of the original data
		GL_UNSIGNED_BYTE, //type of data
		marte->pixels //pointer to start of data
	);
	
	glBindTexture(GL_TEXTURE_2D, texture_id_planetas[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,//target
		0,				//level, = 0 base, no mipmap
		GL_RGB,			//the way opengl stores the data
		jupiter->width, //width
		jupiter->height, //height
		0,				 //border, must be 0
		GL_RGB,			 //the format of the original data
		GL_UNSIGNED_BYTE, //type of data
		jupiter->pixels //pointer to start of data
	);

	glBindTexture(GL_TEXTURE_2D, texture_id_planetas[4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,//target
		0,				//level, = 0 base, no mipmap
		GL_RGB,			//the way opengl stores the data
		saturno->width, //width
		saturno->height, //height
		0,				 //border, must be 0
		GL_RGB,			 //the format of the original data
		GL_UNSIGNED_BYTE, //type of data
		saturno->pixels //pointer to start of data
	);

	glBindTexture(GL_TEXTURE_2D, texture_id_planetas[5]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,//target
		0,				//level, = 0 base, no mipmap
		GL_RGB,			//the way opengl stores the data
		uranus->width, //width
		uranus->height, //height
		0,				 //border, must be 0
		GL_RGB,			 //the format of the original data
		GL_UNSIGNED_BYTE, //type of data
		uranus->pixels //pointer to start of data
	);

	glBindTexture(GL_TEXTURE_2D, texture_id_planetas[6]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,//target
		0,				//level, = 0 base, no mipmap
		GL_RGB,			//the way opengl stores the data
		neptuno->width, //width
		neptuno->height, //height
		0,				 //border, must be 0
		GL_RGB,			 //the format of the original data
		GL_UNSIGNED_BYTE, //type of data
		neptuno->pixels //pointer to start of data
	);

	glBindTexture(GL_TEXTURE_2D, texture_id_planetas[7]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,//target
		0,				//level, = 0 base, no mipmap
		GL_RGB,			//the way opengl stores the data
		sol->width, //width
		sol->height, //height
		0,				 //border, must be 0
		GL_RGB,			 //the format of the original data
		GL_UNSIGNED_BYTE, //type of data
		sol->pixels //pointer to start of data
	);
	
}

void cargarNave() {
	string inputfile = "Vaisseau.obj";
	vector <tinyobj::shape_t> shapes;
	vector<tinyobj::material_t> materials;
	string err;
	bool ret = tinyobj::LoadObj(shapes, materials, err, inputfile.c_str());

	//Miramos errores
	cout << "# of shapes   :" << shapes.size() << endl;
	if (!err.empty()) std::cerr << err << std::endl;

	//Creamos los buffers extrayendo la info de los archivos cargados

	GLfloat* vertices = &(shapes[0].mesh.positions[0]);
	GLuint vertices_size = shapes[0].mesh.positions.size() * sizeof(GLfloat);
	GLuint* indices = &(shapes[0].mesh.indices[0]);
	GLuint indices_size = shapes[0].mesh.indices.size() * sizeof(GLuint);
	g_NumTriangles = shapes[0].mesh.indices.size() / 3;

	GLfloat* uvs = &(shapes[0].mesh.texcoords[0]);
	GLuint uvs_size = shapes[0].mesh.texcoords.size() * sizeof(GLfloat);

	GLfloat* normals = &(shapes[0].mesh.normals[0]);
	GLuint normals_size = (shapes[0].mesh.normals.size() * sizeof(GLfloat));

	// Create the VAO where we store all geometry (stored in g_Vao)
	g_Vao2 = gl_createAndBindVAO();

	gl_createAndBindAttribute(uvs, uvs_size, g_ShaderProgram[2], "a_uv", 2);
	gl_createAndBindAttribute(vertices, vertices_size, g_ShaderProgram[2], "a_vertex", 3);

	gl_createIndexBuffer(indices, indices_size);

	//unbind everything
	gl_unbindVAO();
}

// ----------------------------------------------------------------------------------------
// This function manually creates a square geometry (defined in the array vertices[])
// ------------------------------------------------------------------------------------------
void createGeometry()
{

	//Cargamos el objeto
	string inputfile = "sphere.obj";
	vector <tinyobj::shape_t> shapes;
	vector<tinyobj::material_t> materials;
	string err;
	bool ret = tinyobj::LoadObj(shapes, materials, err, inputfile.c_str());

	//Miramos errores
	cout << "# of shapes   :" << shapes.size() << endl;
	if (!err.empty()) std::cerr << err << std::endl;

	//Creamos los buffers extrayendo la info de los archivos cargados

	GLfloat* vertices = &(shapes[0].mesh.positions[0]);
	GLuint vertices_size = shapes[0].mesh.positions.size() * sizeof(GLfloat);
	GLuint* indices = &(shapes[0].mesh.indices[0]);
	GLuint indices_size = shapes[0].mesh.indices.size() * sizeof(GLuint);
	g_NumTriangles = shapes[0].mesh.indices.size() / 3;

	GLfloat* uvs = &(shapes[0].mesh.texcoords[0]);
	GLuint uvs_size = shapes[0].mesh.texcoords.size() * sizeof(GLfloat);

	GLfloat* normals = &(shapes[0].mesh.normals[0]);
	GLuint normals_size = (shapes[0].mesh.normals.size() * sizeof(GLfloat));

	// Create the VAO where we store all geometry (stored in g_Vao)
	g_Vao = gl_createAndBindVAO();

	gl_createAndBindAttribute(uvs,uvs_size,g_ShaderProgram[0], "a_uv",2);
	gl_createAndBindAttribute(vertices, vertices_size, g_ShaderProgram[0], "a_vertex", 3);
	gl_createAndBindAttribute(normals, normals_size, g_ShaderProgram[0], "a_normal", 3);

	gl_createAndBindAttribute(uvs, uvs_size, g_ShaderProgram[1], "a_uv", 2);
	gl_createAndBindAttribute(vertices, vertices_size, g_ShaderProgram[1], "a_vertex", 3);

	gl_createIndexBuffer(indices, indices_size);

	//unbind everything
	gl_unbindVAO();

	//make sure global var has correct number of triangles
	//why? because we will need it in onDisplay
	//g_NumTriangles = sizeof(indices) / (sizeof(GLuint) * 3);

	cargarNave();
	cargarTexturas();
}


void drawEarth() {
	
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// activate shader and VAO
	glUseProgram(g_ShaderProgram[0]);
	gl_bindVAO(g_Vao);


	//Las enlazamos con el shader
	GLuint u_model = glGetUniformLocation(g_ShaderProgram[0], "u_model");
	GLuint u_projection = glGetUniformLocation(g_ShaderProgram[0], "u_projection");
	GLuint u_view = glGetUniformLocation(g_ShaderProgram[0], "u_view");
	GLuint u_light_dir = glGetUniformLocation(g_ShaderProgram[0], "u_light_dir");
	GLuint u_light_color = glGetUniformLocation(g_ShaderProgram[0], "u_light_color");
	GLuint u_cam_pos = glGetUniformLocation(g_ShaderProgram[0], "u_cam_pos");
	GLuint u_shininess = glGetUniformLocation(g_ShaderProgram[0], "u_shininess");

	GLuint u_normal_matrix = glGetUniformLocation(g_ShaderProgram[0], "u_normal_matrix");

	GLuint u_texture = glGetUniformLocation(g_ShaderProgram[0], "u_texture");
	GLuint u_texture_normal = glGetUniformLocation(g_ShaderProgram[0], "u_texture_normal");
	GLuint u_texture_spec = glGetUniformLocation(g_ShaderProgram[0], "u_texture_spec");
	GLuint u_ambient = glGetUniformLocation(g_ShaderProgram[0], "u_ambient");
	

	//set MVP
	float velocidad_rotacion = 0.01;
	float radio_rotacion = radio_tierra;
	float movimiento_tierra= movimiento*velocidad_rotacion;
	
	
	mat4 translate_matrix = translate(mat4(1.0f), vec3(radio_rotacion*glm::cos(movimiento_tierra), 0, radio_rotacion*glm::sin(movimiento_tierra)));
	mat4 view_matrix = lookAt(cam_pos, cam_target, vec3(0, 1, 0)); //cam_pos and cam_target set in update!
	mat4 scale_matrix = scale(mat4(1.0f),vec3(tamany_terra, tamany_terra, tamany_terra));
	mat4 projection_matrix = glm::perspective(60.0f, (float)(g_ViewportWidth / g_ViewportHeight), 0.1f, 50.0f);

	mat4 model_matrix = translate_matrix*scale_matrix;
	mat3 normal_matrix = inverseTranspose((mat3(model_matrix)));

	//We upload the uniforms
	//send all values to shader
	glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(model_matrix));
	glUniformMatrix4fv(u_view, 1, GL_FALSE, glm::value_ptr(view_matrix));
	glUniformMatrix4fv(u_projection, 1, GL_FALSE, glm::value_ptr(projection_matrix));

	glUniform1i(u_texture, 0);
	glUniform1i(u_texture_normal,1);
	glUniform1i(u_texture_spec,2);

	glUniform3f(u_light_dir, -radio_rotacion*glm::cos(movimiento_tierra), 0, -radio_rotacion*glm::sin(movimiento_tierra));

	glUniform3f(u_light_color, 1, 1, 1);
	glUniform3f(u_ambient, 0.5,0.5,0.5);
	glUniform3f(u_cam_pos, cam_pos.x, cam_pos.y, cam_pos.z);
	glUniform1f(u_shininess, 100);
	
	glUniformMatrix3fv(u_normal_matrix,1,GL_FALSE,glm::value_ptr(normal_matrix));
	


	//Diffuse color
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id_earth[0]);

	//Normal
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture_id_earth[1]);

	//specular
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texture_id_earth[2]);



	// Draw to back buffer
	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles, GL_UNSIGNED_INT, 0);

	//unbind vao and shader
	gl_unbindVAO();
	glUseProgram(0);
}

void drawSkyBox() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glUseProgram(g_ShaderProgram[1]);

	gl_bindVAO(g_Vao);

	GLuint u_model = glGetUniformLocation(g_ShaderProgram[1], "u_model");
	GLuint u_projection = glGetUniformLocation(g_ShaderProgram[1], "u_projection");
	GLuint u_view = glGetUniformLocation(g_ShaderProgram[1], "u_view");
	GLuint u_texture = glGetUniformLocation(g_ShaderProgram[1], "u_texture");
	

	mat4 translate_matrix = translate(mat4(1.0f), cam_pos);

	mat4 view_matrix = lookAt(cam_pos, cam_target, vec3(0, 1, 0)); //cam_pos and cam_target set in update!
	mat4 projection_matrix = glm::perspective(60.0f, (float)(g_ViewportWidth / g_ViewportHeight), 0.1f, 50.0f);
	mat4 scale_matrix = scale(mat4(1.0f),vec3(30,30,30));
	mat4 model_matrix = translate_matrix*scale_matrix;
	glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(model_matrix));
	glUniformMatrix4fv(u_view, 1, GL_FALSE, glm::value_ptr(view_matrix));
	glUniformMatrix4fv(u_projection, 1, GL_FALSE, glm::value_ptr(projection_matrix));
	glUniform1i(u_texture, 0);


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id_skybox[0]);

	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles, GL_UNSIGNED_INT, 0);

	gl_unbindVAO();
	glUseProgram(0);
}

void drawMercury() {
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
	// activate shader and VAO
	glUseProgram(g_ShaderProgram[2]);
	gl_bindVAO(g_Vao);


	//Las enlazamos con el shader
	GLuint u_model = glGetUniformLocation(g_ShaderProgram[2], "u_model");
	GLuint u_projection = glGetUniformLocation(g_ShaderProgram[2], "u_projection");
	GLuint u_view = glGetUniformLocation(g_ShaderProgram[2], "u_view");
	GLuint u_light_dir = glGetUniformLocation(g_ShaderProgram[2], "u_light_dir");
	GLuint u_light_color = glGetUniformLocation(g_ShaderProgram[2], "u_light_color");
	GLuint u_cam_pos = glGetUniformLocation(g_ShaderProgram[2], "u_cam_pos");
	GLuint u_shininess = glGetUniformLocation(g_ShaderProgram[2], "u_shininess");
	GLuint u_normal_matrix = glGetUniformLocation(g_ShaderProgram[2], "u_normal_matrix");
	GLuint u_texture = glGetUniformLocation(g_ShaderProgram[2], "u_texture");
	GLuint u_ambient = glGetUniformLocation(g_ShaderProgram[2], "u_ambient");


	//set MVP
	float velocidad_rotacion = velocitat_terra*1.6;
	float radio_rotacion = radio_tierra*0.39;
	float movimiento_mercurio =  movimiento*velocidad_rotacion;

	mat4 translate_matrix = translate(mat4(1.0f), vec3(radio_rotacion*glm::cos(movimiento_mercurio), 0, radio_rotacion*glm::sin(movimiento_mercurio)));
	mat4 scale_matrix = scale(mat4(1.0f),vec3(tamany_terra*0.38, tamany_terra*0.38, tamany_terra*0.38));
	mat4 view_matrix = lookAt(cam_pos, cam_target, vec3(0, 1, 0)); //cam_pos and cam_target set in update!
	mat4 projection_matrix = glm::perspective(60.0f, (float)(g_ViewportWidth / g_ViewportHeight), 0.1f, 50.0f);
	mat4 model_matrix = translate_matrix*scale_matrix;
	mat3 normal_matrix = inverseTranspose((mat3(model_matrix)));

	


	//Diffuse color
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id_planetas[0]);

	//We upload the uniforms
	//send all values to shader
	glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(model_matrix));
	glUniformMatrix4fv(u_view, 1, GL_FALSE, glm::value_ptr(view_matrix));
	glUniformMatrix4fv(u_projection, 1, GL_FALSE, glm::value_ptr(projection_matrix));

	glUniform1i(u_texture,0);
	
	glUniform3f(u_light_dir,-radio_rotacion*glm::cos(movimiento_mercurio), 0,-radio_rotacion*glm::sin(movimiento_mercurio));

	glUniform3f(u_light_color, 1, 1, 1);
	glUniform3f(u_ambient, 0.5, 0.5, 0.5);
	glUniform3f(u_cam_pos, cam_pos.x, cam_pos.y, cam_pos.z);
	glUniform1f(u_shininess, 100);

	glUniformMatrix3fv(u_normal_matrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));

	

	// Draw to back buffer
	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles, GL_UNSIGNED_INT, 0);

	//unbind vao and shader
	gl_unbindVAO();
	glUseProgram(0);

}
void drawVenus() {
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// activate shader and VAO
	glUseProgram(g_ShaderProgram[2]);
	gl_bindVAO(g_Vao);


	//Las enlazamos con el shader
	GLuint u_model = glGetUniformLocation(g_ShaderProgram[2], "u_model");
	GLuint u_projection = glGetUniformLocation(g_ShaderProgram[2], "u_projection");
	GLuint u_view = glGetUniformLocation(g_ShaderProgram[2], "u_view");
	GLuint u_light_dir = glGetUniformLocation(g_ShaderProgram[2], "u_light_dir");
	GLuint u_light_color = glGetUniformLocation(g_ShaderProgram[2], "u_light_color");
	GLuint u_cam_pos = glGetUniformLocation(g_ShaderProgram[2], "u_cam_pos");
	GLuint u_shininess = glGetUniformLocation(g_ShaderProgram[2], "u_shininess");
	GLuint u_normal_matrix = glGetUniformLocation(g_ShaderProgram[2], "u_normal_matrix");
	GLuint u_texture = glGetUniformLocation(g_ShaderProgram[2], "u_texture");
	GLuint u_ambient = glGetUniformLocation(g_ShaderProgram[2], "u_ambient");


	//set MVP
	float velocidad_rotacion = velocitat_terra*1.82;
	float radio_rotacion = radio_tierra*0.72;
	float movimiento_venus = movimiento*velocidad_rotacion;

	mat4 translate_matrix = translate(mat4(1.0f), vec3(radio_rotacion*glm::cos(movimiento_venus), 0, radio_rotacion*glm::sin(movimiento_venus)));
	mat4 scale_matrix = scale(mat4(1.0f), vec3(tamany_terra*0.95, tamany_terra* 0.95, tamany_terra* 0.95));
	mat4 view_matrix = lookAt(cam_pos, cam_target, vec3(0, 1, 0)); //cam_pos and cam_target set in update!
	mat4 projection_matrix = glm::perspective(60.0f, (float)(g_ViewportWidth / g_ViewportHeight), 0.1f, 50.0f);
	mat4 model_matrix = translate_matrix*scale_matrix;
	mat3 normal_matrix = inverseTranspose((mat3(model_matrix)));




	//Diffuse color
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id_planetas[1]);

	//We upload the uniforms
	//send all values to shader
	glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(model_matrix));
	glUniformMatrix4fv(u_view, 1, GL_FALSE, glm::value_ptr(view_matrix));
	glUniformMatrix4fv(u_projection, 1, GL_FALSE, glm::value_ptr(projection_matrix));

	glUniform1i(u_texture, 0);

	glUniform3f(u_light_dir, -radio_rotacion*glm::cos(movimiento_venus), 0, -radio_rotacion*glm::sin(movimiento_venus));

	glUniform3f(u_light_color, 1, 1, 1);
	glUniform3f(u_ambient, 0.5, 0.5, 0.5);
	glUniform3f(u_cam_pos, cam_pos.x, cam_pos.y, cam_pos.z);
	glUniform1f(u_shininess, 100);

	glUniformMatrix3fv(u_normal_matrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));



	// Draw to back buffer
	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles, GL_UNSIGNED_INT, 0);

	//unbind vao and shader
	gl_unbindVAO();
	glUseProgram(0);
}
void drawMars() {
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// activate shader and VAO
	glUseProgram(g_ShaderProgram[2]);
	gl_bindVAO(g_Vao);


	//Las enlazamos con el shader
	GLuint u_model = glGetUniformLocation(g_ShaderProgram[2], "u_model");
	GLuint u_projection = glGetUniformLocation(g_ShaderProgram[2], "u_projection");
	GLuint u_view = glGetUniformLocation(g_ShaderProgram[2], "u_view");
	GLuint u_light_dir = glGetUniformLocation(g_ShaderProgram[2], "u_light_dir");
	GLuint u_light_color = glGetUniformLocation(g_ShaderProgram[2], "u_light_color");
	GLuint u_cam_pos = glGetUniformLocation(g_ShaderProgram[2], "u_cam_pos");
	GLuint u_shininess = glGetUniformLocation(g_ShaderProgram[2], "u_shininess");
	GLuint u_normal_matrix = glGetUniformLocation(g_ShaderProgram[2], "u_normal_matrix");
	GLuint u_texture = glGetUniformLocation(g_ShaderProgram[2], "u_texture");
	GLuint u_ambient = glGetUniformLocation(g_ShaderProgram[2], "u_ambient");


	//set MVP
	float velocidad_rotacion = velocitat_terra*0.44;
	float radio_rotacion = radio_tierra*1.52;
	float movimiento_marte = movimiento*velocidad_rotacion;

	mat4 translate_matrix = translate(mat4(1.0f), vec3(radio_rotacion*glm::cos(movimiento_marte), 0, radio_rotacion*glm::sin(movimiento_marte)));
	mat4 scale_matrix = scale(mat4(1.0f), vec3(tamany_terra*0.53, tamany_terra* 0.53, tamany_terra* 0.53));
	mat4 view_matrix = lookAt(cam_pos, cam_target, vec3(0, 1, 0)); //cam_pos and cam_target set in update!
	mat4 projection_matrix = glm::perspective(60.0f, (float)(g_ViewportWidth / g_ViewportHeight), 0.1f, 50.0f);
	mat4 model_matrix = translate_matrix*scale_matrix;
	mat3 normal_matrix = inverseTranspose((mat3(model_matrix)));




	//Diffuse color
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id_planetas[2]);

	//We upload the uniforms
	//send all values to shader
	glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(model_matrix));
	glUniformMatrix4fv(u_view, 1, GL_FALSE, glm::value_ptr(view_matrix));
	glUniformMatrix4fv(u_projection, 1, GL_FALSE, glm::value_ptr(projection_matrix));

	glUniform1i(u_texture, 0);

	glUniform3f(u_light_dir, -radio_rotacion*glm::cos(movimiento_marte), 0, -radio_rotacion*glm::sin(movimiento_marte));

	glUniform3f(u_light_color, 1, 1, 1);
	glUniform3f(u_ambient, 0.5, 0.5, 0.5);
	glUniform3f(u_cam_pos, cam_pos.x, cam_pos.y, cam_pos.z);
	glUniform1f(u_shininess, 100);

	glUniformMatrix3fv(u_normal_matrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));



	// Draw to back buffer
	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles, GL_UNSIGNED_INT, 0);

	//unbind vao and shader
	gl_unbindVAO();
	glUseProgram(0);

}
void drawJupiter() {
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// activate shader and VAO
	glUseProgram(g_ShaderProgram[2]);
	gl_bindVAO(g_Vao);


	//Las enlazamos con el shader
	GLuint u_model = glGetUniformLocation(g_ShaderProgram[2], "u_model");
	GLuint u_projection = glGetUniformLocation(g_ShaderProgram[2], "u_projection");
	GLuint u_view = glGetUniformLocation(g_ShaderProgram[2], "u_view");
	GLuint u_light_dir = glGetUniformLocation(g_ShaderProgram[2], "u_light_dir");
	GLuint u_light_color = glGetUniformLocation(g_ShaderProgram[2], "u_light_color");
	GLuint u_cam_pos = glGetUniformLocation(g_ShaderProgram[2], "u_cam_pos");
	GLuint u_shininess = glGetUniformLocation(g_ShaderProgram[2], "u_shininess");
	GLuint u_normal_matrix = glGetUniformLocation(g_ShaderProgram[2], "u_normal_matrix");
	GLuint u_texture = glGetUniformLocation(g_ShaderProgram[2], "u_texture");
	GLuint u_ambient = glGetUniformLocation(g_ShaderProgram[2], "u_ambient");


	//set MVP
	float velocidad_rotacion = velocitat_terra*0.44;
	float radio_rotacion = radio_tierra*2;
	float movimiento_jupiter = movimiento*velocidad_rotacion;

	mat4 translate_matrix = translate(mat4(1.0f), vec3(radio_rotacion*glm::cos(movimiento_jupiter), 0, radio_rotacion*glm::sin(movimiento_jupiter)));
	mat4 scale_matrix = scale(mat4(1.0f), vec3(tamany_terra*6, tamany_terra*6, tamany_terra*6));
	mat4 view_matrix = lookAt(cam_pos, cam_target, vec3(0, 1, 0)); //cam_pos and cam_target set in update!
	mat4 projection_matrix = glm::perspective(60.0f, (float)(g_ViewportWidth / g_ViewportHeight), 0.1f, 50.0f);
	mat4 model_matrix = translate_matrix*scale_matrix;
	mat3 normal_matrix = inverseTranspose((mat3(model_matrix)));




	//Diffuse color
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id_planetas[3]);

	//We upload the uniforms
	//send all values to shader
	glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(model_matrix));
	glUniformMatrix4fv(u_view, 1, GL_FALSE, glm::value_ptr(view_matrix));
	glUniformMatrix4fv(u_projection, 1, GL_FALSE, glm::value_ptr(projection_matrix));

	glUniform1i(u_texture, 0);

	glUniform3f(u_light_dir, -radio_rotacion*glm::cos(movimiento_jupiter), 0, -radio_rotacion*glm::sin(movimiento_jupiter));

	glUniform3f(u_light_color, 1, 1, 1);
	glUniform3f(u_ambient, 0.5, 0.5, 0.5);
	glUniform3f(u_cam_pos, cam_pos.x, cam_pos.y, cam_pos.z);
	glUniform1f(u_shininess, 100);

	glUniformMatrix3fv(u_normal_matrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));



	// Draw to back buffer
	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles, GL_UNSIGNED_INT, 0);

	//unbind vao and shader
	gl_unbindVAO();
	glUseProgram(0);

}
void drawSaturn() {
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// activate shader and VAO
	glUseProgram(g_ShaderProgram[2]);
	gl_bindVAO(g_Vao);


	//Las enlazamos con el shader
	GLuint u_model = glGetUniformLocation(g_ShaderProgram[2], "u_model");
	GLuint u_projection = glGetUniformLocation(g_ShaderProgram[2], "u_projection");
	GLuint u_view = glGetUniformLocation(g_ShaderProgram[2], "u_view");
	GLuint u_light_dir = glGetUniformLocation(g_ShaderProgram[2], "u_light_dir");
	GLuint u_light_color = glGetUniformLocation(g_ShaderProgram[2], "u_light_color");
	GLuint u_cam_pos = glGetUniformLocation(g_ShaderProgram[2], "u_cam_pos");
	GLuint u_shininess = glGetUniformLocation(g_ShaderProgram[2], "u_shininess");
	GLuint u_normal_matrix = glGetUniformLocation(g_ShaderProgram[2], "u_normal_matrix");
	GLuint u_texture = glGetUniformLocation(g_ShaderProgram[2], "u_texture");
	GLuint u_ambient = glGetUniformLocation(g_ShaderProgram[2], "u_ambient");


	//set MVP
	float velocidad_rotacion = velocitat_terra*0.31;
	float radio_rotacion = radio_tierra*3;
	float movimiento_saturno = movimiento*velocidad_rotacion;

	mat4 translate_matrix = translate(mat4(1.0f), vec3(radio_rotacion*glm::cos(movimiento_saturno), 0, radio_rotacion*glm::sin(movimiento_saturno)));
	mat4 scale_matrix = scale(mat4(1.0f), vec3(tamany_terra*4, tamany_terra* 4, tamany_terra*4));
	mat4 view_matrix = lookAt(cam_pos, cam_target, vec3(0, 1, 0)); //cam_pos and cam_target set in update!
	mat4 projection_matrix = glm::perspective(60.0f, (float)(g_ViewportWidth / g_ViewportHeight), 0.1f, 50.0f);
	mat4 model_matrix = translate_matrix*scale_matrix;
	mat3 normal_matrix = inverseTranspose((mat3(model_matrix)));




	//Diffuse color
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id_planetas[4]);

	//We upload the uniforms
	//send all values to shader
	glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(model_matrix));
	glUniformMatrix4fv(u_view, 1, GL_FALSE, glm::value_ptr(view_matrix));
	glUniformMatrix4fv(u_projection, 1, GL_FALSE, glm::value_ptr(projection_matrix));

	glUniform1i(u_texture, 0);

	glUniform3f(u_light_dir, -radio_rotacion*glm::cos(movimiento_saturno), 0, -radio_rotacion*glm::sin(movimiento_saturno));

	glUniform3f(u_light_color, 1, 1, 1);
	glUniform3f(u_ambient, 0.5, 0.5, 0.5);
	glUniform3f(u_cam_pos, cam_pos.x, cam_pos.y, cam_pos.z);
	glUniform1f(u_shininess, 100);

	glUniformMatrix3fv(u_normal_matrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));



	// Draw to back buffer
	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles, GL_UNSIGNED_INT, 0);

	//unbind vao and shader
	gl_unbindVAO();
	glUseProgram(0);
}
void drawUranus() {
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// activate shader and VAO
	glUseProgram(g_ShaderProgram[2]);
	gl_bindVAO(g_Vao);


	//Las enlazamos con el shader
	GLuint u_model = glGetUniformLocation(g_ShaderProgram[2], "u_model");
	GLuint u_projection = glGetUniformLocation(g_ShaderProgram[2], "u_projection");
	GLuint u_view = glGetUniformLocation(g_ShaderProgram[2], "u_view");
	GLuint u_light_dir = glGetUniformLocation(g_ShaderProgram[2], "u_light_dir");
	GLuint u_light_color = glGetUniformLocation(g_ShaderProgram[2], "u_light_color");
	GLuint u_cam_pos = glGetUniformLocation(g_ShaderProgram[2], "u_cam_pos");
	GLuint u_shininess = glGetUniformLocation(g_ShaderProgram[2], "u_shininess");
	GLuint u_normal_matrix = glGetUniformLocation(g_ShaderProgram[2], "u_normal_matrix");
	GLuint u_texture = glGetUniformLocation(g_ShaderProgram[2], "u_texture");
	GLuint u_ambient = glGetUniformLocation(g_ShaderProgram[2], "u_ambient");


	//set MVP
	float velocidad_rotacion = velocitat_terra*0.2;
	float radio_rotacion = radio_tierra*4;
	float movimiento_urano = movimiento*velocidad_rotacion;

	mat4 translate_matrix = translate(mat4(1.0f), vec3(radio_rotacion*glm::cos(movimiento_urano), 0, radio_rotacion*glm::sin(movimiento_urano)));
	mat4 scale_matrix = scale(mat4(1.0f), vec3(tamany_terra*2, tamany_terra*2, tamany_terra*2));
	mat4 view_matrix = lookAt(cam_pos, cam_target, vec3(0, 1, 0)); //cam_pos and cam_target set in update!
	mat4 projection_matrix = glm::perspective(60.0f, (float)(g_ViewportWidth / g_ViewportHeight), 0.1f, 50.0f);
	mat4 model_matrix = translate_matrix*scale_matrix;
	mat3 normal_matrix = inverseTranspose((mat3(model_matrix)));




	//Diffuse color
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id_planetas[5]);

	//We upload the uniforms
	//send all values to shader
	glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(model_matrix));
	glUniformMatrix4fv(u_view, 1, GL_FALSE, glm::value_ptr(view_matrix));
	glUniformMatrix4fv(u_projection, 1, GL_FALSE, glm::value_ptr(projection_matrix));

	glUniform1i(u_texture, 0);

	glUniform3f(u_light_dir, -radio_rotacion*glm::cos(movimiento_urano), 0,-radio_rotacion*glm::sin(movimiento_urano));

	glUniform3f(u_light_color, 1, 1, 1);
	glUniform3f(u_ambient, 0.5, 0.5, 0.5);
	glUniform3f(u_cam_pos, cam_pos.x, cam_pos.y, cam_pos.z);
	glUniform1f(u_shininess, 100);

	glUniformMatrix3fv(u_normal_matrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));



	// Draw to back buffer
	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles, GL_UNSIGNED_INT, 0);

	//unbind vao and shader
	gl_unbindVAO();
	glUseProgram(0);
}
void drawNeptune() {
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// activate shader and VAO
	glUseProgram(g_ShaderProgram[2]);
	gl_bindVAO(g_Vao);


	//Las enlazamos con el shader
	GLuint u_model = glGetUniformLocation(g_ShaderProgram[2], "u_model");
	GLuint u_projection = glGetUniformLocation(g_ShaderProgram[2], "u_projection");
	GLuint u_view = glGetUniformLocation(g_ShaderProgram[2], "u_view");
	GLuint u_light_dir = glGetUniformLocation(g_ShaderProgram[2], "u_light_dir");
	GLuint u_light_color = glGetUniformLocation(g_ShaderProgram[2], "u_light_color");
	GLuint u_cam_pos = glGetUniformLocation(g_ShaderProgram[2], "u_cam_pos");
	GLuint u_shininess = glGetUniformLocation(g_ShaderProgram[2], "u_shininess");
	GLuint u_normal_matrix = glGetUniformLocation(g_ShaderProgram[2], "u_normal_matrix");
	GLuint u_texture = glGetUniformLocation(g_ShaderProgram[2], "u_texture");
	GLuint u_ambient = glGetUniformLocation(g_ShaderProgram[2], "u_ambient");


	//set MVP
	float velocidad_rotacion = velocitat_terra * 0.17;
	float radio_rotacion = radio_tierra*5;
	float movimiento_neptuno = movimiento* velocidad_rotacion;

	mat4 translate_matrix = translate(mat4(1.0f), vec3(radio_rotacion*glm::cos(movimiento_neptuno), 0, radio_rotacion*glm::sin(movimiento_neptuno)));
	mat4 scale_matrix = scale(mat4(1.0f), vec3(tamany_terra*2.1, tamany_terra* 2.1, tamany_terra* 2.1));
	mat4 view_matrix = lookAt(cam_pos, cam_target, vec3(0, 1, 0)); //cam_pos and cam_target set in update!
	mat4 projection_matrix = glm::perspective(60.0f, (float)(g_ViewportWidth / g_ViewportHeight), 0.1f, 50.0f);
	mat4 model_matrix = translate_matrix*scale_matrix;
	mat3 normal_matrix = inverseTranspose((mat3(model_matrix)));




	//Diffuse color
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id_planetas[6]);

	//We upload the uniforms
	//send all values to shader
	glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(model_matrix));
	glUniformMatrix4fv(u_view, 1, GL_FALSE, glm::value_ptr(view_matrix));
	glUniformMatrix4fv(u_projection, 1, GL_FALSE, glm::value_ptr(projection_matrix));

	glUniform1i(u_texture, 0);

	glUniform3f(u_light_dir, -radio_rotacion*glm::cos(movimiento_neptuno), 0, -radio_rotacion*glm::sin(movimiento_neptuno));

	glUniform3f(u_light_color, 1, 1, 1);
	glUniform3f(u_ambient, 0.5, 0.5, 0.5);
	glUniform3f(u_cam_pos, cam_pos.x, cam_pos.y, cam_pos.z);
	glUniform1f(u_shininess, 100);

	glUniformMatrix3fv(u_normal_matrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));



	// Draw to back buffer
	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles, GL_UNSIGNED_INT, 0);

	//unbind vao and shader
	gl_unbindVAO();
	glUseProgram(0);

}
void drawSun(){
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// activate shader and VAO
	glUseProgram(g_ShaderProgram[2]);
	gl_bindVAO(g_Vao);


	//Las enlazamos con el shader
	GLuint u_model = glGetUniformLocation(g_ShaderProgram[2], "u_model");
	GLuint u_projection = glGetUniformLocation(g_ShaderProgram[2], "u_projection");
	GLuint u_view = glGetUniformLocation(g_ShaderProgram[2], "u_view");
	GLuint u_light_dir = glGetUniformLocation(g_ShaderProgram[2], "u_light_dir");
	GLuint u_light_color = glGetUniformLocation(g_ShaderProgram[2], "u_light_color");
	GLuint u_cam_pos = glGetUniformLocation(g_ShaderProgram[2], "u_cam_pos");
	GLuint u_shininess = glGetUniformLocation(g_ShaderProgram[2], "u_shininess");
	GLuint u_normal_matrix = glGetUniformLocation(g_ShaderProgram[2], "u_normal_matrix");
	GLuint u_texture = glGetUniformLocation(g_ShaderProgram[2], "u_texture");
	GLuint u_ambient = glGetUniformLocation(g_ShaderProgram[2], "u_ambient");


	//set MVP
	float velocidad_rotacion = 0.1;
	float radio_rotacion = 2;
	float rotacion_sol = movimiento*velocidad_rotacion;
	float tamany_sol = 1;

	mat4 translate_matrix = translate(mat4(1.0f), vec3(0, 0, 0));
	mat4 scale_matrix = scale(mat4(1.0f), vec3(tamany_sol, tamany_sol,tamany_sol));
	mat4 view_matrix = lookAt(cam_pos, cam_target, vec3(0, 1, 0)); //cam_pos and cam_target set in update!
	mat4 projection_matrix = glm::perspective(60.0f, (float)(g_ViewportWidth / g_ViewportHeight), 0.1f, 50.0f);
	mat4 model_matrix = translate_matrix*scale_matrix;
	model_matrix = glm::rotate(model_matrix, rotacion_sol, glm::vec3(1, 0, 0));
	mat3 normal_matrix = inverseTranspose((mat3(model_matrix)));




	//Diffuse color
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id_planetas[7]);

	//We upload the uniforms
	//send all values to shader
	glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(model_matrix));
	glUniformMatrix4fv(u_view, 1, GL_FALSE, glm::value_ptr(view_matrix));
	glUniformMatrix4fv(u_projection, 1, GL_FALSE, glm::value_ptr(projection_matrix));

	glUniform1i(u_texture, 0);

	glUniform3f(u_light_dir, g_light_dir.x, g_light_dir.y, g_light_dir.z);

	glUniform3f(u_light_color, 1, 1, 1);
	glUniform3f(u_ambient, 200,200,200);
	glUniform3f(u_cam_pos, cam_pos.x, cam_pos.y, cam_pos.z);
	glUniform1f(u_shininess, 100);

	glUniformMatrix3fv(u_normal_matrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));



	// Draw to back buffer
	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles, GL_UNSIGNED_INT, 0);

	//unbind vao and shader
	gl_unbindVAO();
	glUseProgram(0);
}


// ------------------------------------------------------------------------------------------
// This function actually draws to screen
// ------------------------------------------------------------------------------------------
void onDisplay()
{
	movimiento = movimiento + 1;
	
	drawSkyBox();
	drawMars();
	drawEarth();
	drawMercury();
	drawVenus();
	drawMars();
	drawJupiter();
	drawSaturn();
	drawUranus();
	drawNeptune();
	drawSun();
	
	
	// Swap the buffers so back buffer is on screen 
	glutSwapBuffers();
}


// ------------------------------------------------------------------------------------------
// Load all resources (shaders and geometry in this case)
// ------------------------------------------------------------------------------------------
void loadResources()
{
	// Load shaders. Mac uses older version of OpenGL and needs
	// slighly different shaders
#ifdef __APPLE__
	Shader simpleShader("shader.vsh", "shader.fsh");
#else
	// In windows the path is relative to main.cpp location
	Shader simpleShader("../src/shader.vert", "../src/shader.frag");
	Shader texShader("../src/shader_tex.vert","../src/shader_tex.frag");
	Shader planetas_sin_bump("../src/planetas_sin_bump.vert", "../src/planetas_sin_bump.frag");
	
#endif
	g_ShaderProgram[0] = simpleShader.program;	//Pinta color diffuso con luz, luz specular con mapa y bump.
	g_ShaderProgram[1] = texShader.program;		//Para pintar solo color diffuso sin luz
	g_ShaderProgram[2] = planetas_sin_bump.program; //Calculan color diffuso con luz y luz especular sin mapping 
	// Crea la geomtria i desa-la al VAO
	createGeometry();
}

void onKeyDown(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		// exit the programme
		exit(EXIT_SUCCESS);
		break;
	case 'w':
		key_flags[0] = 1;
		break;
	case 'a':
		key_flags[1] = 1;
		break;
	case 's':
		key_flags[2] = 1;
		break;
	case 'd':
		key_flags[3] = 1;
		break;
	}
}


// --------------------------------------------------------------
// de-sets boolean flags for keys
// --------------------------------------------------------------
void onKeyUp(unsigned char key, int x, int y)
{
	switch (key)
	{

	case 'w':
		key_flags[0] = 0;
		break;
	case 'a':
		key_flags[1] = 0;
		break;
	case 's':
		key_flags[2] = 0;
		break;
	case 'd':
		key_flags[3] = 0;
		break;
	}
}


// --------------------------------------------------------------
// always update mouse coords, regardless of whether we are clicking or not
// --------------------------------------------------------------
void onMouseMove(int x, int y) {

	//save coords
	mouse_coords[0] = x;
	mouse_coords[1] = y;
}

// --------------------------------------------------------------
// only update camera pitch and yaw if we click-drag
// --------------------------------------------------------------
void onMouseMoveClick(int x, int y) {

	cam_yaw += (mouse_coords[0] - x) * LOOK_SPEED;
	cam_pitch += (mouse_coords[1] - y) * LOOK_SPEED;

	//save coords
	mouse_coords[0] = x;
	mouse_coords[1] = y;
}


// --------------------------------------------------------------
// GLUT callback detects window resize
// --------------------------------------------------------------
void onReshape(int w, int h)
{
	g_ViewportWidth = w;
	g_ViewportHeight = h;
	glViewport(0, 0, g_ViewportWidth, g_ViewportHeight);
}


// --------------------------------------------------------------
// rotate camera according to pitch and yaw,
// move camera according to key flags
// then render (glutPostRedisplay)
// --------------------------------------------------------------
void update() {

	//reset camera to look down z-axis
	vec3 initial_look_vector = vec3(0, 0, -1);
	//rotate look vector around y_axis (yaw)
	vec3 first_rotation = rotate(initial_look_vector, cam_yaw*57.19f, vec3(0, 1, 0));
	//rotate x-axis by same amount - this avoids gimbal lock
	vec3 intermediate_axis = rotate(vec3(1, 0, 0), cam_yaw*57.19f, vec3(0, 1, 0));
	//now rotate pitch around intermediate axis
	vec3 final_look_vector = rotate(first_rotation, cam_pitch*57.19f, intermediate_axis);

	//set camera target to be position + our new look vector
	cam_target = cam_pos + final_look_vector;

	//get forward and side vectors for movement
	vec3 forward = cam_target - cam_pos;
	vec3 side = cross(vec3(0, 1, 0), forward);

	// WASD = forward / back / strafe left / strafe right
	if (key_flags[0]) {
		cam_pos = cam_pos + (forward*MOVE_SPEED);
		cam_target = cam_target + (forward*MOVE_SPEED);
	}
	if (key_flags[1]) {
		cam_pos = cam_pos + (side*MOVE_SPEED);
		cam_target = cam_target + (side*MOVE_SPEED);
	}
	if (key_flags[2]) {
		cam_pos = cam_pos - (forward*MOVE_SPEED);
		cam_target = cam_target - (forward*MOVE_SPEED);
	}
	if (key_flags[3]) {
		cam_pos = cam_pos - (side*MOVE_SPEED);
		cam_target = cam_target - (side*MOVE_SPEED);
	}

	// tell window to render
	glutPostRedisplay();
}



int main(int argc, char* argv[]) {

	//initalise GLUT - GLUT is a windowing toolkit designed to help us make 
	//OpenGL apps on MS Windows
	glutInit(&argc, argv);
	//screen format and precision
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	//window size
	glutInitWindowSize(g_ViewportWidth, g_ViewportHeight);
	//create the window
	glutCreateWindow("Hello graphics!");

	//Init GLEW - glew allows us to use loads of useful opengl functions, especially on Windows
	//it's not 100% necessary though
#if !defined(__APPLE__)
	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
		return EXIT_FAILURE;
	}
#endif

	// Clear the background colour to our global variable
	glClearColor(g_backgroundColor.x, g_backgroundColor.y, g_backgroundColor.z, 1.0f);

	// Load resources
	loadResources();

	//this line is very important, as it tell GLUT what function to execute
	//every frame (which should be our draw function)
	glutDisplayFunc(onDisplay);

	//tell GLUT about all our callback functions
	glutKeyboardUpFunc(onKeyUp);
	glutKeyboardFunc(onKeyDown);
	glutReshapeFunc(onReshape);
	glutPassiveMotionFunc(onMouseMove);
	glutMotionFunc(onMouseMoveClick);
	glutIdleFunc(update);

	//start everything up
	glutMainLoop();

	return EXIT_SUCCESS;
}

