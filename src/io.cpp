#include "include/io.hpp"
#include <cstdlib>
#include <cstdio>

char* get_file_contents(const char* filepath)
{
    char* buffer = 0;
    long length;
    FILE* f = fopen(filepath, "rb");

    if (f)
    {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = (char*)calloc(length, length);  // same as C
        if (buffer)
            fread(buffer, 1, length, f);
        fclose(f);
        return buffer;
    }

    printf("Error reading file %s\n", filepath);
    exit(2);
}
