#pragma once

#include "AnimationWindow.h"
#include "Genre.h"
#include "SubGenre.h"
#include "widgets/Button.h"
#include "widgets/DropdownList.h"
#include <format>

static constexpr int genreCellWidth = 350;
static constexpr int ratingCellWidth = 100; 
static constexpr int CellHeight = 33; 
static constexpr int windowWidth = 1200;
static constexpr int windowHeight = 800;
static constexpr int buttonWidth = 200;
static constexpr int buttonHeight = 75;
static constexpr int dropDownWidth = 350;
static constexpr int dropDownHeight = 75;
static TDT4102::Point tableCorner = {150, 25};


class GenreWindow: public TDT4102::AnimationWindow
{
    private:
    std::vector<std::string> vec = std::vector<std::string> (19, "TEST");
    TDT4102::Button button;
    TDT4102::DropdownList dropDownList;
    public:
    void DrawGenreCell(std::shared_ptr<Genre> genrePtr, const TDT4102::Point& position); //Bør funke for både en Genre og SubGenre pointer
    void DrawTable(std::shared_ptr<Genre> genrePtr); //Vil BARE funke for Genre pointer
    
    //Constructors
    GenreWindow();
};
