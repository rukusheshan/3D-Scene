#include "windowManager.h"
#include "MeshBuilder.h"
#include "Shader.h"
#include "Loader.h"
#include "Model.h"
#include "Light.h"
#include "LightShader.h"
#include "Material.h"
#include "OBJLoader.h"
#include "Camera.h"
#include <gtc/type_ptr.hpp>
#include <glm.hpp>

void floatUniforms(Light light, Material material, Shader shader) {
	glUniform3f(shader.lightPosLoc, light.position.x, light.position.y, light.position.z);
	glUniform3f(shader.ambLightLoc, light.getambient().x, light.getambient().y, light.getambient().z);
	glUniform3f(shader.diffLightLoc, light.getdiffuse().x, light.getdiffuse().y, light.getdiffuse().z);
	glUniform3f(shader.specLightLoc, light.getspecular().x, light.getspecular().y, light.getspecular().z);
	glUniform3f(shader.ambLoc, material.getambient().x, material.getambient().y, material.getambient().z);
	glUniform3f(shader.diffLoc, material.getdiffuse().x, material.getdiffuse().y, material.getdiffuse().z);
	glUniform3f(shader.specLoc, material.getspecular().x, material.getspecular().y, material.getspecular().z);
	glUniform1f(shader.constLoc, light.constant);
	glUniform1f(shader.lineLoc, light.linear);
	glUniform1f(shader.quadLoc, light.quadratic);
}

void renderLight(Light light, LightShader lightShader, Camera camera) {
	glUniformMatrix4fv(lightShader.transformLoc, 1, GL_FALSE, glm::value_ptr(light.getTransform()));
	glUniformMatrix4fv(lightShader.combinedLoc, 1, GL_FALSE, glm::value_ptr(camera.getCombined()));
}
void renderMesh(Model *model, Shader shader, Camera camera, Light light, Material material) {
	glUniformMatrix4fv(shader.transformLoc, 1, GL_FALSE, glm::value_ptr(model->getTransform()));
	glUniformMatrix4fv(shader.combinedLoc, 1, GL_FALSE, glm::value_ptr(camera.getCombined()));
	glUniform3f(shader.viewPosLoc, camera.position.x, camera.position.y, camera.position.z);
	floatUniforms(light, material, shader);
	for (auto m : model->getMeshes()) {
		glBindVertexArray(m->getVAO());
		glBindTexture(GL_TEXTURE_2D, m->getTextureID());
		glDrawElements(GL_TRIANGLES, m->getnumIndices(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}

windowManager wManager; 
const char* vertexFile = "Shaders/vertexShader.txt";
const char* fragmentFile = "Shaders/fragmentShader.txt";
float fov = 45.0f;
int main() {
	wManager.WIDTH = 900;
	wManager.HEIGHT = 600;
	wManager.init();

	MeshBuilder meshbuilder;
	Shader shader(vertexFile, fragmentFile);
	Light light;
	Material material;
	LightShader lightShader;

	Camera camera(fov, wManager.WIDTH / wManager.HEIGHT, 0.1f, 100.0f,
		glm::vec3(0.0f, 1.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 3.0f, 0.1f);

	Loader loader;
	LoaderData planeData = loader.CreateMesh(meshbuilder.plane, 32, meshbuilder.indices, 6);
	LoaderData cubeData = loader.CreateMesh(meshbuilder.cubeVertices, 192, meshbuilder.cubeIndices, 36);
	vector<LoaderData> stallData = loader.LoadModel("./Assets/Stall/stall.obj");
	
	planeData.textureID = loader.LoadTexture("./Assets/images.jpg");
	cubeData.textureID = loader.LoadTexture("./Assets/awesomeface.png");
	stallData[0].textureID = loader.LoadTexture("./Assets/Stall/stallTexture.png");
	
	vector<Model*> models;
	Model stallModel;
	for (auto d : stallData) {
		stallModel.addMesh(new Mesh(d.vao, d.indexCount, d.ebo, d.textureID));
		stallModel.RotateObject(180.0f);
	}
	models.push_back(&stallModel);

	Model plane, cubes[6];
	plane.addMesh(new Mesh(planeData.vao, planeData.indexCount, planeData.ebo, planeData.textureID));
	cubes[0].addMesh(new Mesh(cubeData.vao, cubeData.indexCount, cubeData.ebo, cubeData.textureID));
	cubes[1].addMesh(new Mesh(cubeData.vao, cubeData.indexCount, cubeData.ebo, cubeData.textureID));
	cubes[2].addMesh(new Mesh(cubeData.vao, cubeData.indexCount, cubeData.ebo, cubeData.textureID));
	cubes[3].addMesh(new Mesh(cubeData.vao, cubeData.indexCount, cubeData.ebo, cubeData.textureID));
	cubes[4].addMesh(new Mesh(cubeData.vao, cubeData.indexCount, cubeData.ebo, cubeData.textureID));
	cubes[5].addMesh(new Mesh(cubeData.vao, cubeData.indexCount, cubeData.ebo, cubeData.textureID));

	cubes[0].setPosition(-3, 1.25, 0.0);
	cubes[1].setPosition(-5, 0.25, 1.0);
	cubes[2].setPosition(2, 1.0, -6.0);
	cubes[3].setPosition(2, 1.0, 6.0);
	cubes[4].setPosition(7, 0.25, 1.0);
	cubes[5].setPosition(-7, 1, -9.0);
	
	models.push_back(&plane);
	
	for(int i = 0; i < 6 ;i++)
		models.push_back(&cubes[i]);

	do {
		wManager.preRender();
		wManager.calculateDelta();
		camera.KeyControl(wManager.getKeys(), wManager.getDelta());
		camera.MouseControl(wManager.getXChange(), wManager.getYChange());

		shader.start();
	
	
		for (auto m : models) {
			m->update(wManager.getDelta());
		}
		for (auto m : models) {
			renderMesh(m, shader, camera, light, material);
		}

		glUseProgram(lightShader.lightShaderProg);
		renderLight(light, lightShader, camera);
		glBindVertexArray(cubeData.vao);
	//	glDrawArrays(GL_TRIANGLES, 0, 288);
		glUseProgram(0);
	    wManager.update();
	} while (wManager.closeNotRequested());
}

void HandleScroll(GLFWwindow* window, double xOffset, double yOffSet)
{
	fov -= (float)yOffSet;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 45.0f)
		fov = 45.0f;
}