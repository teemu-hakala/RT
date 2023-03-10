# Raytracer in C
## Final Hive project

### Task:
Create a 3d graphics renderer to simulate light (raytracer) in C from a scene description file. 
A minimum of 4 shapes are required, all which should be able to be translated, rotated and scaled.
Multiple light sources are needed, and their position, brightness, colour and shininess should be able to be adjusted in the scene file. 

### Installation / Prerequisites


### Description

### Features
- JSON parsed scene descriptions
- Ambient light
- Parallel light
- Reflection
- Transparency
- Refraction
- Patterns:
	- can be scaled, rotated, shifted
- Textures:
	- parsed with ppm3 files
	- can be applied to all objects with UV mapping
	- can be scaled, rotated, shifted	
- Normal disruption
- Soft shadows
- Composed elementes: cubes, made from 6 limited planes
- Multithreading
- Colour filters
- Screenshots of rendered images from inside the project
	- saved as ppm6 files
- Loading progress bar
- Live interaction with the scene
	- first person camera
- Skybox
- Makefile to run all the available scenes

### what's next?
If given more time, additional features could include:
- anti-aliasing
- perlin noise
- simplex noise
- negative objects
- bump mapping
- textures used to modify objects transparency
- groups

### Known issues
- ambient light not working when value is 0. 


### Images

