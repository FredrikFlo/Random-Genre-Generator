#include "GenreWindow.h"


void GenreWindow::DrawGenreCell(std::shared_ptr<Genre> genrePtr, const TDT4102::Point& position)
{
    //Tegne cellen til hvor navnet befinner seg
    this->draw_line({position.x, position.y}, {position.x + genreCellWidth, position.y});
    this->draw_line({position.x + genreCellWidth, position.y}, {position.x + genreCellWidth, position.y + CellHeight});
    this->draw_line({position.x + genreCellWidth, position.y + CellHeight}, {position.x, position.y + CellHeight});
    this->draw_line({position.x, position.y}, {position.x, position.y + CellHeight});

    //Tegne selve texten i den cellen
    this->draw_text({position.x, position.y}, genrePtr->GetName(), TDT4102::Color::black, 23, TDT4102::Font::arial_bold);

    //Ønsker å knytte en button til hver SubGenre i subGenres vektoren.


    //Tegne cellen til hvor ratingen befinner seg
    this->draw_line({position.x + genreCellWidth, position.y}, {position.x + genreCellWidth + ratingCellWidth, position.y});
    this->draw_line({position.x + genreCellWidth + ratingCellWidth, position.y}, {position.x + genreCellWidth + ratingCellWidth, position.y + CellHeight});
    this->draw_line({position.x + genreCellWidth + ratingCellWidth, position.y + CellHeight}, {position.x + genreCellWidth, position.y + CellHeight});
    this->draw_line({position.x + genreCellWidth, position.y}, {position.x + genreCellWidth, position.y + CellHeight});

    std::string temp = std::format("{:.1f}", genrePtr->GetRating()); //Konverterer double til en string
    //Tegne ratingen i den cellen
    this->draw_text({position.x + genreCellWidth, position.y}, temp, TDT4102::Color::black, 23, TDT4102::Font::arial);
}

void GenreWindow::DrawTable()
{
    genreVector.at(count)->SetGenreRating();
    this->DrawGenreCell(genreVector.at(count), tableCorner);

    int cellCount = 0;
    for(auto sg : genreVector.at(count)->subGenres)
    {
        // La til static_pointer_cast fordi det funket ikke ellers. Hvorfor? Vet ikke.
        this->DrawGenreCell(std::static_pointer_cast<Genre>(sg), {tableCorner.x, tableCorner.y + CellHeight*(cellCount + 1) + 2});
        cellCount++;
    }
}

void GenreWindow::DecrementCount()
{
    count--;
    if (count < 0)
    {
        count = genreVector.size() + count;
    }
}

void GenreWindow::IncrementCount()
{
    count++; 
    if(count >= genreVector.size())
    {
        count = count - genreVector.size();
    }
}

void GenreWindow::DrawImage()
{
    this->draw_image({650, 150}, images.at(count), 350, 350);
}

void GenreWindow::UpdateDropDown()
{
    dropDownList.setOptions(genreVector.at(count)->sgNames);
}

void GenreWindow::RateCallback()
{
    int index = stringToCountMapVector.at(count).at(dropDownList.getSelectedValue());
    try 
    {
        double newSGRating = std::stod(textInput.getText());
        genreVector.at(count)->subGenres.at(index)->SetSubGenreRating(newSGRating);
    }
    catch(std::invalid_argument& e)
    {
        // Kanskje vise en error på skjermen
    }
    textInput.setText("");
}

GenreWindow::GenreWindow() : TDT4102::AnimationWindow{100, 100, windowWidth, windowHeight, "Random Genre Generator"}, 
                             rateButton({630 + dropDownWidth/2 - buttonWidth/2, 600}, buttonWidth, buttonHeight, "RATE"),
                             leftButton({25, 200}, pageButtonWidth, pageButtonHeight, "<"),
                             rightButton({windowWidth-25-pageButtonWidth, 200}, pageButtonWidth, pageButtonHeight, ">"),
                             homeButton({25, 25}, 100, 100, "HOME"),
                             dropDownList({650, 25}, dropDownWidth, dropDownHeight, vec),
                             textInput({930, 610}, 80, 30, "") 
{
    add(rateButton);
    add(leftButton);
    add(rightButton);
    add(homeButton);
    add(dropDownList); 
    add(textInput); 

    for (auto g : genreVector)
    {
        //Lager en liste med bilder
        images.emplace_back(g->GetName() + ".jpg");

        //Lager en vector av flere maps for indexen til hver instanse av SubGenre
        std::map<std::string, int> tempMap;
        int subGenrePlacement = 0;

        for (auto sg : g->subGenres)
        {
            // map stuff
            tempMap[sg->GetName()] = subGenrePlacement;
            subGenrePlacement ++;
        }

        stringToCountMapVector.emplace_back(tempMap);
    }

    //Callbacks
    leftButton.setCallback(std::bind(&GenreWindow::DecrementCount, this));
    rightButton.setCallback(std::bind(&GenreWindow::IncrementCount, this));
    rateButton.setCallback(std::bind(&GenreWindow::RateCallback, this));
}