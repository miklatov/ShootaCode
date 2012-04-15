#include "Meter.h"

Meter::Meter(Ship* t_pTarget) : pTarget(t_pTarget)
{
    anchored = false;
}

bool Meter::update(sf::RenderWindow& win)
{
//    std::cout << "Updating meter" << std::endl;
    //check that target object exists
    if(pTarget==NULL)
    {
//        std::cout << "Meter target is null" << std::endl;
//        int dump;
//        std::cin >> dump;
        //mark for destruction in iteration
        return false;
    }
    else
    {
//        std::cout << "Meter target " << pTarget->id << " is ok" << std::endl;
//        int dump;
//        std::cin >> dump;
        if (!anchored)
        {
            //calculate barSize
            float propHealthLeft = float(pTarget->health) / float(pTarget->maxHealth);
            int barLength = propHealthLeft * dims.x;

            //create Rectangle
            sf::Color barCol(255 - 255* propHealthLeft,255*propHealthLeft,0);
            bar = sf::Shape::Rectangle(coords.x,coords.y, coords.x + barLength, coords.y + dims.y, barCol, 2, barCol);
        }
        else
        {
            float propHealthLeft = float(pTarget->health) / float(pTarget->maxHealth);
            int barLength = propHealthLeft * pTarget->dims.x;

            //create Rectangle
            sf::Color barCol(255 - 255* propHealthLeft,255*propHealthLeft,0);
            bar = sf::Shape::Rectangle(pTarget->coords.x,pTarget->coords.y+pTarget->dims.y*0.9, pTarget->coords.x  + barLength, pTarget->coords.y + pTarget->dims.y * 0.91, barCol, 1, barCol);
        }



        //draw bar
        win.Draw(bar);

        return true;
    }
}
