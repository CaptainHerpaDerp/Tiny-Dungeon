#include "MoveEffects.h"

MoveEffects& MoveEffects::Get()
{
    static MoveEffects me;
    return me;
}

MoveEffects::MoveEffects()
{
    cout << "loaded MoveEffects" << endl;
}

