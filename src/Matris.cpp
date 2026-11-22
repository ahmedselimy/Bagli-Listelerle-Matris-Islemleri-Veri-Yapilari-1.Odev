/**
* @file Matris.cpp
* @description Matris sinifinin metotlari.
* @course Veri Yapıları
* @assignment 1. Odev
* @date 21.11.2026
* @author Ahmed Selim Yılmaz
*/

#include "Matris.hpp"
#include <iomanip>
#include <sstream>
#include <cstdlib>

using namespace std;

Matris::Matris() {
    bas = NULL;
    satirSayisi = 0;
    sutunSayisi = 0;
    ortalama = 0.0;
}

Matris::~Matris() {
    temizle();
}

void Matris::temizle() {
    HucreDugum* satirBasi = bas;
    while (satirBasi != NULL) {
        HucreDugum* sonrakiSatir = satirBasi->asagi;
        HucreDugum* gezgin = satirBasi;
        while (gezgin != NULL) {
            HucreDugum* silinecek = gezgin;
            gezgin = gezgin->sag;
            delete silinecek;
        }
        satirBasi = sonrakiSatir;
    }
    bas = NULL;
    satirSayisi = 0;
    sutunSayisi = 0;
    ortalama = 0.0;
}

void Matris::ortalamayiHesapla() {
    if (bosMu()) {
        ortalama = 0.0;
        return;
    }

    int toplam = 0;
    int adet = 0;

    HucreDugum* satirBasi = bas;
    while (satirBasi != NULL) {
        HucreDugum* gezgin = satirBasi;
        while (gezgin != NULL) {
            toplam += gezgin->veri;
            adet++;
            gezgin = gezgin->sag;
        }
        satirBasi = satirBasi->asagi;
    }

    if (adet > 0) {
        ortalama = (double)toplam / adet;
    } else {
        ortalama = 0.0;
    }
}

HucreDugum* Matris::dugumGetir(int satir, int sutun) const {
    if (satir < 0 || satir >= satirSayisi || sutun < 0 || sutun >= sutunSayisi) {
        return NULL;
    }

    HucreDugum* gezgin = bas;
    for (int i = 0; i < satir && gezgin != NULL; i++) {
        gezgin = gezgin->asagi;
    }
    for (int j = 0; j < sutun && gezgin != NULL; j++) {
        gezgin = gezgin->sag;
    }
    return gezgin;
}

bool Matris::dizidenOlustur(int satir, int sutun, const int* veriler) {
    temizle();

    if (satir <= 0 || sutun <= 0 || veriler == NULL) {
        return false;
    }

    HucreDugum* oncekiSatirBasi = NULL;
    int k = 0;

    for (int r = 0; r < satir; r++) {
        HucreDugum* suankiSatirBasi = NULL;
        HucreDugum* sol = NULL;
        HucreDugum* ust = oncekiSatirBasi;

        for (int c = 0; c < sutun; c++) {
            HucreDugum* yeni = new HucreDugum(veriler[k]);
            k++;

            if (c == 0) {
                suankiSatirBasi = yeni;
            } else {
                sol->sag = yeni;
            }

            if (ust != NULL) {
                ust->asagi = yeni;
                ust = ust->sag;
            }

            sol = yeni;
        }

        if (r == 0) {
            bas = suankiSatirBasi;
        }
        oncekiSatirBasi = suankiSatirBasi;
    }

    satirSayisi = satir;
    sutunSayisi = sutun;
    ortalamayiHesapla();
    return true;
}

bool Matris::rastgeleOlustur(int satir, int sutun) {
    if (satir <= 0 || sutun <= 0 || satir * sutun > 100) {
        return false;
    }

    int sayilar[100];
    for (int i = 0; i < 100; i++) {
        sayilar[i] = i;
    }

    for (int i = 99; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = sayilar[i];
        sayilar[i] = sayilar[j];
        sayilar[j] = tmp;
    }

    return dizidenOlustur(satir, sutun, sayilar);
}

int Matris::getSatirSayisi() const {
    return satirSayisi;
}

int Matris::getSutunSayisi() const {
    return sutunSayisi;
}

bool Matris::kareMatrisMi() const {
    return satirSayisi > 0 && satirSayisi == sutunSayisi;
}

bool Matris::bosMu() const {
    return bas == NULL || satirSayisi <= 0 || sutunSayisi <= 0;
}

double Matris::aritmetikOrtalama() const {
    return ortalama;
}

