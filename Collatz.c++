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
int c[32] = {0,3,2,2,2,2,2,4,1,4,1,3,2,2,3,4,1,2,3,3,1,1,3,3,2,3,2,4,3,3,4,5};
int d[32] = {0,2,1,1,2,2,2,20,1,26,1,10,4,4,13,40,2,5,17,17,2,2,20,20,8,22,8,71,26,26,80,242};
// int s[32] = {0,1,7,2,5,8,16,3,19,6,14,9,9,17,17,4,12,20,20,7,7,15,15,10,23,10,111,18,18,81,106,5};

int cycle_length (int n) {
    // //assert(n > 0);
    int step = 1;
    while(n>1)
    {
        while(n > 32 && (n%32) != 0)
        {
            int a = n >> 5;
            int b = n % 32;
            n=a*(int)pow(3,c[b])+d[b];
            step += 5+c[b];
        }
        if((n % 2) == 0)
        {
            n=n/2;
            ++step;
        }
        else
        {
            n=n+(n>>1)+1;
            step+=2;
        }
    }
        
    return step;
    //assert(c > 0);
    }


int collatz_eval (int i, int j) {
    //assert(i > 0);
    //assert(j > 0);
    //assert(i <= 1000000);
    //assert(j <= 1000000);
    //assert(i <= j);   
    int n = -1;
    if(j < i){
        int t = j;
        j = i;
        i = t;} 
    int m = (j-i)/2;
    if(m > i)
        i=m;
    
    for(int p = i; p <= j; p++){
        int t = 0;
        // if(storage.count(p)>0)
        //     t = storage[p];
        // else{
                t = cycle_length(p);
                //storage[p]=t;}
        
        if(t > n)
            n = t;}
    //assert(n > 0);
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
