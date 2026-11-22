/**
* @file Ekran.cpp
* @description Konsol yazdirma ve menu islemleri.
* @course Veri Yapıları
* @assignment 1. Odev
* @date 21.11.2026
* @author Ahmed Selim Yılmaz
*/

#include "Ekran.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>

using namespace std;

Ekran::Ekran() {
    secili = NULL;
    dosyaAdi = "Veri.txt";
    bilgiMesaji = "";
    pencereBaslangic = 0;
    aktifMod = 0;
    calisiyor = true;
}

Ekran::~Ekran() {
}

string Ekran::adresYazisi(MatrisDugum* adres) const {
    if (adres == NULL) {
        return "NULL";
    }
    ostringstream ss;
    ss << adres;
    return ss.str();
}

string Ekran::ortala(const string& metin, int genislik) const {
    int uzunluk = (int)metin.length();
    if (uzunluk >= genislik) {
        return metin.substr(uzunluk - genislik, genislik);
    }

    int bosluk = genislik - uzunluk;
    int sol = bosluk / 2;
    int sag = bosluk - sol;

    string sonuc = "";
    for (int i = 0; i < sol; i++) sonuc += " ";
    sonuc += metin;
    for (int i = 0; i < sag; i++) sonuc += " ";
    return sonuc;
}

void Ekran::satiraYaz(string* ekran, int toplamSatir, int satir, int sutun, const string& metin) const {
    if (satir < 0 || satir >= toplamSatir || sutun < 0) {
        return;
    }
    int gerekli = sutun + (int)metin.length();
    if ((int)ekran[satir].length() < gerekli) {
        ekran[satir].append(gerekli - (int)ekran[satir].length(), ' ');
    }
    for (int i = 0; i < (int)metin.length(); i++) {
        ekran[satir][sutun + i] = metin[i];
    }
}

void Ekran::girisTemizle() {
    cin.clear();
    cin.ignore(10000, '\n');
}

void Ekran::sayfaAyarla() {
    if (liste.bosMu() || secili == NULL) {
        pencereBaslangic = 0;
        return;
    }

    int indeks = liste.indeksBul(secili);
    if (indeks < 0) {
        pencereBaslangic = 0;
        return;
    }

    pencereBaslangic = (indeks / 5) * 5;
}

