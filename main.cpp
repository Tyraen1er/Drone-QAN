#define TAILLE_SECTEUR 100
float taille_secteur = TAILLE_SECTEUR;


void setup()
{
  Serial.begin(9600);
}

void loop()
{ 
    traiter_string();
}
