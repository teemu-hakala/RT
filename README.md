# Explanation
- two remotes (github and vogsphere)
- feature-based branching
---
# Complete
- `closed` keyword support for scene files

# To do
## instant fixes
- check that `origin` and `translation` are both applied
	- (remove origin from parser)
- antialiasing to combat the cone jagged edge issue with certain pixel ratios
	- FXAA, subsampling + supersampling -> configurable from .json
- object IDs?
- remove 42 headers
- SIGSEGV on empty file

---
## future
- store references to intersections within the object as well as the sorted vector
	- this allows easier dereferencing of a parent object intersections in case of limited objects
- time the rendering phase and accept input in the middle of rendering (justified bonus library)
- shasum from .json file to keep track of changes in scene
- lights within transparent objects (christmas tree scene)

---
# Evaluation
### (Check VIDEO and DEMO renders)
- https://cdn.intra.42.fr/video/video/921/rtv1-rt_en.mp4
- https://projects.intra.42.fr/projects/rt
## Eval form
- The group is organised, time is managed well
- Submit the project
- Author file
- `norminette`
- Everyone is present
- No recalculation on expose. For `mlx`: use of `mlx_expose_hook`
- Prepare scenes for validation (Images in subject)
- 4 basic shapes. (Plane, Sphere, Cone, Cylinder)
- Eye anywhere, in any direction
- Multilight
	- brightness
	- shadows
	- shine effect
	- specular spot
- scene file++ (hierarchical file)
- ambiance light++ (configurable)

...

- parented object limitations (shaped slices of a place limit the parent object)
---
