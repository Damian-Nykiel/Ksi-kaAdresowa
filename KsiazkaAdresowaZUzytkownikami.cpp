#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

string nazwaPliku = "KsiazkaAdresowa.txt", nazwaPliku2 = "Uzytkownicy.txt";

struct Uzytkownik {
    int id = 0;
    string nazwa = "", haslo = "";
};

struct Adresat {
    int id = 0;
    string imie = "", nazwisko = "", numerTelefonu = "", email = "", adres = "";
};

string wczytajLinie() {
    string wejscie = "";
    getline(cin, wejscie);
    return wejscie;
}

char wczytajZnak() {
    string wejscie = "";
    char znak  = {0};
    cin.sync();

    while (true) {
        getline(cin, wejscie);

        if (wejscie.length() == 1) {
            znak = wejscie[0];
            break;
        }
        cout << "To nie jest pojedynczy znak. Wpisz ponownie." << endl;
    }
    return znak;
}

int wczytajLiczbeCalkowita() {
    string wejscie = "";
    int liczba = 0;

    while (true) {
        getline(cin, wejscie);

        stringstream myStream(wejscie);
        if (myStream >> liczba)
            break;
        cout << "To nie jest liczba. Wpisz ponownie. " << endl;
    }
    return liczba;
}

string konwerjsaIntNaString(int liczba) {
    ostringstream ss;
    ss << liczba;
    string str = ss.str();

    return str;
}

string zamienPierwszaLitereNaDuzaAPozostaleNaMale(string tekst) {
    if (!tekst.empty()) {
        transform(tekst.begin(), tekst.end(), tekst.begin(), ::tolower);
        tekst[0] = toupper(tekst[0]);
    }
    return tekst;
}

string nazwaZalogowanegoUzytkownika(vector<Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika) {
    for (vector<Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++) {
        if (idZalogowanegoUzytkownika == itr->id)
            return itr->nazwa;
    }
}

void dopiszUzytkownikaDoPliku(Uzytkownik nowy) {
    fstream plikTekstowy;
    plikTekstowy.open(nazwaPliku2.c_str(), ios::out | ios::app);

    if (plikTekstowy.good() == true) {
        plikTekstowy << nowy.id << '|';
        plikTekstowy << nowy.nazwa << '|';
        plikTekstowy << nowy.haslo << '|' << endl;
        plikTekstowy.close();

    } else {
        cout << "Nie udalo sie otworzyc pliku i zapisac w nim danych." << endl;
        system("pause");
    }
}

void rejestracja (vector<Uzytkownik> &uzytkownicy) {
    Uzytkownik uzytkownik;

    string nazwa, haslo;
    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwa;

    for (vector<Uzytkownik>::iterator itr = uzytkownicy.begin(), koniec = uzytkownicy.end(); itr != koniec; itr++) {
        if (itr->nazwa == nazwa) {
            cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
            cin >> nazwa;
            itr = uzytkownicy.begin();
        }
    }
    cout << "Podaj haslo: ";
    cin >> haslo;
    uzytkownik.haslo = haslo;
    uzytkownik.nazwa = nazwa;
    if (uzytkownicy.empty() == true) {
        uzytkownik.id = 1;
    } else {
        uzytkownik.id = uzytkownicy.back().id + 1;
    }

    uzytkownicy.push_back(uzytkownik);
    dopiszUzytkownikaDoPliku(uzytkownik);

    cout << "Konto zalozone" << endl;
    Sleep(1000);
}

int logowanie (vector<Uzytkownik> &uzytkownicy) {
    string nazwa, haslo;
    cout << "Podaj nazwe: ";
    cin >> nazwa;

    for (vector<Uzytkownik>::iterator  itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++) {
        if (itr->nazwa == nazwa) {
            for (int proby = 0; proby < 3; proby++) {
                cout << "Podaj haslo. Pozostalo prob " << 3-proby << ": ";
                cin >> haslo;
                if (itr->haslo == haslo) {
                    cout << "Zalogowales sie." << endl;
                    Sleep(1000);
                    return itr->id;
                }
            }
            cout << "Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba." << endl;
            Sleep(3000);
            return 0;
        }
    }
    cout << "Nie ma uzytkownika z takim loginem" << endl;
    Sleep(1500);
    return 0;
}

