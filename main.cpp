#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct Uzytkownik {
    int id;
    string nazwa, haslo;
};

struct Kontakt {
    string imie="", nazwisko="", adres="", email="", nrTelefonu="";
    unsigned int id = 0;
};


void rejestracja(vector<Uzytkownik> &uzytkownicy);
int logowanie(vector<Uzytkownik> &uzytkownicy);
void zmianaHasla(vector<Uzytkownik> &uzytkownicy,int idZalogowanegoUzytkownika);

void wczytajAdresatowZPliku(char* nazwaPliku, vector<Kontakt> &adresaci);
void dodajAdresata(char* nazwaPliku, vector<Kontakt> &adresaci);
void dodajAdresataDoPliku(char* nazwaPliku,Kontakt dodawanyKontakt);
void wyswietlWszystkichAdresatow(vector<Kontakt> &adresaci);
void wyszukajAdresataPoNazwisku(vector<Kontakt> &adresaci);
void wyszukajAdresataPoImieniu(vector<Kontakt> &adresaci);
void usunAdresata(char* nazwaPliku,vector<Kontakt> &adresaci);
void aktualizujPlikZAdresatami(char* nazwaPliku, vector<Kontakt> &adresaci);
void usunAdresataOPozycji(vector<Kontakt> &adresaci, unsigned int pozycjaAdresataDoUsuniecia);
void edytujDaneAdresata(char* nazwaPliku, vector<Kontakt> &adresaci, unsigned int pozycjaAdresataWPamieci, string pole);
int wyszukajAdresataPoID(vector<Kontakt> &adresaci, unsigned int szukaneId);
void wyswietlAdresata(Kontakt adresatDoWyswietlenia);
void wyswietlTytul();
void wyczyscEkran();
void wyswietlMenu(char* nazwaPliku, vector<Kontakt> &adresaci);


int konwertujTekstNaLiczbe(string liczba);
string konwertujLiczbeNaTekst(int liczba);

int menuGlowne();
int menuEdycjiAdresata(vector<Kontakt> &adresaci, int pozycjaAdresataWPamieci);

Kontakt konwertujTekstNaKontakt(string liniaZDanymiAdresata);
string konwertujKontaktNaTekst(Kontakt kontaktDoKonwersji);


int main() {
    char* nazwaPliku = "ksiazka_adresowa_nowy_format.txt";
    vector<Uzytkownik> uzytkownicy;
    vector<Kontakt> adresaci;
    int idZalogowanegoUzytkownika = 0;
    int iloscUzytkownikow = uzytkownicy.size();
    char wybor;

    while(true) {
        if (idZalogowanegoUzytkownika == 0) {
            system("cls");
            cout << "1. Rejestracja" << endl;
            cout << "2. Logowanie" << endl;
            cout << "9. Zakoncz program" << endl;
            cin >>  wybor;

            if (wybor=='1') {
                rejestracja(uzytkownicy);
                iloscUzytkownikow = uzytkownicy.size();
            } else if (wybor=='2') {
                idZalogowanegoUzytkownika = logowanie(uzytkownicy);
            } else if (wybor=='9') {
                exit(0);
            }

        } else {
            system("cls");
            cout << "1. Zmiana hasla" << endl;
            cout << "2. Wylogowanie" << endl;
            cout << "9. Zakoncz program" << endl;
            cin >>  wybor;

            if (wybor=='1') {
                zmianaHasla(uzytkownicy, idZalogowanegoUzytkownika);
            } else if (wybor=='2') {
                idZalogowanegoUzytkownika = 0;
            } else if (wybor=='9') {
                cout << "Wylogowano" << endl;
                Sleep(1000);
                exit(0);
            }
        }

    }

    wyswietlTytul();
    wczytajAdresatowZPliku(nazwaPliku, adresaci);
    wyswietlMenu(nazwaPliku, adresaci);

    return 0;
}

void dodajAdresataDoPliku(char* nazwaPliku,Kontakt dodawanyKontakt) {
    fstream plik;
    plik.open(nazwaPliku,ios::out | ios::app);
    if (plik.good()) {
        plik << konwertujKontaktNaTekst(dodawanyKontakt) << endl;

        cout << "Dodano adresata o id: " << dodawanyKontakt.id << endl;
        plik.close();
        system("pause");
    } else {
        cout << "Nie udalo sie dodac adresata o id: " << dodawanyKontakt.id << endl;
        system("pause");
    }
}

