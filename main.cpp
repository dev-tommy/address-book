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
    unsigned int idUzytkownika = 0;
};

void rejestracjaUzytkownika(char* nazwaPlikuUzytkownicy);
void zmianaHaslaUzytkownika(char* nazwaPlikuUzytkownicy, vector<Uzytkownik> &uzytkownicy,int idUzytkownika);
void wczytajAdresatowZPliku(char* nazwaPlikuAdresaci, vector<Kontakt> &adresaci, int idUzytkownika);
void dodajAdresata(char* nazwaPlikuAdresaci, vector<Kontakt> &adresaci, int idUzytkownika);
void dodajUzytkownika(char* nazwaPlikuUzytkownicy, vector<Uzytkownik> &uzytkownicy);
void dodajAdresataDoPliku(char* nazwaPlikuAdresaci,Kontakt dodawanyKontakt);
void dodajUzytkownikaDoPliku(char* nazwaPlikuUzytkownicy, Uzytkownik dodawanyUzytkownik);
void wyswietlWszystkichAdresatow(vector<Kontakt> &adresaci);
void wyszukajAdresataPoNazwisku(vector<Kontakt> &adresaci);
void wyszukajAdresataPoImieniu(vector<Kontakt> &adresaci);
void usunAdresata(char* nazwaPlikuAdresaci,vector<Kontakt> &adresaci);
void aktualizujPlikZAdresatami(char* nazwaPlikuAdresaci, Kontakt edytowanyAdresat);
void usunAdresataOPozycji(char* nazwaPlikuAdresaci, int idAdresataDoUsuniecia);
void edytujDaneAdresata(char* nazwaPlikuAdresaci, vector<Kontakt> &adresaci, unsigned int pozycjaAdresataWPamieci, string pole);
void wyswietlAdresata(Kontakt adresatDoWyswietlenia);
void wyswietlTytul();
void wyczyscEkran();
void wyswietlMenu(char* nazwaPlikuAdresaci, char* nazwaPlikuUzytkownicy, vector<Kontakt> &adresaci, vector<Uzytkownik> &uzytkownicy);

int wczytajUzytkownikowZPliku(char* nazwaPlikuUzytkownicy, vector<Uzytkownik> &uzytkownicy);
int logowanieUzytkownika(char* nazwaPlikuUzytkownicy);
int wyszukajAdresataPoID(vector<Kontakt> &adresaci, unsigned int szukaneId);
int konwertujTekstNaLiczbe(string liczba);
int menuGlowne();
int menuLogowania();
int menuEdycjiAdresata(vector<Kontakt> &adresaci, int pozycjaAdresataWPamieci);
int podajOstatnieIdAdresata(char* nazwaPlikuAdresaci);

string konwertujLiczbeNaTekst(int liczba);
string konwertujKontaktNaTekst(Kontakt kontaktDoKonwersji);
string konwertujUzytkownikaNaTekst(Uzytkownik uzytkownikDoKonwersji);

Kontakt konwertujTekstNaKontakt(string liniaZDanymiAdresata);
Uzytkownik konwertujTekstNaUzytkownik(string liniaZDanymiUzytkownika);

int main() {
    char* nazwaPlikuAdresaci = "Adresaci.txt";
    char* nazwaPlikuUzytkownicy = "Uzytkownicy.txt";
    vector<Uzytkownik> uzytkownicy;
    vector<Kontakt> adresaci;
    wyswietlTytul();
    wyswietlMenu(nazwaPlikuAdresaci, nazwaPlikuUzytkownicy, adresaci, uzytkownicy);

    return 0;
}

