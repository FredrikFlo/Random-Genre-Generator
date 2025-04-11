#include "GenreWindow.h"
#include "Functions.h"

int GenreWindow::GetTotalUnrated() const
{
    int amount = 0;
    for(auto genrePtr : genreVector)
    {
        amount += genrePtr->GetUnratedSG(); // Antall unrated i genre og plusser dem sammen 
    }
    return amount; 
}

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
    // tenger ratingen som en tekst
}

void GenreWindow::DrawTableOverflow()
{
    genreVector.at(count)->SetGenreRating(); // Oppdaterer ratingen vi har blitt gitt
    this->DrawGenreCell(genreVector.at(count), tableCorner); // tegner hoved sjangeren sin cellet

    int cellCount = 0; // holder orden på hvilken cellet vi undersøker (IKKE lik indeksen til en vektor)
    for(int indexCount = 0; indexCount < genreVector.at(count)->subGenres.size(); indexCount++)
    {
        if (indexCount <= tableOverflowCount * 19 - 1 || indexCount > (tableOverflowCount + 1) * 19 - 1) // lager bare 19 celler
        {
            continue;
        }

        if (cellCount == dropDownList.getIndex()) // sjekker om cellCount er lik den riktig dropDownList indeksen
        {
            this->draw_triangle({tableCorner.x - 10, tableCorner.y + CellHeight*(cellCount + 1) + 2 + CellHeight / 2},
            {tableCorner.x - 30, tableCorner.y + CellHeight*(cellCount + 1) + 2},
            {tableCorner.x - 30, tableCorner.y + CellHeight*(cellCount + 2) + 2}, TDT4102::Color::red); // Tegner trekanten som peker på riktig boks
        }

        this->DrawGenreCell(std::static_pointer_cast<Genre>(genreVector.at(count)->subGenres.at(indexCount)), // tegner cellen
                            {tableCorner.x, tableCorner.y + CellHeight*(cellCount + 1) + 2}); 
        cellCount++; // går til neste cellet
    }
}

void GenreWindow::DrawImage()
{
    this->draw_image({650, 175}, images.at(count), 350, 350); // forklart i header filen .
}

void GenreWindow::UpdateDropDown()
{
    dropDownList.setOptions(genreVector.at(count)->sgNames); // forklart i header filen. 
}

void GenreWindow::DrawRatingText()
{
    this->draw_text({650+5+buttonWidth, 600+10}, std::format("{:.1f}", slider.getValue() / 10.0), TDT4102::Color::black, 30U, TDT4102::Font::arial_bold); 
    // forklart i header filen.
}

void GenreWindow::SetVisibility(bool isTableVisible)
{
    int tempIndex = 0; 
    while(tempIndex < 8) // 8 er antall widgets i vanlig vinduet.
    {
        widgets.at(tempIndex).get().setVisible(isTableVisible); // setter de widgetsene til visible
        tempIndex++;
    }
    while(tempIndex < widgets.size())
    {
        widgets.at(tempIndex).get().setVisible(!isTableVisible); // Setter de widgetsene til invisible
        tempIndex++;
    }
}