void Ekran::yazdir() const {
    string yildiz = "******************";
    string cizgi = "------------------";
    string ayirac = "----------------------------------------------";

    int mSatir = 0;
    int mSutun = 0;
    if (secili != NULL && secili->matris != NULL && !secili->matris->bosMu()) {
        mSatir = secili->matris->getSatirSayisi();
        mSutun = secili->matris->getSutunSayisi();
    }

    int menuSutun = 58;
    if (27 + mSutun * 3 + 3 > menuSutun) {
        menuSutun = 27 + mSutun * 3 + 3;
    }

    MatrisDugum* gorunenler[5];
    int adet = 0;

    if (!liste.bosMu()) {
        int baslangic = pencereBaslangic;
        if (baslangic < 0) baslangic = 0;
        if (baslangic >= liste.getBoyut()) baslangic = liste.getBoyut() - 1;

        MatrisDugum* gezgin = liste.getBas();
        for (int i = 0; i < baslangic && gezgin != NULL; i++) {
            gezgin = gezgin->sonraki;
        }
        while (gezgin != NULL && adet < 5) {
            gorunenler[adet] = gezgin;
            adet++;
            gezgin = gezgin->sonraki;
        }
    }

    int seciliSira = -1;
    for (int i = 0; i < adet; i++) {
        if (gorunenler[i] == secili) {
            seciliSira = i;
            break;
        }
    }

    int sonKutuBitis = (adet > 0) ? (2 + (adet - 1) * 8 + 7) : 10;
    int matrisSatirBas = (seciliSira >= 0) ? (2 + seciliSira * 8) : 2;
    int matrisBitis = matrisSatirBas + (mSatir > 0 ? mSatir : 1);

    int altSatir = sonKutuBitis + 1;
    if (matrisBitis + 1 > altSatir) altSatir = matrisBitis + 1;
    if (altSatir < 10) altSatir = 10;

    int toplamSatir = altSatir + 1;
    string* ekran = new string[toplamSatir];

    satiraYaz(ekran, toplamSatir, 0, 0, ayirac);

    if (adet == 0) {
        satiraYaz(ekran, toplamSatir, 3, 0, "Listede matris yok.");
    } else {
        for (int i = 0; i < adet; i++) {
            int r = 2 + i * 8;
            MatrisDugum* d = gorunenler[i];

            ostringstream ortSS;
            ortSS << fixed << setprecision(2) << d->matris->aritmetikOrtalama();

            satiraYaz(ekran, toplamSatir, r + 0, 0, yildiz);
            satiraYaz(ekran, toplamSatir, r + 1, 0, "*" + ortala(adresYazisi(d), 16) + "*");
            satiraYaz(ekran, toplamSatir, r + 2, 0, cizgi);
            satiraYaz(ekran, toplamSatir, r + 3, 0, "*" + ortala(ortSS.str(), 16) + "*");
            satiraYaz(ekran, toplamSatir, r + 4, 0, cizgi);
            satiraYaz(ekran, toplamSatir, r + 5, 0, "*" + ortala(adresYazisi(d->sonraki), 16) + "*");
            satiraYaz(ekran, toplamSatir, r + 6, 0, yildiz);

            if (d == secili) {
                for (int k = 0; k < 7; k++) {
                    satiraYaz(ekran, toplamSatir, r + k, 20, "<-");
                }
            }
        }
    }

    if (secili != NULL && secili->matris != NULL) {
        if (secili->matris->bosMu()) {
            satiraYaz(ekran, toplamSatir, matrisSatirBas, 27, "[Matris bos]");
        } else {
            for (int r = 0; r < mSatir; r++) {
                satiraYaz(ekran, toplamSatir, matrisSatirBas + r, 27, secili->matris->satirMetniGetir(r));
            }
        }
    }

    if (aktifMod == 0) {
        satiraYaz(ekran, toplamSatir, 0, menuSutun, "|---- Dugum gezilimi aktif --------|");
        satiraYaz(ekran, toplamSatir, 1, menuSutun, "|   w/s tuslari ile gezebilirsiniz |");
        satiraYaz(ekran, toplamSatir, 2, menuSutun, "|   q tusu ile one dugum ekle      |");
        satiraYaz(ekran, toplamSatir, 3, menuSutun, "|   e tusu ile arkaya dugum ekle   |");
        satiraYaz(ekran, toplamSatir, 4, menuSutun, "|   f tusu ile dugum secilebilir   |");
        satiraYaz(ekran, toplamSatir, 5, menuSutun, "|   x tusu ile kaydet ve cik       |");
        satiraYaz(ekran, toplamSatir, 6, menuSutun, "|----------------------------------|");
    } else if (aktifMod == 1) {
        satiraYaz(ekran, toplamSatir, 0, menuSutun, "|---- Dugum islemleri aktif -------|");
        satiraYaz(ekran, toplamSatir, 1, menuSutun, "|   1 tusu ile satir silin         |");
        satiraYaz(ekran, toplamSatir, 2, menuSutun, "|   2 tusu ile sutun silin         |");
        satiraYaz(ekran, toplamSatir, 3, menuSutun, "|   3 tusu ile elementer islemler  |");
        satiraYaz(ekran, toplamSatir, 4, menuSutun, "|   x tusu ile dugum gezimine gidin|");
        satiraYaz(ekran, toplamSatir, 5, menuSutun, "|----------------------------------|");
    } else {
        satiraYaz(ekran, toplamSatir, 0, menuSutun, "|---- Elementer islemler aktif ----|");
        satiraYaz(ekran, toplamSatir, 1, menuSutun, "|   1 tusu ile satir degistir      |");
        satiraYaz(ekran, toplamSatir, 2, menuSutun, "|   2 tusu ile sutun degistir      |");
        satiraYaz(ekran, toplamSatir, 3, menuSutun, "|   3 tusu ile satir-sutun degistir|");
        satiraYaz(ekran, toplamSatir, 4, menuSutun, "|   x tusu ile geri donun          |");
        satiraYaz(ekran, toplamSatir, 5, menuSutun, "|----------------------------------|");
    }

    satiraYaz(ekran, toplamSatir, altSatir, 0, ayirac);

    for (int i = 0; i < toplamSatir; i++) {
        cout << ekran[i] << "\n";
    }

    delete[] ekran;

    if (!liste.bosMu()) {
        int toplamSayfa = (liste.getBoyut() + 4) / 5;
        int mevcutSayfa = (pencereBaslangic / 5) + 1;
        cout << "Sayfa: " << mevcutSayfa << " / " << toplamSayfa << endl;
    }
}

