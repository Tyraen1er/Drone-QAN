
#define TAILLE_SECTEUR 100
float taille_secteur = TAILLE_SECTEUR;

struct vector
{
  float x;
  float y;
};

vector operator+(vector const& a, vector const& b)
{
  vector r;
  r.x = a.x + b.x;
  r.y = a.y + b.y;
  return r;
}

vector operator-(vector const& v1, vector const& v2)
{
  vector r;
  r.x = v1.x - v2.x;
  r.y = v1.y - v2.y;
  return r;
}

float norme_2(vector const v)
{
  return v.x * v.x + v.y * v.y ;
}

struct segment
{
  vector A;
  vector B;
};


float det(vector u, vector v);
{
  return u.x*v.y-u.y*v.x;
}

bool collision(segment seg_AB, segment seg_CD);
{
  vector AB = seg_AB.B - seg_AB.A ;
  vector CD = seg_CD.B - seg_CD.A ;
  vector AC = seg_CD.A - seg_AB.A ;
  vector AD = seg_CD.B - seg_AB.A ;
  vector CA = seg_AB.A - seg_CD.A ;
  vector CB = seg_AB.B - seg_CD.A ;

  return det(AB,AC)*det(AB,AD) < 0 && det(CD,CA)*det(CD,CB) < 0 ;
}

bool collision(vector carre, vector point)
{
  return !( point.x < carre.x || point.y < carre.y || point.x > carre.x + taille_secteur || point.y > carre.y + taille_secteur ); 
}

bool collision(vect carre, segment seg)
{
  if collision(carre, seg.A) || collision(carre, seg.B)
  {
    return true;
  }
  else
  {
    segment seg1 {carre, {carre.x + taille_secteur,carre.y} } ;
    segment seg2 {{carre.x + taille_secteur,carre.y}, {carre.x + taille_secteur, carre.y + taille_secteur}} ;
    segment seg3 {{carre.x + taille_secteur, carre.y + taille_secteur} , {carre.x ,carre.y + taille_secteur}} ;
    segment seg4 {carre,{carre.x ,carre.y + taille_secteur}} ;
    return( collision(seg1,seg) || collision(seg2,seg) || collision(seg3,seg) || collision(seg4,seg) );
  }
}

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



bool point_triangle(vector M, vector A, vector B, vector C)
{

  float normes[3] = { norme_2(A-M), norme_2(B-M), norme_2(C-M) };

  int plus_grand = 0;
  float taille_plus_grand = 0;

  for(int i=0; i<3; ++i)
  {
    if (normes[i] > plus_grand)
    {
      plus_grand = i;
      taille_plus_grand = normes[i];
    }
  }

  vector somme_des_petits;

  switch(plus_grand)
  {
    case 0 :
      somme_des_petits = B + C ;
      break;
    case 1 :
      somme_des_petits = A + C ;
      break;
    case 2 :
      somme_des_petits = A + B ;
      break;
    default :
      break;
  }
  return norme_2(somme_des_petits) > norme_2(A+B+C);
}




void setup()
{
  Serial.begin(9600);
}

void loop()
{ 
    traiter_string();
}
