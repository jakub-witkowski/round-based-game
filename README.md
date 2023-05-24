# round-based-game
C-based game (player program only)

This repository includes the files I have prepared for the technical assignment from TietoEvry (C Working Student).

Time constraints didn't allow me to try the mediator. Only the player is included. My plan for the mediator, thought, was to write player output to file (player1.txt). This output would then be fed to the mediator together with rozkazy.txt. The mediator would update the positions of units and settle the outcomes of the battles, eventually writing the new input data for the player in the file status.txt. These, in turn, would be read by the second player.

As it is, the program relies on fixed format of both the status.txt file and the player1.txt file. The status file is ordered as follows: gold (1 line), bases (2 lines), active units (i.e., non-training units). A sample status file is included. The player1.txt file is ordered as follows: training units (1 line), gold (1 line), bases (2 lines), followed by the remaining active units.

As specified in the instructions for the assignment, the program is executed by: ./player mapa.txt status.txt rozkazy.txt [time_limit].

The time limit is optional, but the default is set to 5 seconds. It no status.txt file is present, the program loads default values.

----

W tym repozytorium znajdują się pliki, które przygotowałem jako część zadania technicznego (TietoEvry, C Working Student).

Repozytorium zawiera tylko plik gracza (na przygotowanie mediatora nie pozwolił mi czas). Według moich zamierzeń, mediator sczytywałby dane wyjściowe z programu gracza (plik player1.txt) i zestawiał je z danymi z pliku rozkazy.txt. Następnie mediator uaktualniałby dane i przekazywałby je do pliku status.txt, skąd byłby pobierane przez gracza numer 2.

W obecnej postaci program bazuje na stałym formacie plików status.txt oraz player1.txt. Plik statusu jest uporządkowany w następujący sposób: złoto (1 linia), stan baz (2 linie), aktywne jednostki (=nie w czasie treningu). Dołączony jest przykładowy plik status.txt. Organizacja pliku player1.txt: jednostki szkolące się (1 linia), złoto (1 linia), stan baz (2 linie), następnie - aktywne jednostki.

Jak wskazano w instrukcji do zadania, program uruchamia następujące polecenie: ./player mapa.txt status.txt rozkazy.txt [limit_czasowy].

Limit czasu jest argumentem opcjonalnym, wartość domyślna to 5 sekund. Jeśli nie ma pliku status.txt, program wczytuje domyślne dane startowe.
