/* search.c -- Fikri Enggaransyah ( Data & file Engineer) */
#include "search.h"
#include<ctype.h>
#include <stdlib.h>
#include <string.h>

int contains_ci (const char *hay, const char *needle)
{
    size_t ln = strlen(needle);
    if (ln == 0) return 1;
    for (; *hay; hay++){
        size_t i =0;
        while (i < ln && hay [1] &&
                tolower((unsigned char)hay[i]) == tolower((unsigned char)needle[i]))
            i++;
        if (i == ln) return 1;

    }
    return 0;
}

size_t search_record (const Database *db, SearchField field,
                        const char value, size_t **out_idx)
{
size_t count = 0;
*out_idx = NULL;
if (db->size == 0) return 0;

size_t *idx = malloc (db->size * sizeof(size_t));
if (!idx) return 0;

for (size_t i = 0; i < db->size; i++) {
    const char *target = (field == FIELD_NIM) ? db->data[i].nikm : db->data[i].nama;
    if (contains_ci(target, value)) idx[cout++] = i;
    
    }
    if (count == 0) { free(idx); return 0;}
    *out_idx =idx
    return count;
    
}.