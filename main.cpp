#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>
#include <bitset>
#include <cmath>
#include <random>
#include "Coder.h"

using namespace std;

void statistics(vector<unsigned char> stream, float p){
    float h = 0;
    int size_ar = 1000;
    int *statistics = new int[size_ar];
    float p_teor;
    float p_pr;
    for (int i = 0; i < size_ar; i++)
            statistics[i] = 0;
    for (int i = 0; i < stream.size(); i++){
        if (stream[i] < size_ar){
            statistics[stream[i]]++;
        }
    }
    for (int i = 0; i < size_ar; i++){
        if (statistics[i] > 0){
            float p = (float)statistics[i] / stream.size();
            h += p * log2(p);
        }
    }
    printf("Entropy = %f\n", -h);
    printf("N\tpTeoria\t\tpPr\n");
    FILE *file = fopen("graf.txt", "wb");
    for (int i = 0; i < 10; i++)    {
        p_teor = pow(1-p, (float(i))) * p;
        p_pr = (float)statistics[i] / stream.size();
        printf("%d\t%f\t%f\n", i, p_teor, p_pr);
        fprintf(file, "%d\t%f\t%f\n", i, p_teor, p_pr);
    }
    delete[] statistics;
}

void writeStrFile(char *name_file, vector<unsigned char> &str, int size_str){
    FILE *file = fopen(name_file, "wb");
    for (int i = 0; i < size_str; i++){
        int k = str[i];
	fprintf(file, "%d", k);
    }
    fclose(file);
}

void writeBitsStr(char *name_file, vector <bool> &encod_str){
    FILE *file = fopen(name_file, "wb");
    bitset <8> byte;
    unsigned char ch;
    bool exit = false;
    for (int i = 0; i < encod_str.size(); i += 8){
        for (int j = i; j < i + 8; j++){
            if (j >= encod_str.size()){
                exit = true;
            }
            else            {
                byte[j - i] = encod_str[j];
            }
        }
        ch = byte.to_ulong();
        fwrite(&ch, 1, sizeof(unsigned char), file);
        if (exit == true)
            break;
    }
    fclose(file);
}

void genGeomStr(int size_str, float p, char* name_file){
    std::vector <unsigned char> str;
    for (int i = 0; i < size_str; i++){
        double vr = 0;
        int k = 0;
        while (vr == 0){
            vr = (double)rand()/RAND_MAX;
            if (vr < p)
                vr = 1;
            else{
                vr = 0;
                k++;
            }
        }
        str.push_back(k);
    }
    writeStrFile(name_file, str, size_str);
}

void readStrFile(char *name_file, vector<unsigned char> &str, int size_str){
    FILE *file = fopen(name_file, "rb");
    unsigned char *ch = new unsigned char [size_str];
    int *k = new int [size_str]; 
    fread(k, 1, sizeof(int)*size_str, file);	
    for (int i = 0; i < size_str; i++){
	str.push_back(ch[i]);
    }
    fclose(file);
}

int getM(float p){
    int m = 1;
    float pr = float(1) / (p + 1);
    bool flag = false;
    float lp = 0;
    float rp = 0;
    while (true){
        lp = pow(p, (float)m);
        rp = pow(p, (float)(m - 1));
        if (pr >= lp && pr < rp){
                flag = true;
                break;
        }
        else{
            m++;
        }
    }
    return m;
}

int main(int argc, char** argv) {
    srand(time(NULL));
    int size_stream = 1000;
    float p = 0.9;
    int m = 3;
    char *name_stream_file = "stream.txt";
    char *name_encod_stream_file_n = "encoding_stream_n.txt";
    char *name_encod_stream_file = "encoding_stream.txt";
    char *name_decoding_stream_n = "decoding_stream_n.txt";
    char *name_decoding_stream = "decoding_stream.txt";
    genGeomStr(size_stream, p, name_stream_file);

    vector <unsigned char> stream;
    readStrFile(name_stream_file, stream, size_stream);
    statistics(stream, p);    
    
    vector<bool> encoding_stream;
    vector<unsigned char> decoding_stream;
    Coder *coder = new Coder();
    coder->codingStr(stream, encoding_stream, m, size_stream);
    writeBitsStr(name_encod_stream_file_n, encoding_stream);
    coder->decodingStr(decoding_stream, encoding_stream, m, size_stream);
    writeStrFile(name_decoding_stream_n, decoding_stream, size_stream);
    for (int i = 0; i < decoding_stream.size(); i++){
        if ((decoding_stream[i] - stream[i]) != 0){
            printf("Erorr %d/n", i);
        }
    }
    printf("rate non-optimal parametr M = %f\n", float(encoding_stream.size()) / size_stream);
    
    int new_m = getM(p);
    printf("optimal m = %d\n", new_m);
    vector<bool> encoding_stream_new;
    vector<unsigned char> decoding_stream_new;
    coder->codingStr(stream, encoding_stream_new, new_m, size_stream);
    writeBitsStr(name_encod_stream_file, encoding_stream_new);
    coder->decodingStr(decoding_stream_new, encoding_stream_new, new_m, size_stream);
    writeStrFile(name_decoding_stream, decoding_stream_new, size_stream);
    for (int i = 0; i < decoding_stream_new.size(); i++){
        if ((decoding_stream_new[i] - stream[i]) != 0){
            printf("Erorr %d/n", i);
        }
    }
    printf("rate optimal parametr M = %f\n", float(encoding_stream_new.size()) / size_stream);
    int s = 0;
    
    return 0;
}

