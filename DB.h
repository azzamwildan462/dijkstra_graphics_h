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
        string nama;
        int x;
        int y;
        vector<int> hubungan_node;
        int tanda_akhir_hubungan_node;
    } Node;

    /* Setiap node punya data jarak masing masing terhadap node lainnya */
    vector<vector<float>> data_jarak_node;

private:
    /**
     * @brief Untuk resize vector 2 dimensi
     * @param vector adalah vector yang akan di-resize
     */
    void resizeVector2d(vector<vector<float>> vector, unsigned int size);

    /**
     * @brief Mendapatkan jalur dari hasil algoritma dijkstra
     */
    void getPath(vector<int> path_temp, int dst);
    int cariJarakTerkecilDijkstra(vector<int> jarak_antar_node, vector<bool> sudah_dilewati, unsigned int src);
    bool cekHubungan(int src_pos, int dst_pos);

private:
    vector<int> jarak_antar_node;
    vector<bool> sudah_dilewati;
    vector<int> path_temp;
    unsigned int iter_get;

public:
    unsigned short int banyak_node;
    vector<Node> node;
    vector<int> data_hasil_dijkstra;

public:
    DB();
    string cariNodeTerdekatStr(string node_yang_ingin_dicari);
    float pitagoras(float x1, float y1, float x2, float y2);
    int cariNodeTerdekat(string node_yang_ingin_dicari);
    void show();
    void append(string nama_node, int x, int y);
    int searchByName(string nama_node);
    void connect2arah(string src, string dst);
    void simpanDataJarak(int pos);
    void initDijkstra();
    bool cariRute(string asal, string tujuan);
};

#endif