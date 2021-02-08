#include <iostream>
#include <fstream>
#include <iterator>
#include <iomanip>
#include <limits.h>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <chrono>
using namespace std::chrono;
using namespace std;

// Funkcja generująca losową zawartość tablicy o długości N
std::vector<int> losuj(int N)
{
    std::vector<int>arr;
    int i, a;
    for(i=0; i<N; i++)
    {
        a = rand ( ) % 1000;
        arr.push_back(a);
    }
    return arr;
}

// Funkcja wczytania danych z pliku
std::vector<int> wczytanie(char *nazwa_pliku)
{
    std::vector<int> arr;
    ifstream plik(nazwa_pliku);        // Wczytywany plik

    // Sprawdzenie czy plik istnieje i otworzenie go
    if (plik.good())
    {
        // Wczytanie danych do tablicy
        int x = 0;
        while (plik >> x)
        {
            arr.push_back(x);
        }
        // Zamknięcie pliku.
        plik.close();
    }
    else
    {
        cout << "Error!";
        _exit(0);
    }
    return arr;
}

// Funkcja zapisu do pliku
void zapisz_do_pliku(char *nazwa_pliku, std::vector<int> arr, int arrLength)
{
    fstream plik;
    plik.open(nazwa_pliku, ios::out|ios::app);
    for (int i = 0; i < arrLength; i++)
    {
        plik<<arr[i]<<" ";
    }
    plik<<endl<<endl;
    plik.close();
}

// Funkcja pomocnicza do sortowania kopcowego
void sortowanie_kopcowe_pomocnicze(std::vector<int>&arr, int &N, int i)
{
    int maks = i; // przypisanie najwiekszej wartosci do zmiennej
    int l = 2 * i + 1; // lewy = 2*i + 1
    int p = 2 * i + 2; // prawy = 2*i + 2

    // Jeśli lewe dziecko jest większe
    if (l < N && arr[l] > arr[maks])
        maks = l;

    // Jeśli prawe dziecko jest większe
    if (p < N && arr[p] > arr[maks])
        maks = p;

    //
    if (maks != i)
    {
        swap(arr[i], arr[maks]);

        // Rekursyjne powtarzanie funkcji
        sortowanie_kopcowe_pomocnicze(arr, N, maks);
    }
}

// Główna funkcja sortowania kopcowego
void sortowanie_kopcowe(std::vector<int>&arr, int &N)
{
    // Budowa kopca
    for (int i = N / 2 - 1; i >= 0; i--)
        sortowanie_kopcowe_pomocnicze(arr, N, i);

    for (int i = N - 1; i > 0; i--)
    {
        // Przeniesienie korzenia na koniec
        swap(arr[0], arr[i]);

        // Funkcja pomocnicza do sortowania
        sortowanie_kopcowe_pomocnicze(arr, i, 0);
    }
}

