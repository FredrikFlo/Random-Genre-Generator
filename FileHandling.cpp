#include "FileHandling.h"

void Strip(std::string& str)
{
    // Denne loopen skal fjerne alle mellomrom fra den venstre siden. Sletter den første indeksen dersom den er lik ' '
    while(str.length() > 0) 
    {
        if (str.at(0) == ' ')
        {
            str.erase(0, 1);
        }
        else{break;}
    }
    
    int count = str.length() - 1; //setter count lik slutten av strengen

    // Denne loopen skal fjerne alle mellomrom fra den høyre siden. 
    //Sletter den siste indeksen dersom den er lik ' ' og tar rede at den siste indeksen dekrementers for hver iterasjon
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

// Denne funksjonen tar inn en stringstream som tilsvarer en av linjene i GenreData.txt som starter med SubGenre: , men med Genre: slettet 
void CreateSubGenre(std::istringstream &iss, std::string &name, std::vector<std::shared_ptr<Genre>> &genreVector)
{
    double rating;
    std::string temp;
    bool isRated;

    // Sender inn alt fra string stream helt til den ender opp på '|'
    std::getline(iss, name, '|');
    Strip(name); // Remove White Space

    // Sender inn alt fra string helt til den ender opp på '|'
    std::getline(iss, temp, '|'); 
    Strip(temp); // Remove White Space
    rating = std::stod(temp); // Antar at det ligger et tall der å gjør det om til double

    // Sender inn resten av strengen
    std::getline(iss, temp); 
    Strip(temp); // Remove White Space
    isRated = std::stoi(temp); //gjør om til en int som vil også være en bool 

    genreVector.at(genreVector.size()-1)->AddGenre(std::make_shared<SubGenre>(name, rating, isRated)); 
    //Lagrer SubGenre instansen gjennom en pointer i subGenres vectoren til den Genre instansen lengst bak i genreVectoren i GenreWindow.h
    genreVector.at(genreVector.size()-1)->sgNames.push_back(name); 
    //Legger til navnet i en vektor med alle andre navn.
}

// Denne funksjonen tar in en stringstream men starter som Genre: i stedet
void CreateGenre(std::istringstream &iss, std::string &name, std::vector<std::shared_ptr<Genre>> &genreVector)
{
    // tar stringstreamen og sender in til name
    std::getline(iss, name);
    Strip(name); // Remove White Space
    genreVector.push_back(std::make_shared<Genre>(name)); // caller konstruktøren til Genre og plasser den konstruktøren inn i genreVector
}

std::vector<std::shared_ptr<Genre>> LoadFromFile(const std::string& filename)
{
    std::ifstream ifs(filename); //lager input file stream med filenavnet

    // Sjekker om filen finnes
    if (!ifs)
    {
        throw std::logic_error("File Not Found");
    }

    std::string line;
    std::string type;
    std::vector<std::shared_ptr<Genre>> genreVector;
    
    // Den henter ut hver linje i GenreData.txt en og en
    while(std::getline(ifs, line))
    {
        // Lager linjen til en stringstream
        std::istringstream iss(line);
        iss >> type;
        std::string name;
        
        // Hvis den starter med Genre: så håndterer funksjonen den linjen slik at den skal skape en Genre
        if(type == "Genre:")
        {
            CreateGenre(iss, name, genreVector); // Skaper et Genre istansen fra det den leser
        }
        // Ellers hvis den starter med SubGenre: så håndterer funksjone den linjen slik at den skal eskape en SubGenre instanse inne i Genre
        else if (type == "SubGenre:")
        {
            CreateSubGenre(iss, name, genreVector); // Skaper en SubGenre instanse inn i subGenreVector til den Genre som ble sist laget.
        }
        else // VI håper at vi ikke kommer hit
        {
            throw std::logic_error("Beginning of line does not start with Genre: or SubGenre: ");
        }
    }
    return genreVector; 
}

void SaveToFile(const std::string& fileName, const std::vector<std::shared_ptr<Genre>>& genreVector)
{
    // Lager en ouput file stream med filenavnet
    std::ofstream ofs(fileName); // Trenger ikke å skjekke om den finnes siden den lager en ny fil vis ikke
    for (int i = 0; i < genreVector.size(); i++)  // itererer gjennom indeksene i genreVector som har alle instanser av Genre: objektet
    {
        ofs << "Genre: " << genreVector.at(i)->GetName() << std::endl;  // skriver informasjon på samme måte som vi fikk den
        for (int j = 0; j < genreVector.at(i)->subGenres.size(); j++) // itererer gjennom indeksen i subGenres vectoren til den ene genre som gjelder
        {
            ofs << "SubGenre: " << genreVector.at(i)->subGenres.at(j)->GetName() << " | " 
                                      << genreVector.at(i)->subGenres.at(j)->GetRating() << " | "
                                      << genreVector.at(i)->subGenres.at(j)->HasRating() << std::endl; // skriver informasjon på samme måte som vi fikk den
        }
    }
}