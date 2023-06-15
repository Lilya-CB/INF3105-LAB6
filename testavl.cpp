/* Tests pour la classe ArbreAVL.
 * Lab6 -- Arbres AVL
 * UQAM / Département d'informatique
 * INF3105 - Structures de données et algorithmes
 * http://ericbeaudry.uqam.ca/INF3105/lab6/
 *
 * Pour compiler: g++ -o testavl testavl.cpp
 */
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "arbreavl.h"

bool test0(){
    std::cout << "Test #0 : ArbreAVL / Affichage" << std::endl;
    ArbreAVL<int> arbre;
    arbre.inserer(4);
    arbre.inserer(2);
    arbre.inserer(6);
    arbre.inserer(1);
    arbre.inserer(3);
    arbre.inserer(5);
    arbre.inserer(7);
    arbre.afficher();
    
    if(arbre.taille()!=7){
        std::cout << "Erreur: L'arbre résultant devrait contenir 7 éléments." << std::endl;
        return false;
    }
    
    std::cout << "Le test #0 demande une vérificaiton manuelle. Ci-haut, arbre.afficher() devrait avoir affiché:\n"
     << "\t\t\t4\n"
     << "\t2\t\t\t\t6\n"
     << "1\t\t3\t\t5\t\t7\n"
     << std::endl;
    
    std::cout << "Si vous obtenez le bon résultat, faites `return true;` à la fin de la fonction test0().\n"
       << "Vous pouvez également mettre en commentaire l'appel à test0() dans la fonction main()." << std::endl;    
    return false;
}

bool test1(){
    std::cout << "Test #1 : ArbreAVL / Insertions + Tests d'appartenance (contient)" << std::endl;
    int nberreurs=0;
    ArbreAVL<int> arbre;
    if(arbre.contient(5)){
        nberreurs++;
        std::cout << " >> Erreur #1 : 5 ne devrait pas être dans l'arbre!" << std::endl;
    }
    int nombres[]{5, 1, 7, 2, 6};
    for(int n : nombres)
        arbre.inserer(n);
    if(arbre.taille()!=5){
        nberreurs++;
        std::cout << " >> Erreur #2 : l'arbre doit contenir 5 éléments!" << std::endl;    
    }
    for(int n : nombres)
        if(!arbre.contient(n)){
            nberreurs++;
            std::cout << " >> Erreur #3 : " << n << " devrait être dans l'arbre!" << std::endl;
        }
    // Tests de réinsertions
    for(int n : nombres){
        arbre.inserer(n);
        if(arbre.taille()!=5){
            nberreurs++;
            std::cout << " >> Erreur #4 : l'arbre doit contenir 5 éléments!" << std::endl;    
        }
    }
    if(nberreurs==0)
        std::cout << " ==> OK" << std::endl;
    return nberreurs==0;    
}

bool test2(){
    std::cout << "Test #2 : ArbreAVL / Insertions + Tests hauteur" << std::endl;
    ArbreAVL<int> arbre;
    int nberreurs=0;
    if(arbre.hauteur()!=0){
        nberreurs++;
        std::cout << " >> Erreur #1 : l'arbre devrait avoir une hauteur = 0 !" << std::endl;
    }
    arbre.inserer(2);
    if(arbre.hauteur()!=1){
        nberreurs++;
        std::cout << " >> Erreur #2 : l'arbre devrait avoir une hauteur = 1 !" << std::endl;
    }
    arbre.inserer(1);
    arbre.inserer(2); // déjà là !
    arbre.inserer(3);
    if(arbre.hauteur()!=2){
        nberreurs++;
        std::cout << " >> Erreur #3 : l'arbre devrait avoir une hauteur = 1 !" << std::endl;
    }
    
    ArbreAVL<int> arbre2;
    arbre2.inserer(1);
    arbre2.inserer(2);
    if(arbre.hauteur()!=2){
        nberreurs++;
        std::cout << " >> Erreur #4 : l'arbre devrait avoir une hauteur = 2 !" << std::endl;
    }
    arbre2.inserer(3); // devrait provoquer rotation
    if(arbre.hauteur()!=2){
        nberreurs++;
        std::cout << " >> Erreur #5 : l'arbre devrait avoir une hauteur = 2 !" << std::endl;
    }

    ArbreAVL<int> arbre3;
    arbre2.inserer(3);
    arbre2.inserer(1);
    if(arbre.hauteur()!=2){
        nberreurs++;
        std::cout << " >> Erreur #6 : l'arbre devrait avoir une hauteur = 2 !" << std::endl;
    }
    arbre2.inserer(2); // devrait provoquer rotation
    if(arbre.hauteur()!=2){
        nberreurs++;
        std::cout << " >> Erreur #7 : l'arbre devrait avoir une hauteur = 2 !" << std::endl;
    }
    
    if(nberreurs==0)
        std::cout << " ==> OK" << std::endl;
    return nberreurs==0;    
}