void zapiszNoweHasloWPliku(vector<Uzytkownik> &uzytkownicy){
    fstream plikTekstowy;
    string liniaZDanymiUzytkownika = "";

    plikTekstowy.open(nazwaPliku2.c_str(), ios::out);
    if (plikTekstowy.good())
    {
        for (vector<Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
        {
            liniaZDanymiUzytkownika += konwerjsaIntNaString(itr->id) + '|';
            liniaZDanymiUzytkownika += itr->nazwa + '|';
            liniaZDanymiUzytkownika += itr->haslo + '|';

            plikTekstowy << liniaZDanymiUzytkownika << endl;
            liniaZDanymiUzytkownika = "";
        }
        plikTekstowy.close();
    }
    else
    {
        cout << "Nie mozna otworzyc pliku Uzytkownicy.txt" << endl;
    }

}


void zmianaHasla(vector<Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika) {
    string haslo;

    cout << "Podaj nowe haslo: ";
    cin >> haslo;
    for (vector<Uzytkownik>::iterator  itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++) {
        if (itr->id == idZalogowanegoUzytkownika) {
            itr->haslo = haslo;
            zapiszNoweHasloWPliku(uzytkownicy);
            cout << "Haslo zostalo zmienione" << endl;
            Sleep(1500);
        }
    }
}

Uzytkownik pobierzDaneUzytkownika(string daneUzytkownikaOddzielonePionowymiKreskami) {
    Uzytkownik uzytkownik;

    string pojedynczaDanaUzytkonwika = "";
    int numerPojedynczejDanejUzytkownika = 1;

    for (int pozycjaZnaku = 0; pozycjaZnaku < daneUzytkownikaOddzielonePionowymiKreskami.length(); pozycjaZnaku++) {
        if (daneUzytkownikaOddzielonePionowymiKreskami[pozycjaZnaku] != '|') {
            pojedynczaDanaUzytkonwika += daneUzytkownikaOddzielonePionowymiKreskami[pozycjaZnaku];
        } else {
            switch(numerPojedynczejDanejUzytkownika) {
            case 1:
                uzytkownik.id = atoi(pojedynczaDanaUzytkonwika.c_str());
                break;
            case 2:
                uzytkownik.nazwa = pojedynczaDanaUzytkonwika;
                break;
            case 3:
                uzytkownik.haslo = pojedynczaDanaUzytkonwika;
                break;
            }
            pojedynczaDanaUzytkonwika = "";
            numerPojedynczejDanejUzytkownika++;
        }
    }
    return uzytkownik;
}

void wczytajUzytkownikowZPliku(vector<Uzytkownik> &uzytkownicy) {
    Uzytkownik uzytkownik;
    string daneJednegoUzytkownikaOddzielonePionowymiKreskami = "";

    fstream plikTekstowy;
    plikTekstowy.open(nazwaPliku2.c_str(), ios::in);

    if (plikTekstowy.good() == true) {
        while (getline(plikTekstowy, daneJednegoUzytkownikaOddzielonePionowymiKreskami)) {
            uzytkownik = pobierzDaneUzytkownika(daneJednegoUzytkownikaOddzielonePionowymiKreskami);
            uzytkownicy.push_back(uzytkownik);
        }
        plikTekstowy.close();
    }
}

Adresat pobierzDaneAdresata(string daneAdresataOddzielonePionowymiKreskami) {
    Adresat adresat;
    string pojedynczaDanaAdresata = "";
    int numerPojedynczejDanejAdresata = 1;

    for (int pozycjaZnaku = 0; pozycjaZnaku < daneAdresataOddzielonePionowymiKreskami.length(); pozycjaZnaku++) {
        if (daneAdresataOddzielonePionowymiKreskami[pozycjaZnaku] != '|') {
            pojedynczaDanaAdresata += daneAdresataOddzielonePionowymiKreskami[pozycjaZnaku];
        } else {
            switch(numerPojedynczejDanejAdresata) {
            case 1:
                adresat.id = atoi(pojedynczaDanaAdresata.c_str());
                break;
            case 2:
                break;
            case 3:
                adresat.imie = pojedynczaDanaAdresata;
                break;
            case 4:
                adresat.nazwisko = pojedynczaDanaAdresata;
                break;
            case 5:
                adresat.numerTelefonu = pojedynczaDanaAdresata;
                break;
            case 6:
                adresat.email = pojedynczaDanaAdresata;
                break;
            case 7:
                adresat.adres = pojedynczaDanaAdresata;
                break;
            }
            pojedynczaDanaAdresata = "";
            numerPojedynczejDanejAdresata++;
        }
    }
    return adresat;
}

int pobierzIDUzytkownikaZDanych (string daneAdresataOddzielonePionowymiKreskami) {

    int id = 0;
    int numerPojedynczejDanejAdresata = 1;
    string pojedynczaDanaAdresata = "";

    for (int pozycjaZnaku = 0; numerPojedynczejDanejAdresata <= 2; pozycjaZnaku++) {
        if (daneAdresataOddzielonePionowymiKreskami[pozycjaZnaku] != '|')
            pojedynczaDanaAdresata =+ daneAdresataOddzielonePionowymiKreskami[pozycjaZnaku];
        else {
            if (numerPojedynczejDanejAdresata == 2)
                id = atoi(pojedynczaDanaAdresata.c_str());
            pojedynczaDanaAdresata = "";
            numerPojedynczejDanejAdresata++;
        }
    }
    return id;
}

void wczytajAdresatowZPliku(vector<Adresat> &adresaci, int idZalogowanegoUzytkownika) {
    Adresat adresat;
    string daneJednegoAdresataOddzielonePionowymiKreskami = "";

    fstream plikTekstowy;
    plikTekstowy.open(nazwaPliku.c_str(), ios::in);

    if (plikTekstowy.good() == true) {
        while (getline(plikTekstowy, daneJednegoAdresataOddzielonePionowymiKreskami)) {
            int idUzytkownikaPobraneZDanych = pobierzIDUzytkownikaZDanych(daneJednegoAdresataOddzielonePionowymiKreskami);
            if (idUzytkownikaPobraneZDanych == idZalogowanegoUzytkownika) {
                adresat = pobierzDaneAdresata(daneJednegoAdresataOddzielonePionowymiKreskami);
                adresaci.push_back(adresat);
            }
        }
        plikTekstowy.close();
    }
}

void wypiszWszystkichAdresatow(vector<Adresat> &adresaci) {
    system("cls");
    if (!adresaci.empty()) {
        for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
            cout << "Id:                 " << itr->id << endl;
            cout << "Imie:               " << itr->imie << endl;
            cout << "Nazwisko:           " << itr->nazwisko << endl;
            cout << "Numer telefonu:     " << itr->numerTelefonu << endl;
            cout << "Email:              " << itr->email << endl;
            cout << "Adres:              " << itr->adres << endl << endl;
        }
        cout << endl;
    } else {
        cout << "Ksiazka adresowa jest pusta." << endl << endl;
    }

    system("pause");
}

