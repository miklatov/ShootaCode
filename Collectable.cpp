#include "Collectable.h"

Collectable::Collectable(DataBank* t_pData) : GameObject(t_pData)
{
    //add type
    type+=ClassType::Collectable;
}
