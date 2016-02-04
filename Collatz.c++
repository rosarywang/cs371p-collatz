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

    //#define CACHE

    #ifdef CACHE
    int storage[33]= {0,1,2,8,3,6,9,17,4,20,7,15,10,10,18,18,5,13,21,21,8,8,16,16,11,24,11,112,19,19,19,107,6};
    #endif

int collatz_eval (int i, int j) {
    // assert(i > 0);
    // assert(j > 0);
    // assert(i < 1000000);
    // assert(j < 1000000);  

    // i = abs(i);
    // j = abs(j);

    int n = -1;

    if(j < i){
        int t = j;
        j = i;
        i = t;} 

    int m = (j - i) / 2;

    if(m > i)
        i = m;
    
    for(int p = i; p <= j; p++) {

        int t = 1;
            long q = (long)p;
            while(q > 1) {

                while(q > 32 ) {// && (q % 32) != 0) {
                    long a = q >> 5;
                    long b = q % 32;
                    q=a * (long) pow(3, c[(int)b]) + d[(int)b];
                    t += 5+c[(int)b];
                }
                #ifdef CACHE
                if(q <= 32)
                {
                    t += storage[(int)q]-1;
                    q = 1;
                }  
                else {
                #endif 
                    if((q % 2) == 0) {
                        q = q / 2;
                        ++t;}

                    else {
                        q = q + (q >> 1) + 1;
                        t+=2;}
                #ifdef CACHE 
                }
                               
                #endif
            }        
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