void dodajAdresata(char* nazwaPliku, vector<Kontakt> &adresaci) {
    bool pobranoDane = false;
    char odpowiedz;
    unsigned int liczbaKontaktow = adresaci.size();
    unsigned int ostatnieID;
    Kontakt dodawanyKontakt;

    if (liczbaKontaktow>0) {
        ostatnieID = adresaci[liczbaKontaktow-1].id;
    } else {
        ostatnieID = 0;
    }

    dodawanyKontakt.id = ostatnieID+1;

    while(!pobranoDane) {
        odpowiedz=0;
        wyczyscEkran();
        wyswietlTytul();

        cout << " Dodaj kontakt" << endl;
        cout << "---------------" << endl;
        cout << endl;

        cin.sync();
        cout << "Podaj imie: ";
        getline(cin,dodawanyKontakt.imie);
        cout << "Podaj nazwisko: ";
        getline(cin,dodawanyKontakt.nazwisko);
        cout << "Podaj numer telefonu: ";
        getline(cin,dodawanyKontakt.nrTelefonu);
        cout << "Podaj e-mail: ";
        getline(cin,dodawanyKontakt.email);
        cout << "Podaj adres: ";
        getline(cin,dodawanyKontakt.adres);

        while((odpowiedz!='t') && (odpowiedz!='n')) {
            cout << endl << "Czy dane sa poprawne (t-tak/n-nie/a-anuluj) ? ";
            cin >> odpowiedz;
            if (odpowiedz == 't')
                pobranoDane = true;
            if (odpowiedz == 'a')
                return;
        }
    }

    adresaci.push_back(dodawanyKontakt);
    dodajAdresataDoPliku(nazwaPliku, dodawanyKontakt);
}

void wyswietlWszystkichAdresatow(vector<Kontakt> &adresaci) {
    bool brakKontaktow = true;
    unsigned int liczbaKontaktow = adresaci.size();
    wyczyscEkran();
    wyswietlTytul();

    cout << " Wszyscy adresaci [ " << liczbaKontaktow << " ]:" << endl;
    cout << "---------------------" << endl;
    cout << endl;

    for (int i=0; i<liczbaKontaktow; i++) {
        brakKontaktow = false;
        if (adresaci[i].id != 0)
            wyswietlAdresata(adresaci[i]);
    }
    if (brakKontaktow)
        cout << "Brak kontaktow do wyswietlenia." << endl << endl;
    system("pause");
}

void wyswietlAdresata(Kontakt adresatDoWyswietlenia) {
    cout << "ID:          " << adresatDoWyswietlenia.id << endl;
    cout << "Imie:        " << adresatDoWyswietlenia.imie << endl;
    cout << "Nazwisko:    " << adresatDoWyswietlenia.nazwisko << endl;
    cout << "Nr telefonu: " << adresatDoWyswietlenia.nrTelefonu << endl;
    cout << "E-mail:      " << adresatDoWyswietlenia.email << endl;
    cout << "Adres:       " << adresatDoWyswietlenia.adres << endl;
    cout << endl;
}

void wyszukajAdresataPoNazwisku(vector<Kontakt> &adresaci) {
    string nazwisko;
    bool brakKontaktow = true;
    unsigned int liczbaKontaktow = adresaci.size();

    wyczyscEkran();
    wyswietlTytul();

    cout << " Wyszukaj adresata wg nazwiska:" << endl;
    cout << "--------------------------------" << endl;
    cout << endl;
    cout << "Podaj nazwisko: ";
    cin.sync();
    getline(cin, nazwisko);
    cout << endl;
    cout << "Znalezieni adresaci: " << endl << endl;

    for (int i=0; i<liczbaKontaktow; i++) {
        if (adresaci[i].nazwisko == nazwisko) {
            brakKontaktow = false;
            wyswietlAdresata(adresaci[i]);
        }
    }
    if (brakKontaktow) {
        cout << "Nie znaleziono adresata z tym nazwiskiem." << endl << endl;
    }
    system("pause");
}