// WHEELL
std::string GenreWindow::DrawWheel(double angleOffset, TDT4102::Point origin, bool spinSubGenreWheel)
{
    // Regn ut antall subGenres (for weighting)
    int subGenreAmount = 0;
    double degrees = 0;
    double totalDegrees = 0;
    double startDegrees = 0; 
    double endDegrees = 0; 
    std::string winner;

    if (!spinSubGenreWheel) // Sjekker om den skal spinne genre hjulet
    // Her er egentlig koden i denne if setningen helt lik den under 
    {
        //Tegn antall hjul med degrees
        for (int genreIndex = 0; genreIndex < genreVector.size(); genreIndex++) // itererer over alle sjangeren og deres indexer
        {   
            if(GetTotalUnrated() == 0) // hvis det ingen ratinger og gi så for du en tekst og funksjonen gjør ingenting pga return setningen
            {
                draw_text({windowWidth/2 , windowHeight/2}, "No more genres to rate :(", TDT4102::Color::red, 30U, TDT4102::Font::arial_bold_italic);
                return ""; 
            }
            if(genreVector.at(genreIndex)->GetUnratedSG() == 0) // hvis den ene Genre har ingen ratinger så ønsker vi hoppe til neste sjanger
            {
                continue;
            }
            TDT4102::Color genreColor = intToColorMap[genreIndex % 5]; // tar indeksen å gir den en av de 5 fargene i mappen
            degrees = genreVector.at(genreIndex)->GetUnratedSG() / double(GetTotalUnrated()) * 360; // La til double for å sikre presisjon
            // den regner også ut degrees som skal være størrelsen på alle sektorene til denne ratingen basert på forholdet mellom antall unrated SubGenre i denne Genre til den totale summen
            startDegrees = totalDegrees + angleOffset;
            endDegrees = totalDegrees + angleOffset + degrees;
            
            DrawArc(startDegrees, endDegrees, origin, genreColor, winner, genreIndex, spinSubGenreWheel); //Tegn ARC
            DrawRadii(origin, startDegrees, endDegrees); //Tegn Radiusene
            draw_text({int(origin.x + 210 * std::cos(pi / 180 * (startDegrees + (endDegrees - startDegrees) / 2))),  //Tegn Navnet
                int(origin.y - 210 * std::sin(pi / 180 * (startDegrees + (endDegrees - startDegrees) / 2))) - 10},
                genreVector.at(genreIndex)->GetName(), TDT4102::Color::black, 20U, TDT4102::Font::arial); 
            draw_triangle({origin.x + 190, origin.y},
                          {origin.x + 190 + 30, origin.y + 5},
                          {origin.x + 190 + 30, origin.y - 5}, TDT4102::Color::red); //Tegner pekeren som peker på riktig skive av hjulet
            
            totalDegrees += degrees;
        } 
    }
    else if (spinSubGenreWheel)
    {
        int subGenreIndex = 0;
        for (auto subGenrePtr : genreVector.at(count)->subGenres)
        {
            if (subGenrePtr->HasRating())
            {
                continue; 
            }
            TDT4102::Color genreColor = intToColorMap[subGenreIndex % 5];
            degrees = 360 / double(genreVector.at(count)->GetUnratedSG());
            startDegrees = totalDegrees + angleOffset;
            endDegrees = totalDegrees + angleOffset + degrees;

            DrawArc(startDegrees, endDegrees, origin, genreColor, winner, subGenreIndex, spinSubGenreWheel);  //Tegn Radiusene
            DrawRadii(origin, startDegrees, endDegrees); //Tegn Radiusene
            draw_text({int(origin.x + 210 * std::cos(pi / 180 * (startDegrees + (endDegrees - startDegrees) / 2))), 
                int(origin.y - 210 * std::sin(pi / 180 * (startDegrees + (endDegrees - startDegrees) / 2))) - 10},
                subGenrePtr->GetName(), TDT4102::Color::black, 20U, TDT4102::Font::arial); //Tegn Navnet 
            draw_triangle({origin.x + 190, origin.y},
                          {origin.x + 190 + 30, origin.y + 5},
                          {origin.x + 190 + 30, origin.y - 5}, TDT4102::Color::red);
        
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
                       int(origin.y - 200 * std::sin(pi / 180 * (startDegrees)))}); // tegner en strek til en startDegree men radius lik 200 pixel
    draw_line(origin, {int(origin.x + 200 * std::cos(pi / 180 * (endDegrees))), 
                       int(origin.y - 200 * std::sin(pi / 180 * (endDegrees)))}); // samme men med endDegree
}

void GenreWindow::DrawArc(double startDegrees, double endDegrees, const TDT4102::Point &origin, const TDT4102::Color &genreColor, std::string &winner, int genreIndex, bool spinSubGenre)
{
    if ((startDegrees < 360 && endDegrees < 360) || startDegrees >= 360 && endDegrees >= 360) 
    // hvis start degree og end degree er enten begge større enn eller begge mindre enn360, så blir FixDegrees kalt på begge inngang parameterene.
    {       
        draw_arc(origin, 200, 200, FixDegrees(startDegrees), FixDegrees(endDegrees), genreColor);
        draw_arc(origin, 210, 210, FixDegrees(startDegrees), FixDegrees(endDegrees), genreColor);
        draw_arc(origin, 205, 205, FixDegrees(startDegrees), FixDegrees(endDegrees), genreColor);
        // her hadde det vært et problem siden vi trekker angleOffset, men det er ikke det siden vi bruker FixDegrees til å få det positivt (ikke tenk på dette vis du ikke må)
    }
    else if (endDegrees >= 360 && !spinSubGenre) // Dersom kun endDegrees er større og vi spinner et Genre hjul
    {
        draw_arc(origin, 200, 200, 0, endDegrees - 360); // tenge en bue fra 0 til endDegrees - 360
        draw_arc(origin, 200, 200, startDegrees, 360); // tegne en bue fra startDegree antageligvis mindre en 360 dersom den fail på tidligere if
        // må gjøre dette fordi draw_arc er bygget opp på et litt ufin måte
        winner = genreVector.at(genreIndex)->GetName(); // returner winneren dersom den faller i denne katergorien (dette er den eneste forskjellen far den under)
    }
    else if (endDegrees >= 360 && spinSubGenre)
    {
        draw_arc(origin, 200, 200, 0, endDegrees - 360);
        draw_arc(origin, 200, 200, FixDegrees(startDegrees), 360);
        winner = genreVector.at(count)->subGenres.at(genreIndex)->GetName();
    }
}