void dopiszAdresataDoPliku(Adresat adresat, int idZalogowanegoUzytkownika) {
    fstream plikTekstowy;
    plikTekstowy.open(nazwaPliku.c_str(), ios::out | ios::app);

    if (plikTekstowy.good() == true) {
        plikTekstowy << adresat.id << '|';
        plikTekstowy << idZalogowanegoUzytkownika << '|';
        plikTekstowy << adresat.imie << '|';
        plikTekstowy << adresat.nazwisko << '|';
        plikTekstowy << adresat.numerTelefonu << '|';
        plikTekstowy << adresat.email << '|';
        plikTekstowy << adresat.adres << '|' << endl;
        plikTekstowy.close();

        cout << endl << "Adresat zostal dodany" << endl;
        system("pause");
    } else {
        cout << "Nie udalo sie otworzyc pliku i zapisac w nim danych." << endl;
        system("pause");
    }
}

void zapiszWszystkichAdresatowDoPlikuTekstowego(vector<Adresat> &adresaci, int idWybranegoAdresata, int idZalogowanegoUzytkownika) {
    fstream plikTekstowy, plikTekstowy2;
    string liniaZDanymiAdresata = "";
    string pojedynczaDanaAdresata = "";
    int numerDanejAdresata = 1;
    int idAdresata = 0;

    plikTekstowy.open(nazwaPliku.c_str(), ios::in);
    plikTekstowy2.open("Adresaci_tymczasowy.txt", ios::out);
    if (plikTekstowy.good()) {
        while (getline(plikTekstowy, liniaZDanymiAdresata)) {
            numerDanejAdresata = 1;
            for (int pozycjaZnaku = 0; numerDanejAdresata <= 1; pozycjaZnaku++) {
                if (liniaZDanymiAdresata[pozycjaZnaku] != '|') {
                    pojedynczaDanaAdresata += liniaZDanymiAdresata[pozycjaZnaku];
                } else {
                    idAdresata = atoi(pojedynczaDanaAdresata.c_str());
                    numerDanejAdresata++;
                    pojedynczaDanaAdresata = "";
                }
            }
            if (idAdresata == idWybranegoAdresata) {
                for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
                    if( itr->id == idWybranegoAdresata) {
                        liniaZDanymiAdresata = "";
                        liniaZDanymiAdresata += konwerjsaIntNaString(itr->id) + '|';
                        liniaZDanymiAdresata += konwerjsaIntNaString(idZalogowanegoUzytkownika) + '|';
                        liniaZDanymiAdresata += itr->imie + '|';
                        liniaZDanymiAdresata += itr->nazwisko + '|';
                        liniaZDanymiAdresata += itr->numerTelefonu + '|';
                        liniaZDanymiAdresata += itr->email + '|';
                        liniaZDanymiAdresata += itr->adres + '|';

                        plikTekstowy2 << liniaZDanymiAdresata << endl;
                        liniaZDanymiAdresata = "";
                    } else
                        continue;
                }
            } else {
                plikTekstowy2 << liniaZDanymiAdresata << endl;
                liniaZDanymiAdresata = "";
            }
        }
        plikTekstowy.close();
        plikTekstowy2.close();
        remove("KsiazkaAdresowa.txt");
        rename("Adresaci_tymczasowy.txt", "KsiazkaAdresowa.txt");

    } else {
        cout << "Nie mozna otworzyc pliku KsiazkaAdresowa.txt" << endl;
    }
}

