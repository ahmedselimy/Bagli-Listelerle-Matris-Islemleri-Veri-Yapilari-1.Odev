/**
* @file MatrisDugum.cpp
* @description Her bir matrisi bagli liste icinde tutan MatrisDugum sinifinin kaynak dosyasi.
* @course Veri Yapıları
* @assignment 1. Odev
* @date 21.11.2026
* @author Ahmed Selim Yılmaz
*/

#include "MatrisDugum.hpp"
#include <cstddef>

MatrisDugum::MatrisDugum(Matris* matris) {
    this->matris = matris;
    this->sonraki = NULL;
    this->onceki = NULL;
}

MatrisDugum::~MatrisDugum() {
    if (matris != NULL) {
        delete matris;
        matris = NULL;
    }
}
