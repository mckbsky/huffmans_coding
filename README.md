# Tytuł projektu: (ew. do zmiany)
huffmans_coding 

Prosty program do kompresji tekstu metodą Huffmana


Autorzy:
Maciej Brzęczkowski
Mariusz Lewczuk

Opis:
Algorytm Huffmana to algorytm do kompresji tekstu. Polegający na zasadzie: częściej występujące litery - mniej bitów, 
mniej występujące litery więcej bitów. Poswstaje na podstawie drzewa, które w liściach posiada posortowane znaki od zależności ich wystąpień.
Drzewo powstaje w połączeniu kolejno dwóch najmniej występujących znaków i utworzenia z nich drzewa z korzeniem i dwoma liśćmi,
powtarzane jest to dla wszystkich znaków występujących w danym tekscie, następnie dwa ostatnie drzewa są łączone w jedno aż do ostatniego.
Na koniec do lewych węzłów dopisujemy "0" a do prawych "1" i odczytujemy sćieżke do każdej z liter, oraz zapisujemy kody.

Opis własnego kodu to będzie z komentarzy tree.h + zrobić kilka zrzutów z plików i kodu.

Opis sposobu mierzenia wydajności programu:
Wydajność programy mierzymy dwoma wartościami - miarą kompresji oraz pomiarem czasu.
Kompresje mierzymy w sposoób - dopisz ja nie jestem do końca tego pewien.
Czas mierzymy za pomocą biblioteki time.h za pomocą funkcji clock(), która zwraca aktualny czas (tick) procesora oraz stałej "CLOCKS_PER_SEC",
dzięki której otrzymujemy czas w milisekundach.

Co do wyników testów to nie mam nawet jak zacząć na lorem ipsum mozna max 88kb co jest stasznie małe, szukałem duzych ksiazek to nie przechodza.

Wnioski:
Algorytm Huffmana to bezstratny algorytm kompresji danych, który najlepiej sprawdza sie przy tekście.
W tekscie dzięki niemu potrafimy uzyskać średnio do (tu wstawić wynik) % kompresji, co więcej jest on (stosunkowo?) szybki.
