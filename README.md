I. Pașii de instalare:

1) Se conectează placa Arduino Uno R3 la calculatorul personal, prin intermediul unui cablu USB.
2) Codul sursă scris în limbajul C++ este încărcat pe placă utilizând aplicația Arduino IDE.

3) Se conectează calculatorul personal la placa Raspberry Pi 1 Model B+, prin intermediul aplicației PuTTY, pe baza adresei IP a plăcii.
4) Se autentifică utilizatorul prin nume de utilizator și parolă.
5) Se creează un director care va fi folosit ulterior folosind comanda "mkdir [numeDirector]".

6) Se conectează calculatorul personal la placa Raspberry Pi 1 Model B+, prin intermediul aplicației WinSCP, pe baza adresei IP a plăcii.
7) Se autentifică utilizatorul prin nume de utilizator și parolă.
8) Se transferă fișierul care conține codul sursă, scris în limbajul de programare C, de pe calculatorul personal pe placă în directorul creat anterior.



II. Pașii de compilare:

1) Codul sursă scris în limbajul C++ este compilat pe calculatorul personal utilizând aplicația Arduino IDE.
2) Codul sursă scris în limbajul C este compilat pe placa Raspberry Pi 1 Model B+ utilizând comanda "gcc [numeFișier].c -o [numeExecutabil]".



III. Pașii de lansare:

1) Se navighează în directorul în care se află codul sursă folosind comanda "cd [numeDirector]", prin intermediul aplicației PuTTY.
2) Executabilul se rulează folosind comanda "sudo ./[numeExecutabil]", după care se introduce parola.



IV. Pașii compleți pentru punerea aplicației în funcțiune:

1) Se conectează placa Arduino Uno R3 la calculatorul personal, prin intermediul unui cablu USB.
2) Codul sursă scris în limbajul C++ este compilat și încărcat pe placă utilizând aplicația Arduino IDE.

3) Se alimentează placa Raspberry Pi 1 Model B+ și sursa externă de 5 V / 6 A.
4) Se conectează placa Arduino Uno R3 la placa Raspberry Pi 1 Model B+, prin intermediul unui cablu USB.
5) Se conectează calculatorul personal și placa Raspberry Pi 1 Model B+ la aceeași rețea. Pentru placă se folosește un cablu Ethernet.

6) Se conectează calculatorul personal la placa Raspberry Pi 1 Model B+, prin intermediul aplicației PuTTY, pe baza adresei IP a plăcii.
7) Se autentifică utilizatorul prin nume de utilizator și parolă.
8) Se creează un director care va fi folosit ulterior folosind comanda "mkdir [numeDirector]".

9) Se conectează calculatorul personal la placa Raspberry Pi 1 Model B+, prin intermediul aplicației WinSCP, pe baza adresei IP a plăcii.
10) Se autentifică utilizatorul prin nume de utilizator și parolă.
11) Se transferă fișierul care conține codul sursă, scris în limbajul de programare C, de pe calculatorul personal pe placă în directorul creat anterior.

12) Se navighează în directorul în care se află codul sursă folosind comanda "cd [numeDirector]", prin intermediul aplicației PuTTY.
13) Codul sursă se compilează folosind comanda "gcc [numeFișier].c -o [numeExecutabil]".
14) Executabilul se rulează folosind comanda "sudo ./[numeExecutabil]", după care se introduce parola.



În cadrul proiectului, directorul utilizat se numește "Raul", fișierul care conține codul sursă pentru Arduino Uno R3 se numește "FinalArduino", iar cel care conține codul sursă pentru Raspberry Pi 1 Model B+ se numește "FinalRaspberry". Aceste denumiri nu influențează funcționarea corectă a sistemului.
