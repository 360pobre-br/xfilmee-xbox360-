
#include "search.h"
#include <cstring>
#include <cctype>

int search_movie(const char *query)
{
    if (!query || !query[0])
        return -1;

    for (unsigned int i = 0; i < movie_count; i++) {
        const char *title = movies[i].title;

        if (strlen(title) < strlen(query))
            continue;

        bool found = false;

        for (size_t j = 0;
             title[j] && !found; j++) {

            size_t k = 0;

            while (query[k] && title[j + k] &&
                   tolower((unsigned char)title[j + k]) ==
                   tolower((unsigned char)query[k])) {
                k++;
            }

            if (!query[k]) {
                found = true;
            }
        }

        if (found)
            return (int)i;
    }

    return -1;
}
