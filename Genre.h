#pragma once

#include <iostream>
#include <vector>
#include <memory>

class SubGenre;

class Genre
{
private: 
std::string name; // navn på sjangeren
// Denne er initialisert i LoadFromFile() funksjonen

protected:
double genreRating; // antall rating instansen av objektet har
// denne blir arvet ned til SubGenre siden de skal også ha en 
// Blir brukt hovedsaklig i tabellen og den logikken.
// Denne blir initialisert med SetGenreRating i Genre klassen og SetSubGenreRating i SubGenre klassen

public:
std::vector<std::shared_ptr<SubGenre>> subGenres; 
// vector med SubGenre til den Genren. Denne blir laget når LoadFromFile() blir kalt. 
// Vi bruker vektor med pointers fordi SubGenre ikke har en kopikonstruktør
// denne kunne burde kanskje vært privat sånn at SubGenre ikke arvet den, men det har ikke oppstått noen problemer enda
std::vector<std::string> sgNames; 
// sgNames er egentlig bare brukt i bilde Generering. 
// Disse bildene blir brukt i GenreWindow konstruktøren siden alle bildene har navnet + ".jpg" denne logikken kan bli sett i GenreWindow.
// kunne også vært privat, trenger bare noen getter funksjoner.  

int GetUnratedSG() const; // Denne teller antall SubGenres i vektoren subGenres som ikke har en rating
double GetRating() const; // Denne henter ut den private ratingen
std::string GetName() const; //Denne henter ut navne på instansen
virtual void SetGenreRating(); //Setter genreRating lik snittet av flere SubGenre og deres genreRating
virtual void AddGenre(std::shared_ptr<SubGenre> subGenre); //Legger til en ny sjanger til subGenres vektoren (IKKE bruk const da funker ikke move)
//Den funksjonen er brukt i LoadFromFile()
virtual bool HasRating() const; // Sjekker om minst en SubGenre i subGenres har en rating
// Denne blir brukt med hensyn til hjulet for å unngå å tegne den delen dersom den ikke har noen relevante SubGenres

// constructors
Genre() = delete; // Vi ønsker ikke å tillate kopiere av instanser av Genre klassen fordi det risikerer at endringene ikke blir lagret til filen i SaveToFile()
Genre(const std::string& nameInput): name{nameInput}, genreRating{0}{}; // Dette er konstruktør med bare navnet. Tror det er denne som blir brukt i LoadFromFile()
Genre(const std::string& nameInput, const double& ratingInput): name{nameInput}, genreRating{ratingInput} {}; // I motsetning til den forrige konstruktøren så har den rating å tilordne
// Er ikke sikker på om jeg bruker denne, tror kanskje det bare var for testing. 
virtual ~Genre() {}; // Samme forklaring som virtual destruktøren til SubGenre.
};