# Arborescence des fichiers

Nous allons dans cette partie expliquer l'organisation du projet en différents répertoires.
Nous détaillerons le contenu de chacun de ceux-ci.

!!! note
	Nous verrons des dossiers appelés *swan* et *swangeo*, En effet, le code SWAN est disponible en deux versions légèrement différentes:
	
	- *swan* prend en paramètre des fichiers *.grd* en coordonnées CARTESIENNES.
	- *swangeo* prend en paramètre des fichiers *.grd* en coordonnées GEOGRAPHIQUES.
	
	Les fichiers sources en langage NabLab sont quasiment identiques, le schéma numérique est lui exactement identique. 
	La différence est que les pas d'espace sont les mêmes pour toutes les mailles du maillage dans *swan*, et dépendent du couple (latitude / longitude) dans *swangeo*.

Liste des répertoires:

- META-INF : contient un fichier d'information à destination de NabLab.
- data : jeux de données
	- swan : bathymétries et surfaces d'eau en coordonnées CARTESIENNES, au format .grd (.nc), à n'utiliser qu'avec le programme *swan*.
    - swangeo : idem pour *swangeo*.
- src-gen-cpp/stl-thread : le répertoire de génération C++
	- swan : fichiers du code source C++ du programme *swan* et fichier *CMakeLists.txt* pour la compilation.
    - swangeo : iden pour *swangeo*. 
- src-gen : répertoire de génération Json et TeX
	- swan : contient un fichier *Swan.tex*, une représentation du fichier source *Swan.n* sous forme de fichier LaTeX, ainsi qu'un exemple de fichier Json.
    - swangeo : idem pour *swangeo*
- src : répertoire des fichiers de code source de l'utilisateur
	- bathylib : contient les fichiers *BathyLib.n* et *BathyLib.ngen* qui définissent respectivement l'extension BathyLib et le provider C++ de l'extension 
	- swan : contient le fichier de code source *Swan.n* et le fichier de configuration de la génération de l'application *Swan.ngen*
    - swangeo : idem pour *swangeo*
- usecases : répertoire contenant les cas tests
	- swan : jeux de données au format *.json*, destinés à être personnalisés par l'utilisateur. Nous rappelons que ces fichiers sont à donner en argument du programme *swan* uniquement.
		- squareGaussCases : jeux de données au format *.json*, ainsi qu'une vidéo par cas test montrant le résultat que l'on obtient après simulation, en utilisant le fichier json en question. Le contenu de ce sous dossier n'est pas destiné à être modifié par l'utilisateur.
    - swangeo : jeux de données au format *.json*, destinés à être personnalisés par l'utilisateur. Nous rappelons que ces fichiers sont à donner en argument du programme *swangeo* uniquement.
    	- mediterrCases : jeux de données au format *.json*, ainsi qu'une vidéo par cas test montrant le résultat que l'on obtient après simulation, en utilisant le fichier json en question. 
    	Ces cas tests concernent le tsunami provoqué par le séisme de Boumerdes, 2003. Le contenu de ce sous dossier n'est pas destiné à être modifié par l'utilisateur. 
    	- mediterranee2021 : eux de données au format *.json*. Ce cas test concerne le tsunami provoqué par le séisme de Mars 2021 au large de l'Algérie.
