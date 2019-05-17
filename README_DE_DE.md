# Cerasus🌸
Dieses Programm ist ein Cerasus DirectX Render Dynamic Link Library-Projekt.

## Sprache
  * [English](https://github.com/Alopex6414/Cerasus/blob/master/README.md)
  * [简体中文](https://github.com/Alopex6414/Cerasus/blob/master/README_ZH_CN.md)
  * [繁體中文](https://github.com/Alopex6414/Cerasus/blob/master/README_ZH_TW.md)
  * [日本語](https://github.com/Alopex6414/Cerasus/blob/master/README_JA_JP.md)
  * [русский](https://github.com/Alopex6414/Cerasus/blob/master/README_RU_RU.md)
  * [Français](https://github.com/Alopex6414/Cerasus/blob/master/README_FR_FR.md)
  * [Deutsch](https://github.com/Alopex6414/Cerasus/blob/master/README_DE_DE.md)

## Abstrakt
In diesem Projekt geht es hauptsächlich um DX9-Spiele, Video, Wallpaper-Rendering, Musik, Soundeffekte, Lautsprecherspiele, Tastatur, Maus, Joystick-Steuerung und einige spielbezogene Programme. Die Bibliothek ist für das schnelle und einfache Entwickeln, Debuggen, Testen und Bereitstellen von Spielen, Anwendungen und Grafiken konzipiert. Der Name Cerasus wird angenommen, weil er auf Latein für Kirschblüte steht und so farbenfroh ist wie unser Spiel.

Verfassungen
Cerasus besteht jetzt aus 4 Teilen, der **Direct** -Klasse, die für das Rendering von DirectX-Grafiken verantwortlich ist, der **Cerasus** -Klasse für spielphysikalische Algorithmen, der **Sakura** -Klasse für GUI-Interaktionsschnittstellen und der **DXUI** Klasse für das Rendering-Management.
* **Direct-Klassen, die in erster Linie für den zugrunde liegenden Teil von DirectX verantwortlich sind, z. B. Grafikwiedergabe, Musikeffekte, Spielinteraktion, Videodekodierung, Partikelsysteme usw.**
* **Die Cerasus - Klasse ist hauptsächlich für den Kern und die Hilfsteile des Spiels verantwortlich, einschließlich physikalischer Algorithmen, grundlegender Grundelemente, der Anzeige von Bildwiederholungen bei Bildwiederholungen usw.**
* **Die Sakura-Klasse ist hauptsächlich für Spielinteraktionen wie Szenen, Dialoge, Schaltflächen usw. Verantwortlich.**
* **Die DXUI-Klasse ist hauptsächlich für das Game-Management verantwortlich, einschließlich der Game-Skripte, der Ressourcendekodierung und des Schedule-Managements, die derzeit noch nicht abgeschlossen sind ...**

## Eigenschaften
  * ### DirectClass
    * #### *`DirectCommon` ist eine öffentliche DirectX-Header-Datei, die` DirectX9`- und `DirectX11`-Header-Dateien, Bibliotheksdateien und einige gängige Makros enthält sowie Funktionen in der` D3DX`-Bibliothek, einschließlich DirectInput, DirectSound , DirectShow usw. *
    * #### *`DirectTypes` definiert hauptsächlich die Aufzählung und Struktur von DirectX.*
    * #### *`DirectTemplate` definiert hauptsächlich einige häufig verwendete Funktionsvorlagen, z. B. die Freigabe von Zeigerobjekten und COM-Schnittstellen.*
    * #### *`DirectGraphics` geht es hauptsächlich um` DX9`-Gerätestatus, Geräteobjekte, Geräteparameter, Grafikkartenmodell, Renderingformat, Pufferformat, Vorlagentiefe, Auflösung und andere Initialisierung, Rendering von Renderingparametern, Renderingfluss Steuerelement und zugehörige Rendering-Objekt-Schnittstelle.*
    * #### *`DirectGraphics11`-Klasse ist eine` DX11`-Version der `DirectGraphics`-Klasse. Es wird hauptsächlich zum Booten und Initialisieren des DX11-Renderings verwendet. Verglichen mit dem Initialisierungsprozess von `DX9` ist der Unterschied relativ groß.*
    * #### *`DirectGraphics3D` geht es hauptsächlich um das Rendern von 3D-Grafiken. Es muss den Scheitelpunktpuffer und den Indexpuffer von 3D-Grafiken füllen und die Grafiken (Strecken, Drehen, Schwenken usw.) sowie die Rendereinstellungen (Licht, Material, Textur, Alpha-Mischung) in eine Matrix umwandeln Gerät.*
    * #### *`DirectGraphics2D` geht es hauptsächlich um das Rendern von 2D-Grafiken, die den Scheitelpunktpuffer und den Indexpuffer von 2D-Grafiken füllen müssen. Im Vergleich zum 3D-Rendering ist es aufgrund des einzigartigen Vertex-Formats einfach, komplexe Matrixtransformationen durchzuführen. Nachdem Sie den Rendermodus eingestellt haben, können Sie die Ausgabe endgültig auf dem Gerät rendern.*
    * #### *`DirectInput` wird hauptsächlich für interaktive Eingabegeräte wie Tastaturen, Mäuse und Joysticks verwendet. Bietet die Möglichkeit, mit der Treiberschicht zu interagieren, einschließlich Initialisierung, Erkennung, Rückmeldung und Verarbeitung. *
    * #### *`DirectSound` wird hauptsächlich für Spielemusik-Effekte verwendet und unterstützt die Dekodierung von Wav- und PCM-Dateien. Bietet die Möglichkeit, mit der Treiberschicht zu interagieren, einschließlich Initialisierung, Erkennung, Rückmeldung und Verarbeitung.*
    * #### *`DirectShow` -Klasse wird hauptsächlich für die Wiedergabe von Spielanimationsmusik verwendet. Die Anzahl der Decoder, die von sich aus unterstützt werden, ist nicht groß. Die gemeinsame COM-Schnittstelle wird bereitgestellt, und das entsprechende Dekodierungsprogramm muss für die Entwicklungsdatei geschrieben werden.*
    * #### *`DirectMesh` wird hauptsächlich zum Zeichnen einiger Sammlungen von D3DX selbst verwendet, einschließlich Würfel, Kugeln, Zylinder, Torus, Polygone und Teekannen.*
    * #### *`DirectFont` wird für das Rendern von Schriftarten verwendet. Dieser Teil wird nicht von Direct3D, sondern von GDI verwendet, sodass die Rendereffizienz nicht sehr hoch ist.*
    * #### *`DirectSprite` wird hauptsächlich für das Rendern von Partikelschwärmen verwendet (z. B. das Rendern von Schneeflocken-Laubpartikeln). Es kann das Rendern von Partikeln einfacher 2D-Grafiken (z. B. Erstellen, Matrixtransformation und Rendern) durchführen.*
    * #### *`DirectSurface` -Klasse wird für einfaches Bildschirmrendering, Bildschirmaufzeichnung und hohe Effizienz verwendet, die zum Erstellen von Video-Playern verwendet werden können.*
    * #### *`DirectTexture` wird hauptsächlich zum Zeichnen von Texturgrafiken verwendet. Texturbilder können aus einer Datei oder aus dem Speicher geladen werden, um 3D-Grafiken oder 2D-Grafik-Vertex-Indizes zu rendern. Dies ist leistungsfähiger als die DirectSurface-Klasse.*
    * #### *`DirectThreadSafe` wird für die Ressourcensicherheit zwischen Threads verwendet. Mit CriticalSection werden hauptsächlich Ressourcen innerhalb der Klasse geschützt und Ressourcenwettbewerbe verhindert.*
    * #### *`DirectSafe` wird für die Ressourcensicherheit zwischen Threads verwendet. Genau wie bei DirectThread muss CriticalSection nach dem Beenden der DirectSafe-Klasse nicht gelöscht werden. Es kann mehrmals verwendet werden.*
    &nbsp;
  * ### CerasusClass
    * #### *`Cerasusfps` -Klasse wird hauptsächlich zur Berechnung der Framerate des D3DX-Renderings verwendet und im Fenster angezeigt, um festzustellen, ob das Spiel Frames verloren hat.*
    * #### *`CerasusUnit` wird hauptsächlich zum Zeichnen von 2D-Grundelementen im 3D-Koordinatensystem verwendet, normalerweise rechteckigen Grundelementen. Texturen können aus Dateien geladen oder über Ressourcen entpackt werden. CerasusUnit verfügt auch über Koordinatentransformationen, Materialien, Beleuchtungs- und Rendereigenschaften für 3D-Grundelemente.*
    * #### *`CerasusAlgorithm` definiert hauptsächlich einige gängige Algorithmen für Grafiken. Diese Algorithmen werden in der Regel in Form von statischen Elementfunktionen angegeben und können im Programm aufgerufen werden.*
    * #### *`CerasusType` wird hauptsächlich verwendet, um den Typ der Cerasus-Klasse zu definieren.*
    &nbsp;
  * ### SakuraClass
    * #### *`SakuraUICommon` ist eine gemeinsame Header-Datei für die Sakura-Klasse.*
    * #### *`SakuraBlend` -Klasse wird hauptsächlich für die Wiedergabe von primitiven Texturen und Text verwendet.*
    * #### *`SakuraButton` -Klasse wird hauptsächlich für Button-Steuerelemente verwendet.*
    * #### *`SakuraCheckBox` -Klasse wird hauptsächlich für das CheckBox-Steuerelement verwendet.*
    * #### *`SakuraComboBox` -Klasse wird hauptsächlich für das ComboBox-Steuerelement verwendet.*
    * #### *`SakuraControl` -Klasse wird für die Basisklasse der Kontrollklasse verwendet und stellt andere von Kontrollklassen abgeleitete Schnittstellen bereit.*
    * #### *`SakuraDialog` -Klasse wird hauptsächlich zum Erstellen von Fenstern verwendet. Als Container für Steuerelemente können Sie verschiedene Arten von Steuerelementen und Antworten hinzufügen.*
    * #### *`SakuraEidtBox` -Klasse wird hauptsächlich für das EditBox-Steuerelement verwendet.*
    * #### *`SakuraElement` -Klasse wird hauptsächlich für das Rendern von Steuerelementen verwendet.*
    * #### *`SakuraListBox`-Klasse wird hauptsächlich für das ListBox-Steuerelement verwendet.*
    * #### *`SakuraRadioButton` -Klasse wird hauptsächlich für die RadioButton-Steuerung verwendet.*
    * #### *`SakuraResource` wird hauptsächlich für die Verwaltung von Sakura-Klassenressourcen verwendet.*
    * #### *`SakuraResourceManager`-Klasse wird hauptsächlich für die Sakura-Klassen-Ressourcenverwaltungsklasse verwendet.*
    * #### *`SakuraScrollBar` -Klasse wird hauptsächlich für das ScrollBar-Steuerelement verwendet.*
    * #### *`SakuraSlider`-Klasse wird hauptsächlich für das Slider-Steuerelement verwendet.*
    * #### *`SakuraStatic` -Klasse hauptsächlich für Steuerelemente zum Zeichnen von Schriftarten.*
    * #### *`SakuraUint`-Klasse zeichnet hauptsächlich Primitive.*
    &nbsp;
  * ### DXUIClass
      Die DXUI-Klasse ist vorübergehend nicht fertiggestellt, um aktualisiert zu werden ...
    &nbsp;
    
## Lizenz
   Copyright (C) 2017 ~ 2019, Team wunderschöne Blase, alle Rechte vorbehalten.
