

# TODO
## instant fixes
- `closed` keyword support for scene files
- check that `origin` and `translation` are both applied
- antialiasing to combat the cone jagged edge issue with certain pixel ratios
	- FXAA, subsampling + supersampling -> configurable from .json
---
## future
- store references to intersections within the object as well as the sorted vector
	- this allows easier dereferencing of a parent object intersections in case of limited objects
- time the rendering phase and accept input in the middle of rendering (justified bonus library)
- shasum from .json file to keep track of changes in scene

---
