/**
* @file MatrisListesi.cpp
* @description MatrisListesi sinifinin metotlari.
* @course Veri Yapıları
* @assignment 1. Odev
* @date 21.11.2026
* @author Ahmed Selim Yılmaz
*/

#include "MatrisListesi.hpp"
#include <fstream>
#include <sstream>

using namespace std;

MatrisListesi::MatrisListesi() {
    bas = NULL;
    son = NULL;
    boyut = 0;
}

MatrisListesi::~MatrisListesi() {
    temizle();
}

void MatrisListesi::temizle() {
    MatrisDugum* gezgin = bas;
    while (gezgin != NULL) {
        MatrisDugum* sil = gezgin;
        gezgin = gezgin->sonraki;
        delete sil;
    }
    bas = NULL;
    son = NULL;
    boyut = 0;
}

void MatrisListesi::oneEkle(Matris* yeniMatris) {
    if (yeniMatris == NULL) return;

    MatrisDugum* yeni = new MatrisDugum(yeniMatris);
    if (bas == NULL) {
        bas = yeni;
        son = yeni;
    } else {
        yeni->sonraki = bas;
        bas->onceki = yeni;
        bas = yeni;
    }
    boyut++;
}

void MatrisListesi::sonaEkle(Matris* yeniMatris) {
    if (yeniMatris == NULL) return;

    MatrisDugum* yeni = new MatrisDugum(yeniMatris);
    if (bas == NULL) {
        bas = yeni;
        son = yeni;
    } else {
        son->sonraki = yeni;
        yeni->onceki = son;
        son = yeni;
    }
    boyut++;
}

MatrisDugum* MatrisListesi::ortayiBul(MatrisDugum* baslangic) {
    MatrisDugum* yavas = baslangic;
    MatrisDugum* hizli = baslangic->sonraki;

    while (hizli != NULL && hizli->sonraki != NULL) {
        yavas = yavas->sonraki;
        hizli = hizli->sonraki->sonraki;
    }
    return yavas;
}

MatrisDugum* MatrisListesi::birlestir(MatrisDugum* sol, MatrisDugum* sag) {
    if (sol == NULL) return sag;
    if (sag == NULL) return sol;

    MatrisDugum* yeniBas = NULL;
    if (sol->matris->aritmetikOrtalama() <= sag->matris->aritmetikOrtalama()) {
        yeniBas = sol;
        sol = sol->sonraki;
    } else {
        yeniBas = sag;
        sag = sag->sonraki;
    }

    MatrisDugum* kuyruk = yeniBas;
    while (sol != NULL && sag != NULL) {
        if (sol->matris->aritmetikOrtalama() <= sag->matris->aritmetikOrtalama()) {
            kuyruk->sonraki = sol;
            sol = sol->sonraki;
        } else {
            kuyruk->sonraki = sag;
            sag = sag->sonraki;
        }
        kuyruk = kuyruk->sonraki;
    }

    if (sol != NULL) {
        kuyruk->sonraki = sol;
    } else {
        kuyruk->sonraki = sag;
    }

    return yeniBas;
}

MatrisDugum* MatrisListesi::mergeSort(MatrisDugum* baslangic) {
    if (baslangic == NULL || baslangic->sonraki == NULL) {
        return baslangic;
    }

    MatrisDugum* orta = ortayiBul(baslangic);
    MatrisDugum* sagBas = orta->sonraki;
    orta->sonraki = NULL;

    MatrisDugum* solSirali = mergeSort(baslangic);
    MatrisDugum* sagSirali = mergeSort(sagBas);

    return birlestir(solSirali, sagSirali);
}

void MatrisListesi::sirala() {
    if (bas == NULL || bas->sonraki == NULL) return;

    bas = mergeSort(bas);

    MatrisDugum* oncekiDugum = NULL;
    MatrisDugum* gezgin = bas;
    while (gezgin != NULL) {
        gezgin->onceki = oncekiDugum;
        oncekiDugum = gezgin;
        gezgin = gezgin->sonraki;
    }
    son = oncekiDugum;
}

MatrisDugum* MatrisListesi::dugumSil(MatrisDugum* hedef) {
    if (hedef == NULL || bas == NULL) return NULL;

    MatrisDugum* sonrakiSecili = (hedef->sonraki != NULL) ? hedef->sonraki : hedef->onceki;

    if (hedef->onceki != NULL) {
        hedef->onceki->sonraki = hedef->sonraki;
    } else {
        bas = hedef->sonraki;
    }

    if (hedef->sonraki != NULL) {
        hedef->sonraki->onceki = hedef->onceki;
    } else {
        son = hedef->onceki;
    }

    delete hedef;
    boyut--;
    return sonrakiSecili;
}

MatrisDugum* MatrisListesi::getBas() const {
    return bas;
}

int MatrisListesi::getBoyut() const {
    return boyut;
}

bool MatrisListesi::bosMu() const {
    return bas == NULL || boyut == 0;
}

int MatrisListesi::indeksBul(MatrisDugum* hedef) const {
    int i = 0;
    MatrisDugum* gezgin = bas;
    while (gezgin != NULL) {
        if (gezgin == hedef) return i;
        gezgin = gezgin->sonraki;
        i++;
    }
    return -1;
}

bool MatrisListesi::dosyadanOku(const string& dosyaAdi, string& hataMesaji) {
    ifstream dosya(dosyaAdi.c_str());
    if (!dosya.is_open()) {
        return false;
    }

    temizle();
    hataMesaji = "";

    int hataliAdet = 0;
    ostringstream hataliListe;

    string satirMetni;
    while (getline(dosya, satirMetni)) {
        istringstream ss(satirMetni);
        int satir = 0;
        int sutun = 0;

        if (!(ss >> satir >> sutun)) continue;
        if (satir <= 0 || sutun <= 0 || satir > 500 || sutun > 500) continue;

        if (satir != sutun) {
            if (hataliAdet < 5) {
                if (hataliAdet > 0) hataliListe << ", ";
                hataliListe << satir << "x" << sutun;
            } else if (hataliAdet == 5) {
                hataliListe << ", ...";
            }
            hataliAdet++;
            continue;
        }

        int adet = satir * sutun;
        int* veriler = new int[adet];
        bool tamam = true;

        for (int i = 0; i < adet; i++) {
            if (!(ss >> veriler[i])) {
                tamam = false;
                break;
            }
        }

        if (tamam) {
            Matris* m = new Matris();
            if (m->dizidenOlustur(satir, sutun, veriler)) {
                sonaEkle(m);
            } else {
                delete m;
            }
        }

        delete[] veriler;
    }

    dosya.close();
    sirala();

    if (hataliAdet > 0) {
        dosyayaKaydet(dosyaAdi);
        ostringstream msj;
        msj << "Hata: Kare matris olmayan " << hataliAdet
            << " matris (" << hataliListe.str() << ") silindi.";
        hataMesaji = msj.str();
    }

    return true;
}

bool MatrisListesi::dosyayaKaydet(const string& dosyaAdi) const {
    ofstream dosya(dosyaAdi.c_str());
    if (!dosya.is_open()) {
        return false;
    }

    MatrisDugum* gezgin = bas;
    while (gezgin != NULL) {
        if (gezgin->matris != NULL && !gezgin->matris->bosMu()) {
            gezgin->matris->dosyayaYaz(dosya);
        }
        gezgin = gezgin->sonraki;
    }

    dosya.close();
    return true;
}
