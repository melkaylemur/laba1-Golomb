#include "Coder.h"

Coder::Coder() {
}

Coder::~Coder() {
}

void Coder::codingStr(vector<unsigned char>& str, vector<bool>& encod_str, int m, int size_str){
    int size_r = 0;

    vector <bool> r_vec;
    vector <bool> q_vec;
    
    for (int i = 0; i < size_str; i++){
        int n = str[i];
        int q = n/m;
        int r = n - m*q;
        
        for (int i = 0; i < q; i++){
            q_vec.push_back(0);
        }
        q_vec.push_back(1);

        if (m%2 == 0){
            vector <bool> r_vec_vr;
            size_r = (int)log2(m);
            for (int i = 0; r > 0; i++){
                if (r%2 == 0){
                    r_vec_vr.push_back(0);
                }
                else{
                    r_vec_vr.push_back(1);
                }
                r /= 2;
            }
            while(size_r > r_vec_vr.size()){
                r_vec_vr.push_back(0);
            }
            for (int i = 0; i < r_vec_vr.size(); i++){
                r_vec.push_back(r_vec_vr[r_vec_vr.size() - i - 1]);
            }
        }
        else{
            vector <bool> r_vec_vr;
            
            int b = size_r = (int)log2(m)+1;
            int vr = pow(2,b) - m;
            int rr = r;
            if (r < vr){
                size_r = b-1;
            }
            else{
                rr = r + pow(2,b) - m;
            }
            for (int i = 0; rr > 0; i++){
                if (rr%2 == 0){
                    r_vec_vr.push_back(0);
                }
                else{
                    r_vec_vr.push_back(1);
                }
                rr /= 2;
            }
            while(size_r > r_vec_vr.size()){
                r_vec_vr.push_back(0);
            }
            for (int i = 0; i < r_vec_vr.size(); i++){
                r_vec.push_back(r_vec_vr[r_vec_vr.size() - i - 1]);
            }
        }
        encod_str.insert(encod_str.end(), q_vec.begin(), q_vec.end());
        encod_str.insert(encod_str.end(), r_vec.begin(), r_vec.end());
        r_vec.clear();
        q_vec.clear();
        int dfgh=4567;
    }
    
}
void Coder::decodingStr(vector<unsigned char> &decod_str, vector<bool> &encod_str, int m, int size_str)
{
    int q = 0;
    int n = 0;
    int r = 0;
    int index = 0;

    while (index < encod_str.size()){
        q = 0;
        while (encod_str[index] != 1){
            q++;
            index++;
        }
        index++;
        if (m%2 == 0){
            r = 0;
            int b = log2(m);
            int s = 1;
            for (int i = index; i < index+b; i++){
                r = r*2 + encod_str[i];
                s++;
            }
            index += b;
        }
        else{
            r = 0;
            int b = log2(m)+1;
            int vr = pow (2, b) - m;
            for (int i = index; i < index+b-1 ; i++){
                r = r*2 + encod_str[i];
            }
            if (r < vr ){
                decod_str.push_back(q * m + r);
                index += b-1;
            }
            else{
                r = r*2 +encod_str[index+b-1];
                int rr = r - pow (2, b) + m;
                decod_str.push_back(q * m + rr);
                index += b;
            }
        }
        int fgh=5678;
    }
}