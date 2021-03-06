// Tema1_Album.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Meniu.h"
#pragma warning(disable : 4996)
void init(Meniu * m)
{
	char exempleNume[][30] = { "Exploit", "Fuego", "DM" };
	char exempleAlbume[][30] = { "Rising", "Craciun", "Libertatea" };
	char exempleMelodii[][30] = { "UpDown", "Pomul", "Fratii" };
	for (int k = 0; k < 3; ++k) {
		char * nume = new char[20];
		strcpy(nume, exempleNume[k]);
		Artist art(nume, 20);
		for (int s = 0; s < 2; s++) {
			strcpy(nume, exempleAlbume[k]);
			Album alb(nume, (2018 + k + s));
			strcpy(nume, exempleMelodii[k]);
			for (int i = 0; i < 5; ++i)
			{
				Track t(nume, i);
				alb.AdaugaTrack(t);
			}
			art.AdaugaAlbum(alb);
		}
		m->artisti.push_back(art);
	}
}

int main()
{
	Meniu * meniu = new Meniu();
	
	
	init(meniu);
	meniu->MeniuPrincipal();

	

	delete meniu;
    return 0;
}