void wyszukajAdresataPoImieniu(vector<Kontakt> &adresaci) {
    string imie;
    bool brakKontaktow = true;
    unsigned int liczbaKontaktow = adresaci.size();

    wyczyscEkran();
    wyswietlTytul();

    cout << " Wyszukaj adresata wg imienia:" << endl;
    cout << "--------------------------------" << endl;
    cout << endl;
    cout << "Podaj imie: ";
    cin.sync();
    getline(cin, imie);
    cout << endl;
    cout << "Znalezieni adresaci: " << endl << endl;

    for (int i=0; i<liczbaKontaktow; i++) {
        if (adresaci[i].imie == imie) {
            brakKontaktow = false;
            wyswietlAdresata(adresaci[i]);
        }
    }
    if (brakKontaktow) {
        cout << "Nie znaleziono adresata z tym imieniem." << endl << endl;
    }
    system("pause");
}

int wyszukajAdresataPoID(vector<Kontakt> &adresaci, unsigned int szukaneId) {
    unsigned int liczbaKontaktow = adresaci.size();
    for (int i=0; i<liczbaKontaktow; i++) {
        if (adresaci[i].id == szukaneId) {
            return i;
        }
    }
    return -1;
}

void aktualizujPlikZAdresatami(char* nazwaPliku, vector<Kontakt> &adresaci) {
    fstream plik;
    plik.open(nazwaPliku,ios::out);
    if (plik.good()) {
        for (int i=0; i<adresaci.size(); i++) {
            plik << konwertujKontaktNaTekst(adresaci[i]) << endl;
        }
        plik.close();
    } else {
        cout << "Nie udało się zauktualizować pliku" << endl;
        system("pause");
    }

}

void usunAdresataOPozycji(vector<Kontakt> &adresaci, unsigned int pozycjaAdresataDoUsuniecia) {
    adresaci.erase(adresaci.begin()+pozycjaAdresataDoUsuniecia);
}

void usunAdresata(char* nazwaPliku,vector<Kontakt> &adresaci) {
    unsigned int idAdresataDoUsuniecia;
    int pozycjaAdresataDoUsuniecia;
    char wybor;
    wyczyscEkran();
    wyswietlTytul();
    cout << "Podaj ID adresata do usunięcia: ";
    cin >> idAdresataDoUsuniecia;
    cout << endl;
    cout << "Usuniety zostanie adresat: " << endl << endl;
    pozycjaAdresataDoUsuniecia = wyszukajAdresataPoID(adresaci,idAdresataDoUsuniecia);
    if (pozycjaAdresataDoUsuniecia >= 0) {
        wyswietlAdresata(adresaci[pozycjaAdresataDoUsuniecia]);
        while((wybor != 't') && (wybor != 'n')) {
            cout << "Czy napewno chcesz usunąć adresata (t/n) ? ";
            cin >> wybor;
            if (wybor == 't') {
                usunAdresataOPozycji(adresaci, pozycjaAdresataDoUsuniecia);
                aktualizujPlikZAdresatami(nazwaPliku, adresaci);
                cout << "Adresat usunięty !!!" << endl;
                Sleep(1000);
            }
            if (wybor == 'n')
                break;
        }
    } else {
        cout << "Nie znaleziono adresata o id: " << idAdresataDoUsuniecia << endl;
        Sleep(1500);
    }



}

string konwertujKontaktNaTekst(Kontakt kontaktDoKonwersji) {
    string kontaktWFormieTekstu;
    vector<string> polaDanychAdresowych;

    polaDanychAdresowych.push_back(kontaktDoKonwersji.imie);
    polaDanychAdresowych.push_back(kontaktDoKonwersji.nazwisko);
    polaDanychAdresowych.push_back(kontaktDoKonwersji.nrTelefonu);
    polaDanychAdresowych.push_back(kontaktDoKonwersji.email);
    polaDanychAdresowych.push_back(kontaktDoKonwersji.adres);

    kontaktWFormieTekstu = konwertujLiczbeNaTekst(kontaktDoKonwersji.id) + "|";
    for(int i = 0; i < polaDanychAdresowych.size(); i++) {
        kontaktWFormieTekstu+=polaDanychAdresowych[i]+"|";
    }
    return kontaktWFormieTekstu;
}

