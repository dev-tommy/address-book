#include <iostream>
#include <windows.h>

using namespace std;

struct Uzytkownik
{
    int id;
    string nazwa, haslo;
};

int rejestracja(Uzytkownik uzytkownicy[], int userCount)
{
    string nazwa, haslo;
    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwa;

    int i=0;
    while (i<userCount)
    {
        if (uzytkownicy[i].nazwa == nazwa)
        {
            cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
            cin >> nazwa;
            i = 0;
        }
        else
        {
            i++;
        }
    }
    cout << "Podaj haslo: ";
    cin >> haslo;
    uzytkownicy[userCount].nazwa = nazwa;
    uzytkownicy[userCount].haslo = haslo;
    uzytkownicy[userCount].id = userCount + 1;
    cout << "Konto zalozone" << endl;
    Sleep(1000);
    return userCount+1;
}

int logowanie(Uzytkownik uzytkownicy[], int userCount)
{
    string nazwa, haslo;
    cout << "Podaj nazwe: ";
    cin >> nazwa;
    int i = 0;
    while (i<userCount)
    {
        if (uzytkownicy[i].nazwa == nazwa)
        {
            for (int proby=0; proby<3; proby++)
            {
                cout << "Podaj haslo: Pozostało prob " << 3-proby << ": ";
                cin >> haslo;
                if (uzytkownicy[i].haslo == haslo)
                {
                    cout << "Zalogowales sie." << endl;
                    Sleep(1000);
                    return uzytkownicy[i].id;
                }


            }
            cout << "Podales 3 razy bledne haslo. Poczekaj 3 sekundy" << endl;
            Sleep(3000);
            return 0;
        }
        i++;

    }
    cout << "Nie ma uzytkownika z takim loginem" << endl;
    Sleep(1500);
    return 0;
}

void zmianaHasla(Uzytkownik uzytkownicy[],int iloscUzytkownikow,int idZalogowanegoUzytkownika)
{
    string haslo;
    cout << "Podaj nowe haslo: ";  // mozna zapytac tez o stare
    cin >> haslo;
    for (int i=0; i<iloscUzytkownikow; i++)
    {
        if (uzytkownicy[i].id == idZalogowanegoUzytkownika)
        {
            uzytkownicy[i].haslo = haslo;
            cout << "Haslo zostalo zmienione" << endl;
            Sleep(1500);

        }
    }
}

int main()
{
    Uzytkownik uzytkownicy[100];
    int idZalogowanegoUzytkownika = 0;
    int iloscUzytkownikow = 0;
    char wybor;

    while(true)
    {
        if (idZalogowanegoUzytkownika == 0)
        {


            system("cls");
            cout << "1. Rejestracja" << endl;
            cout << "2. Logowanie" << endl;
            cout << "9. Zakoncz program" << endl;
            cin >>  wybor;

            if (wybor=='1')
            {
                iloscUzytkownikow = rejestracja(uzytkownicy, iloscUzytkownikow);
            }
            else if (wybor=='2')
            {
                idZalogowanegoUzytkownika = logowanie(uzytkownicy, iloscUzytkownikow);
            }
            else if (wybor=='9')
            {
                exit(0);
            }

        }
        else
        {
           system("cls");
            cout << "1. Zmiana hasla" << endl;
            cout << "2. Wylogowanie" << endl;
            cout << "9. Zakoncz program" << endl;
            cin >>  wybor;

            if (wybor=='1')
            {
                zmianaHasla(uzytkownicy, iloscUzytkownikow, idZalogowanegoUzytkownika);
            }
            else if (wybor=='2')
            {
                idZalogowanegoUzytkownika = 0;
            }
            else if (wybor=='9')
            {
                exit(0);
            }
        }

    }

    return 0;
}
