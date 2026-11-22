/**
* @file MatrisDugum.hpp
* @description Her bir matrisi bagli liste icinde heap uzerinde tutan dugum sinifinin baslik dosyasi.
* @course Veri Yapıları
* @assignment 1. Odev
* @date 21.11.2026
* @author Ahmed Selim Yılmaz
*/

#ifndef MATRISDUGUM_HPP
#define MATRISDUGUM_HPP

#include "Matris.hpp"

class MatrisDugum {
public:
    Matris* matris;
    MatrisDugum* sonraki;
    MatrisDugum* onceki;

    MatrisDugum(Matris* matris);
    ~MatrisDugum();
};

#endif
