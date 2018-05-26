#include "tetrisgenerators.hpp"
#include "tetristimer.hpp"
#include <stdlib.h>

#define FORMATS_QUANTITY 4

float getMinor(float red, float green, float blue)
{
    float minor_value = red;
    if(green < minor_value) minor_value = green;
    else if(blue < minor_value) minor_value = blue;
    return minor_value;
}

int last_select_formation;
TetrisFormation *generateFormation(TetrisMatrix *matrix, int x, int y)
{
    TetrisFormation *formation = nullptr;

    float red, green, blue, brightness, saturation;
    do
    {
        srand(TetrisTimer::getSystemUseconds());
        red = (float)(rand() % 10)/10;
        green = (float)(rand() % 10)/10;
        blue = (float)(rand() % 10)/10;
        brightness = (red + blue + green)/3;
        if(brightness == 0) saturation = 0;
        else saturation = 1 - ( getMinor(red,green,blue)/brightness );
    }while ( brightness < 0.5 || saturation < 0.5); //color must have saturation and brightness greater than 0.5

    int select_formation;
    do
    {
        select_formation = (rand() % FORMATS_QUANTITY);
    }while (select_formation == last_select_formation);  //the new formation can not be equal to the previous one
    last_select_formation = select_formation;

    switch (select_formation)
    {
        case 0:
        {
            formation = new TFormation(matrix, x, y);
            break;
        }

        case 1:
        {
            formation = new LFormation(matrix, x, y);
            break;
        }

        case 2:
        {
            formation = new OFormation(matrix, x, y);
            break;
        }

        case 3:
        {
            formation = new _Formation(matrix, x, y);
            break;
        }

        default:
        {
            formation = new OFormation(matrix, x, y);
            break;
        }
    }

    formation->setColor(red, green, blue);

    return formation;
}