void wyszukajAdresatowPoImieniu(vector<Adresat> &adresaci) {
    string imiePoszukiwanegoAdresata = "";
    int iloscAdresatow = 0;

    system("cls");
    if (!adresaci.empty()) {
        cout << ">>> WYSZUKIWANIE ADRESATOW O IMIENIU <<<" << endl << endl;

        cout << "Wyszukaj adresatow o imieniu: ";
        imiePoszukiwanegoAdresata = wczytajLinie();

        imiePoszukiwanegoAdresata = zamienPierwszaLitereNaDuzaAPozostaleNaMale(imiePoszukiwanegoAdresata);

        for (vector<Adresat>::iterator  itr = adresaci.begin(); itr != adresaci.end(); itr++) {
            if (itr->imie == imiePoszukiwanegoAdresata) {
                cout << endl;
                cout << "Id:                 " << itr->id << endl;
                cout << "Imie:               " << itr->imie << endl;
                cout << "Nazwisko:           " << itr->nazwisko << endl;
                cout << "Numer Telefonu:     " << itr->numerTelefonu << endl;
                cout << "Nr Email:           " << itr->email << endl;
                cout << "Adres:              " << itr->adres << endl;
                iloscAdresatow++;
            }
        }
        if (iloscAdresatow == 0) {
            cout << endl << "Nie ma adresatow z tym imieniem w ksiazce adresowej" << endl;
        } else {
            cout << endl << "Ilosc adresatow z imieniem: >>> " << imiePoszukiwanegoAdresata << " <<<";
            cout << " w ksiazce adresowej wynosi: " << iloscAdresatow << endl << endl;
        }
    } else {
        cout << "Ksiazka adresowa jest pusta" << endl << endl;
    }
    cout << endl;
    system("pause");
}

