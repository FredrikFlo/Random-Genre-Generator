#pragma once

#include "Genre.h"

class SubGenre: public Genre
{
private:
bool isRated; 
// Dette er en bool som sier om SubGenre har blitt rata før
// Dersom den er 0 vil den ha isRated = false og dersom den ikke er null så bør isRated = true
// Dette blir nyttig for flere funksjoner i vinduet 
//      - Hjulet skal ikke inkludere sjangere som har blitt ratet
//      - Hoved Genre ratingene skal ikke ta gjennomsnittet av SubGenres som ikke har en rating. 

public:
virtual void SetGenreRating() override; // Denne funksjonen ønsker vi at skal bare tilhøre Genre klassen, vi vil ha en annen setter som tar in en double
virtual void AddGenre(std::shared_ptr<SubGenre> subGenre) override; // Samme som før bare at det finnes ingen andre funksjon lik denne 
virtual bool HasRating() const override; // denne skal returnere isRated
void SetSubGenreRating(double rating); //Denne skal sette genreRating lik det den tar inn. genreRating er en variable arvet fra Genre klassen

// Constructors
SubGenre() = delete; //Vi ønsker ikke å kopiere en instanse av SubGenre siden det kan bli komplisert med hensyn på data lagring til fil. 
SubGenre(const std::string& nameInput, const double& genreRating, const bool& isRated): Genre(nameInput, genreRating), isRated{isRated} {};
virtual ~SubGenre() {}; //Hørte at virtual destructors var viktige å definere, men jeg trenger egentlig ingen definisjon for den siden jeg bruker smart pointers.
};