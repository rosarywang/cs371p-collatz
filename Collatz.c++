// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2016
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

//#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair
#include <tr1/unordered_map>

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


int cycle_length (int n, tr1::unordered_map<int, int> storage) {
    // //assert(n > 0);
   if(storage.count(n)>0)
        return storage[n];
    int step = 1;
    if(n>1)
    {
        if ((n % 2) == 0)
            step += (cycle_length(n/2,storage));
        else
            step += (cycle_length((3 * n)+1,storage));

    }
    if(storage.count(n)==0)
    {
        storage.insert({n,step});
    }
        
    return step;
    //assert(c > 0);
    }


int collatz_eval (int i, int j) {
    // <your code>
    //assert(i > 0);
    //assert(j > 0);
    //assert(i <= 1000000);
    //assert(j <= 1000000);
    //assert(i <= j);
    
    tr1::unordered_map<int, int> storage;
    
    int n = -1;
    if(j < i){
        int t = j;
        j = i;
        i = t;}
    int m = (j-i)/2;
    while(m > i)
    {
        i=m;
        m=(j-i)/2;
    }
    for(int p = i; p <= j; p++){
        int t = cycle_length(p, storage);
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
