#include "Functions.h"


void Run()
{
    GenreWindow win{}; //Lager en instanse av GenreWindow med default konstruktøren
    double angleOffset = 0; //Dette er vinkelen som alle punktene i hjulet vil være forskyvet
    TDT4102::Point origin1 = {325, 300}; // Dette er origo i det ene hjulet
    TDT4102::Point origin2 = {windowWidth - origin1.x, origin1.y}; //Dette er origo i det andre hjulet
    
    while(!win.should_close())
    {
        if(!win.GetHomeBool()) // Denne situasjonen gjelder for når vi ønsker å vise tabellen
        {
            win.DrawTableOverflow(); // Denne funksjonen tegner hele tabellen for den Genre som gjelder
            win.DrawImage(); // Denne funksjonen tegner bilde til den Genre som gjelder 
            win.UpdateDropDown(); // Denne funksjon oppdateter dropdownlisten til å inneholdet navnet på SubGenre til den Genre som gjelder
            win.DrawRatingText(); // Denne funksjon tegner verdien til slideren
            win.draw_text({1115, 620}, std::to_string((win.GetCount()+1)) + "/" + std::to_string(win.genreVector.size())); // Denne funksjonen tegner sidetall
            CheckKeys(win); // Sjekker om noen spesifikke keys er i bruk
            win.SetVisibility(true); //Denne setter visibility av de knappene som tilsvarer tabell siden til true
        }
        else
        {
            win.SetVisibility(false); // Denne setter visiblity av de knappen som tilsvarer hjul sjermen til false
            angleOffset = FixDegrees(angleOffset); //For å holde angleOffset mellom 0 og 360 sånn at den ikke blir utrolig stor å gjøre programmet tregere (Grunne ser du i logikken til DrawWheel)
            win.DrawWheel(angleOffset, origin1, false); // Tegner det første hjulet som gjelder alle sjangerene med den riktige origoen og forskyvningen
            win.DrawWheel(angleOffset, origin2, true); // Tegner det andre hjulet som gjelder alle under sjangere
            win.draw_text({windowWidth/2 - 150, 650}, "PRESS 'SPACE' TO SPIN", TDT4102::Color::red, 30U, TDT4102::Font::arial_bold_italic); // Tegner teksten
            angleOffset -= 1; // Dekrementerer angleOffset for hver iterasjon slik at hjulet spinner som en animasjon
            if (win.is_key_down(KeyboardKey::SPACE)) // Sjekker om hjulet skal spinne for ny sjanger
            {
                win.SpinCallback();
            }
            if (win.is_key_down(KeyboardKey::ESCAPE)) // Sjekker om den skal bytte til tabell sjermen
            {
                win.tableCallback();
                Sleep(300);
            }
        }
        SaveToFile("GenreData.txt", win.genreVector); // Lagrer ratingen osv underveis.
        win.next_frame();
    }
}

//Functionality 
double FixDegrees(double angle)
{
    while(angle >= 360) // Dersom vinkelen er større enn 360 trekker den fra 360 helt til den ikke er større en 360 lenger
    {
        angle -= 360;
    }
    while(angle < 0) // Dersom vinkelen er mindre enn 360 plusser den på 360 helt til den er større en 0. 
    {
        angle += 360;
    }
    return angle;
}

void CheckKeys(GenreWindow &win)
{
    // denne sier litt seg selv. Alle funksjonene under er definert og diskutert i GenreWindow.cpp og GenreWindow.h
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
    if (win.is_key_down(KeyboardKey::ESCAPE))
    {
        win.homeCallback();
        Sleep(300);
    }
    if (win.is_key_down(KeyboardKey::SPACE))
    {
        win.RateCallback();
        Sleep(300);
    }
}

double RandomDouble(double lower, double upper)
{
    // Sånn er syntaxen det får jeg ikke gjort noe med.
    std::random_device rd;
    std::default_random_engine g(rd());
    std::uniform_real_distribution<double> distribution(lower, upper);

    return distribution(g);
}