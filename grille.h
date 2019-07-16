#include "geometry.h"

class grille
{
public:
  unsigned char& operator()(int ligne,int colonne)
  {
    return table[nb_colonnes*ligne + colonne];
  }

private:

  vector get_carre(int ligne, int colonne)
  {
    return vector {carre.x + colonne * taille_secteur, carre.y + ligne * taille_secteur};
  }
  vector get_carre(int i)
  {
    return get_carre(i / nb_lignes, i % nb_colonnes) ;
  }

  vector origine;
  int nb_lignes;
  int nb_colonnes;
  unsigned char* table;
};