bool test3(){
    std::cout << "Test #3 : ArbreAVL / Insertions 0, 2, 4, 6, 8 ... 1, 3, 5, 7, 9" << std::endl;
    int nberreurs=0;
    ArbreAVL<int> arbre;
    for(int i=0;i<10;i+=2)
       arbre.inserer(i);
    for(int i=0;i<10;i+=2)
        if(!arbre.contient(i)){
            std::cout << i << " >> Erreur #1 i=" << i << std::endl;
            nberreurs++;
        }
    for(int i=1;i<10;i+=2)
        if(arbre.contient(i)){
            std::cout << i << " >> Erreur #2 i=" << i << std::endl;
            nberreurs++;
        }
    for(int i=1;i<10;i+=2)
       arbre.inserer(i);

    for(int i=0;i<10;i++)
        if(!arbre.contient(i)){
            std::cout << i << " >> Erreur #3 i=" << i << std::endl;
            nberreurs++;
        }
    if(nberreurs==0)
        std::cout << " ==> OK" << std::endl;
    return nberreurs==0;
}

int nbMinAVL(int h){
    if(h==0) return 0;
    if(h==1) return 1;
    return 1 + nbMinAVL(h-2) + nbMinAVL(h-1);
}

bool test4(){
    int nberreurs=0;
    std::cout << "Test #4 : ArbreAVL / Vérificateur hauteur sur gros arbres" << std::endl;
    ArbreAVL<int> arbre;
    for(int n=1;n<=1000;n++){
        arbre.inserer(n);
        int h = arbre.hauteur();
        int nbmin = nbMinAVL(h);
        //std::cout << "h=" << h << " i=" << i << " nbmin=" << nbmin << std::endl;
        if(n<nbmin){
             std::cout << "Erreur : la hauteur de l'arbre est trop élevé pour le nombre d'éléments insérer !"
                       << std::endl
                       << "\th=" << h << "\tn=" << n << " nbmin=" << nbmin << std::endl;
             nberreurs++;
        }
    }
    
    ArbreAVL<int> arbre2;
    for(int n=1;n<=1000;n++){
        arbre2.inserer(-n);
        int h = arbre2.hauteur();
        int nbmin = nbMinAVL(h);
        //std::cout << "h=" << h << " i=" << i << " nbmin=" << nbmin << std::endl;
        if(n<nbmin){
            std::cout << "Erreur : la hauteur de l'arbre est trop élevé pour le nombre d'éléments"
                      << std::endl
                      << "\th=" << h << "\tn=" << n << " nbmin=" << nbmin << std::endl;
            nberreurs++;
        }
    }
    if(nberreurs==0)
        std::cout << " ==> OK" << std::endl;
    return nberreurs==0;
}

