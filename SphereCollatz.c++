#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair
#include <math.h>   // pow
#include <stdlib.h> // abs

using namespace std;

#define CACHE

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

#ifdef CACHE
int storage[33] = {0,1,2,8,3,6,9,17,4,20,7,15,10,10,18,18,5,13,21,21,8,8,16,16,11,24,11,112,19,19,19,107,6};
#endif

int collatz_eval (int i, int j) {

    i=abs(i);
    j=abs(j);

    if(j < i) {
        int temp = j;
        j = i;
        i = temp;
    } 

    /*
      check if the search space can be reduce by half
      save time by not searching for interval that would not contain the max cycle length
    */
    int m = (j - i) / 2;
    if(m > i)
        i = m;
    
    int max = -1;

    for(int p = i; p <= j; ++p) {

        int step = 1;

        long q = (long)p;

        /*
           an time space trade oof optimization based on modular restriction
           this algorithm allows the program to calculate the value of 3n+1/n/2 5 steps ahead
           cut meaningless computation on value that is not the final answer
        */
        while(q > 32 ) {
            long a = q >> 5;
            long b = q % 32;
            q = a * (long)pow(3, c[(int)b]) + d[(int)b];
            step += 5 + (int)c[(int)b];
        }

        /*
           the only cache implemented
           tried storing and retrieving cache at other location, but it only slows down the program
        */
        #ifdef CACHE
        if(q > 0){
            step += storage[(int)q] - 1;
            q = 1;
        }
        #endif 

        /*  if no cache, then return to the old method  */
        #ifndef CACHE
        while(q > 1) {
            if((q % 2) == 0) {
                q = q / 2;
                ++step;
            }
            else {
                q = q + (q >> 1) + 1;
                step += 2;
            }
        }
        #endif

        if(step > max)
            max = step;
    }

    return max;
}
    
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
    collatz_solve(cin, cout);
    return 0;}