// Funkcja sortowania przez wybór
void sortowanie_przez_wybor(std::vector<int>&arr, int &N)
{
    int i, j, k;

    for (i = 0; i < N-1; i++)
    {
        // Szukanie najmniejszej wartosci w nieposortowanej tablicy
        k = i;
        for (j = i+1; j < N; j++)
            if (arr[j] < arr[k])
                k = j;

        // Swap znalezionego najmniejszego elementu z pierwszym elementem
        swap(arr[k], arr[i]);
    }
}
// Funkcja sortująca malejąco - użyta przy teście pesymistycznym algorytmów
void sortowanie_przez_wybor_malejaco(std::vector<int>&arr, int &n)
{
    int i, j, k;
    for (i = 0; i < n-1; i++)
    {
        // Szukanie najmniejszej wartosci w nieposortowanej tablicy
        k = i;
        for (j = i+1; j < n; j++)
            if (arr[j] > arr[k])
                k = j;

        // Swap znalezionego najmniejszego elementu z pierwszym elementem
        swap(arr[k], arr[i]);
    }
}
// Funkcja wykonująca testy przypadku oczekiwanego dla sortowania kopcowego
void testy_typ_kopcowe()
{
    int i, N=1000;
    std::vector<int>tab;
    int liczba_testow = 8;
    cout<<"Testy sortowania przez kopcowanie dla przypadku oczekiwanego:"<<endl;
    for(i=0; i<liczba_testow; i++)
    {
        // Generowanie zawartości tablicy
        tab=losuj(N);
        // Pomiar czasu
        auto start = high_resolution_clock::now();
        sortowanie_kopcowe(tab, N);
        auto stop = high_resolution_clock::now();
        std::chrono::duration<double> czas = stop-start;
        cout<<"Czas dla "<<N<<" liczb w tablicy: ";
        std::cout << std::setw(9) << czas.count() << " s."<< endl;
        N = N * 2 ;
    }
}
// Funkcja wykonująca testy przypadku pesymistycznego dla sortowania kopcowego
void testy_pes_kopcowe()
{
    int i, N=1000;
    std::vector<int>tab;
    int liczba_testow = 8;
    cout<<endl<<"Testy sortowania przez kopcowanie dla przypadku pesymistycznego: "<<endl; //Przypadek pesymistyczny - sortowanie tablicy posortowanej odwrotnie
    for(i=0; i<liczba_testow; i++)
    {
        // Generowanie zawartości tablicy
        tab=losuj(N);
        sortowanie_przez_wybor_malejaco(tab, N);
        // Pomiar czasu
        auto start = high_resolution_clock::now();
        sortowanie_kopcowe(tab, N);
        auto stop = high_resolution_clock::now();
        std::chrono::duration<double> czas = stop-start;
        cout<<"Czas dla "<<N<<" liczb w tablicy: ";
        std::cout << std::setw(9) << czas.count() << " s."<< endl;
        N = N * 2 ;
    }
}
// Funkcja wykonująca testy przypadku optymistycznego dla sortowania kopcowego
void testy_opt_kopcowe()
{
    int i,j, N=1000;
    std::vector<int>tab;
    int liczba_testow = 8, a=100;
    cout<<"Testy sortowania przez kopcowanie dla przypadku optymistycznego: "<<endl; //Przypadek optymistyczny - tablica uporządkowana z niewielką liczbą elementów nie na swoich miejscach
    for(i=0; i<liczba_testow; i++)
    {
        // Generowanie zawartości tablicy
        tab=losuj(N);
        sortowanie_kopcowe(tab, N);
        for(j=0; j<liczba_testow; j++)
        {
            swap(tab[j], tab[a]);
            a = a + 100;
        }
        // Pomiar czasu
        auto start = high_resolution_clock::now();
        sortowanie_kopcowe(tab, N);
        auto stop = high_resolution_clock::now();
        std::chrono::duration<double> czas = stop-start;
        cout<<"Czas dla "<<N<<" liczb w tablicy: ";
        std::cout << std::setw(9) << czas.count() << " s."<< endl;
        N = N * 2;
    }
}
// Funkcja wykonująca testy przypadku oczekiwanego dla sortowania przez wybór
void testy_typ_wybor()
{
    int i, N=1000;
    std::vector<int>tab;
    int liczba_testow = 8;
    cout<<"Testy sortowania przez wybor dla przypadku oczekiwanego:"<<endl;
    for(i=0; i<liczba_testow; i++)
    {
        // Generowanie zawartości tablicy
        tab=losuj(N);
        // Pomiar czasu
        auto start = high_resolution_clock::now();
        sortowanie_przez_wybor(tab, N);
        auto stop = high_resolution_clock::now();
        std::chrono::duration<double> czas = stop-start;
        cout<<"Czas dla "<<N<<" liczb w tablicy: ";
        std::cout << std::setw(9) << czas.count() << " s."<< endl;
        // zwiekszenie rozmiarow tablicy
        N = N * 2 ;
    }
}
// Funkcja wykonująca testy przypadku pesymistycznego dla sortowania przez wybór
void testy_pes_wybor()
{
    int i, N=1000;
    std::vector<int>tab;
    int liczba_testow = 8;
    cout<<"Testy sortowania przez kopcowanie dla przypadku pesymistycznego: "<<endl; //Przypadek pesymistyczny - sortowanie tablicy posortowanej odwrotnie
    for(i=0; i<liczba_testow; i++)
    {
        // Generowanie zawartości tablicy
        tab=losuj(N);
        sortowanie_przez_wybor_malejaco(tab, N);
        // Pomiar czasu
        auto start = high_resolution_clock::now();
        sortowanie_przez_wybor(tab, N);
        auto stop = high_resolution_clock::now();
        std::chrono::duration<double> czas = stop-start;
        cout<<"Czas dla "<<N<<" liczb w tablicy: ";
        std::cout << std::setw(9) << czas.count() << " s."<< endl;
        // zwiekszenie rozmiarow tablicy
        N = N * 2 ;
    }
}
// Funkcja wykonująca testy przypadku optymistycznego dla sortowania przez wybór
void testy_opt_wybor()
{
    int i,j, N=1000;
    std::vector<int>tab;
    int liczba_testow = 8, a=100;
    cout<<"Testy sortowania przez wybor dla przypadku optymistycznego: "<<endl; //Przypadek optymistyczny - tablica uporządkowana z niewielką liczbą elementów nie na swoich miejscach
    for(i=0; i<liczba_testow; i++)
    {
        // Generowanie zawartości tablicy
        tab=losuj(N);
        sortowanie_kopcowe(tab, N);
        for(j=0; j<liczba_testow; j++)
        {
            swap(tab[j], tab[a]);
            a = a + 100;
        }
        // Pomiar czasu
        auto start = high_resolution_clock::now();
        sortowanie_przez_wybor(tab, N);
        auto stop = high_resolution_clock::now();
        std::chrono::duration<double> czas = stop-start;
        cout<<"Czas dla "<<N<<" liczb w tablicy: ";
        std::cout << std::setw(9) << czas.count() << " s."<< endl;
        // zwiekszenie rozmiarow tablicy
        N = N * 2 ;
    }
}

int main()
{
    std::vector<int>tab;
    tab = wczytanie("Dane.txt");
    int N=tab.size();
    sortowanie_przez_wybor_malejaco(tab, N);
    zapisz_do_pliku("zapis.txt", tab, N);

    testy_typ_kopcowe();
    testy_typ_wybor();
    testy_opt_kopcowe();
    testy_opt_wybor();
    testy_pes_kopcowe();
    testy_pes_wybor();


    return 0;
}