bool test5()
{
    int nberreurs=0;
    std::cout << "Test #5 : ArbreAVL / vérification hauteur avec insertions aléatoires." << std::endl;
 
    // Initialisation du générateur de nombres aléatoires   
    time_t t;
    srand((unsigned) time(&t));
    
    for(int test=0;nberreurs<0 && test<500;test++){
        ArbreAVL<int> arbre;
        for(int i=0,n=0;i<500;i++){
          int nombre = rand() % 2000;
          if(arbre.contient(nombre)) continue;
          arbre.inserer(nombre);
          n++;
          int h = arbre.hauteur();
          int nbmin = nbMinAVL(h);
          //std::cout << "h=" << h << " i=" << i << " nbmin=" << nbmin << std::endl;
          if(n<nbmin){
              std::cout << "Erreur : la hauteur de l'arbre est trop élevé pour le nombre d'éléments." << std::endl
                        << "\th=" << h << "\tn=" << n << " nbmin=" << nbmin << std::endl
                        << "Le problème vient probablement d'un erreur dans le calcul des indices d'équilibre." << nbmin << std::endl
                        ;
              nberreurs++;
          }
        }
    }
    if(nberreurs==0)
        std::cout << " ==> OK" << std::endl;
    return nberreurs==0;
}


bool test6()
{
    int nberreurs=0;
    std::cout << "Test #6 : ArbreAVL / vider" << std::endl;
    ArbreAVL<int> arbre;
    arbre.vider();
    if(!arbre.vide()){
        std::cout << " >> Erreur #1" << std::endl;
        nberreurs++;
    }
    arbre.inserer(2);
    if(arbre.vide()){
        std::cout << " >> Erreur #2" << std::endl;
        nberreurs++;
    }
    arbre.vider();
    if(!arbre.vide()){
        std::cout << " >> Erreur #3" << std::endl;
        nberreurs++;
    }
    arbre.inserer(2);
    arbre.inserer(3);
    arbre.inserer(1);
    if(arbre.vide()){
        std::cout << " >> Erreur #4" << std::endl;
        nberreurs++;
    }
    arbre.vider();
    if(!arbre.vide()){
        std::cout << " >> Erreur #3" << std::endl;
        nberreurs++;
    }
    if(nberreurs==0)
        std::cout << " ==> OK" << std::endl;
    return nberreurs==0;
}

bool test7()
{
    int nberreurs=0;
    std::cout << "Test #7 : ArbreAVL / enlèvement" << std::endl;
    ArbreAVL<int> arbre1;
    arbre1.inserer(1);
    arbre1.enlever(2);
    if(!arbre1.contient(1) || arbre1.contient(2) || arbre1.taille()!=1){
            std::cout<< " >> Erreur #1" << std::endl;
            nberreurs++;
    }
    arbre1.enlever(1);
    if(arbre1.contient(1) || arbre1.contient(2) || arbre1.taille()!=0){
            std::cout<< " >> Erreur #2" << std::endl;
            nberreurs++;
    }

    arbre1.inserer(2);
    arbre1.inserer(1);
    arbre1.inserer(3);
    arbre1.inserer(4);
    arbre1.enlever(3);
    if(arbre1.contient(3) || !arbre1.contient(4) || arbre1.taille()!=3){
            std::cout<< " >> Erreur #3" << std::endl;
            nberreurs++;
    }
    arbre1.enlever(1);
    if(arbre1.contient(1) || !arbre1.contient(2) || arbre1.taille()!=2){
            std::cout<< " >> Erreur #4" << std::endl;
            nberreurs++;
    }
    arbre1.vider();
    arbre1.inserer(2);
    arbre1.inserer(1);
    arbre1.inserer(3);
    arbre1.enlever(1);
    if(arbre1.contient(1) || !arbre1.contient(2) || !arbre1.contient(3)|| arbre1.taille()!=2){
            std::cout<< " >> Erreur #5" << std::endl;
            nberreurs++;
    }
    
    
    ArbreAVL<int> arbre;
    for(int i=0;i<20;i+=2)
        arbre.inserer(i);
    for(int i=1;i<20;i+=2)
        arbre.inserer(i);
    for(int i=0;i<20;i++)
        arbre.enlever(i);
    for(int i=0;i<20;i++)
        if(arbre.contient(i)){
            std::cout<< " >> Erreur #6  i=" << i << std::endl;
            nberreurs++;
        }
    if(nberreurs==0)
        std::cout << " ==> OK" << std::endl;
    return nberreurs==0;
}