void wyszukajAdresatowPoNazwisku(vector<Adresat> &adresaci) {
    string nazwiskoPoszukiwanegoAdresata = "";
    int iloscAdresatow = 0;

    system("cls");
    if (!adresaci.empty()) {
        cout << ">>> WYSZUKIWANIE ADRESATOW O NAZWISKU <<<" << endl << endl;

        cout << "Wyszukaj adresatow o nazwisku: ";
        nazwiskoPoszukiwanegoAdresata = wczytajLinie();
        nazwiskoPoszukiwanegoAdresata = zamienPierwszaLitereNaDuzaAPozostaleNaMale(nazwiskoPoszukiwanegoAdresata);

        for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
            if (itr->nazwisko == nazwiskoPoszukiwanegoAdresata) {
                cout << endl;
                cout << "Id:                 " << itr->id << endl;
                cout << "Imie:               " << itr->imie << endl;
                cout << "Nazwisko:           " << itr->nazwisko << endl;
                cout << "Numer Telefonu:     " << itr->numerTelefonu << endl;
                cout << "Nr Email:           " << itr->email << endl;
                cout << "Adres:              " << itr->adres << endl;
                iloscAdresatow++;
            }
        }
        if (iloscAdresatow == 0) {
            cout << endl << "Nie ma adresatow z tym nazwiskiem w ksiazce adresowej" << endl;
        } else {
            cout << endl << "Ilosc adresatow z nazwiskiem: >>> " << nazwiskoPoszukiwanegoAdresata << " <<<";
            cout << " w ksiazce adresowej wynosi: " << iloscAdresatow << endl << endl;
        }
    } else {
        cout << "Ksiazka adresowa jest pusta" << endl << endl;
    }
    cout << endl;
    system("pause");
}

int wyszukajIdOstatniegoAdresata () {
    string pojedynczaDanaAdresata = "";
    string daneJednegoAdresataOddzielonePionowymiKreskami = "";
    string dane = "";
    int id = 0;
    int numerDanejAdresata = 1;

    fstream plikTekstowy;
    plikTekstowy.open(nazwaPliku.c_str(), ios::in);
    if (plikTekstowy.good() == true) {
        while (getline(plikTekstowy, daneJednegoAdresataOddzielonePionowymiKreskami))
            dane = daneJednegoAdresataOddzielonePionowymiKreskami;

        for (int pozycjaZnaku = 0; numerDanejAdresata <= 1; pozycjaZnaku++) {
            if (dane[pozycjaZnaku] != '|') {
                pojedynczaDanaAdresata += dane[pozycjaZnaku];
            } else {
                id = atoi(pojedynczaDanaAdresata.c_str());
                numerDanejAdresata++;
                pojedynczaDanaAdresata = "";
            }
        }
    }
    plikTekstowy.close();
    return id;
}

void dodajAdresata(vector<Adresat> &adresaci, int idZalogowanegoUzytkownika) {
    Adresat adresat;

    system("cls");
    cout << ">>> DODAWANIE NOWEGO ADRESATA <<<" << endl << endl;

    int idOstatniegoAdresata = wyszukajIdOstatniegoAdresata();
    adresat.id = idOstatniegoAdresata + 1;

    cout << "Podaj imie: ";
    adresat.imie = wczytajLinie();
    adresat.imie = zamienPierwszaLitereNaDuzaAPozostaleNaMale(adresat.imie);

    cout << "Podaj nazwisko: ";
    adresat.nazwisko  = wczytajLinie();
    adresat.nazwisko = zamienPierwszaLitereNaDuzaAPozostaleNaMale(adresat.nazwisko);

    cout << "Podaj numer telefonu: ";
    adresat.numerTelefonu = wczytajLinie();

    cout << "Podaj email: ";
    adresat.email = wczytajLinie();

    cout << "Podaj adres: ";
    adresat.adres = wczytajLinie();

    adresaci.push_back(adresat);

    dopiszAdresataDoPliku(adresat, idZalogowanegoUzytkownika);
}

