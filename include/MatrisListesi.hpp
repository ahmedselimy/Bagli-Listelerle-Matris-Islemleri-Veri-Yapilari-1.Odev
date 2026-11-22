/**
* @file MatrisListesi.hpp
* @description Matris dugumlerini tutan bagli liste sinifi.
* @course Veri Yapıları
* @assignment 1. Odev
* @date 21.11.2026
* @author Ahmed Selim Yılmaz
*/

#ifndef MATRISLISTESI_HPP
#define MATRISLISTESI_HPP

#include "MatrisDugum.hpp"
#include <string>

class MatrisListesi {
private:
    MatrisDugum* bas;
    MatrisDugum* son;
    int boyut;

    MatrisDugum* ortayiBul(MatrisDugum* baslangic);
    MatrisDugum* birlestir(MatrisDugum* sol, MatrisDugum* sag);
    MatrisDugum* mergeSort(MatrisDugum* baslangic);

public:
    MatrisListesi();
    ~MatrisListesi();

    void temizle();
    void oneEkle(Matris* yeniMatris);
    void sonaEkle(Matris* yeniMatris);
    void sirala();
    MatrisDugum* dugumSil(MatrisDugum* hedef);

    MatrisDugum* getBas() const;
    int getBoyut() const;
    bool bosMu() const;
    int indeksBul(MatrisDugum* hedef) const;

    bool dosyadanOku(const std::string& dosyaAdi, std::string& hataMesaji);
    bool dosyayaKaydet(const std::string& dosyaAdi) const;
};

#endif