Kontakt konwertujTekstNaKontakt(string liniaZDanymiAdresata) {
    Kontakt kontaktTymczasowy;
    int numerPola = 0;
    char znak;
    kontaktTymczasowy.id=0;
    // Id | imie | nazwisko | telefon | email | adres
    while(liniaZDanymiAdresata.length()) {
        znak = liniaZDanymiAdresata[0];
        if (znak == '|') {
            numerPola++;
            liniaZDanymiAdresata.erase(0,1);
            continue;
        }
        switch(numerPola) {
        case 0:
            if ((znak >= '0') && (znak <='9')) {
                kontaktTymczasowy.id *= 10;
                kontaktTymczasowy.id += (znak - '0');
            }
            break;
        case 1:
            kontaktTymczasowy.imie+=znak;
            break;
        case 2:
            kontaktTymczasowy.nazwisko+=znak;
            break;
        case 3:
            kontaktTymczasowy.nrTelefonu+=znak;
            break;
        case 4:
            kontaktTymczasowy.email+=znak;
            break;
        case 5:
            kontaktTymczasowy.adres+=znak;
            break;
        }
        liniaZDanymiAdresata.erase(0,1);
    }

    return kontaktTymczasowy;
}

void wczytajAdresatowZPliku(char* nazwaPliku, vector<Kontakt> &adresaci) {
    string liniaZDanymiAdresata;
    fstream plik;

    adresaci.clear();
    plik.open(nazwaPliku,ios::in);
    if (plik.good())
    {
        cin.sync();
        while(!plik.eof()) {
            getline(plik,liniaZDanymiAdresata);
            if (liniaZDanymiAdresata.length() > 0)
                adresaci.push_back(konwertujTekstNaKontakt(liniaZDanymiAdresata));
        }

    }

    plik.close();
}

void edytujDaneAdresata(char* nazwaPliku, vector<Kontakt> &adresaci, unsigned int pozycjaAdresataWPamieci, string pole) {
    wyswietlTytul();
    cout << "Podaj ID:  " << adresaci[pozycjaAdresataWPamieci].id << endl;
    cout << endl;
    cout << "Adresat do edycji: " << endl;
    wyswietlAdresata(adresaci[pozycjaAdresataWPamieci]);
    if (pole == "imie") {
        cout << "Podaj nowe imię: ";
        cin >> adresaci[pozycjaAdresataWPamieci].imie;
    } else if (pole == "nazwisko") {
        cout << "Podaj nowe nazwisko: ";
        cin >> adresaci[pozycjaAdresataWPamieci].nazwisko;
    } else if (pole == "numer telefonu") {
        cout << "Podaj nowy numer telefonu: ";
        cin >> adresaci[pozycjaAdresataWPamieci].nrTelefonu;
    } else if (pole == "email") {
        cout << "Podaj nowy email: ";
        cin >> adresaci[pozycjaAdresataWPamieci].email;
    } else if (pole == "adres") {
        cout << "Podaj nowy adres: ";
        cin >> adresaci[pozycjaAdresataWPamieci].adres;
    }
    aktualizujPlikZAdresatami(nazwaPliku, adresaci);
    cout << "Dane zmienione! " << endl;
    Sleep(1000);
}

void wyswietlMenu(char* nazwaPliku, vector<Kontakt> &adresaci) {
    bool menuEdycjiAdresataAktywne = false;
    bool menuGlowneAktywne = true;
    int idAdresata, pozycjaAdresataWPamieci;

    while(menuGlowneAktywne) {
        switch(menuGlowne()) {
        case 1:
            dodajAdresata(nazwaPliku, adresaci);
            break;
        case 2:
            wyszukajAdresataPoImieniu(adresaci);
            break;
        case 3:
            wyszukajAdresataPoNazwisku(adresaci);
            break;
        case 4:
            wyswietlWszystkichAdresatow(adresaci);
            break;
        case 5:
            usunAdresata(nazwaPliku, adresaci);
            break;
        case 6:
            menuEdycjiAdresataAktywne = true;
            while(menuEdycjiAdresataAktywne) {
                wyswietlTytul();
                cout << "Podaj ID:  ";
                cin >> idAdresata;
                pozycjaAdresataWPamieci = wyszukajAdresataPoID(adresaci, idAdresata);
                switch(menuEdycjiAdresata(adresaci, pozycjaAdresataWPamieci)) {
                case 1:
                    edytujDaneAdresata(nazwaPliku, adresaci, pozycjaAdresataWPamieci, "imie");
                    break;
                case 2:
                    edytujDaneAdresata(nazwaPliku, adresaci, pozycjaAdresataWPamieci, "nazwisko");
                    break;
                case 3:
                    edytujDaneAdresata(nazwaPliku, adresaci, pozycjaAdresataWPamieci, "numer telefonu");
                    break;
                case 4:
                    edytujDaneAdresata(nazwaPliku, adresaci, pozycjaAdresataWPamieci, "email");
                    break;
                case 5:
                    edytujDaneAdresata(nazwaPliku, adresaci, pozycjaAdresataWPamieci, "adres");
                    break;
                case 6:
                    menuEdycjiAdresataAktywne = false;
                    break;
                default:
                    cout << " Brak takiej opcji !!! ";
                    Sleep(1000);
                }
                menuEdycjiAdresataAktywne = false;
            }
            break;
        case 9:
            menuGlowneAktywne = false;
            break;
        default:
            cout << " Brak takiej opcji !!! ";
            Sleep(1000);
        }
    }
}

