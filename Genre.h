#pragma once

#include <iostream>
#include <vector>
#include <memory>

class SubGenre;

class Genre
{
private: 
//private member variables
std::string name; // navn på sjangeren

protected:
double genreRating; // antall rating den har

public:
std::vector<std::shared_ptr<SubGenre>> subGenres; // vector med SubGenre
std::vector<std::string> sgNames;
// public member functions
double GetRating() const;
std::string GetName() const;
virtual void SetGenreRating(); //Setter genreRating lik snittet av flere SubGenre og deres genreRating
virtual void AddGenre(std::shared_ptr<SubGenre> subGenre); //Legger til en sjanger til subGenres
virtual bool HasRating() const; // Sjekker om en SubGenre i subGenres har en rating

// constructors
Genre() = delete; 
Genre(const std::string& nameInput): name{nameInput}, genreRating{0}{};
Genre(const std::string& nameInput, const double& ratingInput): name{nameInput}, genreRating{ratingInput} {};
virtual ~Genre() {};
};