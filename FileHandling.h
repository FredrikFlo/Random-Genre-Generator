#pragma once

#include "Genre.h"
#include "SubGenre.h"
#include <fstream>
#include <sstream>
#include <string>

void Strip(std::string& str);

std::vector<std::shared_ptr<Genre>> LoadFromFile(const std::string &fileName); // Lager alle objektene ut ifra informasjonen i LoadFromFile

void CreateSubGenre(std::istringstream &iss, std::string &name, std::string &temp, double &rating, bool &isRated, std::vector<std::shared_ptr<Genre>> &genreVector);

void CreateGenre(std::istringstream &iss, std::string &name, std::vector<std::shared_ptr<Genre>> &genreVector);

void SaveToFile(const std::string& fileName, const std::vector<std::shared_ptr<Genre>>& genreVector); // Lagrer alle objektene og dataen i filen
