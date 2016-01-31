#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair
#include <tr1/unordered_map>
#include <math.h> 

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
tr1::unordered_map<int, int> storage;
bool arr[1000000] = {false};

// int cycle_length (int n, int step) {
//     // //assert(n > 0);
//     if(storage[n]!=0)
//         return storage[n]+step-1;
//     if(n>1)
//     {
//         if ((n % 2) == 0)
//             step = (cycle_length((n/2),step+1));
//         else
//             step = (cycle_length(((3 * n)+1),step+1));

//     }
//     return step;
//     //assert(c > 0);
//     }

int cycle_length (int n) {
    // //assert(n > 0);
    if(n<1000000 && arr[n-1])
        return storage[n];
    int step = 1;
    if(n>1)
    {
        if ((n % 2) == 0)
            step += (cycle_length(n/2));
        else
            step += (cycle_length((3 * n)+1));

    }
    if(n<1000000 && arr[n-1]==false)
        storage[n]=step;
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
    

    int n = 0;
    if(j < i){
        int t = j;
        j = i;
        i = t;}
    int m = (j - i) / 2;
    if(i > m)
        m = i;
    for(int p = m; p <= j; p++){
        int t = cycle_length(p);
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

// ----
// main
// ----


int main () {
    // storage[10]=7;
    // storage[16]=5;
    // storage[22]=16;
    // storage[28]=19;
    // storage[34]=14;
    // storage[40]=9;
    // storage[46]=17;
    // storage[52]=12;
    // storage[58]=20;
    // storage[64]=7;
    // storage[70]=15;
    // storage[76]=23;
    // storage[82]=111;
    // storage[88]=31;
    // storage[94]=106;
    // storage[100]=26;
    // storage[106]=13;
    // storage[112]=21;
    // storage[118]=34;
    // storage[124]=109;
    collatz_solve(cin, cout);
    return 0;}

