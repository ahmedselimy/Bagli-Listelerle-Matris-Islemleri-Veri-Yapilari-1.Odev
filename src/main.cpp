/**
* @file main.cpp
* @description Bagli liste tabanli matris yonetim uygulamasinin ana program dosyasi.
* @course Veri Yapıları
* @assignment 1. Odev
* @date 21.11.2026
* @author Ahmed Selim Yılmaz
*/

#include "Ekran.hpp"
#include <cstdlib>
#include <ctime>

int main() {
    srand((unsigned int)time(NULL));

    Ekran ekran;
    ekran.baslat();

    return 0;
}
