# Upravljanje potrošnjom energije korištenjem sleep moda

![Arduino Uno Compatible](https://img.shields.io/badge/Platform-Arduino_Uno-blue)
![LED Visualization](<https://img.shields.io/badge/Visualization-1_LED_(RGB)-yellowgreen>)

## 1. Opis zadatka

Cilj zadatka je demonstrirati mogućnosti upravljanja potrošnjom energije mikrokontrolera korištenjem sleep modova. Mikrokontroler periodično prelazi u stanje mirovanja (sleep), a budi se na temelju pritiska tipkala ili isteka vremena zadanog pomoću Watchdog timera. U sklopu rješenja koristi se i LED dioda za vizualnu indikaciju rada sustava.

**Ključne karakteristike:**

- Mikrokontroler ulazi u sleep mode za smanjenje potrošnje energije.
- LED dioda se uključuje na 5 sekundi prije svakog ulaska u sleep.
- Prekid se generira putem: pritiska tipkala (vanjski prekid) ili watchdog timera (~4 sekunde timeout).

## 2. Hardverske komponente

| Komponenta        | Količina | Pin na Arduino Uno  |
| ----------------- | -------- | ------------------- |
| Arduino Uno       | 1        | -                   |
| LED dioda         | 1        | 13                  |
| Tipkalo           | 1        | 2 (INT0)            |

## 3. Slika spojeva

![image](https://github.com/user-attachments/assets/cbc8b167-b224-4565-aac8-b7156ac4e064)


## 4. Opis rješenja

[Link na wokwi zadatak](https://wokwi.com/projects/427690850175983617)

Program se sastoji od nekoliko glavnih dijelova:

- Inicijalizacija (setup): Definiraju se ulazno-izlazni pinovi, serijska komunikacija, sleep mod i vanjski prekid na tipkalu.

- Glavna petlja (loop): LED dioda se uključuje na 5 sekundi, zatim se mikrokontroler priprema za spavanje. Nakon ulaska u sleep mod, čeka se prekid (tipkalo ili Watchdog timer) za buđenje.

- Sleep logika (enterSleepMode): Omogućava sleep mod i CPU se uspavljuje. Izlazak iz moda se vrši kad prekid postavi zastavicu isAwake na true.

- Konfiguracija Watchdog timera (setupWatchdogTimer): Timer se konfigurira tako da generira prekid nakon približno 4 sekunde.

### Tablica funkcionalnosti

| Funkcija             | Opis funkcionalnosti                                              |
| -------------------- | ----------------------------------------------------------------- |
| setup()              | Inicijalizacija pinova, prekida i sleep moda                      |
| loop()               | Upravljanje LED diodom i prelazak u sleep mod                     |
| onButtonPress()      | ISR za vanjski prekid – buđenje mikrokontrolera pritiskom tipkala |
| ISR(WDT_vect)        | ISR za Watchdog timer – buđenje nakon timeouta (~4s)              |
| enterSleepMode()     | Ulazak u sleep i čekanje na buđenje                               |
| setupWatchdogTimer() | Konfiguracija Watchdog timera za generiranje prekida              |

## 5. Zaključak

Projekt uspješno demonstrira tehniku upravljanja potrošnjom energije mikrokontrolera korištenjem sleep modova. Korištenje vanjskog prekida i Watchdog timera omogućava buđenje mikrokontrolera iz sleep moda bez potrebe za stalnim aktivnim nadzorom. Ovakav pristup je posebno koristan u uređajima koji se napajaju iz baterije, gdje je očuvanje energije ključni faktor.