bool test8()
{
    int nberreurs=0;
    std::cout << "Test #8 : ArbreAVL / opérateur =" << std::endl;
    ArbreAVL<int> arbre1;
    for(int i=0;i<20;i++)
        arbre1.inserer(i);
    ArbreAVL<int> arbre2;
    arbre2 = arbre1;
    for(int i=0;i<20;i++)
        if(!arbre2.contient(i)){
            std::cout << " >> Erreur #1  i=" << i  << std::endl;
            nberreurs++;
        }
    ArbreAVL<int> arbre3;
    arbre2 = arbre3;
    for(int i=0;i<20;i++)
        if(arbre2.contient(i)){
            std::cout << " >> Erreur #2  i=" << i << std::endl;
            nberreurs++;
        }
    arbre1 = arbre1; // devrait être sans effet
    if(arbre1.vide()){
        std::cout << " >> Erreur #4" << std::endl;
        nberreurs++;
    }
    for(int i=0;i<20;i++)
        if(!arbre1.contient(i)){
            std::cout << " >> Erreur #5  i=" << i << std::endl;
            nberreurs++;
        }
    if(nberreurs==0)
        std::cout << " ==> OK" << std::endl;
    return nberreurs==0;
}

bool test9()
{
    int nberreurs=0;
    std::cout << "Test #9 : ArbreAVL / constructeur par copie" << std::endl;
    ArbreAVL<int> arbre1;
    for(int i=0;i<20;i++)
        arbre1.inserer(i);
    ArbreAVL<int> arbre2(arbre1);
    for(int i=0;i<20;i++)
        if(!arbre2.contient(i)){
            std::cout << i << " >> Erreur !arbre2.contient(i)" << std::endl;
            nberreurs++;
        }
    ArbreAVL<int> arbre3(arbre2);
    for(int i=0;i<20;i++)
        if(!arbre3.contient(i)){
            std::cout << i << "+ >> Erreur !arbre3.contient(i)" << std::endl;
            nberreurs++;
        }
    arbre3.vider();
    for(int i=0;i<20;i++)
        if(arbre3.contient(i)){
            std::cout << i << "+ >> Erreur arbre3.contient(i)" << std::endl;
            nberreurs++;
        }    
    for(int i=0;i<20;i++)
        if(!arbre2.contient(i)){
            std::cout << i << "+ >> Erreur !arbre2.contient(i)" << std::endl;
            nberreurs++;
        }
    if(nberreurs==0)
        std::cout << " ==> OK" << std::endl;
    return nberreurs==0;
}


