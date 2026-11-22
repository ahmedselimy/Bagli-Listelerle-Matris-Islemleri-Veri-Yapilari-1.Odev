/**
* @file Matris.hpp
* @description Elemanlari dugumlerde tutulan matris sinifi.
* @course Veri Yapıları
* @assignment 1. Odev
* @date 21.11.2026
* @author Ahmed Selim Yılmaz
*/

#ifndef MATRIS_HPP
#define MATRIS_HPP

#include "HucreDugum.hpp"
#include <fstream>
#include <string>

class Matris {
private:
    HucreDugum* bas;
    int satirSayisi;
    int sutunSayisi;
    double ortalama;

    void ortalamayiHesapla();
    HucreDugum* dugumGetir(int satir, int sutun) const;

public:
    Matris();
    ~Matris();

    void temizle();
    bool dizidenOlustur(int satir, int sutun, const int* veriler);
    bool rastgeleOlustur(int satir, int sutun);

    int getSatirSayisi() const;
    int getSutunSayisi() const;
    bool kareMatrisMi() const;
    bool bosMu() const;
    double aritmetikOrtalama() const;

    bool satirSil(int satirIndeks);
    bool sutunSil(int sutunIndeks);
    bool satirDegistir(int satir1, int satir2);
    bool sutunDegistir(int sutun1, int sutun2);
    bool satirSutunDegistir(int satirIndeks, int sutunIndeks);

    std::string satirMetniGetir(int satirIndeks) const;
    void dosyayaYaz(std::ofstream& dosya) const;
};

#endif
