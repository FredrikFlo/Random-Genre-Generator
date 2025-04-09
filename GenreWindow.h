#pragma once

#include "AnimationWindow.h"
#include "Genre.h"
#include "SubGenre.h"
#include "FileHandling.h"
#include "widgets/Button.h"
#include "widgets/DropdownList.h"
#include "widgets/TextInput.h"
#include "widgets/Slider.h"
#include "Image.h"

#include <format>
#include <map>
#include <cmath>

// Dette er bare noen konstanter som blir brukt litt her og der. Egentlig litt rotete
static constexpr double pi = 3.14159265358979323846; 
static constexpr int genreCellWidth = 350;
static constexpr int ratingCellWidth = 100; 
static constexpr int CellHeight = 33; 
static constexpr int windowWidth = 1200;
static constexpr int windowHeight = 800;
static constexpr int buttonWidth = 290;
static constexpr int buttonHeight = 75;
static constexpr int pageButtonHeight = 300;
static constexpr int pageButtonWidth = 75;
static constexpr int dropDownWidth = 350;
static constexpr int dropDownHeight = 75;
static constexpr int textInputHeight = 100;
static constexpr int textInputWidth = 250;
static TDT4102::Point tableCorner = {150, 25};
static constexpr TDT4102::Point origin1 = {325, 300};
static constexpr TDT4102::Point origin2 = {windowWidth - origin1.x, origin1.y};

class GenreWindow: public TDT4102::AnimationWindow
{
    private:
    // Denne brukes til å initialisere  dropDownList options fordi genreVector.at(count)->sgNames ikke funker for en eller annen grunn. 
    std::vector<std::string> vec = std::vector<std::string> (19, "TEST"); 
    
    // Knapper osv. 
    TDT4102::Button rateButton; 
    TDT4102::Button leftButton;
    TDT4102::Button rightButton;
    TDT4102::Button homeButton;
    TDT4102::Button tableButton;
    TDT4102::Slider slider;
    TDT4102::Button plusButton; 
    TDT4102::Button minusButton; 
    TDT4102::DropdownList dropDownList;

    bool homeWindow = false; // Denne boolen er true dersom animation window skal vise hjem skjermen 
    int count = 0; // Denne verdien tilsvarer indeksen i genreVector som skal bli vist og håndtert for diverse funksjoner 
    std::vector<std::map<std::string, int>> stringToCountMapVector; // Detter er en vektor med flere mapper som tilsvarer alle navne til alle SubGenre og hvor de ligger i subGenres i hoved Genre instansen
    // Den er initialisert i konstruktøren 
    std::map<std::string, int> stringToGenreCountMap; // Dette er en mappe som tar inn navne på alle instansene i genresVectoren og gir indeksen
    // Den er også intialisert i konstruktøren
    std::map<int, TDT4102::Color> intToColorMap // Denne tar inn en int mellom 0, 4 og gir en farge. Den er brukt i å tegne hjulet.
    {
        {0, TDT4102::Color::red},
        {1, TDT4102::Color::goldenrod},
        {2, TDT4102::Color::green},
        {3, TDT4102::Color::blue},
        {4, TDT4102::Color::purple}
    };
    
    public:
    const std::vector<std::shared_ptr<Genre>> genreVector = LoadFromFile("GenreData.txt"); // Lagre en vektor genreVector som tar vektoren laget fra funksjonen LoadFromFile.
    std::vector<TDT4102::Image> images{}; // En vektor med bilder som blir initalisert i GenreWindow konstruktøren
    void DrawGenreCell(std::shared_ptr<Genre> genrePtr, const TDT4102::Point& position); //Bør funke for både en Genre og SubGenre pointer den gjør det!!
    //Denne er kalt på inne i DrawTable
    void DrawTable(); //Vil BARE funke for Genre pointer siden SubGenre er ikke interessert i subGenres vektoren
    // Denne blir håndtert med henysn til counten over
    void DrawImage(); // Tegner bilde som med hensyn til count definert over
    void DrawRatingText(); // Denne tegner verdien på slideren
    void UpdateDropDown(); // Denne opdaterer valgen på dropdownlist med hensyn på counten over
    int GetCount() const {return count;} // Denne henter count
    bool GetHomeBool() const {return homeWindow;} // Denne henter bool homeWindow 
    int GetTotalUnrated() const; // Denne regner ut antall SubGenres som er Unrated i hele programmet
    void SetHomeBool(bool newBool) {homeWindow = newBool;} // tilordner bool homeWindow
    void SetVisibility(bool isTableVisible); //Denne gjør sånn at noen knapper er tilgjenglige og andre ikke

    //Wheel stuff
    std::string DrawWheel(double angleOffset, TDT4102::Point origin, bool spinSubGenreWheel); // Denne tegner et hjul
    void DrawRadii(TDT4102::Point &origin, double startDegrees, double endDegrees); // Denne blir kalt av DrawWheel og tegner radiusene
    void DrawArc(double startDegrees, double endDegrees, const TDT4102::Point &origin, const TDT4102::Color &genreColor, 
                 std::string &winner, int genreIndex, bool spinSubGenre); // Denne tegner buene
   
    //Call Back Funksjoner
    void DecrementCount(); // Denne trekker 1 fra count
    void IncrementCount(); // Denne plusser 1 på count
    void IncrementSlider(); // Denne plusser Slider verdien med 0.1 (måtte endre på slider filene)
    void DecrementSlider(); // Denne trekker fra Slider verdien med 0.1
    void RateCallback();  // Denne tilordner subGenre ratingen som er gitt på slideren
    void IncrementDropdownIndex(); // Denne endrer på indeksen til dropDownListen sine options slik at piltastene kan bli brukt.
    void DecrementDropdownIndex(); // -//-
    void homeCallback(); // Denne endre på homeBool slik at vi viser home sjermen
    void tableCallback(); // motstatte som den over
    void SpinCallback(); // Denne spinner hjulet (Heftig funksjon)
    
    //Constructors
    GenreWindow();
}; 