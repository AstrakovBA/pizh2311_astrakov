#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdint>
#include <filesystem>
#include <unordered_map>

using namespace std;

struct Params {
    uint16_t h = 0;
    uint16_t w = 0;
    string in_file;
    string out_folder;
    uint64_t max_steps = 0;
    uint64_t save_freq = 0;
};

#pragma pack(push, 1)
struct BMP {
    uint16_t type = 0x4D42;
    uint32_t size;
    uint32_t reserved = 0;
    uint32_t offset = 54;
    uint32_t header_size = 40;
    int32_t width;
    int32_t height;
    uint16_t planes = 1;
    uint16_t bpp = 24;
    uint32_t compression = 0;
    uint32_t img_size = 0;
    int32_t x_res = 1000;
    int32_t y_res = 1000;
    uint32_t used = 0;
    uint32_t important = 0;
};
#pragma pack(pop)

uint8_t palette[5][3] = {
    {255, 255, 255},
    {0, 255, 0},
    {128, 0, 128},
    {255, 255, 0},
    {0, 0, 0}
};

Params extract_args(int argc, char* argv[]) {
    unordered_map<string, string> a;
    for (int i = 1; i + 1 < argc; i += 2) {
        a[argv[i]] = argv[i + 1];
    }

    Params p;
    if (a.count("-l")) p.h = stoi(a["-l"]);
    if (a.count("--length")) p.h = stoi(a["--length"]);
    if (a.count("-w")) p.w = stoi(a["-w"]);
    if (a.count("--width")) p.w = stoi(a["--width"]);
    if (a.count("-i")) p.in_file = a["-i"];
    if (a.count("--input")) p.in_file = a["--input"];
    if (a.count("-o")) p.out_folder = a["-o"];
    if (a.count("--output")) p.out_folder = a["--output"];
    if (a.count("-m")) p.max_steps = stoull(a["-m"]);
    if (a.count("--max-iter")) p.max_steps = stoull(a["--max-iter"]);
    if (a.count("-f")) p.save_freq = stoull(a["-f"]);
    if (a.count("--freq")) p.save_freq = stoull(a["--freq"]);

    return p;
}

void read_input(const string& path, vector<vector<uint64_t>>& field) {
    ifstream in(path);
    string ln;
    while (getline(in, ln)) {
        istringstream s(ln);
        int x, y;
        uint64_t c;
        s >> x;
        s.ignore();
        s >> y;
        s.ignore();
        s >> c;
        if (y < field.size() && x < field[0].size()) {
            field[y][x] += c;
        }
    }
}

void write_image(const string& fname, const vector<vector<uint64_t>>& data) {
    int h = data.size();
    int w = data[0].size();
    int row_bytes = (w * 3 + 3) & ~3;
    int total_size = 54 + row_bytes * h;

    BMP bmp;
    bmp.size = total_size;
    bmp.width = w;
    bmp.height = h;
    bmp.img_size = row_bytes * h;

    ofstream out(fname, ios::binary);
    out.write(reinterpret_cast<char*>(&bmp), sizeof(bmp));

    vector<uint8_t> row(row_bytes);

    for (int y = h - 1; y >= 0; --y) {
        fill(row.begin(), row.end(), 0);
        for (int x = 0; x < w; ++x) {
            int v = data[y][x] > 3 ? 4 : static_cast<int>(data[y][x]);
            row[x * 3 + 0] = palette[v][2];
            row[x * 3 + 1] = palette[v][1];
            row[x * 3 + 2] = palette[v][0];
        }
        out.write(reinterpret_cast<char*>(row.data()), row_bytes);
    }
}

bool update(vector<vector<uint64_t>>& mat) {
    int h = mat.size();
    int w = mat[0].size();
    auto tmp = mat;
    bool active = false;

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            if (mat[y][x] >= 4) {
                uint64_t drop = mat[y][x] / 4;
                tmp[y][x] -= drop * 4;
                if (y > 0) tmp[y - 1][x] += drop;
                if (y + 1 < h) tmp[y + 1][x] += drop;
                if (x > 0) tmp[y][x - 1] += drop;
                if (x + 1 < w) tmp[y][x + 1] += drop;
                active = true;
            }
        }
    }

    mat = tmp;
    return active;
}

int main(int argc, char* argv[]) {
    if (argc < 9) {
        cout << "Usage: ./sandpiles -l <height> -w <width> -i <input.tsv> -o <output_dir> -m <max_iter> -f <freq>\n";
        return 1;
    }

    Params p = extract_args(argc, argv);
    filesystem::create_directories(p.out_folder);

    vector<vector<uint64_t>> grid(p.h, vector<uint64_t>(p.w, 0));
    read_input(p.in_file, grid);

    for (uint64_t i = 0; i <= p.max_steps; ++i) {
        if (p.save_freq && i % p.save_freq == 0) {
            string out_name = p.out_folder + "/state_" + to_string(i) + ".bmp";
            write_image(out_name, grid);
        }

        if (!update(grid)) {
            cout << "Stable at iteration: " << i << endl;
            break;
        }
    }

    if (p.save_freq == 0) {
        string final_out = p.out_folder + "/final.bmp";
        write_image(final_out, grid);
    }

    return 0;
}
