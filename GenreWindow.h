#pragma once

#include "AnimationWindow.h"
#include "Genre.h"
#include "SubGenre.h"
#include "FileHandling.h"
#include "widgets/Button.h"
#include "widgets/DropdownList.h"
#include "widgets/TextInput.h"
#include "Image.h"
#include <format>
#include <map>


static constexpr int genreCellWidth = 350;
static constexpr int ratingCellWidth = 100; 
static constexpr int CellHeight = 33; 
static constexpr int windowWidth = 1200;
static constexpr int windowHeight = 800;
static constexpr int buttonWidth = 200;
static constexpr int buttonHeight = 75;
static constexpr int pageButtonHeight = 300;
static constexpr int pageButtonWidth = 75;
static constexpr int dropDownWidth = 350;
static constexpr int dropDownHeight = 75;
static constexpr int textInputHeight = 100;
static constexpr int textInputWidth = 250;
static TDT4102::Point tableCorner = {150, 25};


class GenreWindow: public TDT4102::AnimationWindow
{
    private:
    std::vector<std::string> vec = std::vector<std::string> (19, "TEST");
    TDT4102::Button rateButton;
    TDT4102::Button leftButton;
    TDT4102::Button rightButton;
    TDT4102::Button homeButton;
    TDT4102::DropdownList dropDownList;
    TDT4102::TextInput textInput;
    
    int count = 0;
    std::vector<std::map<std::string, int>> stringToCountMapVector;
    
    public:
    const std::vector<std::shared_ptr<Genre>> genreVector = LoadFromFile("test.txt");
    std::vector<TDT4102::Image> images{};
    void DrawGenreCell(std::shared_ptr<Genre> genrePtr, const TDT4102::Point& position); //Bør funke for både en Genre og SubGenre pointer
    void DrawTable(); //Vil BARE funke for Genre pointer
    void DrawImage();
    void UpdateDropDown();
    int GetCount() const {return count;}
    
    //Call Back Funksjoner
    void DecrementCount();
    void IncrementCount();
    void RateCallback(); 
    
    //Constructors
    GenreWindow();
};
