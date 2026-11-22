/**
* @file HucreDugum.cpp
* @description Matrisin tek bir elemanini tutan HucreDugum sinifinin kaynak dosyasi.
* @course Veri Yapıları
* @assignment 1. Odev
* @date 21.11.2026
* @author Ahmed Selim Yılmaz
*/

#include "HucreDugum.hpp"
#include <cstddef>

HucreDugum::HucreDugum(int veri) {
    this->veri = veri;
    this->sag = NULL;
    this->asagi = NULL;
}

HucreDugum::~HucreDugum() {
}
