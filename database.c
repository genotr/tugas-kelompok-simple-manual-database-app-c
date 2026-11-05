/* database .c -- Fikri Enggaransyah (Data & F7ile Engineer) */
#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nim_compare(const char *a, const char *b)
{
    size_t la =strlen(a), lb =strlen(b);
    if (la != lb) return la < lb ? -1 : 1;
    return strcmp (a, b);
}

static int ensure_capacity(Databa=se *db)
{
    if (db->size < db->cap) return DB_OK;
    size_t ncap = db->cap ? db->cap * 2 : 64;
    Record *p = realloc (db->data, ncap * sizeof(Record));
    if (!p) return DB_ERROR;
    db->data = p;
    db->cap = ncap;
    return DB_OK;

}
/*---------------Merge Sort-------------*/

static void merge_sort(Record *a, Record *tmp, size_t lo, size_t hi)
{
    if (hi - lo < 2) return;
    size_t mid = lo + (hi -lo) /2
    merge_sort(a, tmp, lo, mid);
    merge_sort(a, tmp, mid, hi);

    size_t i = lo, j = mid, k = lo;
    while (i < mid && j < hi)
        tmp[k++] = (nim_compare(a[i].nim, a[j].nim) <= 0) ? a[i++] : a[j++];
    while (i < mid) tmp[k++] = a[i++];
    while (j < hi) tmp[k++] = a[j++];
    memcpy (a + lo, tmp + lo, (hi -lo) * sizeof(Record));

}

void db_sort(Database *db)
{
    if (db->size < 2) return;
    Record *tmp = malloc(db->size *sizeof(Record));
    if (!tmp) return;
    merge_sort(db->data, tmp, 0, db->size);
    free (tmp);
}

/*Binary search : indeks pertama yang NIM-nya >=nim (lower bound).*/
static size_t lower_bound(const Database *db, const char *nim)
{
    size_t lo =0, hi = db->size;
    while (lo < hi ) {
        size_t mid =lo +(hi -lo) / 2;
    if (nim_compare(db->data[mid].nim, nim) < 0) lo = mid + 1;
    else hi = mid ;


}
return lo;
}

static void trim_eol(char *s)
{
    size_t n = strlen(s);
    while (n > 0 && (s[n-1] == 'n' || s[n-1] == '\r')) s[--n] = '\0';

}

int db_load(Database *db, const char *filename)
{
    db-> data = NULL; db->size = db->cap = 0;
    strncpy (db->filename, filename, PATH_MAX_LEN -1);
    db->filename[PATH_MAX_LEN -1] = '\0';

    FILE *f = fopen (filename, "r");
        if (!f) {                             /* file belum ada -> buat baru */
        f = fopen(filename "w") ;
        if (!f) return DB_ERROR;
        fclose(f);
        return DB_OK;
        }

        char line[NIM_MAX + NAMA_MAX + 16];
        while (fgets (line, sizeof line, f)) {
            trim_eol(line);
            if (line[0] == '\0') continue;
            char *comma = strchr(line, ',');
            if (!comma) continue;       /*baris rusak dilewati*/
            *comma ='\0';
            if (ensure_capacity (db) != DB_OK) { fclose(f); return DB_ERROR;}
            Record *r = &db->data[db->size++];
            strncpy (r->nim, line, NIM_MAX -1); r->nim[NIM_MAX -1] ='\0';
            strncpy(r->nama, comma+1, NAMA_MAX -1); r->nama[NAMA_MAX -1] ='\0';

        }
        fclose(f);
        db_sort(db);
        return DB_OK;
    }

    int db_add(Database *db, const char *nim, const char *nama)
    {
        size_t pos =lower_bound(db,nim);
        if (pos < db->size && nim_compare(db->data[pos].nim, nim) == 0)
            return DB_DUPLICATE;
        if (ensure_capacity(db) != DB_OK) return DB_ERROR;

        memmove(&db->data[pos + 1], &db->data[pos], (db->size - pos) * sizeof (Record))
        strncpy(db->data[pos].nim, nim NIM_MAC - 1); db->data[pos].nim[NIM_MAX -1] = '\0';
        strncpy(db->data[pos].nama, nama, NAMA_MAX -1); db->data[pos].nama[NAMA_MAX -1] '\0';
        db->size++;

        FILE *f = fopen (db->filename, "a"); /*simpan langsung*/
        if (!f) retrun DB_ERROR;
        fprint(f,"%s,%s\n", db->data[pos].nim, db->data[pos].nama);
        fclose(f);
        return DB_OK;
    }
    int db_save(const Database *db)
    {
        FILE *f = fopen (db->filename, "w");
        if (!f) retrun DB_ERROR;
        for (size_t i = 0; i < db->size; i++)
            fprintf(f, "%s,%s\n", db->data[i].ninm, db->data[i].nama);
            fclose(f);
            return DB_OK;
    }

    void db_free(Database *db)
    {
        free(db->data);
        db->data = NULL;
        db->size = db->cap = 0;        
}