int konwertujTekstNaLiczbe(string liczba) {
    return atoi(liczba.c_str());
}

string konwertujLiczbeNaTekst(int liczba) {
    stringstream tmp;
    string przekonwertowanaLiczba;
    tmp << liczba;
    przekonwertowanaLiczba = tmp.str().c_str();
    return przekonwertowanaLiczba;
}

void wyczyscEkran() {
    system("cls");
}

int menuGlowne() {
    int wybor;
    wyswietlTytul();
    cout << "1. Dodaj adresata" << endl;
    cout << "2. Wyszukaj po imieniu" << endl;
    cout << "3. Wyszukaj po nazwisku" << endl;
    cout << "4. Wyswietl wszystkich adresatów" << endl;
    cout << "5. Usuń adresata" << endl;
    cout << "6. Edytuj adresata" << endl;
    cout << "9. Zakoncz program" << endl;
    cout << "Twój wybór: ";
    cin >> wybor;
    return wybor;
}

int menuEdycjiAdresata(vector<Kontakt> &adresaci, int pozycjaAdresataWPamieci) {
    int wybor;
    if (pozycjaAdresataWPamieci >= 0) {
        cout << endl;
        cout << "Adresat do edycji: " << endl;
        wyswietlAdresata(adresaci[pozycjaAdresataWPamieci]);
        cout << endl;
        cout << "Które pole chcesz edytkować?" << endl;
        cout << "1 - imię" << endl;
        cout << "2 - nazwisko" << endl;
        cout << "3 - numer telefonu" << endl;
        cout << "4 - emial" << endl;
        cout << "5 - adres" << endl;
        cout << "6 - Wroc do menu glownego" << endl;
        cout << "Twój wybór: ";
        cin >> wybor;
        return wybor;
    } else {
        cout << "Nie znaleziono adresata!" << endl;
        Sleep(1000);
    }
    return 6;
}

void wyswietlTytul() {
    wyczyscEkran();
    cout << "KSIĄŻKA ADRESOWA" << endl;
}

void rejestracja(vector<Uzytkownik> &uzytkownicy) {
    string nazwa, haslo;
    int userCount = uzytkownicy.size();
    Uzytkownik userToRegister;

    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwa;

    int i=0;
    while (i<userCount) {
        if (uzytkownicy[i].nazwa == nazwa) {
            cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
            cin >> nazwa;
            i = 0;
        } else {
            i++;
        }
    }
    cout << "Podaj haslo: ";
    cin >> haslo;

    userToRegister.nazwa = nazwa;
    userToRegister.haslo = haslo;
    userToRegister.id = userCount + 1;

    uzytkownicy.push_back(userToRegister);

    cout << "Konto zalozone" << endl;
    Sleep(1000);
}

int logowanie(vector<Uzytkownik> &uzytkownicy) {
    string nazwa, haslo;
    int userCount = uzytkownicy.size();

    cout << "Podaj nazwe: ";
    cin >> nazwa;
    int i = 0;
    while (i<userCount) {
        if (uzytkownicy[i].nazwa == nazwa) {
            for (int proby=0; proby<3; proby++) {
                cout << "Podaj haslo: Pozostało prob " << 3-proby << ": ";
                cin >> haslo;
                if (uzytkownicy[i].haslo == haslo) {
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

void zmianaHasla(vector<Uzytkownik> &uzytkownicy,int idZalogowanegoUzytkownika) {
    string haslo;
    int userCount = uzytkownicy.size();

    cout << "Podaj nowe haslo: ";  // mozna zapytac tez o stare
    cin >> haslo;
    for (int i=0; i<userCount; i++) {
        if (uzytkownicy[i].id == idZalogowanegoUzytkownika) {
            uzytkownicy[i].haslo = haslo;
            cout << "Haslo zostalo zmienione" << endl;
            Sleep(1500);

        }
    }
}

