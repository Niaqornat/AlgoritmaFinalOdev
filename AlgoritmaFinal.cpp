#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

struct Siparis {
    int id;
    string musteriAdi;
    string siparisDetayi;
};

vector<Siparis> siparisler;
const string DOSYA_ADI = "siparisler.txt";


void dosyadanOku() {
    ifstream dosya(DOSYA_ADI);
    if (dosya.is_open()) {
        Siparis siparis;
        while (dosya >> siparis.id) {
            dosya.ignore(); 
            getline(dosya, siparis.musteriAdi);
            getline(dosya, siparis.siparisDetayi);
            siparisler.push_back(siparis);
        }
        dosya.close();
    }
}


void dosyayaKaydet() {
    ofstream dosya(DOSYA_ADI, ios::trunc);
    if (dosya.is_open()) {
        for (const auto &siparis : siparisler) {
            dosya << siparis.id << "\n"
                  << siparis.musteriAdi << "\n"
                  << siparis.siparisDetayi << "\n";
        }
        dosya.close();
    }
}


void kayitEkle() {
    Siparis yeniSiparis;
    cout << "Siparis ID: ";
    cin >> yeniSiparis.id;
    cin.ignore();
    cout << "Musteri Adi: ";
    getline(cin, yeniSiparis.musteriAdi);
    cout << "Siparis Detayi: ";
    getline(cin, yeniSiparis.siparisDetayi);
    siparisler.push_back(yeniSiparis);
    dosyayaKaydet();
    cout << "Siparis basariyla eklendi!\n";
}


void kayitSil() {
    int silinecekID;
    cout << "Silinecek Siparis ID: ";
    cin >> silinecekID;
    for (auto it = siparisler.begin(); it != siparisler.end(); ++it) {
        if (it->id == silinecekID) {
            siparisler.erase(it);
            dosyayaKaydet();
            cout << "Siparis basariyla silindi!\n";
            return;
        }
    }
    cout << "Siparis bulunamadi.\n";
}


void kayitGuncelle() {
    int guncellenecekID;
    cout << "Guncellenecek Siparis ID: ";
    cin >> guncellenecekID;
    for (auto &siparis : siparisler) {
        if (siparis.id == guncellenecekID) {
            cin.ignore();
            cout << "Yeni Musteri Adi: ";
            getline(cin, siparis.musteriAdi);
            cout << "Yeni Siparis Detayi: ";
            getline(cin, siparis.siparisDetayi);
            dosyayaKaydet();
            cout << "Siparis basariyla guncellendi!\n";
            return;
        }
    }
    cout << "Siparis bulunamadi.\n";
}


void kayitAra() {
    int arananID;
    cout << "Aranacak Siparis ID: ";
    cin >> arananID;
    for (const auto &siparis : siparisler) {
        if (siparis.id == arananID) {
            cout << "Siparis Bulundu!\n";
            cout << "ID: " << siparis.id << "\n";
            cout << "Musteri Adi: " << siparis.musteriAdi << "\n";
            cout << "Siparis Detayi: " << siparis.siparisDetayi << "\n";
            return;
        }
    }
    cout << "Siparis bulunamadi.\n";
}


void menu() {
    int secim;
    do {
        cout << "\n--- Restoran Siparis Takip Otomasyonu ---\n";
        cout << "1. Siparis Ekle\n";
        cout << "2. Siparis Sil\n";
        cout << "3. Siparis Guncelle\n";
        cout << "4. Siparis Ara\n";
        cout << "5. Cikis\n";
        cout << "Seciminiz: ";
        cin >> secim;

        switch (secim) {
            case 1: kayitEkle(); break;
            case 2: kayitSil(); break;
            case 3: kayitGuncelle(); break;
            case 4: kayitAra(); break;
            case 5: cout << "Programdan cikiliyor...\n"; break;
            default: cout << "Gecersiz secim! Tekrar deneyin.\n";
        }
    } while (secim != 5);
}

int main() {
    dosyadanOku(); 
    menu();
    return 0;
}