void usunAdresata(vector<Adresat> &adresaci, int idZalogowanegoUzytkownika) {
    int idUsuwanegoAdresata = 0;
    char znak;
    bool czyIstniejeAdresat = false;

    system("cls");
    if (!adresaci.empty()) {
        cout << ">>> USUWANIE WYBRANEJ OSOBY <<<" << endl << endl;
        cout << "Podaj numer ID adresata ktorego chcesz USUNAC: ";
        idUsuwanegoAdresata = wczytajLiczbeCalkowita();

        for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
            if (itr->id == idUsuwanegoAdresata) {
                czyIstniejeAdresat = true;
                cout << endl << endl << "Potwierdz naciskajac klawisz 't': ";
                znak = wczytajZnak();
                if (znak == 't') {
                    adresaci.erase(itr);
                    cout << endl << endl << "Szukany adresat zostal USUNIETY" << endl << endl;
                    zapiszWszystkichAdresatowDoPlikuTekstowego(adresaci, idUsuwanegoAdresata, idZalogowanegoUzytkownika);
                    break;
                } else {
                    cout << endl << endl << "Wybrany adresat NIE zostal usuniety" << endl << endl;
                    break;
                }
            }
        }
        if (czyIstniejeAdresat == false) {
            cout << endl << "Nie ma takiego adresata w ksiazce adresowej" << endl << endl;
        }
    } else {
        cout << "Ksiazka adresowa jest pusta" << endl << endl;
    }

    system("pause");
}

void edytujAdresata(vector<Adresat> &adresaci, int idZalogowanegoUzytkownika) {
    int idWybranegoAdresata = 0;
    char wybor;
    bool czyIstniejeAdresat = false;

    system("cls");
    if (!adresaci.empty()) {
        cout << ">>> EDYCJA WYBRANEGO ADRESATA <<<" << endl << endl;
        cout << "Podaj numer ID adresata u ktorego chcesz zmienic dane: ";
        idWybranegoAdresata = wczytajLiczbeCalkowita();

        for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
            if (itr->id == idWybranegoAdresata) {
                czyIstniejeAdresat = true;

                cout << endl << "Ktore dane zaktualizowac: " << endl;
                cout << "1 - Imie" << endl;
                cout << "2 - Nazwisko" << endl;
                cout << "3 - Numer telefonu" << endl;
                cout << "4 - Email" << endl;
                cout << "5 - Adres" << endl;
                cout << "6 - Powrot " << endl;
                cout << endl << "Wybierz 1-6: ";
                wybor = wczytajZnak();

                switch (wybor) {
                case '1':
                    cout << "Podaj nowe imie: ";
                    itr->imie = wczytajLinie();
                    itr->imie = zamienPierwszaLitereNaDuzaAPozostaleNaMale(itr->imie);
                    cout << endl << "Imie zostalo zmienione" << endl << endl;
                    zapiszWszystkichAdresatowDoPlikuTekstowego(adresaci, idWybranegoAdresata, idZalogowanegoUzytkownika);
                    break;
                case '2':
                    cout << "Podaj nowe nazwisko: ";
                    itr->nazwisko = wczytajLinie();
                    itr->nazwisko = zamienPierwszaLitereNaDuzaAPozostaleNaMale(itr->nazwisko);
                    cout << endl << "Nazwisko zostalo zmienione" << endl << endl;
                    zapiszWszystkichAdresatowDoPlikuTekstowego(adresaci, idWybranegoAdresata, idZalogowanegoUzytkownika);
                    break;
                case '3':
                    cout << "Podaj nowy numer telefonu: ";
                    itr->numerTelefonu = wczytajLinie();
                    cout << endl << "Numer telefonu zostal zmieniony" << endl << endl;
                    zapiszWszystkichAdresatowDoPlikuTekstowego(adresaci, idWybranegoAdresata, idZalogowanegoUzytkownika);
                    break;
                case '4':
                    cout << "Podaj nowy email: ";
                    itr->email = wczytajLinie();
                    cout << endl << "Email zostal zmieniony" << endl << endl;
                    zapiszWszystkichAdresatowDoPlikuTekstowego(adresaci, idWybranegoAdresata, idZalogowanegoUzytkownika);
                    break;
                case '5':
                    cout << "Podaj nowy adres zamieszkania: ";
                    itr->adres = wczytajLinie();
                    cout << endl << "Adres zostal zmieniony" << endl << endl;
                    zapiszWszystkichAdresatowDoPlikuTekstowego(adresaci, idWybranegoAdresata, idZalogowanegoUzytkownika);
                    break;
                case '6':
                    cout << endl << "Powrot do menu glownego" << endl << endl;
                    break;
                default:
                    cout << endl << "Nie ma takiej opcji w menu! Powrot do menu glownego." << endl << endl;
                    break;
                }
            }
        }
        if (czyIstniejeAdresat == false) {
            cout << endl << "Nie ma takiego adresata w ksiazce adresowej." << endl << endl;
        }
    } else {
        cout << "Ksiazka adresowa jest pusta." << endl << endl;
    }
    system("pause");
}

