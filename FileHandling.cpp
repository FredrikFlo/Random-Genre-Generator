#include "FileHandling.h"

void Strip(std::string& str)
{
    
    while(str.length() > 0)
    {
        if (str.at(0) == ' ')
        {
            str.erase(0, 1);
        }
        else{break;}
    }
    
    int count = str.length() - 1;

    while (str.length() > 0)
    {
        if (str.at(count) == ' ')
        {
            str.erase(count, count + 1);
            count--;
        }
        else{break;}
    }
}

void CreateSubGenre(std::istringstream &iss, std::string &name, std::string &temp, double &rating, bool &isRated, std::vector<std::shared_ptr<Genre>> &genreVector)
{
    std::getline(iss, name, '|');
    Strip(name);

    std::getline(iss, temp, '|');
    Strip(temp);
    rating = std::stod(temp);

    std::getline(iss, temp);
    Strip(temp);
    isRated = std::stoi(temp);

    genreVector.at(genreVector.size()-1)->AddGenre(std::make_shared<SubGenre>(name, rating, isRated)); //Lagrer SubGenre objektet i subGenres
    genreVector.at(genreVector.size()-1)->sgNames.push_back(name); //Legger til navnet i en vektor
}

void CreateGenre(std::istringstream &iss, std::string &name, std::vector<std::shared_ptr<Genre>> &genreVector)
{
    std::getline(iss, name, '|');
    Strip(name);
    genreVector.push_back(std::make_shared<Genre>(name));
}

std::vector<std::shared_ptr<Genre>> LoadFromFile(const std::string& filename)
{
    std::ifstream ifs(filename);

    if (!ifs)
    {
        throw std::logic_error("File Not Found");
    }

    std::string line;
    std::string type;
    std::vector<std::shared_ptr<Genre>> genreVector;
    
    while(std::getline(ifs, line))
    {
        std::istringstream iss(line);
        iss >> type;
        std::string name;
        
        if(type == "Genre:")
        {
            CreateGenre(iss, name, genreVector);
        }
        else if (type == "SubGenre:")
        {
            double rating;
            std::string temp;
            bool isRated;
            CreateSubGenre(iss, name, temp, rating, isRated, genreVector);
        }
        else
        {
            throw std::logic_error("Beginning of line does not start with Genre: or SubGenre: ");
        }
    }
    return genreVector; 
}

void SaveToFile(const std::string& fileName, const std::vector<std::shared_ptr<Genre>>& genreVector)
{
    std::ofstream ofs(fileName);
    for (int i = 0; i < genreVector.size(); i++)
    {
        ofs << "Genre: " << genreVector.at(i)->GetName() << std::endl; 
        for (int j = 0; j < genreVector.at(i)->subGenres.size(); j++)
        {
            ofs << "SubGenre: " << genreVector.at(i)->subGenres.at(j)->GetName() << " | " 
                                      << genreVector.at(i)->subGenres.at(j)->GetRating() << " | "
                                      << genreVector.at(i)->subGenres.at(j)->HasRating() << std::endl; 
        }
    }
}