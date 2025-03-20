#include "test.h"

void test(const std::string& line)
{
    std::string type; 
    std::string name;
    std::stringstream ss(line);
    
    ss >> type; 
    std::getline(ss, name, '|');
    Strip(name);
    Genre genre(name);
    std::cout << genre.GetName() << std::endl;
}

void test1(const std::string& line1)
{
    std::string type; 
    std::string name;
    std::string temp;
    double rating;
    bool isRated;
    std::stringstream ss(line1);
    Genre genre1(std::string("Pop"));

    ss >> type;
    std::getline(ss, name, '|');
    Strip(name);

    std::getline(ss, temp, '|');
    Strip(temp);
    rating = std::stod(temp);

    std::getline(ss, temp);
    Strip(temp);
    isRated = std::stoi(temp);

    genre1.AddGenre(std::make_shared<SubGenre>(name, rating, isRated));
}