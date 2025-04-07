#include "GenreWindow.h"
#include "Functions.h"

void GenreWindow::DrawGenreCell(std::shared_ptr<Genre> genrePtr, const TDT4102::Point& position)
{
    //Tegne cellen til hvor navnet befinner seg
    this->draw_line({position.x, position.y}, {position.x + genreCellWidth, position.y});
    this->draw_line({position.x + genreCellWidth, position.y}, {position.x + genreCellWidth, position.y + CellHeight});
    this->draw_line({position.x + genreCellWidth, position.y + CellHeight}, {position.x, position.y + CellHeight});
    this->draw_line({position.x, position.y}, {position.x, position.y + CellHeight});

    //Tegne selve texten i den cellen
    this->draw_text({position.x, position.y}, genrePtr->GetName(), TDT4102::Color::black, 23, TDT4102::Font::arial_bold);

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
        if (cellCount == dropDownList.getIndex())
        {
           this->draw_triangle({tableCorner.x - 10, tableCorner.y + CellHeight*(cellCount + 1) + 2 + CellHeight / 2},
                               {tableCorner.x - 30, tableCorner.y + CellHeight*(cellCount + 1) + 2},
                               {tableCorner.x - 30, tableCorner.y + CellHeight*(cellCount + 2) + 2}, TDT4102::Color::red);
        }
        this->DrawGenreCell(std::static_pointer_cast<Genre>(sg), {tableCorner.x, tableCorner.y + CellHeight*(cellCount + 1) + 2});
        cellCount++;
    }
}

void GenreWindow::DrawImage()
{
    this->draw_image({650, 175}, images.at(count), 350, 350);
}

void GenreWindow::UpdateDropDown()
{
    dropDownList.setOptions(genreVector.at(count)->sgNames);
}

void GenreWindow::DrawRatingText()
{
    this->draw_text({650+5+buttonWidth, 600+10}, std::format("{:.1f}", slider.getValue() / 10.0), TDT4102::Color::black, 30U, TDT4102::Font::arial_bold);
}

void GenreWindow::SetVisibility(bool isTableVisible)
{
    int tempIndex = 0; 
    while(tempIndex < 8) // 8 er antall widgets i vanlig vinduet.
    {
        widgets.at(tempIndex).get().setVisible(isTableVisible);
        tempIndex++;
    }
    while(tempIndex < widgets.size())
    {
        widgets.at(tempIndex).get().setVisible(!isTableVisible);
        tempIndex++;
    }
}

std::string GenreWindow::DrawWheel(double angleOffset, TDT4102::Point origin, bool spinSubGenreWheel)
{
    // Regn ut antall subGenres (for weighting)
    int subGenreAmount = 0;
    double degrees = 0;
    double totalDegrees = 0;
    double startDegrees = 0; 
    double endDegrees = 0; 
    std::string winner;

    if (!spinSubGenreWheel)
    {
        for (auto genrePtr : genreVector)
        {
            subGenreAmount += genrePtr->subGenres.size();
        }
        
        //Tegn antall hjul med degrees
        for (int genreIndex = 0; genreIndex < genreVector.size(); genreIndex++)
        {   
            TDT4102::Color genreColor = intToColorMap[genreIndex % 5];
            degrees = genreVector.at(genreIndex)->subGenres.size() / double(subGenreAmount) * 360; // La til double for å sikre presisjon
            startDegrees = totalDegrees + angleOffset;
            endDegrees = totalDegrees + angleOffset + degrees;
            
            //Tegn ARC
            DrawArc(startDegrees, endDegrees, origin, genreColor, winner, genreIndex, spinSubGenreWheel);
            
            //Tegn Radiusene
            DrawRadii(origin, startDegrees, endDegrees);
            
            //Tegn Navnet
            draw_text({int(origin.x + 210 * std::cos(pi / 180 * (startDegrees + (endDegrees - startDegrees) / 2))), 
                int(origin.y - 210 * std::sin(pi / 180 * (startDegrees + (endDegrees - startDegrees) / 2))) - 10},
                genreVector.at(genreIndex)->GetName(), TDT4102::Color::black, 20U, TDT4102::Font::arial); 
            
            totalDegrees += degrees;
        } 
    }
    else if (spinSubGenreWheel)
    {
        int subGenreIndex = 0;
        for (auto subGenrePtr : genreVector.at(count)->subGenres)
        {
            // if (!subGenrePtr->HasRating())
            // {
            //     continue; 
            // }
            TDT4102::Color genreColor = intToColorMap[subGenreIndex % 5];
            degrees = 360 / double(genreVector.at(count)->subGenres.size());
            startDegrees = totalDegrees + angleOffset;
            endDegrees = totalDegrees + angleOffset + degrees;

            //Tegn ARC
            DrawArc(startDegrees, endDegrees, origin, genreColor, winner, subGenreIndex, spinSubGenreWheel);

            //Tegn Radiusene
            DrawRadii(origin, startDegrees, endDegrees);
            
            //Tegn Navnet
            draw_text({int(origin.x + 210 * std::cos(pi / 180 * (startDegrees + (endDegrees - startDegrees) / 2))), 
                int(origin.y - 210 * std::sin(pi / 180 * (startDegrees + (endDegrees - startDegrees) / 2))) - 10},
                subGenrePtr->GetName(), TDT4102::Color::black, 20U, TDT4102::Font::arial); 
        
            totalDegrees += degrees;
            subGenreIndex++; 
        }
    }
    // returner vinneren by name
    return winner;
}

