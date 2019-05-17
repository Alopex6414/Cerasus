# Cerasus🌸
Ce programme est un projet de bibliothèque de liens dynamiques Render Cerasus DirectX.

## La langue
  * [English](https://github.com/Alopex6414/Cerasus/blob/master/README.md)
  * [简体中文](https://github.com/Alopex6414/Cerasus/blob/master/README_ZH_CN.md)
  * [繁體中文](https://github.com/Alopex6414/Cerasus/blob/master/README_ZH_TW.md)
  * [日本語](https://github.com/Alopex6414/Cerasus/blob/master/README_JA_JP.md)
  * [русский](https://github.com/Alopex6414/Cerasus/blob/master/README_RU_RU.md)
  * [Français](https://github.com/Alopex6414/Cerasus/blob/master/README_FR_FR.md)
  * [Deutsch](https://github.com/Alopex6414/Cerasus/blob/master/README_DE_DE.md)

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
    * #### *`DirectSafe` est utilisée pour la sécurité des ressources entre les threads. Comme pour DirectThread, il n'est pas nécessaire de supprimer la CriticalSection après la sortie de la classe DirectSafe, elle peut être utilisée plusieurs fois.*
    &nbsp;
  * ### CerasusClass
    * #### *`Cerasusfps` est principalement utilisée pour calculer la cadence du rendu D3DX et est dessinée dans la fenêtre pour détecter si le jeu a perdu des images.*
    * #### *`CerasusUnit` est principalement utilisée pour dessiner des primitives 2D dans un système de coordonnées 3D, généralement des primitives rectangulaires. Les textures peuvent être chargées à partir de fichiers ou déplacées dans des ressources. CerasusUnit possède également des propriétés de transformations de coordonnées, de matériaux, d'éclairage et de rendu pour les primitives 3D.*
    * #### *`CerasusAlgorithm` définit principalement certains algorithmes courants pour les graphiques. Ces algorithmes sont généralement donnés sous la forme de fonctions membres statiques et peuvent être appelés dans le programme.*
    * #### *`CerasusType` est principalement utilisée pour définir le type de classe Cerasus.*
    &nbsp;
  * ### SakuraClass
    * #### *`SakuraUICommon` est un fichier d’en-tête partagé pour la classe Sakura.*
    * #### *`SakuraBlend` est principalement utilisée pour le rendu de texture et de texte primitif.*
    * #### *`SakuraButton` est principalement utilisée pour les contrôles Button.*
    * #### *`SakuraCheckBox` est principalement utilisée pour le contrôle CheckBox.*
    * #### *`SakuraComboBox` est principalement utilisée pour le contrôle ComboBox.*
    * #### *`SakuraControl` est utilisée pour la classe de base de la classe de contrôle, fournissant d'autres interfaces dérivées de la classe de contrôle.*
    * #### *`SakuraDialog` est principalement utilisée pour construire des fenêtres. En tant que conteneur pour les contrôles, vous pouvez ajouter différents types de contrôles et de réponses.*
    * #### *`SakuraEidtBox` est principalement utilisée pour le contrôle EditBox.*
    * #### *`SakuraElement` est principalement utilisée pour les primitives de rendu de contrôle.*
    * #### *`SakuraListBox` est principalement utilisée pour le contrôle ListBox.*
    * #### *`SakuraRadioButton` est principalement utilisée pour le contrôle de RadioButton.*
    * #### *`SakuraResource` est principalement utilisée pour la gestion des ressources de la classe Sakura.*
    * #### *`SakuraResourceManager` est principalement utilisée pour la classe de gestion des ressources de classe Sakura.*
    * #### *`SakuraScrollBar` est principalement utilisée pour le contrôle ScrollBar.*
    * #### *`SakuraSlider` est principalement utilisée pour le contrôle Slider.*
    * #### *`SakuraStatic` principalement pour les contrôles de dessin de polices.*
    * #### *`SakuraUint` dessine principalement des primitives.*
    &nbsp;
  * ### DXUIClass
      La classe DXUI est temporairement non terminée, à mettre à jour ...
    &nbsp;
    
## Licence
   Copyright (C) 2017 ~ 2019, Team Gorgeous Bubble, Tous droits réservés.
