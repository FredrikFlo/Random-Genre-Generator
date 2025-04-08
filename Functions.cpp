#include "Functions.h"


void Run()
{
    GenreWindow win{};
    double angleOffset = 0; 
    TDT4102::Point origin1 = {325, 300};
    TDT4102::Point origin2 = {windowWidth - origin1.x, origin1.y};
    
    while(!win.should_close())
    {
        if(!win.GetHomeBool())
        {
            win.DrawTable();
            win.DrawImage();
            win.UpdateDropDown();
            win.DrawRatingText();
            win.draw_text({1115, 620}, std::to_string((win.GetCount()+1)) + "/" + std::to_string(win.genreVector.size()));
            CheckKeys(win); // Sjekker om noen spesifikke keys er i bruk
            win.SetVisibility(true);
        }
        else
        {
            win.SetVisibility(false); //Set Visibility 
            angleOffset = FixDegrees(angleOffset); //For å holde angleOffset mellom 0 og 360
            win.DrawWheel(angleOffset, origin1, false);
            win.DrawWheel(angleOffset, origin2, true);
            win.draw_text({windowWidth/2 - 150, 650}, "PRESS 'SPACE' TO SPIN", TDT4102::Color::red, 30U, TDT4102::Font::arial_bold_italic);
            angleOffset -= 1; 
            if (win.is_key_down(KeyboardKey::SPACE))
            {
                win.SpinCallback();
            }
            if (win.is_key_down(KeyboardKey::ESCAPE))
            {
                win.tableCallback();
                Sleep(300);
            }
        }
        win.next_frame();
    }
    SaveToFile("GenreData.txt", win.genreVector);
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

void CheckKeys(GenreWindow &win)
{
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
    std::random_device rd;
    std::default_random_engine g(rd());
    std::uniform_real_distribution<double> distribution(lower, upper);

    return distribution(g);
}