/*
bool test10()
{
    std::cout << "Test #10 : ArbreAVL / Itérateurs" << std::endl;
    int nberreurs=0;
    ArbreAVL<int> arbre1;
    for(int i=0;i<20;i++)
        arbre1.inserer(i);

    ArbreAVL<int>::Iterateur iter = arbre1.debut();

    for(int i=0;i<20;i++)
    {
        if(iter){
            int v1 = *iter;
            int v2 = arbre1[iter];
            if(v1!=v2 || v1!= i){
                std::cout << i << " >> Erreur" << std::endl;
                nberreurs++;
            }
            ++iter;
        }else{
            std::cout << i << "+ >> Erreur" << std::endl;
            nberreurs++;
        }
     }

    if(nberreurs==0)
        std::cout << " ==> OK" << std::endl;
    return nberreurs==0;
}


bool test11()
{
    int nberreurs=0;
    std::cout << "Test #11 : ArbreAVL / Recherche égal + précédent/suivant" << std::endl;
    ArbreAVL<int> arbre;
    for(int i=0;i<10;i+=2)
        arbre.inserer(i);
  
    for(int i=-2;i<12;i++)
    {
        ArbreAVL<int>::Iterateur iter = arbre.rechercherEgalOuSuivant(i);   
    
        if(i>=9){
            if(iter){
                std::cout << "Erreur rechercherEgalOuSuivant(" << i << ") : " << *iter << std::endl;
                nberreurs++;
            }
        }
        else if(!iter){
            std::cout << "Erreur rechercherEgalOuSuivant(" << i << ") = fin!" << std::endl;
            nberreurs++;
        }
        else{
            int bi = arbre[iter];
            int ebi = i+1;
            ebi -= ebi%2;
            if(ebi<0) ebi = 0;
            if(ebi != bi){
                std::cout << "Erreur rechercherEgalOuSuivant(" << i << ")=" << bi << " != " << ebi << std::endl;
                nberreurs++;
            }
        }
    
    
        iter = arbre.rechercherEgalOuPrecedent(i);
        if(i<0){
            if(iter){
                std::cout << "Erreur rechercherEgalOuPrecedent(" << i << ") : " << *iter << std::endl;
                nberreurs++;
            }
        }
        else if(!iter){
            std::cout << "Erreur rechercherEgalOuPrecedent(" << i << ") = fin!" << std::endl;
            nberreurs++;
        }else{
            int bs = arbre[iter];
            int ebs = i;
            ebs -= ebs%2;
            if(ebs>8) ebs = 8;
       
            if(ebs != bs){
                std::cout << "Erreur rechercherEgalOuPrecedent(" << i << ")=" << bs << " != " << ebs << std::endl;
                nberreurs++;
            }
        }
    }
    if(nberreurs==0)
        std::cout << " ==> OK" << std::endl;
    return nberreurs==0;
}

bool test12()
{
    int nberreurs=0;
    std::cout << "Test #12: ArbreAVL / Itérateurs sur recherche égal + précédent/suivant" << std::endl;
    ArbreAVL<int> arbre;
    for(int i=0;i<10;i++)
        arbre.inserer(i);
  
    for(int cible=0;cible<10;cible++){
        ArbreAVL<int>::Iterateur iter = arbre.rechercher(cible);
        for(int i=cible;i<10;i++)
            if(*iter++ != i){
                std::cout << " Erreur itérateur rechercher : " << i << std::endl;
                nberreurs++;
            }
        if(iter){
            std::cout << " Erreur fin itérateur : " << std::endl;
            nberreurs++;
        }
         
        iter = arbre.rechercherEgalOuPrecedent(cible);
        for(int i=cible;i<10;i++)
            if(*iter++ != i){
                std::cout << " Erreur itérateur rechercherEgalOuPrecedent : " << i << std::endl;
                nberreurs++;
            }
        if(iter){
             std::cout << " Erreur fin rechercherEgalOuPrecedent : " << std::endl;
             nberreurs++;
        }
         
        iter = arbre.rechercherEgalOuSuivant(cible);
        for(int i=cible;i<10;i++)
            if(*iter++ != i){
                std::cout << " Erreur itérateur rechercherEgalOuSuivant : " << i << std::endl;
                nberreurs++;
            }
        if(iter){
            std::cout << " Erreur fin rechercherEgalOuSuivant : " << std::endl;
            nberreurs++;
        }
    }
  
    if(nberreurs==0)
        std::cout << " ==> OK" << std::endl;
    return nberreurs==0;
}
*/
int main(int argc, const char** argv)
{

    bool testsreussis =
        true // Cette ligne «true» permet de commenter la ligne suivante sans elever «&&» de la 2e ligne suivante!
        && test0()
        && test1()
        && test2()
        && test3()
        && test4()
        && test5()
        && test6()
        && test7()
        && test8()
//        && test9()  // Exercice optionel

//        && test10() // Lab 7
//        && test11()
//        && test12()
        ;

    std::cout << std::endl << std::endl
         << "**** Sommaire ****" << std::endl;

    if(testsreussis){
        std::cout << "=> BRAVO, tous les tests ont été réussis!" << std::endl
                  << "=> Attention, ces tests ne sont pas exhaustifs." << std::endl
                  << "=> Réussir tous ces tests ne garanti l'absence de failles." << std::endl
                  << "=> Soyez vigilants, il pourrait rester des bogues." << std::endl;
    }else{
        std::cout << "=> DÉSOLÉ, au moins un test a échoué." << std::endl;
        std::cout << "=> Ne lâchez pas!" << std::endl;
    }   
    return testsreussis ? 0 : 1;

}

