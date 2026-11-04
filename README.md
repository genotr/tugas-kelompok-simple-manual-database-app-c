# tugas-kelompok-simple-manual-database-app-c
Tugas kelompok INF11107 Struktur Data: Membangun aplikasi basis data manual sederhana dengan bahasa C. Fitur: tambah data, cari (NIM/NAMA), sorting, dan penyimpanan file CSV.
Team Member:


Name Student | NIM | Role
1. Rezza Firnando | 2501020090 | Command & Search Engineer
3. sayed abdillah | 2501020067 | QA, tester, dan documentation
4. Fikri Enggaransyah  | 2501020087| Data & File Engineer

Role Available
1. Data & File Engineer
2. Command & Search Engineer
3. QA, Tester, & Documentation

## Build & jalankan

make        #compile -> ./2501020090
./2501020090 GRT.dat
make test          # jalankan 15 test otomatis
'''

## perintah
| Perintah | Fungsi |
|----   |   ---|
|'help' | tampilkan daftar perintah |
|'tambah xxxx yyyy'  | tambah data (xxxx = NIM angka, yyyy = nama, boleh spasi) |
|'cari NIM yyy ' / 'cari NAMA yyy'  | cari sebagian nilai, tidak peduli huruf besar/kecil |
|'berhenti' | simpan & keluar |

Perintah bersifat case sensitive (' HELP' -> *Command not recognised*).

## struktur Data & Algoritma
- **Dynamic array** ' Record[]' (NIM, NAMA), kapasitas dobel otomatis.
- **Merger Sort** O(n log n) saat file dibaca -> data selalu terurut berdasarkan NIM.
- **Binary search + shift** O(log n + n) untuk menyisipkan data baru agar tetap terurut.
- **Pencarian** substring case-insentive linear O(n.m), waktu  diukur dengan 'clock()'.
- **File**: CSV tanpa header 'NIM,NAMA'; dibuat otomatis jika belum ada ; tiap 'tambah' langsung di -append, saat 'berhenti' ditulis ulang terurut.

## Catatan Desain
- NIM duplikat ditolak. Nama tidak boleh mengandung koma (merusak CSV) dan harus mengandung huruf.
- Contoh output: 'docs/output_contoh.txt'.

## Pengumpulan 
Folder bernama '2501020090' dikompres **7zip** ('.7z'), kirim lewat Google From . Deadline **9 November 2026**.
