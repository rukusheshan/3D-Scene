#include "windowManager.h"
#include "MeshBuilder.h"
#include "Shader.h"
#include "Loader.h"
#include "Model.h"
#include "Plane.h"
#include "Texture.h"
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

void renderPlane(Plane plane, Shader shader, Camera camera, Light light, Material material) {
	glUniformMatrix4fv(shader.transformLoc, 1, GL_FALSE, glm::value_ptr(plane.getTransform()));
	glUniformMatrix4fv(shader.combinedLoc, 1, GL_FALSE, glm::value_ptr(camera.getCombined()));
	glUniform3f(shader.viewPosLoc, camera.position.x, camera.position.y, camera.position.z);
	floatUniforms(light, material, shader);
}

void renderMesh(Model model, Shader shader, Camera camera, Light light, Material material) {
	glUniformMatrix4fv(shader.transformLoc, 1, GL_FALSE, glm::value_ptr(model.getTransform()));	
	glUniformMatrix4fv(shader.combinedLoc, 1, GL_FALSE, glm::value_ptr(camera.getCombined()));
	glUniform3f(shader.viewPosLoc, camera.position.x, camera.position.y, camera.position.z); 
	floatUniforms(light, material, shader);
}

windowManager wManager; 
const char* vertexFile = "Shaders/vertexShader.txt";
const char* fragmentFile = "Shaders/fragmentShader.txt";

int main() {
	wManager.WIDTH = 900;
	wManager.HEIGHT = 600;
	wManager.init();
	MeshBuilder meshbuilder;
	Shader shader(vertexFile, fragmentFile);
	Loader loader;
	Light light;
	Material material;
	LightShader lightShader;
	OBJLoader objLoader;
	
	int VAO = loader.loadPlane(meshbuilder.plane, 32, meshbuilder.indices, 6);
	int cubeVAO = loader.loadCube(meshbuilder.cube, 288);
	int imageTexture = loader.loadTexture("./Assets/images.jpg");
	int cubeID = loader.loadTexture("./Assets/awesomeface.png");
	int stallID = loader.loadTexture("./Assets/Stall/stallTexture.png");

	objLoader.LoadFromFile("./Assets/Stall/stall.obj");
	int modelVAO = loader.loadModel(objLoader.getVertices(), objLoader.getNormals(), objLoader.getTexCoords(), objLoader.getFaceVertices());
	Mesh stall(modelVAO, objLoader.getFaceVertices().size() / 3);
	//objLoader.clear();

	Texture textureID(imageTexture), cubeTexture(cubeID), stallTexture(stallID);


	Camera camera(45.0f, wManager.WIDTH / wManager.HEIGHT, 0.1f, 100.0f,
		glm::vec3(0.0f, 1.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 3.0f, 0.05f);
	Plane plane;
	Model cube(cubeVAO);
	Model cube1(cubeVAO);
	Model cube2(cubeVAO);
	Model cube3(cubeVAO);
	Model cube4(cubeVAO);
	Model cube5(cubeVAO);

	Model stallModel(modelVAO);
	cube.setPosition(0.3f, 0.1f, 0.0f);
	cube1.setPosition(-0.3f, 0.1f, 0.0f);
	cube2.setPosition(0.3f, 0.1f, -0.2f);
	cube3.setPosition(0.7f, 0.1f, 0.0f);
	cube4.setPosition(0.7f, 0.1f, -0.0f);
	cube5.setPosition(-0.7f, 0.1f, -0.2f);


	stallModel.setPosition(0.0f, 0.0f, 0.0f);

	do {
		wManager.preRender();
		wManager.calculateDelta();

		camera.KeyControl(wManager.getKeys(), wManager.getDelta());
		camera.MouseControl(wManager.getXChange(), wManager.getYChange());

		shader.start();
		plane.update();
		renderPlane(plane, shader, camera, light, material);
		glBindTexture(GL_TEXTURE_2D, imageTexture);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	
		cube.update(wManager.getDelta());
		renderMesh(cube, shader, camera, light, material);
		glBindTexture(GL_TEXTURE_2D, cubeID);
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 288);

		cube1.update(wManager.getDelta());
		renderMesh(cube1, shader, camera, light, material);
		glBindTexture(GL_TEXTURE_2D, cubeID);
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 288);

		cube2.update(wManager.getDelta());
		renderMesh(cube2, shader, camera, light, material);
		glBindTexture(GL_TEXTURE_2D, cubeID);
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 288);

		cube3.update(wManager.getDelta());
		renderMesh(cube3, shader, camera, light, material);
		glBindTexture(GL_TEXTURE_2D, cubeID);
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 288);

		cube4.update(wManager.getDelta());
		renderMesh(cube4, shader, camera, light, material);
		glBindTexture(GL_TEXTURE_2D, cubeID);
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 288);

		cube5.update(wManager.getDelta());
		renderMesh(cube5, shader, camera, light, material);
		glBindTexture(GL_TEXTURE_2D, cubeID);
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 288);

		stallModel.update(wManager.getDelta());
		renderMesh(stallModel, shader, camera, light, material);
		glBindTexture(GL_TEXTURE_2D, stallID);
		glBindVertexArray(modelVAO);
		glDrawElements(GL_TRIANGLES, stall.getnumIndices(), GL_UNSIGNED_INT ,0 );

		glUseProgram(lightShader.lightShaderProg);
		renderLight(light, lightShader, camera);
		glBindVertexArray(cubeVAO);
	//	glDrawArrays(GL_TRIANGLES, 0, 288);
		glUseProgram(0);
	    wManager.update();
	} while (wManager.closeNotRequested());
}