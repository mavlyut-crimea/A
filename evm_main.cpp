#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
typedef unsigned char pp;

class Pixel {
public:
    pp r, g, b;

    Pixel(pp r, pp g, pp b) {
        this->r = r;
        this->g = g;
        this->b = b;
    }
};

class Header {
public:
    int width{}, height{}, max_brightness{};
    string magic_number;

    void parse(ifstream& fin) {
        fin >> magic_number >> width >> height >> max_brightness;
    }

    void to_string(FILE *file) {
        fprintf(file, "%s\n%d %d\n%d\n", magic_number.c_str(), width, height, max_brightness);
    }

    int get_area() const {
        return width * height;
    }
};

typedef vector<Pixel> vp;

class Image {
private:
    vp pixels;
    Header header;

public:
    int calc(int i, int j) {
        return i * header.width + j;
    }

    Pixel get(int i, int j) {
        return pixels[calc(i, j)];
    }

    void set(int i, int j, pp r, pp g, pp b) {
        pixels[calc(i, j)] = Pixel(r, g, b);
    }

    void parse(ifstream& fin) {
        header.parse(fin);
        pixels = vp(header.get_area(), Pixel(0, 0, 0));
        for (int i = 0; i < header.height; i++) {
            for (int j = 0; j < header.width; j++) {
                pp r, g, b;
                fin >> r >> g >> b;
                set(i, j, r, g, b);
            }
        }
    }

    void to_string(FILE *file) {
        header.to_string(file);
        for (int i = 0; i < header.height; i++) {
            for (int j = 0; j < header.width; j++) {
                Pixel tmp = get(i, j);
                fprintf(file, "%c%c%c", tmp.r, tmp.g, tmp.b);
            }
        }
    }
};

int main() {

    string fileIn = R"(C:\Users\User\CLionProjects\untitled7\photo\2.ppm)";
    string fileOut = R"(C:\Users\User\CLionProjects\untitled7\photo\2-out.ppm)";

    ifstream fin(fileIn, fstream::binary);
    FILE *file = fopen(fileOut.c_str(), "w");

    Image image;
    image.parse(fin);
    image.to_string(file);

    return 0;
}
