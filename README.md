Pașii de compilare, instalare și lansare a aplicației:

1) Se conectează placa Arduino Uno R3 la calculatorul personal, prin intermediul unui cablu USB.
2) Codul sursă scris în limbajul C++ este compilat și încărcat pe placă utilizând aplicația Arduino IDE.

3) Se conectează calculatorul personal și placa Raspberry Pi 1 Model B+ la aceeași rețea.

4) Se conectează calculatorul personal la placa Raspberry Pi 1 Model B+, prin intermediul aplicației PuTTY, pe baza adresei IP a plăcii.
5) Se autentifică utilizatorul prin nume de utilizator și parolă.
6) Se creează un director care va fi folosit ulterior folosind comanda "mkdir [numeDirector]".

7) Se conectează calculatorul personal la placa Raspberry Pi 1 Model B+, prin intermediul aplicației WinSCP, pe baza adresei IP a plăcii.
8) Se transferă fișierul care conține codul sursă, scris în limbajul de programare C, de pe calculatorul personal pe placă în directorul creat anterior.

9) Se conectează placa Arduino Uno R3 la placa Raspberry Pi 1 Model B+, prin intermediul unui cablu USB.

10) Se navighează în directorul în care se află codul sursă folosind comanda "cd [numeDirector]", prin intermediul aplicației PuTTY.
11) Codul sursă se compilează folosind comanda "gcc [numeFișier].c -o [numeExecutabil]".
12) Executabilul se rulează folosind comanda "sudo ./[numeExecutabil]".

În cadrul proiectului, directorul utilizat se numește "Raul", fișierul care conține codul sursă pentru Arduino Uno R3 se numește "FinalArduino", iar cel care conține codul sursă pentru Raspberry Pi 1 Model B+ se numește "FinalRaspberry". Aceste denumiri nu influențează funcționarea corectă a sistemului.
