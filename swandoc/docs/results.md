# Performances et résultats

## Résultats obtenus

Dans cette section, nous discutons des résultats obtenus, que ce soit des performances en elles-mêmes, ou que ce soit de la cohérence de la simulation avec les prédictions faites en 2003 par le CEA.
Nous commençons par analyser les résultats de la simulation, puis nous finissons par les mesures de performances qui ont été effectuées.

Vous trouverez ci-dessous les résultats de la propagation du tsunami de Boumerdes calculés par le programme *swangeo* et les résultats de référence calculé par le CEA en 2003
Ces dernières données sont les durées minimales théoriques d'arrivées.
Nous pouvons remarquer que la valeur calculée par *swangeo* au niveau de la ville de Leucate (ville représentée la plus à gauche) n'est pas cohérente avec les données de référence. 
Nous n'avons pas d'explication pour cela pour l'instant.

Concernant la ville de Fos-sur-mer, nous avons calculé un temps d'arrivée de 95 minutes alors que la référence est de 120 minutes.
Bien que celà soit cohérent (95 < 120), la différence reste assez importante.
Pour toutes les autres villes, les temps d'arrivées calculés sont en adéquation avec les données de référence.
De plus, la forme de la première vague correspond bien à celle de la vague de référence.

### Temps de référence d'arrivée du Tsunami

<img src="./img/simulationBoumerdesAnnotationCEA.svg" alt="Temps d'arrivée du Tsunami calculé par le CEA" title="Temps d'arrivée du Tsunami calculé par le CEA"/>

### Temps d'arrivée du Tsunami calculé avec SwanGeo

<img src="./img/simulationBoumerdesAnnotationCalc.svg" alt="Temps d'arrivée du Tsunami calculé avec SwanGeo" title="Temps d'arrivée du Tsunami calculé avec SwanGeo"/>


## Performances

Regardons maintenant les mesures de performances qui ont été effectués.
Nous n'avons traité que les codes générés avec les backends C++ Multithread STL et C++ Multithread Kokkos.
Nous avons étudier les propriétés de scalabilité forte.
Les mesures ont été faites sur le programme *swan* avec un cas test *canal* disponible dans le répertoire *usecases*.
La version testée était encore en développement aux moments des mesures, mais les algorithmes effectuant la quasi totalité des calculs étaient déjà implémentés.

### Scalabilité forte

Pour étudier la scalabilité forte, il faut doubler la puissance de calcul.
Ici on double le nombre de processeurs en conservant la taille du problème constante (taille du maillage).

Dans l'idéal, en doublant le nombre de processeurs, le temps de calcul devrait être divisé par deux.
Ce résultat est théorique, en pratique, le gain de temps est beaucoup moins élevé.
Le but est seulement de s'approcher le plus possible d'un facteur deux.
Nous avons étudié la scalabilité forte en faisant varier le pas d'écriture.
Cela nous a permis de prouver que ce pas était un facteur limitant.

Nous avons également étudié la scalabilité forte, en fonction de la taille du maillage pour le backend C++ Multithread STL.

<img src="./img/scala_forte_stl_mesh_var.png" alt="scala_forte_stl_mesh_var"/>

<img src="./img/scala_forte_stl_step.png" alt=" scala_forte_stl_step"/>

<img src="./img/scala_forte_kokkos_step.png" alt="scala_forte_kokkos_step"/>

Sur les 3 graphes ci-dessus, lorsque la taille du maillage n'est pas précisée, celle-ci est de 50 000 mailles.
Nous pensons que c'est ce qui explique le fait que les durées d'exécution en fonction du nombre de processeurs utilisé sont relativement constantes, pour un pas d'écriture donné.
La création des threads est coûteuse et masque tout possible gain de performance.

Sur le premier graphe, le pas d'écriture est pris suffisamment grand pour qu'il n'ait quasiment aucun impact sur le temps de calcul.
Ce graphe nous montre bien qu'un gain de performance est présent dès que la taille du maillage augmente. 
Nous remarquons qu'avec 32 coeurs, les performances se dégradent un peu. Les points correspondant semblent aberrants. Il s'agit sans doute d'un problème provoqué par la machine de test.

### Travaux à mener

Nous pensons qu'il serait intéressant de tester les performances sur une machine disposant de GPU, en utilisant le backend de parallélisation KokkosTeamThread.
Faire des tests de scalabilité faible en faisant varier le pas d'écriture pourrait également donner des résultats intéressants.
La version C++ Multithread STL, libéré du facteur limitant qu'est le pas d'écriture, n'a pas montré de propriétés de scalabilité forte.
Nous nous attendons à ce qu'il en soit de même pour la scalabilité faible.
Cependant, la version C++ Multithread Kokkos a montré une certaine scalabilité forte, quoiqu'imparfaite, laissant penser qu'il y a une certaine scalabilité faible grâce à Kokkos.
Nous invitons le lecteur à s'intéresser aux courbes présentes ci-dessus pour en savoir un peu plus.

