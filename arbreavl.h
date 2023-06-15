/* Squelette pour classe générique ArbreAVL<T>.
 * Lab6 -- Arbres AVL
 * UQAM / Département d'informatique
 * INF3105 - Structures de données et algorithmes
 * http://ericbeaudry.uqam.ca/INF3105/lab6/
 */
#if !defined(_ARBREAVL___H_)
#define _ARBREAVL___H_
#include <cassert>

template <class T>
class ArbreAVL {
  public:
    ArbreAVL();
    ~ArbreAVL();

    // Lab6 / Tâche 2 - Fonctions de base
    bool vide() const;
    bool contient(const T&) const;
    void inserer(const T&);
    void vider();

    // Lab6 / Tâche 3
    void enlever(const T&);

    // Lab6 / Tâche 4
    ArbreAVL& operator = (const ArbreAVL&);
    ArbreAVL(const ArbreAVL&);

    // Fonctions pour certains tests ou diagnostique
    int taille() const;
    int hauteur() const;
    void afficher() const;

  private:
    struct Noeud{
        Noeud(const T&);
        T contenu;
        int equilibre;
        Noeud *gauche,
              *droite;
    };
    Noeud* racine;

    // Fonctions internes
    bool inserer(Noeud*&, const T&);
    void rotationGaucheDroite(Noeud*&);
    void rotationDroiteGauche(Noeud*&);
    void vider(Noeud*&);

    // Lab6 / Tâche 4
    void copier(const Noeud*, Noeud*&) const;

    // Fonctions internes pour certains tests
    int hauteur(const Noeud*) const;
    int compter(const Noeud*) const;
    void preparerafficher(const Noeud* n, int profondeur, int& rang, T* elements, int* profondeurs) const;
};


//-----------------------------------------------------------------------------

template <class T>
ArbreAVL<T>::Noeud::Noeud(const T& c)
 : contenu(c), equilibre(0), gauche(nullptr), droite(nullptr)
{
}

template <class T>
ArbreAVL<T>::ArbreAVL() 
 : racine(nullptr)
{
}

template <class T>
ArbreAVL<T>::ArbreAVL(const ArbreAVL<T>& autre)
 : racine(nullptr)
{
    copier(autre.racine, racine);
}

template <class T>
ArbreAVL<T>::~ArbreAVL()
{
    vider(racine);
}

template <class T>
bool ArbreAVL<T>::contient(const T& element) const
{
    return rechercher(racine, element) != nullptr;
}

template <class T>
const T* ArbreAVL<T>::rechercher(Noeud* noeud, const T& element) const{
    if (noeud == nullptr){
        return nullptr;
    } else if (element == noeud->contenu){
        return &(noeud->contenu);
    } else if (element < noeud->contenu){
        return rechercher(noeud->gauche, element);
    } else {
        return rechercher(noeud->droite, element);
    }
}

template <class T>
void ArbreAVL<T>::inserer(const T& element)
{
    inserer(racine, element);
}

template <class T>
bool ArbreAVL<T>::inserer(Noeud*& noeud, const T& element)
{
    //le facteur d'équilibre dans ce cas est calculé :
    // equilibre = hauteur_gauche - hauteur_droite
    if(noeud==nullptr)
    {
        noeud = new Noeud(element);
        return true;
    }
    if(element < noeud->contenu){
        if(inserer(noeud->gauche, element))
        {
            noeud->equilibre++;
            if(noeud->equilibre == 0)
                return false;
            if(noeud->equilibre == 1)
                return true;
            assert(noeud->equilibre==2);
            if(noeud->gauche->equilibre == -1)
                rotationDroiteGauche(noeud->gauche);
            rotationGaucheDroite(noeud);
        }
        return false;
    }
    else if(noeud->contenu < element){
        if(inserer(noeud->droite, element)){
            noeud->equilibre--;
            if (noeud->equilibre == 0){
                return false;
            }
            if (noeud->equilibre == -1){
                return true;
            }
            assert(noeud->equilibre == 2)
            if (noeud->droite->equilibre == -1){
                rotationGaucheDroite(noeud->droite);
            }
            rotationDroiteGauche(noeud);
        }
        return false;
    }

    // element == noeud->contenu
    noeud->contenu = element;  // Mise à jour
    return false;
}

template <class T>
void ArbreAVL<T>::rotationGaucheDroite(Noeud*& racinesousarbre)
{
    Noeud *temp = racinesousarbre->gauche;
    int  ea = temp->equilibre;
    int  eb = racinesousarbre->equilibre;

    //Calcul des nouveaux indices d'équilibre
    int  neb = -(ea>0 ? ea : 0) - 1 + eb;
    int  nea = ea + (neb < 0 ? neb : 0) - 1;

    //Assigner les nouveaux équilibres
    temp->equilibre = nea;
    racinesousarbre->equilibre = neb;

    //Reconnecter les pointeurs
    racinesousarbre->gauche = temp->droite;
    temp->droite = racinesousarbre;
    racinesousarbre = temp;
}

