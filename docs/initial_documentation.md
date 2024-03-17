# Dokumentacja wstępna

## Aplikacja do transferu stylu

**Autorzy**
1. Tomek Owienko (ZPR, ZPRP) - Właściciel Produktu
2. Patryk Filip Gryz (ZPR, ZPRP) - Osoba Odpowiedzialna za Jakość
3. Wojciech Zarzecki (ZPRP) 

## Cel projektu

Głównym celem projektu jest opracowanie aplikacji pozwalającej na serwowanie wyników działania modelu realizującego transfer stylu. Aplikacja będzie pozwalać na wykonywanie tych operacji dla zdjęć oraz obrazu z kamery (pseudo realtime).

## Opis 
Aplikacja zostanie wykonana jako aplikacja działająca głównie w trybie konsolowym z możliwością uruchomienia nakładki GUI. Nakładka GUI pozwalać będzie na wykonywanie transferu stylu dla zdjęć oraz obrazu z kamery.
Model transferu stylu zostanie przeniesiony z języka Python i jest częścią projektu z przedmiotu ZPRP. (repozytorium z modelem: https://github.com/SNURTEL/24l-zprp)

## Zakres funkcjonalny
- możliwość wczytywania modeli serializowanych z Pytorch
- możliwość serwowania wyników modelu dla wgrywanych plików graficznych w formacie png
- możliwość serwowania wyników modelu dla obrazu z kameru
- interfejs konsolowy, pozwalający na serwowanie wyników modelu dla zdjęć 
- interfejs graficzny realizujący możliwość wczytania pliku graficznego oraz wyświetlenie wyniku modelu dla wczytanego zdjęcia. Interfejs będzie pozwalać również na wyświetlanie wyniku działania modelu dla obrazu z kamery

## Technologia i narzędzia
- **Język programowania:** C++
- **Biblioteki:** Boost, Catch, Qt, Libtorch, OpenCV2
- **Narzędzia Budowania:** CMake (Ninja / Make)
- **Kompilatory:** g++, msvc
- **Środowisko programistyczne:** InteliJ Clion
- **System Kontroli Wersji:** Git (Github)

## Harmonogram
- od 25 III do 19 IV - research, zestawienie repozytorium, przygotowania środowiska, przygotowanie szkieletu aplikacji, przedmuch przez warstwy
- od 20 IV do 31 V - przygotowanie interfejsu graficznego aplikacji, wykorzystanie obrazu z kamer na prostym modelu,  wykorzystanie finalnego modelu, optymalizacja, finalne testy

## Wymagania sprzętowe (minimalne)
- system operacyjny Windows 10 (wersja 22H2) lub Linux Ubuntu 20
- 8GB dostępnej pamięci RAM
- karta graficzna obsługująca CUDA