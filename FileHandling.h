#pragma once

#include "Genre.h"
#include "SubGenre.h"
#include <fstream>
#include <sstream>
#include <string>

void Strip(std::string& str); 
// Denne funksjonen tilsvarer egentlig .strip() funksjonen i python

std::vector<std::shared_ptr<Genre>> LoadFromFile(const std::string &fileName); 
// Lager alle objektene ut ifra informasjonen i GenreData.txt

void CreateSubGenre(std::istringstream &iss, std::string &name, std::vector<std::shared_ptr<Genre>> &genreVector);
// denne funksjonen blir beskrevet tydligere i cpp

void CreateGenre(std::istringstream &iss, std::string &name, std::vector<std::shared_ptr<Genre>> &genreVector);
// denne funksjonen blir beskrevet tydligere i cpp

void SaveToFile(const std::string& fileName, const std::vector<std::shared_ptr<Genre>>& genreVector);
// Lagrer dataen fra objektene tilbake til GenreData.txt