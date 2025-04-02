#include "Genre.h"
#include "SubGenre.h"
#include "FileHandling.h"
#include "test.h"
#include "GenreWindow.h"

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

    GenreWindow win{};

    //Funker IKKE!
    while(!win.should_close())
    {
        win.DrawTable();
        win.DrawImage();
        win.UpdateDropDown();
        win.DrawRatingText();
        win.draw_text({1115, 620}, std::to_string((win.GetCount()+1)) + "/" + std::to_string(win.genreVector.size()));
        win.next_frame();
    }
    return 0;
}