void zakonczProgram() {
    cout << endl << "Koniec programu." << endl;
    exit(0);
}

int main() {
    vector<Uzytkownik> uzytkownicy;
    vector<Adresat> adresaci;

    int idZalogowanegoUzytkownika = 0;
    char wybor;

    wczytajUzytkownikowZPliku(uzytkownicy);

    while (true) {
        system("cls");
        if (idZalogowanegoUzytkownika == 0) {
            system("cls");
            cout << ">>> KSIAZKA ADRESOWA <<<" << endl << endl;
            cout << "1. Rejestracja" << endl;
            cout << "2. Logowanie" << endl;
            cout << "3. Zakoncz program" << endl << endl;
            cout << "Twoj wybor: ";
            wybor = wczytajZnak();

            switch(wybor) {
            case '1':
                rejestracja(uzytkownicy);
                break;
            case '2':
                idZalogowanegoUzytkownika = logowanie(uzytkownicy);
                wczytajAdresatowZPliku(adresaci, idZalogowanegoUzytkownika);
                break;
            case '3':
                zakonczProgram();
                break;
            }
        } else {
            cout << ">>> KSIAZKA ADRESOWA <<<   Zalogowany jako: " << nazwaZalogowanegoUzytkownika(uzytkownicy, idZalogowanegoUzytkownika) << endl << endl;
            cout << "1. Dodaj adresata" << endl;
            cout << "2. Wyszukaj po imieniu" << endl;
            cout << "3. Wyszukaj po nazwisku" << endl;
            cout << "4. Wyswietl wszystkich adresatow" << endl;
            cout << "5. Usun adresata" << endl;
            cout << "6. Edytuj adresata" << endl;
            cout << "7. Zmien haslo" << endl;
            cout << "9. Wyloguj sie" << endl << endl;
            cout << "Twoj wybor: ";
            wybor = wczytajZnak();

            switch(wybor) {
            case '1':
                dodajAdresata(adresaci, idZalogowanegoUzytkownika);
                break;
            case '2':
                wyszukajAdresatowPoImieniu(adresaci);
                break;
            case '3':
                wyszukajAdresatowPoNazwisku(adresaci);
                break;
            case '4':
                wypiszWszystkichAdresatow(adresaci);
                break;
            case '5':
                usunAdresata(adresaci, idZalogowanegoUzytkownika);
                break;
            case '6':
                edytujAdresata(adresaci, idZalogowanegoUzytkownika);
                break;
            case '7':
                zmianaHasla(uzytkownicy, idZalogowanegoUzytkownika);
                break;
            case '9':
                idZalogowanegoUzytkownika = 0;
                adresaci.clear();
                break;
            }
        }
    }
    return 0;
}
