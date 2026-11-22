/**
* @file Ekran.hpp
* @description Konsol ciktisi ve menu kontrolu icin Ekran sinifi.
* @course Veri Yapıları
* @assignment 1. Odev
* @date 21.11.2026
* @author Ahmed Selim Yılmaz
*/

#ifndef EKRAN_HPP
#define EKRAN_HPP

#include "MatrisListesi.hpp"
#include <string>

class Ekran {
private:
    MatrisListesi liste;
    MatrisDugum* secili;
    std::string dosyaAdi;
    std::string bilgiMesaji;
    int pencereBaslangic;
    int aktifMod;
    bool calisiyor;

    std::string adresYazisi(MatrisDugum* adres) const;
    std::string ortala(const std::string& metin, int genislik) const;
    void satiraYaz(std::string* ekran, int toplamSatir, int satir, int sutun, const std::string& metin) const;
    void girisTemizle();
    void sayfaAyarla();

    void yazdir() const;
    void gezintiIslemi(char secim);
    void dugumIslemi(char secim);
    void elementerIslem(char secim);
    void yeniMatrisEkle(bool oneMi);

public:
    Ekran();
    ~Ekran();

    void baslat();
};

#endif
