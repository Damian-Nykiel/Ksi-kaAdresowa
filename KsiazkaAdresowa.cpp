#include <iostream>
#include <fstream>
#include <windows.h>
#include <sstream>
#include <vector>

using namespace std;

struct Adresat {
    int id;
    string imie, nazwisko, numerTelefonu, email, adres;
};

string wczytajLinie() {
    string wejscie = "";
    cin.sync();
    getline(cin, wejscie);
    return wejscie;
}

int konwersjaStringNaInt(string liczbaString) {
    int liczbaInt;
    istringstream iss(liczbaString);
    iss >> liczbaInt;

    return liczbaInt;
}

void przepiszWektorDoPliku (vector<Adresat> &adresaci) {
    Adresat przepisywany;

    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out);
    for (vector<Adresat>::iterator itr = adresaci.begin(), koniec = adresaci.end(); itr != koniec; ++itr) {
        przepisywany = *itr;
        plik << przepisywany.id << "|" << przepisywany.imie << "|" << przepisywany.nazwisko << "|" << przepisywany.numerTelefonu << "|" << przepisywany.email << "|" << przepisywany.adres << "|" << endl;
    }
    plik.close();
}

void wczytajAdresatowZPliku (vector<Adresat> &adresaci) {
    Adresat wczytany;
    string linia = "";
    int pozycja = 0;

    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::in);
    if (plik.good() == true) {
        while (getline(plik,linia)) {
            pozycja = linia.find("|");
            wczytany.id = konwersjaStringNaInt(linia.substr(0,pozycja));
            linia.erase(0, pozycja+1);
            pozycja = linia.find("|");
            wczytany.imie = linia.substr(0,pozycja);
            linia.erase(0, pozycja+1);
            pozycja = linia.find("|");
            wczytany.nazwisko = linia.substr(0,pozycja);
            linia.erase(0, pozycja+1);
            pozycja = linia.find("|");
            wczytany.numerTelefonu = linia.substr(0,pozycja);
            linia.erase(0, pozycja+1);
            pozycja = linia.find("|");
            wczytany.email = linia.substr(0,pozycja);
            linia.erase(0, pozycja+1);
            pozycja = linia.find("|");
            wczytany.adres = linia.substr(0,pozycja);
            linia.erase(0, pozycja+1);

            adresaci.push_back(wczytany);
        }
        plik.close();
    } else {
        fstream plik;
        plik.open("KsiazkaAdresowa",ios::out);
        plik.close();
    }
}

int idOstatniegoAdresata (vector<Adresat> &adresaci) {
    Adresat ostatni;
    int idOstatniegoAdresata = 0;

    if (adresaci.empty() == false) {
        ostatni = adresaci.back();
        return idOstatniegoAdresata = ostatni.id;
    } else
        return idOstatniegoAdresata;
}

void dodajAdresata(vector<Adresat> &adresaci) {
    Adresat nowy;
    string imie, nazwisko, numerTelefonu, email, adres;

    system("cls");
    cout << "Dodawanie adresata" << endl;
    cout << "Podaj imi©: ";
    imie = wczytajLinie();
    cout << "Podaj nazwisko: ";
    nazwisko = wczytajLinie();
    cout << "Podaj numer telefonu: ";
    numerTelefonu = wczytajLinie();
    cout << "Podaj email: ";
    email = wczytajLinie();
    cout << "Podaj adres: ";
    adres = wczytajLinie();

    nowy.id = idOstatniegoAdresata(adresaci)+1;
    nowy.imie = imie;
    nowy.nazwisko = nazwisko;
    nowy.numerTelefonu = numerTelefonu;
    nowy.email = email;
    nowy.adres = adres;
    adresaci.push_back(nowy);

    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out | ios::app);
    plik << nowy.id << "|" << nowy.imie << "|" << nowy.nazwisko << "|" << nowy.numerTelefonu << "|" << nowy.email << "|" << nowy.adres << "|" << endl;
    plik.close();
    cout << "Osoba zostaˆa dodana." << endl;
    system("pause");
}

void wyszukiwanieWedlugImienia(vector<Adresat> &adresaci) {
    Adresat porowynwany;
    string wyszukiwaneImie = "";
    char wybor;

    cout << "Podaj wyszukiwane imi©: ";
    wyszukiwaneImie = wczytajLinie();

    for (vector<Adresat>::iterator itr = adresaci.begin(), koniec = adresaci.end(); itr != koniec; ++itr) {
        porowynwany = *itr;
        if (porowynwany.imie == wyszukiwaneImie) {
            cout << endl;
            cout << "ID: " << porowynwany.id << endl;
            cout << porowynwany.imie << " " << porowynwany.nazwisko << endl;
            cout << "Telefon: " << porowynwany.numerTelefonu << endl;
            cout << "Email: " << porowynwany.email << endl;
            cout << "Adres: " << porowynwany.adres << endl;
            cout << endl;
        }
    }
    system("pause");

    cout << endl  << "1. Wyszukaj inne imi©" << endl;
    cout << "2. Powr¢t" << endl;
    cin >> wybor;

    if (wybor == '1')
        wyszukiwanieWedlugImienia(adresaci);
    else if (wybor == '2')
        system("cls");
}

