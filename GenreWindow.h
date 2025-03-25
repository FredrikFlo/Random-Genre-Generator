#include "AnimationWindow.h"
#include "Genre.h"

constexpr int genreCellWidth;
constexpr int genreCellHeight; 
constexpr int ratingCellHeight; 
constexpr int ratingCellHeight; 


class genreWindow: public TDT4102::AnimationWindow
{
    private:
    public:
    void DrawGenreCell(const std::shared_ptr<Genre>& genre) const; //Bør funke for både en Genre og SubGenre pointer
    void DrawTable(const std::shared_ptr<Genre>& genre) const; //Vil BARE funke for Genre pointer
};
