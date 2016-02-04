// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2016
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>              // assert
#include <iostream>             // endl, istream, ostream
#include <sstream>              // istringstream
#include <string>               // getline, string
#include <utility>              // make_pair, pair
#include <tr1/unordered_map>    // unordered_map
#include <math.h>               // pow
#include <stdlib.h>     /* abs */

#include "Collatz.h"

using namespace std;

// ------------
// collatz_read
// ------------

pair<int, int> collatz_read (const string& s) {
    istringstream sin(s);
    int i;
    int j;
    sin >> i >> j;
    return make_pair(i, j);}

// ------------
// collatz_eval
// ------------


long c[32] = {0,3,2,2,2,2,2,4,1,4,1,3,2,2,3,4,1,2,3,3,1,1,3,3,2,3,2,4,3,3,4,5};
long d[32] = {0,2,1,1,2,2,2,20,1,26,1,10,4,4,13,40,2,5,17,17,2,2,20,20,8,22,8,71,26,26,80,242};

int collatz_eval (int i, int j) {
    // assert(i > 0);
    // assert(j > 0);
    // assert(i < 1000000);
    // assert(j < 1000000);  

    i = abs(i);
    j = abs(j);

    tr1::unordered_map<long, int> storage;

    storage[1] = 1;
    storage[2] = 2;
    storage[3] = 8;
    storage[4] = 3;
    storage[5] = 6;
    storage[6] = 9;
    storage[7] = 17;
    storage[8] = 4;
    storage[9] = 20;
    storage[10] = 7;
    storage[11] = 15;
    storage[12] = 10;
    storage[13] = 10;
    storage[14] = 18;
    storage[15] = 18;
    storage[16] = 5;
    storage[17] = 13;
    storage[18] = 21;
    storage[19] = 21;
    storage[20] = 8;
    storage[21] = 8;
    storage[22] = 16;
    storage[23] = 16;
    storage[24] = 11;
    storage[25] = 24;
    storage[26] = 11;
    storage[27] = 112;
    storage[28] = 19;
    storage[29] = 19;
    storage[30] = 19;
    storage[31] = 107;
    storage[32] = 6;

    int n = -1;

    if(j < i){
        int t = j;
        j = i;
        i = t;} 

    int m = (j - i) / 2;

    if(m > i)
        i = m;
    
    for(int p = i; p <= j; p++) {

        int t = 0;

        if(storage.count((long)p) > 0)
            t = storage[(long)p];

        else{
            t = 1;
            long q = (long)p;
            while(q > 1) {

                if(storage.count(q) > 0)
                {
                    t += storage[q]-1;
                    q = 1;
                }
                     
                else{
                    while(q > 32 && (q % 32) != 0) {
                        long a = q >> 5;
                        long b = q % 32;
                        q=a * (long) pow(3, c[(int)b]) + d[(int)b];
                        t += 5+c[(int)b];}

                    if((q % 2) == 0) {
                        q = q / 2;
                        ++t;}

                    else {
                        q = q + (q >> 1) + 1;
                        t+=2;}}}

            storage[(long)p]=t;}
        
        if(t > n)
            n = t;}

    // assert(n > 0);
    return n;}
    
// -------------
// collatz_print
// -------------

void collatz_print (ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (istream& r, ostream& w) {
    string s;
    while (getline(r, s)) {
        const pair<int, int> p = collatz_read(s);
        const int            i = p.first;
        const int            j = p.second;
        const int            v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}
