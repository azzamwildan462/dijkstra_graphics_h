#include "DB.h"

DB::DB()
{
    banyak_node = 0; // inisialisasi awal banyak node adalah 0
}

void DB::append(string nama_node, int x, int y)
{
    if (searchByName(nama_node) >= 0)
    {
        printf("Error: %s Nama node sudah ada yang pakai\n", nama_node.c_str());
        return;
    }
    if (y >= 640)
    {
        printf("Error: %s -> %d koordinat_y keluar batas window\n", nama_node.c_str(), y);
        return;
    }
    if (x >= 1024)
    {
        printf("Error: %s -> %d koordinat_x keluar batas window\n", nama_node.c_str(), x);
        return;
    }
    banyak_node++;                          // menambahkan banyak node
    node.resize(banyak_node);               // me-resize vector node
    node[banyak_node - 1].nama = nama_node; // proses inisialisai node
    node[banyak_node - 1].x = x;
    node[banyak_node - 1].y = y;
    node[banyak_node - 1].tanda_akhir_hubungan_node = -1;
}

void DB::show()
{
    int panjang_nama = 0;
    int panjang_terdekat = 0;
    // header
    for (int i = 0; i < banyak_node; i++) // pre-proses untuk merapikan tabel jika ada nama node yang panjang
    {
        if (node[i].nama.size() >= 0x8)
            panjang_nama = 1;
    }

    // Print header tabel
    if (panjang_nama == 0)
        printf("Nama \t");
    else if (panjang_nama == 1)
        printf("Nama \t\t");

    printf("X\t");

    printf("Y\t");

    printf("Hubungan ");

    printf("\n");
    // End print header tabel

    // Print isi tabel (Database node node)
    for (int i = 0; i < banyak_node; i++)
    {
        // printf("iter-%d\t", i); // untuk debug index
        if (node[i].nama.size() < 0x8)
        {
            if (panjang_nama == 1)
                cout << node[i].nama << "\t\t";
            else if (panjang_nama == 0)
                cout << node[i].nama << "\t";
        }
        else if (node[i].nama.size() >= 0x8)
            cout << node[i].nama << "\t";

        cout << node[i].x << "\t";

        cout << node[i].y << "\t";

        if (node[i].tanda_akhir_hubungan_node == -1)
            printf("- ");
        else
        {
            for (int v = 0; v < node[i].tanda_akhir_hubungan_node; v++) // print hubungan
            {
                cout << node[i].hubungan_node[v] << ", ";
            }
            cout << node[i].hubungan_node[node[i].tanda_akhir_hubungan_node] << " ";
        }
        cout << endl;
    }
}

void DB::resizeVector2d(vector<vector<float>> vector, unsigned int size)
{
    printf("size %d", size);
    vector.resize(size);
    for (int i = 0; i < size; ++i)
        vector[i].resize(size);
}

float DB::pitagoras(float x1, float y1, float x2, float y2)
{
    return sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1))); // Menggunakan rumus pitagoras untuk cari jarak
}

int DB::searchByName(string nama_node)
{
    for (int i = 0; i < banyak_node; i++) // linear search
    {
        if (nama_node == node[i].nama)
        {
            return i;
        }
    }
    // kalo sampek sini berarti node gk ditemukan
    //  printf("node gk ditemukan\n");
    return -1;
}
void DB::connect2arah(string src, string dst)
{
    int src_pos = searchByName(src);
    int dst_pos = searchByName(dst);
    if (src_pos < 0)
    {
        printf("Error: Node %s tidak ditemukan dalam Database\n", src.c_str());
        if (dst_pos >= 0)
            return;
    }
    if (dst_pos < 0)
    {
        printf("Error: Node %s tidak ditemukan dalam Database\n", dst.c_str());
        return;
    }
    if (cekHubungan(src_pos, dst_pos))
    {
        printf("Info: Node %s dengan %s sudah terhubung\n", src.c_str(), dst.c_str());
        // return;
    }
    else
    {
        node[src_pos].tanda_akhir_hubungan_node++;
        node[src_pos].hubungan_node.resize(node[src_pos].tanda_akhir_hubungan_node + 1);
        node[src_pos].hubungan_node[node[src_pos].tanda_akhir_hubungan_node] = dst_pos;
    }
    if (cekHubungan(dst_pos, src_pos))
    {
        printf("Info: Node %s dengan %s sudah terhubung\n", src.c_str(), dst.c_str());
        // return;
    }
    else
    {

        node[dst_pos].tanda_akhir_hubungan_node++;
        node[dst_pos].hubungan_node.resize(node[dst_pos].tanda_akhir_hubungan_node + 1);
        node[dst_pos].hubungan_node[node[dst_pos].tanda_akhir_hubungan_node] = src_pos;
    }

    // Jika sampai sini maka bisa dipastikan aman

    return;
}

void DB::simpanDataJarak(int pos)
{
    for (int i = 0; i < banyak_node; i++)
    {
        if (cekHubungan(i, pos)) // Yang diproses adalah node node yang terhubung
        {
            // printf("onok\n");
            data_jarak_node[i][pos] = pitagoras(node[pos].x, node[pos].y, node[i].x, node[i].y);
        }
        else // Jika tidak terhubung maka diisi dengan 0
        {
            // printf("gak onok\n");
            data_jarak_node[i][pos] = 0;
        }
    }
}

