/* command.c -- Rezza Firnando (command & Search Engineer)*/

#include "command.h"
#include "search.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LINE_MAX_LEN 512

/*--- helper parsing ---*/
static char *skip_spaces(char *s) {while (*s && isspace((unsigned char)*s)) s++; return s; }

static void rtrim(char *s) {
    size_t n= strlen(s);
    while (n > 0 && isspace ((unsigned char)s[n-1])) s[--n] = '\0';
}

/*--- yang ambil satu token dari *p, lalu geser *p ke sisa string. ---*/
static char *next_token(char **p) {
    char *s = skip_spaces(*p);
    if (!*s) { *p = s; return NULL; }
    char *start = s;
    while (*s && !isspace((unsigned char)*s)) s++;
    if (*s) *s++ = '\0';
    *p = skip_spaces(s);
    return start;
}

static int all_digits(const char *s) {
    if (!*s) return 0;
    for (; *s; s++) if (!isdigit((unsigned char)*s)) return 0;
    return 1;
}

static int has_letter(const char *s) {
    for (; *s; s++) if (isalpha((unsigned char)*s)) return 1;
    return 0;
}

/*--- handler perintah ---*/
static void cmd_help(void) {
    puts("available command:");
    puts("help - display this available");
    puts("berhenti - exit and return to Operating System");
    puts("cari xxxx yyyy - search xxxx and yyyy");
    puts("tambah xxxx yyyy - add new data xxxx and yyyy");
}

static void cmd_tambah(Database *db, char *args) {
    char *nim = next_token(&args);
    char *nama = args;
    rtrim(nama);

    if (!nim || !all_digits(nim) || strlen(nim) >= NIM_MAX || *nama == '\0' || !has_letter(nama) || strchr(nama, ',') != NULL || strlen(nama) >= NAMA_MAX) {
        puts("parameter error. tambah xxxx yyyy where xxxx is number and yyyy is string");
        return;
    }

    int r= db_add(db, nim, nama);
    if (r == DB_DUPLICATE) printf("NIM %s sudah ada. data tidak di tambahkan.\n", nim);
    else if (r == DB_ERROR) puts("gagal menyimpan data ke file.");
    else printf("data berhasil ditambahkan: %s %s\n", nim, nama);

}

static void cmd_cari(Database *db, char *args) {
    char *field = next_token(&args);
    char *value = args;
    rtrim(value);

    SearchField sf;
    if (field && strcmp(field, "NIM") ==0) sf = FIELD_NIM;
    else if (field && strcmp(field, "NAMA") == 0) sf = FIELD_NAMA;
    else field = NULL;

    if (!field || *value == '0') {
        puts("syntax error. should only");
        puts("cari xxx yyy");
        puts("where xxx is NIM or NAMA, and yyy is the search value");
        return;
    }

    clock_t t0 = clock();
    size_t *idx = NULL;
    size_t n = search_records(db, sf, value, &idx);
    double secs = (double)(clock() - t0) / CLOCKS_PER_SEC;

    if (n == 0) {
        puts("result:");
        puts("data not found.");
    } else {
        puts("result:");
        for (size_t i = 0; i < n; i++)
        printf("%s %s\n", db->data[idx[i]].nim, db->data[idx[i]].nama);
    }

    printf("total time %.3f seconds\n", secs);
    free(idx);
}

/*--- loop utama ---*/
void command_loop(Database *db) {
    char line[LINE_MAX_LEN];

    for (;;) {
        printf("Your command: ");
        fflush(stdout);
        if (!fgets(line, sizeof line, stdin)) {putchar('\n'); break;} /*--- EOF ---*/

        char *p = line;
        char *cmd = next_token(&p);
        if (!cmd) continue; /*--- baris kosong ---*/

        if (strcmp(cmd, "help") ==0) cmd_help();
        else if (strcmp(cmd, "berhenti") == 0) break;
        else if(strcmp(cmd, "tambah") == 0) cmd_tambah(db, p);
        else if(strcmp(cmd, "cari") == 0) cmd_cari(db, p);
        else puts("Command not recognised. Please use help to display list of comand.");
    }
}