void Ekran::yeniMatrisEkle(bool oneMi) {
    int satir = 0;
    int sutun = 0;

    cout << "Satir sayisi: ";
    if (!(cin >> satir)) {
        girisTemizle();
        bilgiMesaji = "Gecersiz giris.";
        return;
    }

    cout << "Sutun sayisi: ";
    if (!(cin >> sutun)) {
        girisTemizle();
        bilgiMesaji = "Gecersiz giris.";
        return;
    }

    if (satir != sutun) {
        bilgiMesaji = "Hata: Sadece kare matris eklenebilir!";
        return;
    }

    Matris* yeni = new Matris();
    if (yeni->rastgeleOlustur(satir, sutun)) {
        if (oneMi) {
            liste.oneEkle(yeni);
        } else {
            liste.sonaEkle(yeni);
        }
        liste.sirala();
        if (secili == NULL) {
            secili = liste.getBas();
        }
        bilgiMesaji = "Matris eklendi.";
    } else {
        delete yeni;
        bilgiMesaji = "Hata: Boyut 1 ile 10 arasi olmali!";
    }
}

void Ekran::gezintiIslemi(char secim) {
    if (secim == 'w' || secim == 'W') {
        if (secili != NULL && secili->onceki != NULL) {
            secili = secili->onceki;
        }
    } else if (secim == 's' || secim == 'S') {
        if (secili != NULL && secili->sonraki != NULL) {
            secili = secili->sonraki;
        }
    } else if (secim == 'q' || secim == 'Q') {
        yeniMatrisEkle(true);
    } else if (secim == 'e' || secim == 'E') {
        yeniMatrisEkle(false);
    } else if (secim == 'f' || secim == 'F') {
        if (secili != NULL) {
            aktifMod = 1;
        }
    } else if (secim == 'x' || secim == 'X') {
        if (liste.dosyayaKaydet(dosyaAdi)) {
            cout << "Veriler kaydedildi." << endl;
        } else {
            cout << "Kayit hatasi!" << endl;
        }
        calisiyor = false;
    } else {
        bilgiMesaji = "Gecersiz tus.";
    }
}

void Ekran::dugumIslemi(char secim) {
    if (secili == NULL || secili->matris == NULL) {
        aktifMod = 0;
        return;
    }

    if (secim == '1') {
        if (secili->matris->bosMu()) {
            bilgiMesaji = "Matris bos, x ile ana menuye donun.";
            return;
        }
        int indeks = -1;
        cout << "Silinecek satir (0-" << (secili->matris->getSatirSayisi() - 1) << "): ";
        if (!(cin >> indeks)) {
            girisTemizle();
            bilgiMesaji = "Gecersiz giris.";
            return;
        }
        if (secili->matris->satirSil(indeks)) {
            bilgiMesaji = secili->matris->bosMu() ? "Tum satirlar silindi, donuste dugum silinecek." : "Satir silindi.";
        } else {
            bilgiMesaji = "Gecersiz satir indeksi.";
        }
    } else if (secim == '2') {
        if (secili->matris->bosMu()) {
            bilgiMesaji = "Matris bos, x ile ana menuye donun.";
            return;
        }
        int indeks = -1;
        cout << "Silinecek sutun (0-" << (secili->matris->getSutunSayisi() - 1) << "): ";
        if (!(cin >> indeks)) {
            girisTemizle();
            bilgiMesaji = "Gecersiz giris.";
            return;
        }
        if (secili->matris->sutunSil(indeks)) {
            bilgiMesaji = secili->matris->bosMu() ? "Tum sutunlar silindi, donuste dugum silinecek." : "Sutun silindi.";
        } else {
            bilgiMesaji = "Gecersiz sutun indeksi.";
        }
    } else if (secim == '3') {
        if (secili->matris->bosMu()) {
            bilgiMesaji = "Matris bos, islem yapilamaz.";
        } else {
            aktifMod = 2;
        }
    } else if (secim == 'x' || secim == 'X') {
        aktifMod = 0;
        if (secili != NULL && secili->matris->bosMu()) {
            secili = liste.dugumSil(secili);
            bilgiMesaji = "Bosalan matrisin dugumu silindi.";
        } else {
            liste.sirala();
        }
    } else {
        bilgiMesaji = "Gecersiz tus.";
    }
}

