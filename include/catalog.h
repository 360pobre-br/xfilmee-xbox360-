
#ifndef XFILMEE_CATALOG_H
#define XFILMEE_CATALOG_H

typedef struct {
    const char* title;
    const char* description;
    const char* category;
} Movie;

extern const Movie movies[];
extern const unsigned int movie_count;

#endif
