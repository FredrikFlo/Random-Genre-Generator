#include "SubGenre.h"

void SubGenre::SetSubGenreRating(double rating)
{
    this->genreRating = rating; 
    this->isRated = true; 
    // var redd for å sette den lik 0 på grunn av floating point errors. Det vil ikke være noe mindre enn 0.1 så dette bør gå fint
    if (rating < 0.09) 
    {
        // Vi sier at 0 er ikke en valid rating siden det er også default ratingen.
        this->isRated = false; 
    }
}

void SubGenre::AddGenre(std::shared_ptr<SubGenre> subGenre)
{ 
    throw std::logic_error("Can't call AddGenre() on a 'SubGenre' object."); 
    //Ønsker å crashe prosjektet om denne blir kalt. 
}

void SubGenre::SetGenreRating()
{
    throw std::logic_error("Can't call SetGenreRating() with empty parameter list on a 'SubGenre' object.");
    //Ønsker å crashe prosjektet om denne blir kalt.
}

bool SubGenre::HasRating() const
{
    return isRated; 
}

//Dokumentasjon ligger i større grad på h-filene