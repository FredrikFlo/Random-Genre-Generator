#include "Genre.h"
#include "SubGenre.h"

double Genre::GetRating() const // Henter double genreRating
{
    return this->genreRating;
}

std::string Genre::GetName() const // Henter std::string name
{
    return this->name; 
}

void Genre::SetGenreRating()
{
    try
    {
        //Exception Handling for tilfeller hvor Genre ikke har noen SubGenres som har blitt ratet slik at vi ikke deler på null. 
        if(!HasRating())
        {
            throw std::string("No ratings for Genre instance");
        }

        // Hoved Kode for å ta snittet av alle SubGenre ratingsen som er relevante
        double temp = 0; 
        int count = 0;
        for (const auto& subGenrePtr : subGenres)
        {
            if (subGenrePtr->HasRating()) 
            {
                count ++;
                temp += subGenrePtr->GetRating();
            }  
        }
        genreRating = temp / count;
    }

    //Catcher strengen, printer ut feilmelding og setter genreRating = 0;
    catch(const std::string& e)
    {
        std::cout << e << '\n';
        genreRating = 0; 
    }   
}

void Genre::AddGenre(std::shared_ptr<SubGenre> subGenre) // Legger til en subGenre pointer til Genre instansen (IKKE bruk const da funker ikke move)
{
    this->subGenres.emplace_back(std::move(subGenre));
}

bool Genre::HasRating() const // Sjekker om alle SubGenre is subGenres funker. 
{
    bool temp = false; 
    for (int i = 0; i < subGenres.size(); i++)
    {
        temp += subGenres.at(i)->HasRating();
    }
    return temp; 
}

int Genre::GetUnratedSG() const
{
    int amount = 0; 
    for (int i = 0;  i < subGenres.size(); i++)
    {
        if(!(subGenres.at(i)->HasRating()))
        {
            amount++;
        }
    }

    return amount;
}