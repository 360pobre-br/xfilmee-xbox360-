
#include "catalog.h"

const Movie movies[] = {
    {"Filme 01", "Descricao do primeiro filme", "Acao"},
    {"Filme 02", "Descricao do segundo filme", "Comedia"},
    {"Filme 03", "Descricao do terceiro filme", "Aventura"},
    {"Filme 04", "Descricao do quarto filme", "Drama"},
    {"Filme 05", "Descricao do quinto filme", "Animacao"}
};

const unsigned int movie_count =
    sizeof(movies) / sizeof(movies[0]);