void GenreWindow::DrawRadii(TDT4102::Point &origin, double startDegrees, double endDegrees)
{
    draw_line(origin, {int(origin.x + 200 * std::cos(pi / 180 * (startDegrees))), 
                       int(origin.y - 200 * std::sin(pi / 180 * (startDegrees)))});
    draw_line(origin, {int(origin.x + 200 * std::cos(pi / 180 * (endDegrees))), 
                       int(origin.y - 200 * std::sin(pi / 180 * (endDegrees)))});
}

void GenreWindow::DrawArc(double startDegrees, double endDegrees, const TDT4102::Point &origin, const TDT4102::Color &genreColor, std::string &winner, int genreIndex, bool spinSubGenre)
{
    if ((startDegrees < 360 && endDegrees < 360) || startDegrees >= 360 && endDegrees >= 360)
    {       
        draw_arc(origin, 200, 200, FixDegrees(startDegrees), FixDegrees(endDegrees), genreColor);
        draw_arc(origin, 210, 210, FixDegrees(startDegrees), FixDegrees(endDegrees), genreColor);
        draw_arc(origin, 205, 205, FixDegrees(startDegrees), FixDegrees(endDegrees), genreColor);
    }
    else if (endDegrees >= 360 && !spinSubGenre)
    {
        draw_arc(origin, 200, 200, 0, endDegrees - 360);
        draw_arc(origin, 200, 200, startDegrees, 360);
        winner = genreVector.at(genreIndex)->GetName();
        count = genreIndex;
    }
    else if (endDegrees >= 360 && spinSubGenre)
    {
        draw_arc(origin, 200, 200, 0, endDegrees - 360);
        draw_arc(origin, 200, 200, FixDegrees(startDegrees), 360);
        winner = genreVector.at(count)->subGenres.at(genreIndex)->GetName();
    }
}

//Functionality 
double FixDegrees(double angle)
{
    while(angle >= 360)
    {
        angle -= 360;
    }
    while(angle < 0)
    {
        angle += 360;
    }
    return angle;
}

//Callbacks ----------------------

void GenreWindow::DecrementCount()
{
    count--;
    if (count < 0)
    {
        count = genreVector.size() + count;
    }
    dropDownList.setSelectedIndex(0);
}

void GenreWindow::IncrementCount()
{
    count++; 
    if(count >= genreVector.size())
    {
        count = count - genreVector.size();
    }
    dropDownList.setSelectedIndex(0);
}

void GenreWindow::RateCallback()
{
    int index = stringToCountMapVector.at(count).at(dropDownList.getSelectedValue());
    double newSGRating = slider.getValue() / 10.0;
    genreVector.at(count)->subGenres.at(index)->SetSubGenreRating(newSGRating);
    slider.setValue(0); // Denne ble laget inne i Slider filen.
}

void GenreWindow::DecrementSlider()
{
    slider.setValue(slider.getValue()-1);
}

