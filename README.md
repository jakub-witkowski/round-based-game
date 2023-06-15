# round-based-game
C-based game (player program only)

This repository includes the files I have prepared for the technical assignment from TietoEvry (C Working Student).

Time constraints didn't allow me to try the mediator. Only the player is included. My plan for the mediator, thought, was to write player output to file (player1.txt). This output would then be fed to the mediator together with rozkazy.txt. The mediator would update the positions of units and settle the outcomes of the battles, eventually writing the new input data for the player in the file status.txt. These, in turn, would be read by the second player.

As it is, the program relies on fixed format of both the status.txt file and the player1.txt file. The status file is ordered as follows: gold (1 line), bases (2 lines), active units (i.e., non-training units). A sample status file is included. The player1.txt file is ordered as follows: training units (1 line), gold (1 line), bases (2 lines), followed by the remaining active units.

Makefile is included. 
Compilation command: gcc player.c load_status.c menu.c map.c display_map.c list.c train.c move.c attack.c save.c mining.c -lpthread -o player 

As specified in the instructions for the assignment, the program is executed by: ./player mapa.txt status.txt rozkazy.txt [time_limit].

The time limit is optional, but the default is set to 5 seconds.

The original submission was fully functional when tested on MacOS Monterey, but crashed on Ubuntu (double free or corruption (out)). This was caused by the dynamic array holding the unit data. In the present version, tested on both MacOS Monterey 12.6.6 and Ubuntu 22.04, the data are stored in an explicitly declared array. Given the maximum number of rounds allowed to a player (1000), a maximum number of units that is hypothetically achieveable is 501 (including the base) for each player - hence the constant MAX_NUMBER_OF_UNITS equal to 1002.

----

W tym repozytorium znajdują się pliki, które przygotowałem jako część zadania technicznego (TietoEvry, C Working Student).

Repozytorium zawiera tylko plik gracza (na przygotowanie mediatora nie pozwolił mi czas). Według moich zamierzeń, mediator sczytywałby dane wyjściowe z programu gracza (plik player1.txt) i zestawiał je z danymi z pliku rozkazy.txt. Następnie mediator uaktualniałby dane i przekazywałby je do pliku status.txt, skąd byłby pobierane przez gracza numer 2.

W obecnej postaci program bazuje na stałym formacie plików status.txt oraz player1.txt. Plik statusu jest uporządkowany w następujący sposób: złoto (1 linia), stan baz (2 linie), aktywne jednostki (=nie w czasie treningu). Dołączony jest przykładowy plik status.txt. Organizacja pliku player1.txt: jednostki szkolące się (1 linia), złoto (1 linia), stan baz (2 linie), następnie - aktywne jednostki.

Dołączono plik makefile.
Komenda kompilacji: gcc player.c load_status.c menu.c map.c display_map.c list.c train.c move.c attack.c save.c mining.c -lpthread -o player
Jak wskazano w instrukcji do zadania, program uruchamia następujące polecenie: ./player mapa.txt status.txt rozkazy.txt [limit_czasowy].

Limit czasu jest argumentem opcjonalnym, wartość domyślna to 5 sekund.

Pierwotna wersja zadania działała bezproblemowo na MacOS Monterey, ale - jak się okazało - próba uruchomienia pod Ubuntu wywoływała błąd (double free or corruption (out)). Przyczyną okazała się dynamiczna tablica przechowująca dane jednostek. W obecnej wersji, przetestowanej na MacOS Monterey 12.6.6 oraz Ubuntu 22.04, dane jednostek przechowuje jawnie zadeklarowana tablica. Przy maksymalnej liczbie rund równej 1000 dla jednego gracza, maksymalna liczba jednostek, jaką gracz moze hipotetycznie osiągnąć to 501 (wliczając bazę) - stąd stała MAX_NUMBER_OF_UNITS równa 1002.
