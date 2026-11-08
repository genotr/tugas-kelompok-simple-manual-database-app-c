/*
* Program Database Sederhana
* INF11107 Praktikum Struktu Data
*
* Anggota:
* Rezza Firnando | 2501020090 | Command & Search Engineer
* Fikri Enggaransyah | 2501020087 | Data & File Engineer
* Sayed Abdillah | 2501020067 | QA, Tester, & Docs
*/

#include <stdio.h>
#include "database.h"
#include "command.h"

int main(int argc, char *argv[]){
    if(argc != 2) {
        fprintf(stderr, "Usage: %s <data_file>\n", argv[0]);
        return 1;
    }

    Database db;
    if(db_load(&db, argv[1]) !=DB_OK){
        fprintf(stderr, "tidak dapat membuka/membuat file: %s\n", argv[1]);
        return 1;
    }

    command_loop(&db);

    db_save(&db);  /*menyimpan ulang dalam keadaan terurut*/
    db_free(&db);

    return 0;
}
