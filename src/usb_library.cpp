
#include "usb_library.h"

#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

static int equal_ci(const char *a, const char *b)
{
    while (*a && *b) {
        if (tolower((unsigned char)*a) !=
            tolower((unsigned char)*b))
            return 0;

        a++;
        b++;
    }

    return *a == *b;
}

static int is_video(const char *name)
{
    const char *ext = strrchr(name, '.');

    if (!ext)
        return 0;

    return equal_ci(ext, ".mp4") ||
           equal_ci(ext, ".avi") ||
           equal_ci(ext, ".mkv") ||
           equal_ci(ext, ".wmv") ||
           equal_ci(ext, ".mov");
}

int xfilmee_usb_scan(
    const char *directory,
    UsbMovie *output,
    size_t capacity
)
{
    if (!directory || !output || capacity == 0)
        return -1;

    DIR *dir = opendir(directory);

    if (!dir)
        return -1;

    size_t count = 0;
    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {

        if (!is_video(entry->d_name))
            continue;

        if (count >= capacity)
            break;

        UsbMovie *movie = &output[count];

        int n = snprintf(
            movie->path,
            sizeof(movie->path),
            "%s/%s",
            directory,
            entry->d_name
        );

        if (n < 0 || (size_t)n >= sizeof(movie->path))
            continue;

        struct stat info;

        if (stat(movie->path, &info) != 0 ||
            !S_ISREG(info.st_mode))
            continue;

        snprintf(
            movie->filename,
            sizeof(movie->filename),
            "%s",
            entry->d_name
        );

        snprintf(
            movie->title,
            sizeof(movie->title),
            "%s",
            entry->d_name
        );

        char *extension = strrchr(movie->title, '.');

        if (extension)
            *extension = '\0';

        for (char *p = movie->title; *p; p++) {
            if (*p == '_')
                *p = ' ';
        }

        char cover_name[256];

        snprintf(
            cover_name,
            sizeof(cover_name),
            "%s",
            movie->filename
        );

        char *cover_ext = strrchr(cover_name, '.');

        if (cover_ext)
            *cover_ext = '\0';

        snprintf(
            movie->cover_path,
            sizeof(movie->cover_path),
            "usb:/XFILMEE/CAPAS/%s.jpg",
            cover_name
        );

        count++;
    }

    closedir(dir);

    return (int)count;
}
