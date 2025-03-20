#pragma once
#include "Genre.h"


class SubGenre: public Genre
{
private:
bool isRated;

public:
virtual void SetGenreRating() override; //Kjør en try except error ellerno her.
virtual void AddGenre(std::shared_ptr<SubGenre> subGenre) override; // Kjør en try except error ellerno her.
virtual bool HasRating() const override;
void SetSubGenreRating(double rating);

// Constructors
SubGenre() = delete;
SubGenre(const std::string& nameInput, const double& genreRating, const bool& isRated): Genre(nameInput, genreRating), isRated{isRated} {};
virtual ~SubGenre() {};
};