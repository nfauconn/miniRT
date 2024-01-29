[![en](https://img.shields.io/badge/lang-en-pink.svg)](https://github.com/nfauconn/miniRT/blob/master/README.md)
[![fr](https://img.shields.io/badge/lang-fr-purple.svg)](https://github.com/nfauconn/miniRT/blob/master/README.fr.md)

# Project: MiniRT

## 🏁 Goal 🏁

The goal of the program is to generate images using the Raytracing protocol. Those computer-generated images will each represent a scene, as seen from a specific angle and position, defined by simple geometric objects, and each with its own lighting system.

## 🚀 Usage 🚀

```shell
git clone git@github.com:nfauconn/miniRT.git
cd miniRT/Project
make
```

```shell
./miniRT <scene.rt>
```

Scenes examples are located in `scenes/`

If you want to create your own, here are the specifications:

- Each type of element can be separated by one or more line break(s).
- Each type of information from an element can be separated by one or more space(s).
- Each type of element can be set in any order in the file.
- Each element first’s information is the type identifier (composed by one or two character(s)), followed by all specific information for each object in a strict order such as:
- **Ambient lightning**:
	```
	A 0.2 255,255,255
	```
	- identifier: A
	- ambient lighting ratio in range [0.0,1.0]: 0.2
	- R,G,B colors in range [0-255]: 255, 255, 255
- **Camera**:
	```
	C -50.0,0,20 0,0,1 70
	```
	- identifier: C
	- x,y,z coordinates of the view point: -50.0,0,20
	- 3D normalized orientation vector. In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0
       - FOV : Horizontal field of view in degrees in range [0,180]: 70
- **Light(s):**
	```
	L -40.0,50.0,0.0 0.6 10,0,255
	```
	- identifier: L
	- x,y,z coordinates of the light point: -40.0,50.0,0.0
	- the light brightness ratio in range [0.0,1.0]: 0.6
	- R,G,B colors in range [0-255]: 10, 0, 255
- **Sphere(s)**:
	```
	sp 0.0,0.0,20.6 12.6 10,0,255
	```
	- identifier: sp
	- x,y,z coordinates of the sphere center: 0.0,0.0,20.6
	- the sphere diameter: 12.6
	- R,G,B colors in range [0-255]: 10, 0, 255
- **Plane(s):**
	```
	pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
	```
	- identifier: pl
	- x,y,z coordinates of a point in the plane: 0.0,0.0,-10.0
	- 3d normalized normal vector. In range [-1,1] for each x,y,z axis: 0.0,1.0,0.0
	- R,G,B colors in range [0-255]: 0,0,225
- **Cylinder(s):**
	```
	cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
	```
	- identifier: cy
	- x,y,z coordinates of the center of the cylinder: 50.0,0.0,20.6
	- 3d normalized vector of axis of cylinder. In range [-1,1] for each x,y,z axis:
	0.0,0.0,1.0
	- the cylinder diameter: 14.2
	- the cylinder height: 21.42
	- R,G,B colors in range [0,255]: 10, 0, 255

## 💡 Skills 💡



## 📋 Project Instructions 📋

### Rules

| | |
|--|--|
| Program name | miniRT |
Turn in files | `Makefile`, `*.h`, `*.c`
Makefile  | `NAME`, `all`, `clean`, `fclean`, `re` 
Arguments | a scene in format `*.rt`
External functs. | `open`, `close`, `read`, `write`, `printf`, `malloc`, `free`, `perror`, `strerror`, `exit` - all functions of the math library (`-lm man man 3 math`) - all functions of the MinilibX

### Graphics Library

For graphical display management and window manipulation, this project utilizes the `minilibX` graphics library. This library, specifically developed for students at École 42, offers a straightforward interface for creating graphic windows and managing keyboard/mouse events.

### Common Instructions

- **Language**: The project must be written in C.
- **Norm Compliance**: Code must adhere to the Norm of the school.
- **Error Handling**: Programs should not exit unexpectedly (e.g., segmentation fault, bus error, double free). Such incidents will render the project non-functional and result in a score of 0.
- **Memory Management**: All heap allocated memory must be properly freed. Memory leaks are not tolerated.
- **Makefile Requirements**:
   - Must compile source files to the required output with flags `-Wall`, `-Wextra`, and `-Werror`.
   - Must not relink.