bool Matris::satirSil(int satirIndeks) {
    if (bosMu() || satirIndeks < 0 || satirIndeks >= satirSayisi) {
        return false;
    }

    if (satirIndeks == 0) {
        HucreDugum* sil = bas;
        bas = bas->asagi;
        while (sil != NULL) {
            HucreDugum* sonraki = sil->sag;
            delete sil;
            sil = sonraki;
        }
    } else {
        HucreDugum* ust = dugumGetir(satirIndeks - 1, 0);
        HucreDugum* sil = ust->asagi;
        while (ust != NULL && sil != NULL) {
            ust->asagi = sil->asagi;
            HucreDugum* sonrakiSil = sil->sag;
            delete sil;
            sil = sonrakiSil;
            ust = ust->sag;
        }
    }

    satirSayisi--;
    if (satirSayisi == 0) {
        bas = NULL;
        sutunSayisi = 0;
    }

    ortalamayiHesapla();
    return true;
}

bool Matris::sutunSil(int sutunIndeks) {
    if (bosMu() || sutunIndeks < 0 || sutunIndeks >= sutunSayisi) {
        return false;
    }

    if (sutunIndeks == 0) {
        HucreDugum* sil = bas;
        bas = bas->sag;
        while (sil != NULL) {
            HucreDugum* sonraki = sil->asagi;
            delete sil;
            sil = sonraki;
        }
    } else {
        HucreDugum* sol = dugumGetir(0, sutunIndeks - 1);
        HucreDugum* sil = sol->sag;
        while (sol != NULL && sil != NULL) {
            sol->sag = sil->sag;
            HucreDugum* sonrakiSil = sil->asagi;
            delete sil;
            sil = sonrakiSil;
            sol = sol->asagi;
        }
    }

    sutunSayisi--;
    if (sutunSayisi == 0) {
        bas = NULL;
        satirSayisi = 0;
    }

    ortalamayiHesapla();
    return true;
}

bool Matris::satirDegistir(int satir1, int satir2) {
    if (bosMu() || satir1 < 0 || satir1 >= satirSayisi || satir2 < 0 || satir2 >= satirSayisi) {
        return false;
    }
    if (satir1 == satir2) {
        return true;
    }

    HucreDugum* p1 = dugumGetir(satir1, 0);
    HucreDugum* p2 = dugumGetir(satir2, 0);

    while (p1 != NULL && p2 != NULL) {
        int tmp = p1->veri;
        p1->veri = p2->veri;
        p2->veri = tmp;
        p1 = p1->sag;
        p2 = p2->sag;
    }
    return true;
}

bool Matris::sutunDegistir(int sutun1, int sutun2) {
    if (bosMu() || sutun1 < 0 || sutun1 >= sutunSayisi || sutun2 < 0 || sutun2 >= sutunSayisi) {
        return false;
    }
    if (sutun1 == sutun2) {
        return true;
    }

    HucreDugum* p1 = dugumGetir(0, sutun1);
    HucreDugum* p2 = dugumGetir(0, sutun2);

    while (p1 != NULL && p2 != NULL) {
        int tmp = p1->veri;
        p1->veri = p2->veri;
        p2->veri = tmp;
        p1 = p1->asagi;
        p2 = p2->asagi;
    }
    return true;
}

bool Matris::satirSutunDegistir(int satirIndeks, int sutunIndeks) {
    if (bosMu() || !kareMatrisMi()) {
        return false;
    }
    if (satirIndeks < 0 || satirIndeks >= satirSayisi || sutunIndeks < 0 || sutunIndeks >= sutunSayisi) {
        return false;
    }

    HucreDugum* s1 = dugumGetir(satirIndeks, 0);
    HucreDugum* s2 = dugumGetir(0, sutunIndeks);

    while (s1 != NULL && s2 != NULL) {
        if (s1 != s2) {
            int tmp = s1->veri;
            s1->veri = s2->veri;
            s2->veri = tmp;
        }
        s1 = s1->sag;
        s2 = s2->asagi;
    }

    return true;
}

string Matris::satirMetniGetir(int satirIndeks) const {
    if (bosMu() || satirIndeks < 0 || satirIndeks >= satirSayisi) {
        return "";
    }

    HucreDugum* gezgin = dugumGetir(satirIndeks, 0);
    ostringstream ss;
    while (gezgin != NULL) {
        ss << left << setw(3) << gezgin->veri;
        gezgin = gezgin->sag;
    }
    return ss.str();
}

void Matris::dosyayaYaz(ofstream& dosya) const {
    if (bosMu()) {
        return;
    }

    dosya << satirSayisi << " " << sutunSayisi;

    HucreDugum* satirBasi = bas;
    while (satirBasi != NULL) {
        HucreDugum* gezgin = satirBasi;
        while (gezgin != NULL) {
            dosya << " " << gezgin->veri;
            gezgin = gezgin->sag;
        }
        satirBasi = satirBasi->asagi;
    }
    dosya << "\n";
}