void Ekran::elementerIslem(char secim) {
    if (secili == NULL || secili->matris == NULL) {
        aktifMod = 0;
        return;
    }

    if (secim == '1') {
        if (secili->matris->getSatirSayisi() < 2) {
            bilgiMesaji = "Yer degistirmek icin en az 2 satir olmali.";
            return;
        }
        int s1 = -1;
        int s2 = -1;
        int sinir = secili->matris->getSatirSayisi() - 1;

        cout << "1. satir indeksi (0-" << sinir << "): ";
        if (!(cin >> s1)) {
            girisTemizle();
            bilgiMesaji = "Gecersiz giris.";
            return;
        }
        cout << "2. satir indeksi (0-" << sinir << "): ";
        if (!(cin >> s2)) {
            girisTemizle();
            bilgiMesaji = "Gecersiz giris.";
            return;
        }
        if (secili->matris->satirDegistir(s1, s2)) {
            bilgiMesaji = "Satirlar yer degistirildi.";
        } else {
            bilgiMesaji = "Gecersiz satir indeksi.";
        }
    } else if (secim == '2') {
        if (secili->matris->getSutunSayisi() < 2) {
            bilgiMesaji = "Yer degistirmek icin en az 2 sutun olmali.";
            return;
        }
        int s1 = -1;
        int s2 = -1;
        int sinir = secili->matris->getSutunSayisi() - 1;

        cout << "1. sutun indeksi (0-" << sinir << "): ";
        if (!(cin >> s1)) {
            girisTemizle();
            bilgiMesaji = "Gecersiz giris.";
            return;
        }
        cout << "2. sutun indeksi (0-" << sinir << "): ";
        if (!(cin >> s2)) {
            girisTemizle();
            bilgiMesaji = "Gecersiz giris.";
            return;
        }
        if (secili->matris->sutunDegistir(s1, s2)) {
            bilgiMesaji = "Sutunlar yer degistirildi.";
        } else {
            bilgiMesaji = "Gecersiz sutun indeksi.";
        }
    } else if (secim == '3') {
        if (!secili->matris->kareMatrisMi()) {
            bilgiMesaji = "Hata: Matris kare degil, yer degistirilemez!";
            return;
        }
        int s1 = -1;
        int s2 = -1;
        int sinir = secili->matris->getSatirSayisi() - 1;

        cout << "Satir indeksi (0-" << sinir << "): ";
        if (!(cin >> s1)) {
            girisTemizle();
            bilgiMesaji = "Gecersiz giris.";
            return;
        }
        cout << "Sutun indeksi (0-" << sinir << "): ";
        if (!(cin >> s2)) {
            girisTemizle();
            bilgiMesaji = "Gecersiz giris.";
            return;
        }
        if (secili->matris->satirSutunDegistir(s1, s2)) {
            bilgiMesaji = "Satir ve sutun degistirildi.";
        } else {
            bilgiMesaji = "Gecersiz indeks.";
        }
    } else if (secim == 'x' || secim == 'X') {
        aktifMod = 1;
    } else {
        bilgiMesaji = "Gecersiz tus.";
    }
}

void Ekran::baslat() {
    if (!liste.dosyadanOku(dosyaAdi, bilgiMesaji)) {
        if (liste.dosyadanOku("bin/Veri.txt", bilgiMesaji)) {
            dosyaAdi = "bin/Veri.txt";
        } else if (liste.dosyadanOku("../Veri.txt", bilgiMesaji)) {
            dosyaAdi = "../Veri.txt";
        } else {
            bilgiMesaji = "Veri.txt bulunamadi.";
        }
    }

    secili = liste.getBas();
    calisiyor = true;

    while (calisiyor) {
        sayfaAyarla();
        system("cls");
        yazdir();

        if (bilgiMesaji != "") {
            cout << bilgiMesaji << endl;
            bilgiMesaji = "";
        }

        cout << "Secim: ";
        char secim = '\0';
        if (!(cin >> secim)) {
            liste.dosyayaKaydet(dosyaAdi);
            break;
        }

        if (aktifMod == 0) {
            gezintiIslemi(secim);
        } else if (aktifMod == 1) {
            dugumIslemi(secim);
        } else {
            elementerIslem(secim);
        }
    }
}
