#include "geometry.h"

float	taillesecteur;

class grille
{
	public:
		grille(vector *balise, int size)
		{
			vector	tmp = balise[0];
			origine = balise[0];
			segment	*perim;
			int	a = 0;
			int	b = 0;

			//prendre les points Nord Ouest et Sud Est
			while (a < size)
			{
				if (balise[a].x < origine.x)
					origine.x = balise[a].x;
				if (balise[a].y > origine.y)
					origine.y = balise[a].y;

				if (balise[a].x > tmp.x)
					tmp.x = balise[a].x;
				if (balise[a].y < tmp.y)
					tmp.y = balise[a].y;

				++a;
			}
			nb_colonnes = tmp.x - origine.x / taillesecteur;
			nb_lignes = origine.y - tmp.y / taillesecteur;

			//tout mettre à 1
			table = (unsigned char*)malloc(nb_lignes * nb_colonnes);
			memset(table, '1', nb_lignes * nb_colonnes);

			//initialisations segments
			perim = (segment*)malloc(sizeof(segment) * size);
			a = -1;
			while (++a < size - 1)
				segment[a] = (segment){balise[a], balise[a + 1]};
			segment[size - 1] = (segment){balise[size - 1], balise[0]};

			//mettre les carrés traversés par un segment à 0
			a = -1;
			while (++a < size)
			{
				tmp = get_carre(a);
				b = -1;
				while (++b < size)
					if (collision(tmp, perim[b]))
						table[a] = 0;
			}
			free(perim);
			perim = NULL;
		}
		~grille()
		{
			free(table);
		}
		unsigned char& operator()(int ligne,int colonne)
		{
			return table[nb_colonnes*ligne + colonne];
		}

	private:

		vector get_carre(int ligne, int colonne)
		{
			return vector {origine.x + colonne * taille_secteur, origine.y + ligne * taille_secteur};
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

