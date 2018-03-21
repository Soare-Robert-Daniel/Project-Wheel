#include <iostream>
#include <string.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define isbn_code 11
#define nr 10

using namespace std;
class Carte
{
	private:
		char *autor;
		char *titlu;
		char ISBN[isbn_code];
		int an_aparitie;
		
	public:
		Carte();
		Carte(const char *,const char *,const char [isbn_code], int);
		Carte(const Carte&);
		~Carte();
		
		void copiere(const Carte&);
		int getAn() const;
		char * getTitlu() const;
};

Carte::Carte()
{
	autor = NULL;
	titlu = NULL;
	this->an_aparitie = 1998;
}


Carte::Carte(const char *autor,const char *titlu, const char ISBN[isbn_code], int an_aparitie)
{
	if(autor == NULL)
		this->autor = NULL;
	else this->autor = new char[strlen(autor)];
	if(titlu == NULL)
		this->titlu = NULL;
	else this->titlu = new char[strlen(titlu)];

	strcpy(this->autor, autor);
	strcpy(this->titlu, titlu);
	strcpy(this->ISBN, ISBN);
	
	//cout << this->titlu << " " << titlu << '\n';
	
	this->an_aparitie = an_aparitie;
}

Carte::Carte(const Carte& c)
{
	if(c.autor == NULL)
		this->autor = NULL;
	else this->autor = new char[strlen(c.autor) + 1];
	if(c.titlu == NULL)
		this->titlu = NULL;
	else this->titlu = new char[strlen(c.titlu) + 1];

	strcpy(this->autor, c.autor);
	strcpy(this->titlu, c.titlu);
	strcpy(this->ISBN, c.ISBN);
	
	this->an_aparitie = c.an_aparitie;
}

Carte::~Carte()
{
	delete []this->titlu;
	this->titlu = NULL;
	delete []autor;
	this->autor = NULL;
}

int Carte::getAn() const
{
	return this->an_aparitie;
}

char * Carte::getTitlu() const
{
	return this->titlu;
}

void afisare(Carte &c)
{
	cout << c.getTitlu()  << " " << c.getAn() << '\n';
}

void Carte::copiere(const Carte& c)
{
	if(this->autor != NULL)
		delete [] this->autor;
	
	this->autor = new char[strlen(c.autor) + 1];
	
	if(this->titlu != NULL)
		delete [] this->titlu;
		
	this->titlu = new char[strlen(c.titlu) + 1];

	strcpy(this->autor, c.autor);
	strcpy(this->titlu, c.titlu);
	strcpy(this->ISBN, c.ISBN);
	
	this->an_aparitie = c.an_aparitie;
}

int main(int argc, char** argv) {
	
	Carte  *bib = new Carte[nr];

	for(int i = 0; i < nr; ++i){
		
		char autor[20];
		char titlu[20];
		
		strcpy(autor, "Autor");
		autor[strlen(autor)] ='0' + i;
		
		
		strcpy(titlu, "Titlu");
		titlu[strlen(titlu)] ='0' + i;
	
		
		Carte c(autor, titlu, "ISBN12133", 1990 + i);
		
		bib[i].copiere(c);
	}
	
	for(int i = 0; i < nr; ++i){
		afisare(bib[i]);
	}
	
	// Sortez dupa titluri
	for(int i = 0; i < nr; ++i)
	{
		for(int j = i + 1; j < nr; ++j)
			if(strcmp(bib[i].getTitlu(), bib[j].getTitlu()) == 1)
			{
				Carte tmp(bib[i]);
				bib[i].copiere(bib[j]);
				bib[j].copiere(tmp);
			}
	}
	
	// Caut cea mai veche carte
	int min_an = bib[0].getAn();
	int index = 0;
	for(int i = 1; i < nr; ++i)
		if(bib[i].getAn() < min_an)
		{
			min_an = bib[i].getAn();
			index = i;
		}
	cout << "Cea mai veche carte: ";
	afisare(bib[index]);

	// Eliberez spatiul din memorie
	delete []bib;
	
	/*
		Ai gresit sursa prietene!
 	*/
 	
 	/*
	Share share share
	Sa vada toata lumea
	Ca asta-i maneau youtube-rilor 2 din Romania
	Dai tare decibelii sa se aud pana la Selly
	Hai ca a inceput bine anul sa auda si Vlad Munteanu
	
	Ca Max e la inaltime ca o drona
	Da drumul la GTA sa facem o misiune noua
	Tu si iRaphahell voi detineti smecheria
	Cele mai tari canale de gaming din Romania
	
	Haterii haterii n-au nicio valoare
	Ne unim cu totii si ii trimitem la culcare
	Avem atatia fani ii facem fata oricui
	Ca noi suntem forta internetului
	Haterii haterii n-au nicio valoare
	Ne unim cu totii si ii trimitem la culcare
	Avem atatia fani ii facem fata oricui
	Ca noi suntem forta internetului
	
	De ceva timp e pe val val val Andra Gogan gan gan
	Cu vocea ei a cucerit orice regat
	Hei Mimi tu esti apreciata
	C-ai avut curajul sa postezi
	Cum te saruti c-o fata
	
	Cu maneaua asta eu nu vreau sa deranjez
	Nici pe Bianca Adam, nici pe Alex Alvarez
	Melodia asta e pe placul tuturor
	Vin cu cel mai bun refren impotriva haterilor
	
	Mama mama ce se aude?
	Politia!
	Sper ca nu e Calinacio!
	
	Haterii haterii n-au nicio valoare
	Ne unim cu totii si ii trimitem la culcare
	Avem atatia fani ii facem fata oricui
	Ca noi suntem forta internetului
	Haterii haterii n-au nicio valoare
	Ne unim cu totii si ii trimitem la culcare
	Avem atatia fani ii facem fata oricui
	Ca noi suntem forta internetului
	
	Sunt nerabdator mai mult ca niciodata
	Sa-l va pe Insanity pe live cum se joaca
	Dar ce sa vezi la sugestie in fereasta
	Apare Denis Gurau cum joaca Balena Albastra
	Si ne da cu ciocanul si ne face praf
	Asta-i Maximilian cand joaca minecraft
	Si da ne iubesc fanii pe Muntenii si Sellary
	Pe gameri si pe Sefanii versuri.us
	Asa ca voi haterilor eu zic sa faceti nanii
	
	Haterii haterii n-au nicio valoare
	Ne unim cu totii si ii trimitem la culcare
	Avem atatia fani ii facem fata oricui
	Ca noi suntem forta internetului
	Haterii haterii n-au nicio valoare
	Ne unim cu totii si ii trimitem la culcare
	Avem atatia fani ii facem fata oricui
	Ca noi suntem forta internetului
*/
	return 0;
}