void wyszukiwanieWedlugNazwiska(vector<Adresat> &adresaci) {
    Adresat porowynwany;
    string wyszukiwaneNazwisko = "";
    char wybor;

    cout << "Podaj wyszukiwane nazwisko: ";
    wyszukiwaneNazwisko = wczytajLinie();

    for (vector<Adresat>::iterator itr = adresaci.begin(), koniec = adresaci.end(); itr != koniec; ++itr) {
        porowynwany = *itr;
        if (porowynwany.nazwisko == wyszukiwaneNazwisko) {
            cout << endl;
            cout << "ID: " << porowynwany.id << endl;
            cout << porowynwany.imie << " " << porowynwany.nazwisko << endl;
            cout << "Telefon: " << porowynwany.numerTelefonu << endl;
            cout << "Email: " << porowynwany.email << endl;
            cout << "Adres: " << porowynwany.adres << endl;
            cout << endl;
        }
    }
    system("pause");

    cout << endl  << "1. Wyszukaj inne nazwisko" << endl;
    cout << "2. Powr¢t" << endl;
    cin >> wybor;

    if (wybor == '1')
        wyszukiwanieWedlugNazwiska(adresaci);

    else if (wybor == '2')
        system("cls");
}

void wyswietlWszystkichAdresatow(vector<Adresat> &adresaci) {
    for (vector<Adresat>::iterator itr = adresaci.begin(), koniec = adresaci.end(); itr != koniec; ++itr) {
        Adresat wczytany = *itr;
        cout << endl;
        cout << "ID: " << wczytany.id << endl;
        cout << wczytany.imie << " " << wczytany.nazwisko << endl;
        cout << "Telefon: " << wczytany.numerTelefonu << endl;
        cout << "Email: " << wczytany.email << endl;
        cout << "Adres: " << wczytany.adres << endl;
        cout << endl;
    }
}

void usunAdresata(vector<Adresat> &adresaci) {
    char wybor;
    int id;

    system ("cls");
    cout << "Kt¢r¥ osob© chcesz usun¥†?" << endl;
    wyswietlWszystkichAdresatow(adresaci);
    cout << "Podaj ID osoby do usuni©cia: ";
    cin >> id;

    for (vector<Adresat>::iterator itr = adresaci.begin(), koniec = adresaci.end(); itr != koniec; ++itr) {
        Adresat usuwany = *itr;
        if (usuwany.id == id) {
            cout << endl << "Czy na pewno chcesz usun¥† adresata o ID: " << id << "?" << endl;
            cout << "Je¾eli tak wybierz 't', je¾eli nie wybierz 'n'." << endl;
            cin >> wybor;

            if (wybor == 't') {
                adresaci.erase(itr);
                przepiszWektorDoPliku(adresaci);
                cout << "Adresat zostaˆ usuni©ty." << endl;
                system("pause");
            }
            if (wybor == 'n') {
                cout << "Nie usuni©to adresata." << endl;
                system("pause");
            }
        }
    }
}

void edytujAdresata(vector<Adresat> &adresaci) {
    char wybor;
    int id;
    string imie, nazwisko, numerTelefonu, email, adres;

    system ("cls");
    cout << "Kt¢r¥ osob© chcesz edytowa†?" << endl;
    wyswietlWszystkichAdresatow(adresaci);
    cout << "Podaj ID osoby kt¢r¥ chcesz edytowa†: ";
    cin >> id;

    for (vector<Adresat>::iterator itr = adresaci.begin(), koniec = adresaci.end(); itr != koniec; ++itr) {
        Adresat edytowany = *itr;
        if (edytowany.id == id) {
            system ("cls");
            cout << "1 - imi©" << endl;
            cout << "2 - nazwisko" << endl;
            cout << "3 - numer telefonu" << endl;
            cout << "4 - email" << endl;
            cout << "5 - adres" << endl;
            cout << "6 - powr¢t do menu" << endl;

            cin >> wybor;

            if (wybor == '1') {
                cout << "Wpisz imi©: ";
                cin >> imie;
                edytowany.imie = imie;
            } else if (wybor == '2') {
                cout << "Wpisz nazwisko: ";
                cin >> nazwisko;
                edytowany.nazwisko = nazwisko;
            } else if (wybor == '3') {
                cout << "Wpisz numer telefonu: ";
                cin >> numerTelefonu;
                edytowany.numerTelefonu = numerTelefonu;
            } else if (wybor == '4') {
                cout << "Wpisz email: ";
                cin >> email;
                edytowany.email = email;
            } else if (wybor == '5') {
                cout << "Wpisz adres: ";
                cin >> adres;
                edytowany.adres = adres;
            } else if (wybor == '6')
                break;

            adresaci.erase(itr);
            adresaci.insert(itr, edytowany);
            cout << "Edycja zakoäczona pomy˜lnie." << endl;
            system("pause");
        }
    }
    przepiszWektorDoPliku(adresaci);
}

int main() {
    vector<Adresat> adresaci;
    char wybor;

    wczytajAdresatowZPliku(adresaci);

    while (true) {
        system ("cls");
        cout << "1. Dodaj adresata." << endl;
        cout << "2. Wyszukaj po imieniu." << endl;
        cout << "3. Wyszukaj po nazwisku." << endl;
        cout << "4. Wy˜wietl wszystkich adresat¢w." << endl;
        cout << "5. Usuä adresata." << endl;
        cout << "6. Edytuj adresata." << endl;
        cout << "9. Zakoäcz program." << endl;

        cin >> wybor;

        if (wybor == '1') {
            dodajAdresata(adresaci);
        } else if (wybor == '2') {
            wyszukiwanieWedlugImienia(adresaci);
        } else if (wybor == '3') {
            wyszukiwanieWedlugNazwiska(adresaci);
        } else if (wybor == '4') {
            wyswietlWszystkichAdresatow(adresaci);
            system("pause");
        } else if (wybor == '5') {
            usunAdresata(adresaci);
        } else if (wybor == '6') {
            edytujAdresata(adresaci);
        } else if (wybor == '9') {
            exit(0);
        }
    }
    return 0;
}
