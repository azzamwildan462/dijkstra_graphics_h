#include <graphics.h>
#include "DB.h"

/* Prototypes */
void drawVertex(DB *Vertexes, int16_t pos);
void DB_showGUI(DB *Vertexes);
void drawVertex_dijkstra(DB *Vertexes, int16_t pos, vector<int> dijkstra_results);
void DB_showGUI_dijkstra(DB *Vertexes, vector<int> dijkstra_results);
int isDijkstraPath(int src, int dst, vector<int> dijkstra_results);

int main()
{
    DB DbNode;
    vector<int> dijkstra_buffer;
    initwindow(1024, 640);

    /* Untuk menambah node node */
    DbNode.append("Dukuh_Menanggal", 200, 70);
    DbNode.append("Siwalankerto", 300, 500);
    DbNode.append("Taman_Pelangi", 500, 350);
    DbNode.append("Bhayangkara", 200, 200);

    /* Untuk memberi hubungan antar node */
    DbNode.connect2arah("Siwalankerto", "Bhayangkara");
    DbNode.connect2arah("Taman_Pelangi", "Bhayangkara");
    DbNode.connect2arah("Taman_Pelangi", "Dukuh_Menanggal");
    DbNode.connect2arah("Siwalankerto", "Dukuh_Menanggal");

    if (DbNode.cariRute("Siwalankerto", "Taman_Pelangi"))
    {
        /* Untuk print di terminal (cmd) */
        for (size_t i = 0; i < DbNode.data_hasil_dijkstra.size() - 1; i++)
        {
            printf("%s -> ", DbNode.node[DbNode.data_hasil_dijkstra[i]].nama.c_str());
        }
        printf("%s\n", DbNode.node[DbNode.data_hasil_dijkstra[DbNode.data_hasil_dijkstra.size() - 1]].nama.c_str());

        /* Untuk menampilkan jalur pada grafik */
        dijkstra_buffer.resize(DbNode.data_hasil_dijkstra.size());
        dijkstra_buffer = DbNode.data_hasil_dijkstra;
    }
    while (!kbhit())
    {
        // DB_showGUI(&DbNode); // Untuk tampil biasa
        DB_showGUI_dijkstra(&DbNode, dijkstra_buffer); // Untuk tampil dengan hasil dijkstra
    }
    closegraph();

    return 0;
}

void drawVertex(DB *Vertexes, int16_t pos)
{
    /* Menampilkan garis hubungan antar node nya */
    for (int16_t i = 0; i <= Vertexes->node[pos].tanda_akhir_hubungan_node; i++)
    {
        int node_tujuan = Vertexes->node[pos].hubungan_node[i];
        line(Vertexes->node[pos].x, Vertexes->node[pos].y, Vertexes->node[node_tujuan].x, Vertexes->node[node_tujuan].y);
    }

    /* Menampilkan node */
    circle(Vertexes->node[pos].x, Vertexes->node[pos].y, 30);
    outtextxy(Vertexes->node[pos].x - 15, Vertexes->node[pos].y + 15, (char *)Vertexes->node[pos].nama.c_str());
}
void DB_showGUI(DB *Vertexes)
{
    /* Memproses semua node */
    for (int16_t i = 0; i < Vertexes->banyak_node; i++)
    {
        drawVertex(Vertexes, i);
    }
}

void drawVertex_dijkstra(DB *Vertexes, int16_t pos, vector<int> dijkstra_results)
{
    /* Menampilkan garis hubungan antar node nya */
    for (int16_t i = 0; i <= Vertexes->node[pos].tanda_akhir_hubungan_node; i++)
    {
        int node_tujuan = Vertexes->node[pos].hubungan_node[i];

        /* Ketika hubungan antar node merupakan jalur dari hasil dijkstranya */
        if (isDijkstraPath(pos, node_tujuan, dijkstra_results))
        {
            setcolor(2); // Warna hijau
            line(Vertexes->node[pos].x, Vertexes->node[pos].y, Vertexes->node[node_tujuan].x, Vertexes->node[node_tujuan].y);
            setcolor(7); // Menormalkan warna kembali ke putih
        }
        /* Ketika hubungan antar node merupakan jalur dari hasil dijkstranya */
        else if (isDijkstraPath(node_tujuan, pos, dijkstra_results))
        {
            setcolor(2); // Warna hijau
            line(Vertexes->node[pos].x, Vertexes->node[pos].y, Vertexes->node[node_tujuan].x, Vertexes->node[node_tujuan].y);
            setcolor(7); // Menormalkan warna kembali ke putih
        }
        else
            line(Vertexes->node[pos].x, Vertexes->node[pos].y, Vertexes->node[node_tujuan].x, Vertexes->node[node_tujuan].y);
    }

    /* Menampilkan node */
    circle(Vertexes->node[pos].x, Vertexes->node[pos].y, 30);
    outtextxy(Vertexes->node[pos].x - 15, Vertexes->node[pos].y + 15, (char *)Vertexes->node[pos].nama.c_str());
}

void DB_showGUI_dijkstra(DB *Vertexes, vector<int> dijkstra_results)
{
    /* Memproses semua node */
    for (int16_t i = 0; i < Vertexes->banyak_node; i++)
    {
        drawVertex_dijkstra(Vertexes, i, dijkstra_results);
    }
}

/**
 * @brief Untuk mengecek apakah jalur yang dilalui termasuk jalur hasil dijkstra
 * @param src adalah kota asal
 * @param dst adalah kota tujuan yang mau dicek
 * @param dijkstra_results hasil dari algoritma dijkstra
 */
int isDijkstraPath(int src, int dst, vector<int> dijkstra_results)
{
    for (size_t i = 0; i < dijkstra_results.size() - 1; i++)
    {
        if (dijkstra_results[i] == src && dijkstra_results[i + 1] == dst)
        {
            return 1;
        }
    }
    return 0;
}