#include "Genre.h"
#include "SubGenre.h"

double Genre::GetRating() const
{
    return this->genreRating;
}

std::string Genre::GetName() const
{
    return this->name; 
}

void Genre::SetGenreRating()
{
    try
    {
        //Exception Handling for tilfeller hvor Genre ikke har noen SubGenres som har blitt ratet slik at vi ikke deler på null. 
        // Vi ønsker ikke å crashe programmet for denne hendelsen
        if(!HasRating())
        {
            throw std::string("No ratings for Genre instance");
        }

        // Hoved Kode for å ta snittet av alle SubGenre ratingsen som er relevante
        double sumOfAllRatings = 0; // Summen av alle ratingen som har blitt gitt
        int amountWithRatings = 0; // Antall SubGenres med rating
        for (const auto& subGenrePtr : subGenres)
        {
            //iterere gjennom alle SubGenre instansene i subGenre vektoren å sjekker om de har en rating
            if (subGenrePtr->HasRating()) 
            {
                amountWithRatings ++;
                sumOfAllRatings += subGenrePtr->GetRating();
            }  
        }
        genreRating = sumOfAllRatings / amountWithRatings; // blir snittet av alle SubGenre
        // Det er her dele på null faren dukker opp
    }

    //Catcher feilmeldingen over
    catch(const std::string& e)
    {
        std::cout << e << '\n'; // printer "No ratings for Genre instance"
        genreRating = 0; // Setter snittet lik 0
    }   
}

void Genre::AddGenre(std::shared_ptr<SubGenre> subGenre)
{ 
    this->subGenres.emplace_back(std::move(subGenre)); // bruker du const i parameter lista funker ikke const
}

// Denne er egentlig ikke nødvendig man kan heler da bool(GetUnratedSG())
bool Genre::HasRating() const
{
    bool temp = false; // bool er det samme som null
    for (int i = 0; i < subGenres.size(); i++)
    {
        temp += subGenres.at(i)->HasRating(); // så lenge en av dem HasRating() så blir den true eller false
    }
    return temp; 
}

int Genre::GetUnratedSG() const
{
    int amount = 0; // en count av antall SubGeners som har rating
    for (int i = 0;  i < subGenres.size(); i++)
    {
        // Hvis den ikke har rating så blir den telt med i amount
        if(!(subGenres.at(i)->HasRating()))
        {
            amount++;
        }
    }

    return amount;
}

//Bedre dokumentasjonn ligger i h-fila