[![en](https://img.shields.io/badge/lang-en-pink.svg)](https://github.com/nfauconn/miniRT/blob/master/README.md)
[![fr](https://img.shields.io/badge/lang-fr-purple.svg)](https://github.com/nfauconn/miniRT/blob/master/README.fr.md)

# Projet : MiniRT

## 🏁 Objectif 🏁

Le but du programme est de générer des images en utilisant le protocole de Raytracing. Ces images générées par ordinateur représenteront chacune une scène, vue sous un angle et une position spécifiques, définis par des objets géométriques simples, et chacune dotée de son propre système d'éclairage.

## 🚀 Utilisation 🚀

```shell
git clone git@github.com:nfauconn/miniRT.git
cd miniRT/Project
make
```

```shell
./miniRT <scene.rt>
```

Des exemples de scènes se trouvent dans `scenes/`

<img src="./.pics/multi_colo_lights_from_up.png">
<img src="./.pics/cylindre.png">
<img src="./.pics/multicolorlightsdhadows.png">
<img src="./.pics/2sp1pl.png">

Si vous souhaitez changer le ratio, vous pouvez modifier les valeurs de `WIDTH` et `HEIGHT` dans `includes/miniRT.h`

Si vous souhaitez créer votre propre scène, voici les spécifications :

- Chaque type d'élément peut être séparé par un ou plusieurs sauts de ligne.
- Chaque type d'information provenant d'un élément peut être séparé par un ou plusieurs espace(s).
- Chaque type d'élément peut être défini dans n'importe quel ordre dans le fichier.
- Les lumières, sphères, cylindres et plans peuvent être multiples.

- La première information de chaque élément est l'identifiant du type (composé d'un ou deux caractère(s)), suivi de toutes les informations spécifiques à chaque objet dans un ordre strict, tel que :
- **Éclairage ambiant** :
	```
	A	0.2		255,255,255
	```
	- identifiant : A
	- ratio d'éclairage ambiant dans l'intervalle [0,1] : 0.2
	- couleurs R,V,B dans l'intervalle [0-255] : 255, 255, 255
- **Caméra** :
	```
	C	-50,0,20	0,0,1	70
	```
	- identifiant : C
	- coordonnées x,y,z du point de vue : -50,0,20
	- vecteur d'orientation normalisé 3D. Dans l'intervalle [-1,1] pour chaque axe x,y,z : 0,0,1
    - FOV : Champ de vision horizontal en degrés dans l'intervalle [0,180] : 70
- **Lumière** :
	```
	L	-40,50,0	0.6		10,0,255
	```
	- identifiant : L
	- coordonnées x,y,z du point lumineux : -40,50,0
	- ratio de luminosité de la lumière dans l'intervalle [0,1] : 0.6
	- couleurs R,V,B dans l'intervalle [0-255] : 10, 0, 255
- **Sphère** :
	```
	sp	0,0,20.6	12.6	10,0,255
	```
	- identifiant : sp
	- coordonnées x,y,z du centre de la sphère : 0,0,20.6
	- diamètre de la sphère : 12.6
	- couleurs R,V,B dans l'intervalle [0-255] : 10, 0, 255
- **Plan** :
	```
	pl	0,0,-10	0,1,0	0,0,225
	```
	- identifiant : pl
	- coordonnées x,y,z d'un point dans le plan : 0,0,-10
	- vecteur normal normalisé 3D. Dans l'intervalle [-1,1] pour chaque axe x,y,z : 0,1,0
	- couleurs R,V,B dans l'intervalle [0-255] : 0,0,225
- **Cylindre** :
	```
	cy	50,0,20.6	0,0,1	14.2	21.42	10,0,255
	```
	- identifiant : cy
	- coordonnées x,y,z du centre du cylindre : 50,0, 20.6
	- vecteur normalisé 3D de l'axe du cylindre. Dans l'intervalle [-1,1] pour chaque axe x,y,z :
	0,0,1
	- diamètre du cylindre : 14.2
	- hauteur du cylindre : 21.42
	- couleurs R,V,B dans l'intervalle [0-255] : 10, 0, 255

## 💡 Compétences 💡

- **Rendu graphique 3D** :
   - Principes de base du lancer de rayons pour générer des images réalistes
   - Modèle de réflexion de Phong pour un éclairage et un ombrage réalistes

- **Calcul géométrique** :
   - Concepts mathématiques de géométrie et d'algèbre linéaire
   - Transformations géométriques telles que la translation et la rotation à l'aide de matrices

- **Programmation graphique** :
   - Bibliothèque graphique (miniLibX) pour créer et gérer des fenêtres
   - Manipulation de pixels pour rendre des images à l'écran

- **Éclairage et ombrage** :
   - Différents modèles d'éclairage, y compris l'éclairage ambiant, diffus et spéculaire
   - Sources lumineuses multiples et éclairage coloré pour améliorer le réalisme

- **Gestion des données** :
   - Structures de données organisées pour représenter des objets 3D, des lumières et des caméras

- **Analyse syntaxique et I/O de fichiers** :
   - Analyse de fichiers de description de scènes
   - Opérations d'I/O pour lire les configurations de scènes et gérer les erreurs

- **Utilisation de la bibliothèque mathématique** :
    - Maîtrise de l'utilisation des fonctions de la bibliothèque mathématique pour des opérations mathématiques complexes et des transformations

- **Gestion de la mémoire** :
   - Compréhension approfondie de l'allocation et de la libération dynamique de la mémoire
   - Capacité à gérer la mémoire de manière efficace et à prévenir les fuites dans une application complexe

- **Gestion des erreurs et validation** :
   - Gestion des erreurs et messages d'erreur significatifs
   - Validation et assainissement des données d'entrée pour assurer la stabilité de l'application

- **Makefile et Compilation** :
   - Compilation, nettoyage et recompilation du projet
   - Pas de reconnexion des fichiers objets

- **Tests unitaires et débogage** :
    - Rédaction et maintenance de tests unitaires tout au long de la construction du projet en utilisant Criterion pour un code robuste et fiable
    - Débogage de systèmes complexes et assurance de la justesse de l'implémentation

## 📋 Instructions du Projet 📋

### Règles

| | |
|--|--|
| Nom du programme | miniRT |
Fichiers à rendre | `Makefile`, `*.h`, `*.c`
Makefile  | `NAME`, `all`, `clean`, `fclean`, `re`
Arguments | une scène au format `*.rt`
Fonctions externes | `open`, `close`, `read`, `write`, `printf`, `malloc`, `free`, `perror`, `strerror`, `exit` - toutes les fonctions de la bibliothèque mathématique (`-lm man man 3 math`) - toutes les fonctions de la MinilibX

### Bibliothèque graphique

Pour la gestion de l'affichage graphique et la manipulation des fenêtres, ce projet utilise la bibliothèque graphique `minilibX`. Cette bibliothèque, spécifiquement développée pour les étudiants de l'École 42, offre une interface simple pour créer des fenêtres graphiques et gérer les événements clavier/souris.

### Instructions Communes

- **Langage**: Le projet doit être écrit en C.
- **Conformité aux Normes**: Le code doit adhérer aux normes de l'école.
- **Gestion des erreurs**: Les programmes ne doivent pas se fermer de manière inattendue (par exemple, faute de segmentation, erreur de bus, double libération de mémoire). De tels incidents rendront le projet non fonctionnel et entraîneront une note de 0.
- **Gestion de la mémoire** : Toute la mémoire allouée sur le tas doit être correctement libérée. Les fuites de mémoire ne sont pas tolérées.
- **Exigences du Makefile**:
   - Doit compiler les fichiers sources pour obtenir le résultat attendu avec les drapeaux `-Wall`, `-Wextra`, et `-Werror`.
   - Ne doit pas être relié à nouveau.