void GenreWindow::IncrementSlider()
{
    slider.setValue(slider.getValue()+1);
}

void GenreWindow::IncrementDropdownIndex()
{
    dropDownList.setSelectedIndex(dropDownList.getIndex() + 1);
}

void GenreWindow::DecrementDropdownIndex()
{
    dropDownList.setSelectedIndex(dropDownList.getIndex() - 1); 
}

void GenreWindow::homeCallback()
{
    SetHomeBool(true);
}

void GenreWindow::tableCallback()
{
    SetHomeBool(false);
}

void GenreWindow::SpinCallback()
{
    double angularVelocity = RandomDouble(4, 6);
    double acceleration = RandomDouble(0.01, 0.03);
    double angleOffset = RandomDouble(0, 360);
    double temp = 0; 

    std::string genreWinner;
    std::string subGenreWinner;

    while (angularVelocity >= 0)
    {
        angleOffset = FixDegrees(angleOffset);
        DrawWheel(angleOffset, origin1, false);
        angleOffset -= angularVelocity;
        angularVelocity -= acceleration;
        next_frame();
    } 

    genreWinner = DrawWheel(angleOffset, origin1, false);
    temp = angleOffset;
    
    angularVelocity = RandomDouble(4, 6);
    acceleration = RandomDouble(0.01, 0.03);
    angleOffset = RandomDouble(0, 360);
    
    while (angularVelocity >= 0)
    {
        angleOffset = FixDegrees(angleOffset);
        DrawWheel(temp, origin1, false);
        DrawWheel(angleOffset, origin2, true);
        angleOffset -= angularVelocity;
        angularVelocity -= acceleration;
        draw_text({origin1.x - 200, origin1.x + 200 + 20}, "Genre: " + genreWinner);
        next_frame();
    }

    DrawWheel(temp, origin1, false);
    subGenreWinner = DrawWheel(angleOffset, origin2, true);
    draw_text({origin1.x - 200, origin1.x + 200 + 20}, "Genre: " + genreWinner);
    draw_text({windowWidth - origin1.x - 200, origin1.x + 200 + 20}, "SubGenre: " + subGenreWinner);
    next_frame();
    Sleep(3000);
    
}

GenreWindow::GenreWindow() : TDT4102::AnimationWindow{100, 100, windowWidth, windowHeight, "Random Genre Generator"}, 
                             rateButton({650, 600}, buttonWidth, buttonHeight, "RATE"),
                             leftButton({25, 200}, pageButtonWidth, pageButtonHeight, "<"),
                             rightButton({windowWidth-25-pageButtonWidth, 200}, pageButtonWidth, pageButtonHeight, ">"),
                             homeButton({25, 25}, 100, 100, "HOME"),
                             dropDownList({650, 25}, dropDownWidth, dropDownHeight, vec),
                             slider({650, 570}, buttonWidth, 30, 0, 100, 0, 1),
                             plusButton({650 - 10 + buttonWidth+ 40, 570}, 50, 50, "+"),
                             minusButton({650 - 10 + buttonWidth, 570}, 50, 50, "-"),
                             tableButton({25, 25}, 100, 100, "TABLE"),
                             spinButton({windowWidth/2 - buttonWidth/2, 600}, buttonWidth, buttonHeight, "SPIN!")
{
    //Tabell widgets
    add(rateButton);
    add(leftButton);
    add(rightButton);
    add(homeButton);
    add(dropDownList);  
    add(slider);
    add(plusButton);
    add(minusButton); // 7

    //Home widgets
    add(tableButton);
    add(spinButton);

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

    //Callbacks table
    leftButton.setCallback(std::bind(&GenreWindow::DecrementCount, this));
    rightButton.setCallback(std::bind(&GenreWindow::IncrementCount, this));
    rateButton.setCallback(std::bind(&GenreWindow::RateCallback, this));
    plusButton.setCallback(std::bind(&GenreWindow::IncrementSlider, this));
    minusButton.setCallback(std::bind(&GenreWindow::DecrementSlider, this));
    homeButton.setCallback(std::bind(&GenreWindow::homeCallback, this)); 

    //Callbacks Home
    tableButton.setCallback(std::bind(&GenreWindow::tableCallback, this));
}