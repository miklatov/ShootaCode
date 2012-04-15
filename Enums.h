#ifndef ENUMS_H_INCLUDED
#define ENUMS_H_INCLUDED

namespace ClassType
{
    enum
    {
        Entity      = 1,
        GameObject  = 2,
        Projectile  = 4,
        Ship        = 8,
        Enemy       = 16,
        Player      = 32,
        Collectable = 64
    };
}

//namespace GameState
//{
//    enum
//    {
//        Play        =1,
//        Pause       =2,
//        StatScreen  =3
//    };
//}
#endif // ENUMS_H_INCLUDED
