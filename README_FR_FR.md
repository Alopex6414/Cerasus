# Cerasus🌸
Ce programme est un projet de bibliothèque de liens dynamiques Render Cerasus DirectX.

## La langue
  * [English](https://github.com/Alopex6414/Cerasus/blob/master/README.md)
  * [简体中文](https://github.com/Alopex6414/Cerasus/blob/master/README_ZH_CN.md)
  * [繁體中文](https://github.com/Alopex6414/Cerasus/blob/master/README_ZH_TW.md)
  * [日本語](https://github.com/Alopex6414/Cerasus/blob/master/README_JA_JP.md)
  * [русский](https://github.com/Alopex6414/Cerasus/blob/master/README_RU_RU.md)
  * [Français](https://github.com/Alopex6414/Cerasus/blob/master/README_FR_FR.md)

## Abstrait
Ce projet concerne principalement les jeux DX9, la vidéo, le rendu du papier peint, la musique, les effets sonores, le jeu des enceintes, le clavier, la souris, le contrôle par joystick et certaines programmations liées au jeu. La bibliothèque est conçue pour le développement, le débogage, les tests et le déploiement rapides et faciles de jeux, d'applications et de graphiques. Le nom de Cerasus a été adopté car il signifie «fleur de cerisier» en latin et est aussi coloré que notre jeu.

## Constitutions
Cerasus se compose désormais de 4 parties: la classe **Direct** responsable du rendu graphique sous-jacent DirectX, la classe **Cerasus** pour les algorithmes de physique de jeu, la classe **Sakura** pour les interfaces d'interaction GUI et le **DXUI** classe pour la gestion du rendu.
* **Les classes directes sont principalement responsables de la partie sous-jacente de DirectX, telles que le rendu graphique, les effets musicaux, les interactions de jeu, le décodage vidéo, les systèmes de particules, etc.**
* **La classe Cerasus est principalement responsable des parties centrales et auxiliaires du jeu, y compris des algorithmes physiques, des primitives de base, l’affichage du rafraîchissement fps, etc.**
* **La classe Sakura est principalement responsable des interactions de jeu, telles que scènes, boîtes de dialogue, boutons, etc.**
* **La classe DXUI est principalement responsable de la gestion du jeu, notamment des scripts de jeu, du décodage des ressources et de la gestion de la planification, qui ne sont pas terminés pour l'instant ...**

## Caractéristiques
  * ### DirectClass
    * #### *`DirectCommon` est un fichier d'en-tête public DirectX contenant les fichiers d'en-tête` DirectX9` et `DirectX11`, des fichiers de bibliothèque et certaines macros courantes, ainsi que des fonctions dans la bibliothèque` D3DX`, y compris DirectInput, DirectSound , DirectShow, etc.*
    * #### *`DirectTypes` définit principalement l'énumération et la structure de DirectX.*
    * #### *`DirectTemplate` définit principalement certains modèles de fonctions couramment utilisés, tels que la publication des objets de pointeur et des interfaces COM.*
    * #### *`DirectGraphics` concerne principalement l'état du périphérique` DX9`, les objets de périphérique, les paramètres de périphérique, le modèle de carte graphique, le format de rendu, le format du tampon, la profondeur du modèle, la résolution et toute autre initialisation, le rendu d'affichage des paramètres, le flux de rendu contrôle et interface d'objet de rendu associée.*
    * #### *`DirectGraphics11` est une version` DX11` de la classe `DirectGraphics`. Il est principalement utilisé pour démarrer et initialiser le rendu DX11. Par rapport au processus d’initialisation `DX9`, la différence est relativement grande. *
    * #### *`DirectGraphics3D` concerne principalement le rendu des graphiques 3D. Il doit remplir le tampon de vertex et le tampon d’index des graphiques 3D, et transformer en matrice les graphiques (étirer, faire pivoter, faire un panoramique, etc.), les paramètres de rendu (lumière, matériau, texture, mélange alpha), la sortie finale est rendue au dispositif.*
    * #### *`DirectGraphics2D` concerne principalement le rendu des graphiques 2D, qui doivent remplir le tampon de sommets et le tampon d'index des graphiques 2D. En ce qui concerne le rendu 3D, il est facile d’effectuer des transformations matricielles complexes en raison de leur format de sommet unique. Après avoir défini le mode de rendu, vous pouvez enfin restituer la sortie sur le périphérique.*
    * #### *`DirectInput` est principalement utilisée pour les périphériques de saisie interactifs tels que les claviers, les souris et les manettes de jeu. Permet d'interagir avec la couche de pilote, y compris l'initialisation, la détection, le retour d'informations et le traitement.*
    * #### *`DirectSound` est principalement utilisée pour les effets de musique de jeux et prend en charge le décodage de fichiers Wav et PCM. Permet d'interagir avec la couche de pilote, y compris l'initialisation, la détection, le retour d'informations et le traitement.*
    * #### *`DirectShow` est principalement utilisée pour la lecture de musique d'animation de jeux. Le nombre de décodeurs supportés par lui-même n'est pas beaucoup. L'interface COM commune est fournie et le programme de décodage correspondant doit être écrit pour le fichier de développement.*
    * #### *`DirectMesh` est principalement utilisé pour dessiner certaines collections de D3DX, y compris les cubes, les sphères, les cylindres, les tores, les polygones et les théières.*
    * #### *`DirectFont` est utilisée pour le rendu des polices. Cette partie n'est pas utilisée par Direct3D, mais par GDI, de sorte que l'efficacité du rendu n'est pas très élevée.*
    * #### *`DirectSprite` est principalement utilisé pour le rendu par essaim de particules, tel que le rendu de particules décidues en flocon de neige 🍂.Il peut effectuer le rendu par particules de graphiques 2D simples, tels que la création, la transformation de matrice et le rendu.*
    * #### *`DirectSurface` est utilisée pour un rendu d'écran simple, une capture d'écran et une efficacité élevée, qui peuvent être utilisés pour créer des lecteurs vidéo.*
    * #### *`DirectTexture` est principalement utilisée pour dessiner des graphiques de texture. Les images de texture peuvent être chargées à partir d'un fichier ou de la mémoire pour des graphiques 3D ou 2D, qui sont plus puissants que la classe DirectSurface.*
    * #### *`DirectThreadSafe` est utilisée pour la sécurité des ressources entre les threads. Avec CriticalSection, il protège principalement les ressources de la classe et empêche la concurrence des ressources.*
    * #### *`DirectSafe` class is used for resource security between threads. The same as DirectThread, it is not necessary to delete the CriticalSection after the DirectSafe class exits, can be used multiple times.*
    &nbsp;
  * ### CerasusClass
     * #### *`Cerasusfps` class is mainly used to calculate the frame rate of D3DX rendering, and is drawn on the window to detect whether the game has dropped frames.*
     * #### *`CerasusUnit` class is mainly used to draw 2D primitives in 3D coordinate system, usually rectangular primitives. Textures can be loaded from files or unwrapped through resources. CerasusUnit also has coordinate transformations, materials, lighting, and rendering properties for 3D primitives.*
     * #### *`CerasusAlgorithm` class mainly defines some common algorithms for graphics. These algorithms are generally given in the form of static member functions and can be called in the program.*
     * #### *`CerasusType` class is mainly used to define the type of Cerasus class.*
    &nbsp;
  * ### SakuraClass
    &nbsp;
  * ### DXUIClass
    &nbsp;
