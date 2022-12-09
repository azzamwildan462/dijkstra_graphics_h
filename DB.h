#ifndef GLOBAL_VAR_H
#define GLOBAK_VAR_H

#include "stdint.h"
#include "bits/stdc++.h"
#include <vector>

using namespace std;

class DB
{
private:
    /* Struct untuk 1 node nya */
    typedef struct Node
    {
        string nama;                   // Nama
        int x;                         // Koordinat x
        int y;                         // Koordinat y
        vector<int> hubungan_node;     // Terhubung ke node mana aja?
        int tanda_akhir_hubungan_node; // Total ada berapa node yang terhubung
    } Node;

    vector<vector<float>> data_jarak_node; // Menyimpan data jarak antar masing-masing node

private:
    /**
     * @brief Untuk resize vector 2 dimensi
     * @param vector adalah vector yang akan di-resize
     * @param size ukuran vector target
     */
    void resizeVector2d(vector<vector<float>> vector, unsigned int size);

    /**
     * @brief Mendapatkan jalur dari hasil algoritma dijkstra
     * @param path_temp hasil raw dari perhitungan dijkstra
     * @param dst node asal yang digunakan untuk dijkstra
     */
    void getPath(vector<int> path_temp, int dst);
    /**
     * @brief mencari jarak terkecil ke node target, menentukan target node selanjutnya
     * @param jarak_antar_node jarak dari satu node ke node-node lainnya, x->a, x->b, x->c, dst..
     * @param sudah_dilewati data apakah node ini sudah di-proses atau belum
     * @param src node yang akan dicari jarak terkecilnya dengan node mana
     * @return index yang dimiliki oleh node dengan jarak terpendek
     */
    int cariJarakTerkecilDijkstra(vector<int> jarak_antar_node, vector<bool> sudah_dilewati, unsigned int src);
    /**
     * @brief mengecek hubungan dari dua node
     * @param src_pos node 1
     * @param dst_pos node 2
     * @return status hubungan
     */
    bool cekHubungan(int src_pos, int dst_pos);

private:
    vector<int> jarak_antar_node; // Jarak satu node ke node lainnya
    vector<bool> sudah_dilewati;  // Menandai node apakah sudah di-proses atau belum
    vector<int> path_temp;        // Menyimpan sementara
    unsigned int iter_get;        // Untuk keperluan meng-ekstrak hasil dari dijkstras

public:
    unsigned short int banyak_node;  // Banyak node yang ada dalam database
    vector<Node> node;               // Mewakili satu node
    vector<int> data_hasil_dijkstra; // Menyimpan hasil dari perhitungan Dijkstra

public:
    /* Default constructor */
    DB();
    /**
     * @brief metode untuk mencari jarak
     */
    float pitagoras(float x1, float y1, float x2, float y2);
    /**
     * @brief menampilkan semua node pada database
     */
    void show();
    /**
     * @brief Tambah node
     * @param nama_node nama untuk node baru
     * @param x koordinat x untuk node baru
     * @param y koordinat y untuk node baru
     */
    void append(string nama_node, int x, int y);
    /**
     * @brief Mencari node berdasarkan namanya
     * @param nama_node nama node yang ingin dicari
     * @return index node atau posisi node pada database
     */
    int searchByName(string nama_node);
    /**
     * @brief Menghubungkan node-node
     * @param src node asal
     * @param dst node tujuan
     */
    void connect2arah(string src, string dst);
    /**
     * @brief Menyimpan semua data jarak dari satu node ke node node lainnya
     * @param pos index node yang ingin di-proses data jarak dengan node lainnya
     */
    void simpanDataJarak(int pos);
    /**
     * @brief Inisialisasi perhitungan dijkstra
     */
    void initDijkstra();
    /**
     * @brief Main-process untuk mencari jalur terpendek menggunakan algoritma Dijkstra
     * @param asal node asal
     * @param tujuan node tujuan
     */
    bool cariRute(string asal, string tujuan);
};

#endif