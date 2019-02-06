#include "tetrisgenerators.hpp"
#include "tetristimer.hpp"
#include <stdlib.h>

#define FORMATS_QUANTITY 5

float getMinor(float red, float green, float blue)
{
    float minor_value = red;
    if(green < minor_value) minor_value = green;
    else if(blue < minor_value) minor_value = blue;
    return minor_value;
}

TetrisFormation *next_formation;
int last_select_formation;
TetrisFormation *generateFormation(TetrisMatrix *matrix, int x, int y)
{
    TetrisFormation *formation;
    bool first_generate = false;
    do
    {
        first_generate = (next_formation == nullptr);

        formation = next_formation;
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
                next_formation = new TFormation(matrix, x, y);
                break;
            }

            case 1:
            {
                next_formation = new LFormation(matrix, x, y);
                break;
            }

            case 2:
            {
                next_formation = new OFormation(matrix, x, y);
                break;
            }

            case 3:
            {
                next_formation = new _Formation(matrix, x, y);
                goto skip_rotations;
                break;
            }
            case 4:
            {
                next_formation = new SFormation(matrix, x, y);
                break;
            }
            default:
            {
                next_formation = new OFormation(matrix, x, y);
                break;
            }
        }

        next_formation->setColor(red, green, blue);


        for(int anticlockwiseRotations = rand() % 4; anticlockwiseRotations > 0; anticlockwiseRotations -= 1)
        {
            next_formation->anticlockwiseRotate();
        }
        if(rand() % 2) next_formation->invertX();
        if(rand() % 2) next_formation->invertY();

        skip_rotations:

        next_formation->allow_everything = false;

    }while (first_generate);

    return formation;
}

TetrisFormation *getNextFormation()
{
    return next_formation;
}
