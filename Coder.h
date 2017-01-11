#ifndef CODER_H
#define	CODER_H

#include <vector>
#include <stdio.h>
#include <iostream>
#include <math.h>
using namespace std;

class Coder {
public:
    Coder();
    virtual ~Coder();
    
    void codingStr(vector<unsigned char> &str, vector<bool> &encod_str, int m, int size_str);
    void decodingStr(vector<unsigned char> &decod_str, vector<bool> &encod_str, int m, int size_str);
private:

};

#endif	/* CODER_H */