//Callbacks ----------------------

void GenreWindow::DecrementCount()
{
    if (tableOverflowCount > 0) // hvis vi er i en del tabbel av en sjanger så ønsker vi å gå til den tidligere del tabellen.
    {
        tableOverflowCount--;
    }
    else 
    { 
        int tableOverflowNextValue = 0;
        if (count - 1 < 0)
        {
            count = genreVector.size() - count - 1; //sørger for at count ikke blir mindre en null
        }
        else
        {
            count--;
        }
        while(genreVector.at(count)->subGenres.size() > 19 * (tableOverflowNextValue + 1))
        {
            tableOverflowNextValue ++; // viser den siste siden i den sjangeren
        }
        dropDownList.setSelectedIndex(0); // reseter dropDownList sin indeks for å ikke få out of range errors
        tableOverflowCount = tableOverflowNextValue; 
    }
}

void GenreWindow::IncrementCount()
{  
    if (genreVector.at(count)->subGenres.size() > 19 * (1 + tableOverflowCount)) // Sjekker om vektoren har overFlow og inkrementerer overflow i steden for count
    {
        tableOverflowCount++;
    }
    else 
    {
        count++;
        if (count >= genreVector.size())
        {
            count = count - genreVector.size();  //sørger for at count ikke blir mindre en null
        }
        dropDownList.setSelectedIndex(0); // reseter dropDownList sin indeks for å ikke få out of range errors
        tableOverflowCount = 0; // reseter overflow count
    }
}

void GenreWindow::RateCallback()
{
    int index = stringToCountMapVector.at(count).at(dropDownList.getSelectedValue()); // indexen er like indeksen som tilsvarer navne i dropDownListen
    double newSGRating = slider.getValue() / 10.0; // tilordner SubGenre sin rating lik slider.getValue() delt på 10.0.
    // den er delt på 10.0 slik at vi får en double ut. 
    // den er delt på 10 siden slider går fra 0 til 100 fordi det er sånn den er definert
    genreVector.at(count)->subGenres.at(index)->SetSubGenreRating(newSGRating); 
    slider.setValue(0); // Resetter slideren fordi det virker greit
}

void GenreWindow::DecrementSlider()
{
    slider.setValue(slider.getValue()-1); // senker slideren med 0.1 (100 -1 )/10 = 9.9 
}

void GenreWindow::IncrementSlider()
{
    slider.setValue(slider.getValue()+1); // øker slideren med 0.1
}

void GenreWindow::IncrementDropdownIndex()
{
    dropDownList.setSelectedIndex(dropDownList.getIndex() + 1); // Øker dropDownIndexen 
}

void GenreWindow::DecrementDropdownIndex()
{
    dropDownList.setSelectedIndex(dropDownList.getIndex() - 1);  // Sneker DropDownIndexen
}

void GenreWindow::homeCallback()
{
    SetHomeBool(true);
    Sleep(100);
}

void GenreWindow::tableCallback()
{
    SetHomeBool(false);
    Sleep(100);
    dropDownList.setSelectedIndex(0);
}

