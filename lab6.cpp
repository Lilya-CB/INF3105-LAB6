/*
  INF3105 - Structures de données et algorithmes
  Lab6 - Tâche 3 (basée sur Tâche 3 du Lab5).
  g++ -o lab6 lab6.cpp
*/

#include <iostream>
//#include "file.h"  ou  "liste.h"
#include "arbreavl.h"

class PassageCarte{
  public:

  private:
    int temps;
    int numero_carte;

  friend std::istream& operator >> (std::istream&, PassageCarte&);
  friend std::ostream& operator << (std::ostream&, const PassageCarte&);
};

std::istream& operator >> (std::istream& is, PassageCarte& pc)
{
    is >> pc.temps >> pc.numero_carte;
    return is;
}
std::ostream& operator << (std::ostream& os, const PassageCarte& pc)
{
    os << pc.temps << "\t" << pc.numero_carte;
    return os;
}



int main(int argc, const char** argv)
{
    // À compléter.
    while(std::cin){
        PassageCarte pc;
        std::cin >> pc;
        if(!std::cin) break;

        if(true)
            std::cout << "Passage invalide : " << pc << "!" << std::endl;
    }
}