void dodajAdresataDoPliku(char* nazwaPlikuAdresaci,Kontakt dodawanyKontakt) {
    fstream plik;
    plik.open(nazwaPlikuAdresaci,ios::out | ios::app);
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
void dodajUzytkownikaDoPliku(char* nazwaPlikuUzytkownicy, Uzytkownik dodawanyUzytkownik) {
    fstream plik;
    plik.open(nazwaPlikuUzytkownicy,ios::out | ios::app);
    if (plik.good()) {
        plik << konwertujUzytkownikaNaTekst(dodawanyUzytkownik) << endl;

        cout << "Dodano uzytkownika o id: " << dodawanyUzytkownik.id << endl;
        plik.close();
        system("pause");
    } else {
        cout << "Nie udalo sie dodac uzytkownika o id: " << dodawanyUzytkownik.id << endl;
        system("pause");
    }
}
void dodajAdresata(char* nazwaPlikuAdresaci, vector<Kontakt> &adresaci, int idUzytkownika) {
    bool pobranoDane = false;
    char odpowiedz;
    unsigned int liczbaKontaktow = adresaci.size();
    unsigned int ostatnieID;
    Kontakt dodawanyKontakt;


    if (liczbaKontaktow>0) {
        ostatnieID = podajOstatnieIdAdresata(nazwaPlikuAdresaci);
    } else {
        ostatnieID = 0;
    }

    dodawanyKontakt.id = ostatnieID+1;
    dodawanyKontakt.idUzytkownika = idUzytkownika;

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
    dodajAdresataDoPliku(nazwaPlikuAdresaci, dodawanyKontakt);
}
void dodajUzytkownika(char* nazwaPlikuUzytkownicy, vector<Uzytkownik> &uzytkownicy) {
    string nazwa, haslo;
    unsigned int liczbaUzytkownikow = uzytkownicy.size();
    unsigned int ostatnieID;
    Uzytkownik dodawanyUzytkownik;

    if (liczbaUzytkownikow>0) {
        ostatnieID = uzytkownicy[liczbaUzytkownikow-1].id;
    } else {
        ostatnieID = 0;
    }

    dodawanyUzytkownik.id = ostatnieID+1;
    wyswietlTytul();
    cout << "Rejestracja:" << endl;
    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwa;

    int i=0;
    while (i<liczbaUzytkownikow) {
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

    dodawanyUzytkownik.nazwa = nazwa;
    dodawanyUzytkownik.haslo = haslo;

    uzytkownicy.push_back(dodawanyUzytkownik);
    dodajUzytkownikaDoPliku(nazwaPlikuUzytkownicy, dodawanyUzytkownik);
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
void aktualizujPlikZAdresatami(char* nazwaPlikuAdresaci, Kontakt edytowanyAdresat) {
    fstream plik, plik_tymczasowy;
    string liniaZDanymiAdresata;
    Kontakt daneAdresata;
    char* nazwaPlikuTymczasowego = "Adresaci_tymczasowy.txt";

    plik.open(nazwaPlikuAdresaci,ios::in);
    if (plik.good()) {
        plik_tymczasowy.open(nazwaPlikuTymczasowego,ios::out);
        if (plik_tymczasowy.good()) {
            cin.sync();
            while(!plik.eof()) {
                getline(plik,liniaZDanymiAdresata);
                if (liniaZDanymiAdresata.size() > 1) {
                        daneAdresata = konwertujTekstNaKontakt(liniaZDanymiAdresata);

                        if (daneAdresata.id == edytowanyAdresat.id) {
                            plik_tymczasowy << konwertujKontaktNaTekst(edytowanyAdresat) << endl;
                            continue;
                        }
                    plik_tymczasowy << liniaZDanymiAdresata << endl;
                }
            }
            plik_tymczasowy.close();
            plik.close();
            remove(nazwaPlikuAdresaci);
            rename(nazwaPlikuTymczasowego, nazwaPlikuAdresaci);

        }
    } else {
        cout << "Nie udało się zauktualizować pliku" << endl;
        system("pause");
    }

}
void usunAdresataOPozycji(char* nazwaPlikuAdresaci, int idAdresataDoUsuniecia) {
    fstream plik, plik_tymczasowy;
    string liniaZDanymiAdresata;
    Kontakt daneAdresata;
    char* nazwaPlikuTymczasowego = "Adresaci_tymczasowy.txt";

    plik.open(nazwaPlikuAdresaci,ios::in);
    if (plik.good()) {
        plik_tymczasowy.open(nazwaPlikuTymczasowego,ios::out);
        if (plik_tymczasowy.good()) {
            cin.sync();
            while(!plik.eof()) {
                getline(plik,liniaZDanymiAdresata);
                if (liniaZDanymiAdresata.size() > 1) {
                        daneAdresata = konwertujTekstNaKontakt(liniaZDanymiAdresata);

                        if (daneAdresata.id == idAdresataDoUsuniecia) {
                            continue;
                        }
                    plik_tymczasowy << liniaZDanymiAdresata << endl;
                }
            }
            plik_tymczasowy.close();
            plik.close();
            remove(nazwaPlikuAdresaci);
            rename(nazwaPlikuTymczasowego, nazwaPlikuAdresaci);

        }
    } else {
        cout << "Nie udało się zauktualizować pliku" << endl;
        system("pause");
    }
}
void usunAdresata(char* nazwaPlikuAdresaci,vector<Kontakt> &adresaci) {
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
                usunAdresataOPozycji(nazwaPlikuAdresaci, idAdresataDoUsuniecia);
                //aktualizujPlikZAdresatami(nazwaPlikuAdresaci, adresaci);
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
    kontaktWFormieTekstu += konwertujLiczbeNaTekst(kontaktDoKonwersji.idUzytkownika) + "|";
    for(int i = 0; i < polaDanychAdresowych.size(); i++) {
        kontaktWFormieTekstu+=polaDanychAdresowych[i]+"|";
    }
    return kontaktWFormieTekstu;
}
string konwertujUzytkownikaNaTekst(Uzytkownik uzytkownikDoKonwersji) {
    string uzytkownikWFormieTekstu;
    vector<string> polaDanychUzytkownika;

    polaDanychUzytkownika.push_back(uzytkownikDoKonwersji.nazwa);
    polaDanychUzytkownika.push_back(uzytkownikDoKonwersji.haslo);

    uzytkownikWFormieTekstu = konwertujLiczbeNaTekst(uzytkownikDoKonwersji.id) + "|";
    for(int i = 0; i < polaDanychUzytkownika.size(); i++) {
        uzytkownikWFormieTekstu+=polaDanychUzytkownika[i]+"|";
    }
    return uzytkownikWFormieTekstu;
}
Kontakt konwertujTekstNaKontakt(string liniaZDanymiAdresata) {
    Kontakt kontaktTymczasowy;
    int numerPola = 0;
    char znak;
    kontaktTymczasowy.id=0;
    // IdAdresata | IdUzytkownika | imie | nazwisko | telefon | email | adres
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
            if ((znak >= '0') && (znak <='9')) {
                kontaktTymczasowy.idUzytkownika *= 10;
                kontaktTymczasowy.idUzytkownika += (znak - '0');
            }
            break;
        case 2:
            kontaktTymczasowy.imie+=znak;
            break;
        case 3:
            kontaktTymczasowy.nazwisko+=znak;
            break;
        case 4:
            kontaktTymczasowy.nrTelefonu+=znak;
            break;
        case 5:
            kontaktTymczasowy.email+=znak;
            break;
        case 6:
            kontaktTymczasowy.adres+=znak;
            break;
        }
        liniaZDanymiAdresata.erase(0,1);
    }

    return kontaktTymczasowy;
}
Uzytkownik konwertujTekstNaUzytkownik(string liniaZDanymiUzytkownika) {
    Uzytkownik uzytkownikTymczasowy;
    int numerPola = 0;
    char znak;
    uzytkownikTymczasowy.id=0;
    // IdUzytkownika | nazwa | haslo
    while(liniaZDanymiUzytkownika.length()) {
        znak = liniaZDanymiUzytkownika[0];
        if (znak == '|') {
            numerPola++;
            liniaZDanymiUzytkownika.erase(0,1);
            continue;
        }
        switch(numerPola) {
        case 0:
            if ((znak >= '0') && (znak <='9')) {
                uzytkownikTymczasowy.id *= 10;
                uzytkownikTymczasowy.id += (znak - '0');
            }
            break;
        case 1:
            uzytkownikTymczasowy.nazwa+=znak;
            break;
        case 2:
            uzytkownikTymczasowy.haslo+=znak;
            break;
        }
        liniaZDanymiUzytkownika.erase(0,1);
    }

    return uzytkownikTymczasowy;
}
void wczytajAdresatowZPliku(char* nazwaPlikuAdresaci, vector<Kontakt> &adresaci, int idUzytkownika) {
    string liniaZDanymiAdresata;
    fstream plik;
    Kontakt daneAdresata;
    adresaci.clear();
    plik.open(nazwaPlikuAdresaci,ios::in);
    if (plik.good()) {
        cin.sync();
        while(!plik.eof()) {
            getline(plik,liniaZDanymiAdresata);
            if (liniaZDanymiAdresata.length() > 0) {
                daneAdresata = konwertujTekstNaKontakt(liniaZDanymiAdresata);
                if (daneAdresata.idUzytkownika == idUzytkownika)
                    adresaci.push_back(daneAdresata);
            }
        }
    }

    plik.close();
}
int wczytajUzytkownikowZPliku(char* nazwaPlikuUzytkownicy, vector<Uzytkownik> &uzytkownicy) {
    string liniaZDanymiUzytkownika;
    fstream plik;

    uzytkownicy.clear();
    plik.open(nazwaPlikuUzytkownicy,ios::in);
    if (plik.good()) {
        cin.sync();
        while(!plik.eof()) {
            getline(plik,liniaZDanymiUzytkownika);
            if (liniaZDanymiUzytkownika.length() > 0)
                uzytkownicy.push_back(konwertujTekstNaUzytkownik(liniaZDanymiUzytkownika));
        }

    }

    plik.close();

}
void edytujDaneAdresata(char* nazwaPlikuAdresaci, vector<Kontakt> &adresaci, unsigned int pozycjaAdresataWPamieci, string pole) {
    Kontakt edytowanyAdresat = adresaci[pozycjaAdresataWPamieci];
    wyswietlTytul();
    cout << "Podaj ID:  " << edytowanyAdresat.id << endl;
    cout << endl;
    cout << "Adresat do edycji: " << endl;
    wyswietlAdresata(edytowanyAdresat);
    if (pole == "imie") {
        cout << "Podaj nowe imię: ";
        cin >> edytowanyAdresat.imie;
    } else if (pole == "nazwisko") {
        cout << "Podaj nowe nazwisko: ";
        cin >> edytowanyAdresat.nazwisko;
    } else if (pole == "numer telefonu") {
        cout << "Podaj nowy numer telefonu: ";
        cin >> edytowanyAdresat.nrTelefonu;
    } else if (pole == "email") {
        cout << "Podaj nowy email: ";
        cin >> edytowanyAdresat.email;
    } else if (pole == "adres") {
        cout << "Podaj nowy adres: ";
        cin >> edytowanyAdresat.adres;
    }
    aktualizujPlikZAdresatami(nazwaPlikuAdresaci, edytowanyAdresat);
    cout << "Dane zmienione! " << endl;
    Sleep(1000);
}
void wyswietlMenu(char* nazwaPlikuAdresaci, char* nazwaPlikuUzytkownicy, vector<Kontakt> &adresaci, vector<Uzytkownik> &uzytkownicy) {
    bool menuEdycjiAdresataAktywne = false;
    bool zakonczDzialanie = false;
    bool menuLogowaniaAktywne = true;
    bool menuGlowneAktywne = false;
    int idAdresata, pozycjaAdresataWPamieci;
    int idUzytkownika = 0;
    int iloscUzytkownikow = uzytkownicy.size();
    char wybor;

    while(!zakonczDzialanie) {
        while(menuLogowaniaAktywne) {
            if (idUzytkownika == 0) {
                switch(menuLogowania()) {
                case 1:
                    idUzytkownika = logowanieUzytkownika(nazwaPlikuUzytkownicy);
                    wczytajAdresatowZPliku(nazwaPlikuAdresaci, adresaci, idUzytkownika);
                    break;
                case 2:
                    rejestracjaUzytkownika(nazwaPlikuUzytkownicy);
                    break;
                case 9:
                    menuLogowaniaAktywne = false;
                    menuGlowneAktywne = false;
                    zakonczDzialanie = true;
                    break;

                default:
                    cout << " Brak takiej opcji !!! ";
                    Sleep(1000);
                }
            } else {
                menuLogowaniaAktywne = false;
                menuGlowneAktywne = true;
            }
        }
        while(menuGlowneAktywne) {
            switch(menuGlowne()) {
            case 1:
                dodajAdresata(nazwaPlikuAdresaci, adresaci, idUzytkownika);
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
                usunAdresata(nazwaPlikuAdresaci, adresaci);
                wczytajAdresatowZPliku(nazwaPlikuAdresaci, adresaci, idUzytkownika);
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
                        edytujDaneAdresata(nazwaPlikuAdresaci, adresaci, pozycjaAdresataWPamieci, "imie");
                        break;
                    case 2:
                        edytujDaneAdresata(nazwaPlikuAdresaci, adresaci, pozycjaAdresataWPamieci, "nazwisko");
                        break;
                    case 3:
                        edytujDaneAdresata(nazwaPlikuAdresaci, adresaci, pozycjaAdresataWPamieci, "numer telefonu");
                        break;
                    case 4:
                        edytujDaneAdresata(nazwaPlikuAdresaci, adresaci, pozycjaAdresataWPamieci, "email");
                        break;
                    case 5:
                        edytujDaneAdresata(nazwaPlikuAdresaci, adresaci, pozycjaAdresataWPamieci, "adres");
                        break;
                    case 6:
                        menuEdycjiAdresataAktywne = false;
                        break;
                    default:
                        cout << " Brak takiej opcji !!! ";
                        Sleep(1000);
                    }
                    wczytajAdresatowZPliku(nazwaPlikuAdresaci, adresaci, idUzytkownika);
                    menuEdycjiAdresataAktywne = false;
                }
                break;
            case 7:
                wczytajUzytkownikowZPliku(nazwaPlikuUzytkownicy, uzytkownicy);
                zmianaHaslaUzytkownika(nazwaPlikuUzytkownicy, uzytkownicy, idUzytkownika);
                break;
            case 8:
                idUzytkownika = 0;
                menuGlowneAktywne = false;
                menuLogowaniaAktywne = true;
                break;

            default:
                cout << " Brak takiej opcji !!! ";
                Sleep(1000);
            }
        }
    }
}
void wyczyscEkran() {
    system("cls");
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
int menuGlowne() {
    int wybor;
    wyswietlTytul();
    cout << "1. Dodaj adresata" << endl;
    cout << "2. Wyszukaj po imieniu" << endl;
    cout << "3. Wyszukaj po nazwisku" << endl;
    cout << "4. Wyswietl wszystkich adresatów" << endl;
    cout << "5. Usuń adresata" << endl;
    cout << "6. Edytuj adresata" << endl;
    cout << "7. Zmień hasło" << endl;
    cout << "8. Wyloguj się" << endl;
    cout << "Twój wybór: ";
    cin >> wybor;
    return wybor;
}
int menuLogowania() {
    int wybor;
    wyswietlTytul();
    cout << "1. Logowanie" << endl;
    cout << "2. Rejestracja" << endl;
    cout << "9. Zakoncz program" << endl;
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
void rejestracjaUzytkownika(char* nazwaPlikuUzytkownicy) {
    vector<Uzytkownik> uzytkownicy;

    wczytajUzytkownikowZPliku(nazwaPlikuUzytkownicy, uzytkownicy);
    dodajUzytkownika(nazwaPlikuUzytkownicy, uzytkownicy);

    cout << "Konto zalozone" << endl;
    Sleep(1000);
}
int logowanieUzytkownika(char* nazwaPlikuUzytkownicy ) {
    int liczbaUzytkownikow;
    string nazwa, haslo;
    vector<Uzytkownik> uzytkownicy;
    wczytajUzytkownikowZPliku(nazwaPlikuUzytkownicy, uzytkownicy);
    liczbaUzytkownikow = uzytkownicy.size();

    cout << "Podaj nazwe: ";
    cin >> nazwa;
    int i = 0;
    while (i<liczbaUzytkownikow) {
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
void zmianaHaslaUzytkownika(char* nazwaPlikuUzytkownicy, vector<Uzytkownik> &uzytkownicy,int idUzytkownika) {
    fstream plik;
    string haslo;
    int liczbaUzytkownikow = uzytkownicy.size();
    cout << "Podaj nowe haslo: ";  // mozna zapytac tez o stare
    cin >> haslo;
    for (int i=0; i<liczbaUzytkownikow; i++) {
        if (uzytkownicy[i].id == idUzytkownika) {
            uzytkownicy[i].haslo = haslo;

            plik.open(nazwaPlikuUzytkownicy,ios::out);
            if (plik.good()) {
                for (int i=0 ; i<uzytkownicy.size(); i++) {
                    plik << konwertujUzytkownikaNaTekst(uzytkownicy[i]) << endl;
                }
                cout << "Zmieniono haslo uzytkownika o id: " << idUzytkownika << endl;
                plik.close();
                system("pause");
            } else {
                cout << "Nie udalo sie zmienic hasla uzytkownika o id: " << idUzytkownika << endl;
                system("pause");
            }
        }
    }
}
int podajOstatnieIdAdresata(char* nazwaPlikuAdresaci) {
    string liniaZDanymiAdresata;
    fstream plik;
    Kontakt daneAdresata;
    plik.open(nazwaPlikuAdresaci,ios::in);
    if (plik.good()) {
        cin.sync();
        while(!plik.eof()) {
            getline(plik,liniaZDanymiAdresata);
            if (liniaZDanymiAdresata.length() > 0)
                daneAdresata = konwertujTekstNaKontakt(liniaZDanymiAdresata);
        }
        return daneAdresata.id;
    }

    plik.close();
}
