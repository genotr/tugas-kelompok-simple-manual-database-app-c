#ifndef DATABASE_H
#define DATABASE_H

#include <stddef.h>

#define NIM_MAX   32
#define NAMA_MAX  128
#define PATH_MAX_LEN 260

typedef struct {
    char nim[NIM_MAX];
    char nama[NAMA_MAX];
} Record;

typedef struct {
    Record *data;
    size_t  size;
    size_t  cap;
    char    filename[PATH_MAX_LEN];
} Database;

#define DB_OK         0
#define DB_DUPLICATE  1
#define DB_ERROR     -1

int  db_load(Database *db, const char *filename);
int  db_add(Database *db, const char *nim, const char *nama);
int  db_save(const Database *db);
void db_free(Database *db);
void db_sort(Database *db);
int  nim_compare(const char *a, const char *b);

#endif
