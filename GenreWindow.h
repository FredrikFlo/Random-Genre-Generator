#pragma once

#include "AnimationWindow.h"
#include "Genre.h"
#include "SubGenre.h"
#include <format>

static constexpr int genreCellWidth = 350;
static constexpr int ratingCellWidth = 100; 
static constexpr int CellHeight = 33; 
static constexpr int windowWidth = 1200;
static constexpr int windowHeight = 800;
static TDT4102::Point tableCorner = {50, 25};


class GenreWindow: public TDT4102::AnimationWindow
{
    private:
    public:
    void DrawGenreCell(std::shared_ptr<Genre> genrePtr, const TDT4102::Point& position); //Bør funke for både en Genre og SubGenre pointer
    void DrawTable(std::shared_ptr<Genre> genrePtr); //Vil BARE funke for Genre pointer

    //Constructors
    GenreWindow() : TDT4102::AnimationWindow{100, 100, windowWidth, windowHeight, "Random Genre Generator"} {};
};
