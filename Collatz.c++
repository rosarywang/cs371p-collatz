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

//tr1::unordered_map<int, int> storage;
unsigned int c[32] = {0,3,2,2,2,2,2,4,1,4,1,3,2,2,3,4,1,2,3,3,1,1,3,3,2,3,2,4,3,3,4,5};
unsigned int d[32] = {0,2,1,1,2,2,2,20,1,26,1,10,4,4,13,40,2,5,17,17,2,2,20,20,8,22,8,71,26,26,80,242};

int collatz_eval (int i, int j) {
    // assert(i > 0);
    // assert(j > 0);
    // assert(i < 1000000);
    // assert(j < 1000000);  

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

        //if(storage.count(p) > 0)
        //    t = storage[p];

        //else{
            t = 1;
            unsigned int q = (unsigned int)p;
            while(q > 1) {

                // while(q > 32 && (q % 32) != 0) {
                //     unsigned int a = q >> 5;
                //     int b = (int)q % 32;
                //     q=(unsigned int)(a * (unsigned int) pow(3, c[b]) + d[b]);
                //     t += 5+(int)c[b];}

                if((q % 2) == 0) {
                    q = q / 2;
                    ++t;}

                else {
                    q = q + (q >> 1) + 1;
                    t+=2;}}

            //storage[p]=t;}
        
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
