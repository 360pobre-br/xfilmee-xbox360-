
#include "catalog.h"

const Movie movies[] = {
    {
        "FILME 01",
        "Descricao do primeiro filme",
        "ACAO"
    },
    {
        "FILME 02",
        "Descricao do segundo filme",
        "COMEDIA"
    },
    {
        "FILME 03",
        "Descricao do terceiro filme",
        "AVENTURA"
    },
    {
        "FILME 04",
        "Descricao do quarto filme",
        "DRAMA"
    },
    {
        "FILME 05",
        "Descricao do quinto filme",
        "ANIMACAO"
    },
    {
        "FILME 06",
        "Descricao do sexto filme",
        "FICCAO"
    }
};

const unsigned int movie_count =
    sizeof(movies) / sizeof(movies[0]);
