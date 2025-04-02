#include "SubGenre.h"

void SubGenre::SetSubGenreRating(double rating) // setter genreRating lik rating
{
    this->genreRating = rating;
    this->isRated = true; 
    if (int(rating) == 0)
    {
        this->isRated = false; 
    }
}

void SubGenre::AddGenre(std::shared_ptr<SubGenre> subGenre) //Utløser en feil fordi SubGenre skal ikke trenge denne functionen
{
    throw std::logic_error("Can't call AddGenre() on a 'SubGenre' object.");
}

void SubGenre::SetGenreRating() //Samme som før (Jeg bruker SetSubGenreRating i stedet fordi det er forskjell på hva slags parameter den skal ha)
{
    throw std::logic_error("Can't call SetGenreRating() with empty parameter list on a 'SubGenre' object.");
}

bool SubGenre::HasRating() const // Henter private bool
{
    return isRated; 
}

//Constructors 
