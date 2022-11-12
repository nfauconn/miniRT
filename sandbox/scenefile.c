A 0.2 255,255,255
/*
Ambiant light
can only be one
first element is intensity (from 0.0 to 1.0)
next is color in RGB format (from 0 to 255)
*/

//RAY-CASTER
C -50,0,20       0,0,0        70
/*
Camera
can only be one
coordonnées x,y,z du point de vue : 0.0,0.0,20.6 en coordonnes cartesiennes
Vecteur d’orientation 3d dans le range [-1,1] pour chaque axe x,y,z 0.0,0.0,1.0
FOV : Champ de vision horizontal en degrés dans le range [0,180]
*/
L -40,0,30    0.7    255,255,255
/*
Lightsource
Can be multiples but only for bonus
coordonnées x,y,z du point Lumière : 0.0,0.0,20.6 en coordonnes cartesiennes
ratio de lumnosité dans le range [0.0,1.0] : 0.7
(non utilisé dans la partie obligatoire) Couleurs R,G,B dans le range [0-
255] : 10, 0, 255
*/

//FORMES
pl 0.0,0.0,0.0    0,1.0,0       255,0,225
/*
plan
Can be multiples
identifiant : pl
coordonnées x,y,z du point f 0.0,0.0,0.0
Vecteur d’orientation 3d dans le range [-1,1] pour chaque axe x,y,z : 0.0,0.0,1.0
Couleurs R,G,B dans le range [0-255] : 0, 0, 255
Bonus :
damier : ?????
bump map : ????
*/
sp 0,0,20       20       255,0,0
/*
sphere
Can be multiples
identifiant : sp
coordonnées x,y,z du point sphere : 0.0,0.0,20.6
the sphere diameter : 20
Couleurs R,G,B dans le range [0-255] : 10, 0, 255
Bonus :
damier : ?????
bump map : ????
*/
cy 50.0,0.0,20.6      0,0,1.0         14.2      21.42      10,0,255
/*
cylindre
Can be multiples
identifiant : cy
coordonnées x,y,z du point f   50.0,0.0,20.6
Vecteur d’orientation 3d dans le range [-1,1] pour chaque axe x,y,z : 0.0,0.0,1.0
diamètre du cylindre : 14.2
hauteur du cylindre : 21.42
Couleurs R,G,B dans le range [0,255] : 10, 0, 255
Bonus :
damier : ?????
bump map : ????
*/

/*if new shapes, need as much informations about it in the same ways:
center
vecteur
length
height
depth
etc.
colors
bump map
checkerboard
*/