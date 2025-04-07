#include "Functions.h"

int main() 
{
    /*
    "Testing av klasse funksjoner";
    
    Genre rock("rock");
    Genre pop("pop");
    // std::cout << pop.GetRating() << std::endl //0
    //           << rock.GetName() << std::endl; //rock

    SubGenre latinRock("Latin Rock", 0.0, 0);
    SubGenre alternativePop("Alternative Pop", 0.0, 0); 
    // std::cout << latinRock.GetRating() << std::endl //0
    //           << alternativePop.GetName() << std::endl //Alternative Pop
    //           << alternativePop.HasRating() << std::endl //0
    //           << latinRock.HasRating() << std::endl; //0

    latinRock.SetSubGenreRating(8);
    // std::cout << latinRock.GetRating() << std::endl
    //           << latinRock.HasRating() << std::endl;

    // auto latinRockPtr = std::make_shared<SubGenre>(latinRock);
    // auto alternativePopPtr = std::make_shared<SubGenre>(alternativePop);

    // rock.AddGenre(std::move(latinRockPtr));
    rock.AddGenre(std::make_shared<SubGenre>(latinRock));
    pop.AddGenre(std::make_shared<SubGenre>(alternativePop));

    rock.SetGenreRating();
    pop.SetGenreRating();

    std::cout << rock.GetRating() << std::endl
              << pop.GetRating() << std::endl;
   
    */

    // SaveToFile("test2.txt", genreVector);

    Run();
    return 0;
}