void DB::initDijkstra()
{
    // nggawe data jarak sek
    data_jarak_node.resize(banyak_node, vector<float>(banyak_node)); // Resize vektor
    for (int i = 0; i < banyak_node; i++)                            // Proses untuk menyimpan data jarak antar node
    {
        simpanDataJarak(i);
    }
    sudah_dilewati.resize(banyak_node);
    path_temp.resize(banyak_node);
    jarak_antar_node.resize(banyak_node);
    // sudah_dilewati.

    for (int i = 0; i < banyak_node; i++)
    {
        // path_temp[src] = -1;
        jarak_antar_node[i] = INT_MAX;
        sudah_dilewati[i] = 0;
    }

    if (!data_hasil_dijkstra.empty()) // Mengosongkan hasil agar tidak tabrakan dengan hasil sebelumnya
        printf("Debug: Gagal mengosongkan hasil dijkstra\n");
}
bool DB::cariRute(string asal, string tujuan)
{
    int src = searchByName(asal);
    int dst = searchByName(tujuan);
    if (src < 0)
    {
        printf("Error: Node %s tidak ditemukan dalam Database\n", asal.c_str());
        if (dst >= 0)
            return 0;
    }
    if (dst < 0)
    {
        printf("Error: Node %s tidak ditemukan dalam Database\n", tujuan.c_str());
        return 0;
    }
    // Kedua node aman
    int src_temp_temp = src; // safety lanjutan
    initDijkstra();
    jarak_antar_node[src] = 0;
    path_temp[src] = -1;

    for (int i = 0; i < banyak_node - 1; i++) // Proses pembuatan path
    {
        int src_temp = cariJarakTerkecilDijkstra(jarak_antar_node, sudah_dilewati, src_temp_temp);
        if (src_temp == -1) // Safety jika tidak ada jalan apapun
        {
            printf("Debug: Tidak ditemukan jalan\n");
            return 0;
        }
        src_temp_temp = src_temp;
        sudah_dilewati[src_temp] = 1;                              // Jika node sudah diproses maka dianggap sudah dilewati
        for (int dst_temp = 0; dst_temp < banyak_node; dst_temp++) // main-process pembuatan path jalur dijkstra
        {
            if (sudah_dilewati[dst_temp] == 0 && data_jarak_node[src_temp][dst_temp] > 0 && jarak_antar_node[src_temp] + data_jarak_node[src_temp][dst_temp] < jarak_antar_node[dst_temp])
            {
                path_temp[dst_temp] = src_temp;
                jarak_antar_node[dst_temp] = jarak_antar_node[src_temp] + data_jarak_node[src_temp][dst_temp];
            }
        }
        if (src_temp == dst) // Safety
        {
            break;
        }
    }

    if (jarak_antar_node[dst] >= INT_MAX) // Jika masih bernilai sesuai inisialisasi maka dianggap tidak sampai tujuan
    {
        printf("Dari %s tidak ada jalan menuju %s\n", node[src].nama.c_str(), node[dst].nama.c_str());
        return 0;
    }
    else
    {
        printf("jarak: %d\n", jarak_antar_node[dst]);
        iter_get = 0;
        getPath(path_temp, dst);
    }
    // data_hasil_dijkstra.
    for (int i = 0, j = data_hasil_dijkstra.size() - 1; i < j; i++, j--) // membalikkan isi array
    {

        // Menggunakan operasi XOR untuk swap value
        data_hasil_dijkstra[j] ^= data_hasil_dijkstra[i];
        data_hasil_dijkstra[i] = data_hasil_dijkstra[j] ^ data_hasil_dijkstra[i];
        data_hasil_dijkstra[j] ^= data_hasil_dijkstra[i];
    }
    return 1;
}

int DB::cariJarakTerkecilDijkstra(vector<int> jarak_antar_node, vector<bool> sudah_dilewati, unsigned int src)
{
    int min = INT_MAX;
    int min_index = -1;

    for (int v = 0; v < banyak_node; v++)
    {
        if (sudah_dilewati[v] == 0 && jarak_antar_node[v] <= min) // jika node tujuan belum diproses
        {
            min = jarak_antar_node[v];
            min_index = v;
        }
    }
    return min_index;
}

void DB::getPath(vector<int> path_temp, int dst)
{
    // static unsigned int iter = 0;
    // printf("iter = %d\n", iter);
    // printf("iter_get = %d\n", iter_get);
    data_hasil_dijkstra.resize(iter_get + 1);
    data_hasil_dijkstra[iter_get] = dst;
    // printf("path temp %d, dst %d\n", path_temp[dst], dst);
    if (iter_get > banyak_node) // Jika terjadi rekursi lebih dari banyak node
    {
        printf("Debug: Tidak menemukan jalan\n");
        return;
    }
    if (path_temp[dst] == -1) // berhenti saat sampai ke src
        return;
    // iter++;
    iter_get++;
    getPath(path_temp, path_temp[dst]); // Rekursi
    // printf("%d ", dst);
}

bool DB::cekHubungan(int src_pos, int dst_pos)
{
    for (int i = 0; i <= node[src_pos].tanda_akhir_hubungan_node; i++) // linear search
    {
        if (node[src_pos].hubungan_node[i] == dst_pos)
        {
            return 1;
        }
    }

    return 0;
}