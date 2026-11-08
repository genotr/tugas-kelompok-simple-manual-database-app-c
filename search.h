#ifndef SEARCH_H
#define SEARCH_H
#include "database.h"

typedef enum { FIELD_NIM, FIELD_NAMA } SearchField;

int  contains_ci(const char *hay, const char *needle);
size_t search_records(const Database *db, SearchField field,
                      const char *value, size_t **out_idx);

#endif
