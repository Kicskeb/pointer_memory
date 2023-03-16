#include <iostream>
#include <list>
#include <random>
#include <algorithm>
#include <vector>
#include <numeric>
#include <cstdlib>
#include <ctime>
#include <limits>

#define DARABSZAM 5

void shuffle(std::vector<int>& cimek) {
    std::random_device r;
    std::default_random_engine e(r());
    for (size_t i = cimek.size()-1; i>0; i--) {
        std::uniform_int_distribution<size_t> uniform_dist(0, i);
        size_t rand = uniform_dist(e);
        std::swap(cimek[i], cimek[rand]);
    }
}

void kiir(const std::vector<int>& cimek, const std::vector<int*>& values, const std::vector<std::vector<int*>::iterator>& pointers) {
    int sorszam = 1;
    for (auto i : cimek) {
        if (i < 50) {
            //std::cout << i << "\t";
            if (sorszam < 10) std::cout << ' ';
            std::cout << sorszam++ << "\t: ";
            if (i < DARABSZAM) {
                std::cout << values[i] << std::endl;
            }
            if (i >= DARABSZAM) {
                std::cout << &*pointers[i - DARABSZAM] << std::endl;
            }
        }
    }
        std::cout << "Kerlek valasz egy lathato szamot!" << std::endl;

}

int beolvas() {
    while (true) {
        int n = 0;
        std::cin >> n;
        if (!std::cin.fail())
            return n;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Egy szamot irj be!" << std::endl;
    };
}

int main() {
    std::vector<int> cimek(DARABSZAM*2);
    std::iota(cimek.begin(), cimek.end(), 0);
    std::vector<int*> values;
    for (int i = 0; i<5; i++) {
        values.push_back(new int (i));
    }
    std::vector<std::vector<int*>::iterator> pointers(DARABSZAM);
    std::iota(pointers.begin(), pointers.end(), values.begin());
    shuffle(cimek);

    int elso, masodik;
    while (!cimek.empty()) {
        kiir(cimek, values, pointers);
        elso = beolvas();
        std::cout << "Kerlek add meg a masodik szamot!" << std::endl;
        masodik = beolvas();
        try {
            if (std::abs(cimek.at(elso - 1) - cimek.at(masodik - 1)) == 5) {
                int c1 = cimek[elso - 1];
                int c2 = cimek[masodik - 1];
                std::vector<int> new_cim;
                std::copy_if(cimek.begin(), cimek.end(), std::back_inserter(new_cim),
                             [c1, c2](int cim) { return cim != c1 && cim != c2; });
                cimek = new_cim;
            }
        } catch (std::out_of_range& e) {
            std::cout << "Adj meg egy megfelelo szamot!" << std::endl;
        }
    }

}

// Pointer memóriajáték. Legyen kiírva 10 cím, és számokkal lehessen megadni, hogy melyik 2-t fordítja fel.
// Ha a változó értéke ugyanaz, akkor azt később már nem kell megjeleníteni.