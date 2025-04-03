#include "Genre.h"
#include "SubGenre.h"
#include "FileHandling.h"
#include "test.h"
#include "GenreWindow.h"

#include <thread>
#include <chrono>

#include <windows.h>

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
        if(!win.GetHomeBool())
        {
            win.DrawTable();
            win.DrawImage();
            win.UpdateDropDown();
            win.DrawRatingText();
            win.draw_text({1115, 620}, std::to_string((win.GetCount()+1)) + "/" + std::to_string(win.genreVector.size()));
            if (win.is_key_down(KeyboardKey::LEFT))
            {
                win.DecrementCount();
                Sleep(150);
            }
            if (win.is_key_down(KeyboardKey::RIGHT))
            {
                win.IncrementCount();
                Sleep(150);
            }
            if (win.is_key_down(KeyboardKey::UP))
            {
                win.DecrementDropdownIndex();
                Sleep(150);
            }
            if (win.is_key_down(KeyboardKey::DOWN))
            {
                win.IncrementDropdownIndex(); 
                Sleep(150);
            }

            // Set Visibility
            win.SetVisibility(true);
        }
        else
        {
            //Set Visibility 
            win.SetVisibility(false);
        }
        win.next_frame();
    }
    return 0;
}
