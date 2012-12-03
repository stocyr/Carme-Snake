Carme-Snake
===========

A snake game implementation on the microcontroller kit CARME

Links
-----------

* Reference impementation of snake: [Snake on Nokia 3310](http://www.youtube.com/watch?v=dSfo0Jn9qOA&t=1m44s)

* set up *git*: http://help.github.com/win-set-up-git/

* short introduction to *git*: http://spheredev.org/wiki/Git_for_the_lazy

* the *git book*: http://progit.org/book/

Git
-----------

* Editor auf Notepad++ aendern: git config --global core.editor "'C:/Program Files (x86)/Notepad++/notepad++.exe' -multiInst -notabbar -nosession -noPlugin"

* Vereinfachte schematische Darstellung des Git Version Control Systems:

![Git workflow](http://www.terminus-notfallmedizin.de/blog/wp-content/uploads/2011/01/local-remote.png)

Hier ist zu beachten: Anstatt mit `git fetch` das Repository herunter zu laden und dann mit `git merge` mit dem Arbeitsverzeichnis zu synchronisieren,
nutzen wir den Befehl `git pull`, der macht das auf einmal.

* Mit `git add .` koennen saemtliche aenderungen (ausser Files loeschen und hinzufuegen) auf einmal zur *staging area* hinzugefuegt werden.

* Mit `git commit -a -m 'bemerkung zu diesem commit'` kann direkt vom Arbeitsverzeichnis ein commit gemacht werden (ohne `git add`).