#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <err.h>

#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

size_t strlen_utf(char* s)
{
    size_t i = 0;
    size_t nb_utf_8 = 0;
    while (s[i] != '\0')
    {
        if (s[i] < 0 || s[i] > 127)
        {
            nb_utf_8++;
        }
        i++;
    }

    return i - nb_utf_8 / 2;
}

int levenshtein(char *s1, char *s2) {
    unsigned int s1len, s2len, x, y, lastdiag, olddiag;
    s1len = strlen_utf(s1);
    s2len = strlen_utf(s2);
    unsigned int column[s1len + 1];
    for (y = 1; y <= s1len; y++)
        column[y] = y;
    for (x = 1; x <= s2len; x++) {
        column[0] = x;
        for (y = 1, lastdiag = x - 1; y <= s1len; y++) {
            olddiag = column[y];
            column[y] = MIN3(column[y] + 1, column[y - 1] + 1, lastdiag + (s1[y-1] == s2[x - 1] ? 0 : 1));
            lastdiag = olddiag;
        }
    }
    return column[s1len];
}

int distance(int a, int b)
{
    return abs(a-b);
}

void clean_string(char* s)
{
    char *pos;
    if ((pos=strchr(s, '\n')) != NULL)
        *pos = '\0';
    else
        errx(1,"Unexpected error");
}

char* correct_word(char* word)
{
    FILE * database = fopen("mot_francais.txt", "r");
    if (database == NULL)
        errx("1","File not found !");
    char* line = NULL;
    size_t len = 0;
    size_t size_res_string;
    size_t size_word = strlen_utf(word);
    size_t size_corrected_word = INT_MAX;

    int min_levenshtein = INT_MAX;
    int res_levenshtein;

    char *corrected_word = NULL;

    while ((getline(&line, &len, database)) != -1)
    {
        clean_string(line);
        res_levenshtein = levenshtein(word, line);
        size_res_string = strlen_utf(line);

        if (res_levenshtein < min_levenshtein || res_levenshtein == min_levenshtein &&
        distance(size_res_string,size_word) < distance(size_corrected_word,size_word))
        {
            min_levenshtein = res_levenshtein;
            if (corrected_word != NULL)
                free(corrected_word);
            corrected_word = malloc((size_res_string + 1)* sizeof(char) );
            strcpy(corrected_word, line);
            size_corrected_word = strlen_utf(corrected_word);
        }
    }

    free(line);
    fclose(database);
    return corrected_word;
}




