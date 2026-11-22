/**
* @file HucreDugum.hpp
* @description Matrisin tek bir elemanini heap uzerinde tutan dugum sinifinin baslik dosyasi.
* @course Veri Yapıları
* @assignment 1. Odev
* @date 21.11.2026
* @author Ahmed Selim Yılmaz
*/

#ifndef HUCREDUGUM_HPP
#define HUCREDUGUM_HPP

class HucreDugum {
public:
    int veri;
    HucreDugum* sag;
    HucreDugum* asagi;

    HucreDugum(int veri);
    ~HucreDugum();
};

#endif
