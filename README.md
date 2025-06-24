Lucrare de licență cu tema "Robot mobil autonom pentru urmarirea unei persoane"
====
**Candidat: Dan BALAN**

**Coordonator științific: Ș.l.dr.ing. Ana Maria DAN**


Adresa de Github
-------

[Github repository](https://github.com/Nlost/licenta.git)

Structura proiectului
----

```bash
├── Dev      <- Proiectul STM32CubeIDE cu codul sursă pentru STM32F439ZI
├── doc      <- Documentații utilizate pentru dezvoltarea aplicației
├── models   <- Modelele 3D și desenele tehnice ale șasiului
├── openmv   <- Codul sursă pentru OpenMV Cam H7     
```
Pașii de compilare
-----

**Codul sursă pentru STM32**


1. Se descarcă aplicația [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html)
2. La pornirea aplicației, STM32CubeIDE va cere o cale pentru proiect. Se selectează folderul în care a fost descărcat repositoriul de Git.
3. Pentru a compila proiectul, navigați în bara de sus la secțiunea **”Project” -> ”Build all”** sau apăsați pe iconița cu imaginea unui ciocan.
4. Pentru a încărca codul, conectați plăcuța la un PC și navigați în bara de sus la secțiunea **”Run” -> ”Run”** sau apăsați pe iconița de culoare verde cu semnul Play pe ea. 

**Codul sursă pentru OpenMV Cam H7**

1. Se descarcă aplicația [OpenMV IDE](https://openmv.io/pages/download)
2. Se deschide fișierul **main.py** din folderul **openmv** folosind OpenMV IDE
3. Pentru a încărca fișierul main.py, conectați plăcuța la un PC și navigați în bara de sus la secțiunea **”Tools” -> ”Save open script to OpenMV Cam (as main.py)”**

*Observații: Codul poate fi încărcat pe plăcuță și fără utilizarea aplicației OpenMV IDE. Copierea fișierului main.py direct în sistemul de fișiere ale plăcuței OpenMV Cam H7 va duce la același rezultat ca și în pașii descriși mai sus.*

Pașii de lansare a proiectului
---
1. Se încarcă codul pe toate plăcuțele.
2. Se alimentează plăcuțele OpenMV Cam H7 și STM32 Nucleo-144 prin portul micro USB conectat la un powerbank.
3. Se alimentează driverele de motoare de la o sursă de 12V.
