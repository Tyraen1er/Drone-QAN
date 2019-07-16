class GPS
{
    float last_update;
    float lat; // negatif pour le sud, tout en minutes
    float lon; // negatif pour l'ouest, tout en minutes
    float pre;
};

int   i;
int   corrupted;
char  *recu;
char  *trame;
char  buf[4] = {0};
GPS   gps;

void setup()
{
  Serial.begin(9600);
}

//  $GPGGA,064036.289,4836.5375,N,00740.9373,E,1,04,3.2,200.2,M,,,,0000*0E
//  0123456789012345678901234567890123456789012345678901234567890123456789
//  0000000000111111111122222222223333333333444444444455555555556666666666

void loop()
{
  //  Serial.println("coucou");
  if (0 < (i = Serial.available()) && i == 70)
  {
    i = -1;
    corrupted = *trame;
    while (++i < 70)
      corrupted ^= recu[i];
    sprintf(buf, "%x", corrupted);
    if (0 == strncmp(buf, trame, 2))
    {
      Serial.readBytesUntil('\n', recu, i);
      // securité potentielle données reçues fragmentées à rajouter
      if (0 <= strncmp("$GPGGA,", trame, 6) && trame[42] == 1) // check si type de positionnement GPS
      {
        trame = recu + 18; // ignore l'horodate et saute GPGGA deja check

        memmove(buf, trame, 2); // take two digits of latitude
        gps.lat = 60 * atoi(buf);
        trame += 2;
        gps.lat += strtod(trame, NULL);
        while (*trame != ',')
          ++trame;
        gps.lat = (trame[1] == 'N') ? gps.lat : -gps.lat;

        memmove(buf, trame, 3); // take three digits of longitude
        gps.lon = 60 * atoi(buf);
        trame += 3;
        gps.lon += strtod(trame, NULL);
        while (*trame != ',')
          ++trame;
        gps.lon = (trame[1] == 'N') ? gps.lon : -gps.lon;

        trame = recu + 48;
        gps.pre = strtod(trame, NNULL);
      }
    }
    else
    {
      Serial.println("Corrupted data");
    }
  }
}
