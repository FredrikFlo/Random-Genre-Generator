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
            //Set Visibility 
            win.SetVisibility(false);
            angleOffset = FixDegrees(angleOffset); //For å holde angleOffset mellom 0 og 360
            win.DrawWheel(angleOffset, origin1, false);
            win.DrawWheel(angleOffset, origin2, true);
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
}

double RandomDouble(double lower, double upper)
{
    std::random_device rd;
    std::default_random_engine g(rd());
    std::uniform_real_distribution<double> distribution(lower, upper);

    return distribution(g);
}