void GenreWindow::SpinCallback()
{
    double angularVelocity = RandomDouble(4, 6); // gir en tilfeldig start fart
    double acceleration = RandomDouble(0.01, 0.03); // gir en tilfeldig accelration
    double angleOffset = RandomDouble(0, 360); // gir en tilfeldig vinkel forskyvning
    // måten diss verdiene funker på er at angleOffset blir sendt inn i funksjonen slik at hjulet blir plottet med en angle offset faseforskyvning
    // Da blir angularVelocity trukket far angleOffset som for hver frame vil se ut som om den beveger seg litt og litt
    // Senere bli aksjelerasjonen trukket fra angularVelocity slik at avstanden / vinkelen den endres med endres hver frame 
    // til slutt blir faseforskyvningen et tall som ikke endres noe mer (angularVelocity). Da begynner man på neste hjule
    double temp = 0; 

    std::string genreWinner;
    std::string subGenreWinner;

    while (angularVelocity >= 0)
    {
        angleOffset = FixDegrees(angleOffset); // sørger for at angleOffset er mellom 0 og 360
        DrawWheel(angleOffset, origin1, false); // tegner hjulet for disse parameterene hvor false betyr at den tegner Genrene
        angleOffset -= angularVelocity; 
        angularVelocity -= acceleration;
        next_frame();
    } 

    genreWinner = DrawWheel(angleOffset, origin1, false); 
    // når hjulet har stoppet så blir retur verdien til DrawWheel den sektoren som har landet randomiseren har landet på
    // navnet til denn blir lik genreWinner
    
    count = stringToGenreCountMap[genreWinner]; // finner count til genreWinner
    temp = angleOffset; // Setter den tidligere angleOffseten til temp og så gir det nye tilfeldige verdier. 
    angularVelocity = RandomDouble(4, 6);
    acceleration = RandomDouble(0.01, 0.03);
    angleOffset = RandomDouble(0, 360);
    
    while (angularVelocity >= 0)
    {
        angleOffset = FixDegrees(angleOffset); // samme som før
        DrawWheel(temp, origin1, false); // denne tegner hjulet som har stoppet fra den tidligere loopen
        DrawWheel(angleOffset, origin2, true); // denne tegner det nye hjulet med en ny fart osv.
        angleOffset -= angularVelocity;
        angularVelocity -= acceleration;
        draw_text({origin1.x - 200, origin1.x + 200 + 20}, "Genre: " + genreWinner); // her skriver vi ut den Genre winneren fra tidligere loopen
        next_frame();
    }

    DrawWheel(temp, origin1, false); 
    subGenreWinner = DrawWheel(angleOffset, origin2, true);
    draw_text({origin1.x - 200, origin1.x + 200 + 20}, "Genre: " + genreWinner);
    draw_text({windowWidth - origin1.x - 200, origin1.x + 200 + 20}, "SubGenre: " + subGenreWinner); // tegner vinneren til SubGenre hjulet
    next_frame();
    Sleep(3000); // venter 3 sekunder før sjermen endres
}

GenreWindow::GenreWindow() : TDT4102::AnimationWindow{100, 100, windowWidth, windowHeight, "Random Genre Generator"}, // Caller AnimationWindow sin konstruktør 
                             rateButton({650, 600}, buttonWidth, buttonHeight, "RATE"),
                             leftButton({25, 200}, pageButtonWidth, pageButtonHeight, "<"),
                             rightButton({windowWidth-25-pageButtonWidth, 200}, pageButtonWidth, pageButtonHeight, ">"),
                             homeButton({25, 25}, 100, 100, "HOME"),
                             dropDownList({650, 25}, dropDownWidth, dropDownHeight, vec), // lager en dropDown initialisert med noen vilkårlig verdier i en vektor.
                             slider({650, 570}, buttonWidth, 30, 0, 100, 0, 1), // lager en slider fra 0 til 100
                             plusButton({650 - 10 + buttonWidth+ 40, 570}, 50, 50, "+"),
                             minusButton({650 - 10 + buttonWidth, 570}, 50, 50, "-"),
                             tableButton({25, 25}, 100, 100, "TABLE")
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

    int genrePlacement = 0; // denne tilsvarer indeksen til sjangeren i hensyn til hvor de er plassert i ulike vektorer
    for (auto g : genreVector)
    {
        //Lager en liste med bilder for hver sjanger
        images.emplace_back(g->GetName() + ".jpg"); // her blir det utnyttet at bildene er på den riktige formen

        //Lager en map fra navne til en hoved sjanger til indeksen
        stringToGenreCountMap[g->GetName()] = genrePlacement;
        genrePlacement++; 

        //Lager en vector av flere maps for indexen til hver instanse av SubGenre
        std::map<std::string, int> tempMap;
        int subGenrePlacement = 0; // samme logikk som genrePlacement bare for subGenrePlacement

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