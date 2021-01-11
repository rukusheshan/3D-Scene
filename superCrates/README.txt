executable folder have the exe file of the project.
external folder has all the graphics library that are used.
supercrates folder has all the classes for the project.

superCrates/Assets - has all the textures and model for the project.
superCrates/Shaders - has two shader file vertex and fragment shader.

Camera class has implementation of a flexible camera (am not satisfied to call it as FPS camera).
Shader class reads the shader file from the shader file, compiles and returns the shader ID.
Texture class returns the texture ID.
Loader class handles the creation of openGL buffers and loads relevant data.
OBJLoader file reads the OBJ file .
windowManager handles all the window operations.
Material class implements Phong lighting model for plane.
Mesh handles meshID
Model handles the transform of the Mesh
Light and LightShader class renders the light in the scene. 
MeshBuilder has the basic vertices of the primitives



