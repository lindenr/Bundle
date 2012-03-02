#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USAGE_STRING "Usage: bundle [-o output] files\n"

char HEX[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
void file_print(FILE *file, char *str)
{
    char local[4001] = {0,};
    int i, wh;
    for (i = 0, wh = 0; str[i]; ++ i, wh += 4)
    {
        local[wh]   = '\\';
        local[wh+1] = 'x';
        local[wh+2] = HEX[str[i] >> 4];
        local[wh+3] = HEX[str[i] & 15];
    }
    local[wh] = 0;
    fprintf(file, "%s", local);
}

int main(int argc, char *argv[])
{
    FILE *file, *input;
    char str[1001] = {0,}, buf[100], filename[256];
    char *file_arg;
    int i;
    if (argc < 2)
    {
        fprintf(stderr, USAGE_STRING);
        exit (0);
    }
    if (argc == 2)
    {
        file_arg = argv[1];
        input = fopen(file_arg, "r+");
        if (input == NULL)
        {
            fprintf(stderr, "Error: no such file %s\n", file_arg);
            fprintf(stderr, USAGE_STRING);
            exit (0);
        }
        sprintf(filename, "tmp.%s.c", file_arg);
        file = fopen(filename, "w+");
        fprintf(file, "extern char *%s;\n\nchar *%s = \"", file_arg, file_arg);
        while((i=fread(str, 1, 1000, input),i == 1000)) file_print(file, str);
        if (i)
        {
            str[i-1] = 0;
            file_print(file, str);
        }
        fprintf(file, "\";");
        //printf("str: %s\nfile_arg: %s\n", filename, file_arg);
        fclose(input);
        fclose(file);
        printf("Compiling...\n");
        sprintf(buf, "gcc -c %s -o %s.o", filename, file_arg);
        system(buf);
        printf("Done!\n");
        exit(0);
    }
}

