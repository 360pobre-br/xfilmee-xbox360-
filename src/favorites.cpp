
#include "favorites.h"

#define MAX_FAVORITES 100

static unsigned char favorites[MAX_FAVORITES];

void favorite_toggle(unsigned int index)
{
    if (index >= MAX_FAVORITES)
        return;

    favorites[index] = !favorites[index];
}

int favorite_is_active(unsigned int index)
{
    if (index >= MAX_FAVORITES)
        return 0;

    return favorites[index] != 0;
}