template <class T>
void ArbreAVL<T>::rotationDroiteGauche(Noeud*& racinesousarbre)
{
    Noeud *temp = racinesousarbre->droite;
    int  ea = temp->equilibre;
    int  eb = racinesousarbre->equilibre;

    //Calcul des nouveaux indices d'équilibre
    int  nea = -(eb < 0 ? eb : 0) + 1 + ea;
    int  neb = (nea > 0 ? nea : 0) + 1 + eb;

    //Assigner les nouveaux équilibres
    temp->equilibre = neb;
    racinesousarbre->equilibre = nea;

    //Reconnecter les pointeurs
    racinesousarbre->droite = temp->gauche;
    temp->gauche = racinesousarbre;
    racinesousarbre = temp;
}

template <class T>
bool ArbreAVL<T>::vide() const
{
    // À compléter : doit retourner vrai si et seulement si l'arbre est vide.
    return (racine == nullptr);
}

template <class T>
void ArbreAVL<T>::vider(){
  vider(racine);
  racine = nullptr;
}

template <class T>
void ArbreAVL<T>::vider(Noeud*& noeud)
{
    // À compléter.
    if(noeud != nullptr){
        //Vider à gauche
        vider(noeud->gauche);
        //Vider à droite
        vider(noeud->droite);
        //Supprimer le noeud
        delete noeud;
    }
}

template <class T>
void ArbreAVL<T>::copier(const Noeud* source, Noeud*& noeud) const
{
    // À compléter.
}

template <class T>
int  ArbreAVL<T>::hauteur() const{
    return hauteur(racine);
}

template <class T>
int  ArbreAVL<T>::taille() const{
    return compter(racine);
}

template <class T>
int  ArbreAVL<T>::hauteur(const Noeud* n) const{
    if(n==nullptr)
        return 0;
    return 1 + std::max(hauteur(n->gauche, n->droite));
}

template <class T>
int ArbreAVL<T>::compter(const Noeud* n) const{
    if(n==nullptr) return 0;
    return 1 + compter(n->gauche) + compter(n->droite);
}

template <class T>
ArbreAVL<T>& ArbreAVL<T>::operator=(const ArbreAVL& autre) {
    if(this==&autre) return *this;
    vider();
    copier(autre.racine, racine);
    return *this;
}

// ------ Optionnel Lab 6 -----
template <class T>
void ArbreAVL<T>::enlever(const T& element)
{
    if( noeud == nullptr){
        return;
    }

    if (element < noeud->contenu){
        enlever(noeud->gauche,element);
    } else if (element > noeud->contenu){
        enlever(noeud->droite, element);
    } else {
        if (noeud->gauche != nullptr && noeud->droite != nullptr){
            Noeud* noeud_maximum = maximum_sous_arbre_gauche(noeu->gauche);
            noeud->contenu = noeud_maximum->contenu;
            enlever(noeud->gauche, noeud_maximum->contenu);
        }else {
            Noeud* temp = noeud;
            noeud = (noeud->gauche != nullptr) ? noeud->gauche : noeud->droite;
            delete temp;
            return;
        }
    }

    //Rééquilibrer l'arbre
    if (noeud != nullptr){
       int equilibre = hauteur(noeud->gauche) - hauteur(noeud->droite);

       if (equilibre > 1){
           if(noeud->gauche != nullptr && noeud->gauche->equilibre < 0){
               rotationDroiteGauche(noeud->gauche);
           }
           rotationGaucheDroite(noeud);
       } else if (equilibre < -1) {
           if (noeud->droite != nullptr && noeud->droite->equilibre >0){
               rotationGaucheDroite(noeud->droite);
           }
           rotationDroiteGauche(noeud);
       }

       //mise a jour equilibre
       noeud->equilibre = hauteur(noeud->gauche) - hauteur(noeud->droite);
    }
}

template<class T>
typename ArbreAVL<T>::maximum_sous_arbre_gauche(Noeud* node){
    while (node->droite != nullptr) {
        node = node->droite;
    }
    return node;
}



//-----------------------------

// Code fourni pour afficher l'arbre :
#include <iostream>
template <class T>
void ArbreAVL<T>::afficher() const{
    std::cout << "Contenu de l'arbre (";
    int n = taille();
    std::cout << n << " noeuds)\n";
    T* elements = new T[n];
    int* profondeurs = new int[n];
    n=0;
    preparerafficher(racine, 0, n, elements, profondeurs);
    for(int p=0;;p++){
        bool derniereprofondeur = true;
        for(int i=0;i<n;i++){
            if(profondeurs[i]==p){
                std::cout << elements[i];
                derniereprofondeur = false;
            }
            std::cout << '\t';
        }
        std::cout << '\n';
        if(derniereprofondeur) break;
    }
    delete[] profondeurs;
    delete[] elements;
    std::cout << "-------------" << std::endl;
}

template <class T>
void ArbreAVL<T>::preparerafficher(const Noeud* n, int profondeur, int& rang, T* elements, int* profondeurs) const{
    if(n==nullptr) return;
    preparerafficher(n->gauche, profondeur+1, rang, elements, profondeurs);
    elements[rang] = n->contenu;
    profondeurs[rang] = profondeur;
    rang++;
    preparerafficher(n->droite, profondeur+1, rang, elements, profondeurs);
}

#endif
