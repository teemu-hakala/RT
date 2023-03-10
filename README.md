# Raytracer in C
## Final Hive project

### Task:
Create a 3d graphics renderer to simulate light (raytracer) in C from a scene description file. 
A minimum of 4 shapes are required, all which should be able to be translated, rotated and scaled.
Multiple light sources are needed, and their position, brightness, colour and shininess should be able to be adjusted in the scene file. 

### Prerequisites
GCC compiler
(the project also requires the MLX library, but that can be found inside the repository)

### Building
```
git clone https://github.com/teemu-hakala/RT.git RT
cd RT
make
```

### Running
To run provide the scene file path as an argument to the executable. (See above to build executable)
Scene files can be found in the scenes folder.
eg :
``` ./RT scenes/bonuses/composed_elem.json ```


### Description
This raytracer was created with the help of "The Raytracer Challenge" book by James Buick.
All objects are unit objects, meaning their radius or side has a starting size of 1 unit, and are their origin is found at the world origin. 
Instead of changing an objects origin, each object has a transformation matrix, which holds the rotation, translation and scale inputed from the scene file. The inverse of this matrix is applied to the ray, in order to calculate the objects relative position in the 'world'. 
The Phong reflection model is used to simulate the reflection of light from the object's surface, allowing it to appear 3D.
Reflection and refraction cast secondary rays each time an object that is reflective/transparent is hit. The additional rays are limited in the code to a maximum of 5. 
Schlick's approximation is used to approximate the Fresnel effect on transparent surfaces. 
Textures are parsed from ppm type p3 files. Any image can be converted into a ppm3 file using ImageMagick's convert tool.  

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
- soft shadows interfere with the edges of objects with a high refractive index. 


### Images

<img width="504" alt="normal_disruption" src="https://user-images.githubusercontent.com/93197340/224333058-c7eed153-eb57-40ee-9a2d-b28bf00f9f9d.png">
<img width="497" alt="glass_sphere_with_airbubble" src="https://user-images.githubusercontent.com/93197340/224333069-b07f5100-188e-44ec-bea6-35ecc65b8a68.png">
<img width="796" alt="4_textured_objects" src="https://user-images.githubusercontent.com/93197340/224333076-f9ec6d20-b617-416f-aa36-b61878e954cd.png">
<img width="493" alt="composed_element_different_textures" src="https://user-images.githubusercontent.com/93197340/224333081-2d76e3a0-3fbe-46b2-9b54-c6f30519e388.png">
<img width="500" alt="earth" src="https://user-images.githubusercontent.com/93197340/224333087-4588ad76-9c22-42a4-8df6-1e15dff352d3.png">
<img width="778" alt="reflection_refraction_transparency" src="https://user-images.githubusercontent.com/93197340/224333426-c641d692-153d-4322-b349-2bad349f0368.png">
<img width="797" alt="interface" src="https://user-images.githubusercontent.com/93197340/224333066-67b3e533-0d00-48c2-bc0a-135ac88c45c8.png">

## :star: Credits
Jamis Buick [The Ray Tracer Challenge](http://raytracerchallenge.com/)

