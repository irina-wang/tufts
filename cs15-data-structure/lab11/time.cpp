#include <iostream>
#include <chrono>
#include <cmath>

using namespace std;
using namespace chrono; 


// Function recursive_Fib
// Inputs: unsigned int i
// Returns: The i-th Fibonacci number
// Does: Computes the i-th fibonacci number with the naive method
int recursive_Fib(unsigned int n){
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    else{
        return recursive_Fib(n-1) + recursive_Fib(n-2);    
    }
    return -1;
}

// Function recursive_Fib_with_info
// Inputs: unsigned int i
// Returns: The i-th Fibonacci number
// Does: Computes the i-th fibonacci number with the naive method
int recursive_Fib_with_info(unsigned int n, unsigned int p0, unsigned int p1){
    if(n == 0)
        return p0;
    if(n == 1)
        return p1;
    else{
        return recursive_Fib_with_info(n-1,p1,p0+p1);
    }
    return -1;
}

// Function recursive_Fib_with_info
// Inputs: unsigned int i
// Returns: The i-th Fibonacci number
// Does: Computes the i-th fibonacci number directly (without recursion)
int Fib_with_power(unsigned int n){
    // Note that we add 0.5 to the usual formula
    // this is done so that rounding works properly
    return uint((pow((1+sqrt(5))/2,n)-pow((1-sqrt(5))/2,n))/sqrt(5)+0.5);
}


int main(int argc, char *argv[]){
        unsigned int value;
        unsigned int i;
        high_resolution_clock::time_point start, end;
        milliseconds elapsed1, elapsed2, elapsed3;
        // Moments in time are represented by time_points. They are defined 
        // relative to the clocks in the chrono library
        //
        // Chrono has the following clocks
        //      high_resolution_clock: most precise clock
        //      steady_clock:          specifically designed to calculate time 
        //                             intervals.
        //      system_clock:          a system-wide realtime clock.


        if (argc!=2){
                cout << "Error. This program needs two parameters." << endl;
                exit(1);
        }

        value = stoi(argv[1]);


        for(i = 0; i < value; i ++){
            /********************RECURSIVE********************/
            // Get starting time_point
            start = high_resolution_clock::now();
            recursive_Fib(i);
            //cout << value << "-th Fibonacci number, RECURSIVELY." << endl;
            //cout << "Result: " << recursive_Fib(i) << endl;

            // TODO (task 5)

            // Get ending time_point
            end = high_resolution_clock::now();
            // Durations can be converted to various units of time
            elapsed1 = duration_cast<milliseconds>(end - start);
            // elapsed1.count() is the duration length
            //cout << "Took " << elapsed1.count() << " milliseconds" <<endl;

            /**********************INFO**********************/
            start = high_resolution_clock::now();
            recursive_Fib_with_info(i,0,1);
            //cout << value << "-th Fibonacci number, WITH INFO." << endl;
            //cout << "Result: " << recursive_Fib_with_info(i,0,1) << endl;

            // TODO (task 5)

            end = high_resolution_clock::now();
            elapsed2 = duration_cast<milliseconds>(end - start);
            //cout << "Took " << elapsed2.count() << " milliseconds" << endl;

            /**********************POWER**********************/
            start = high_resolution_clock::now();
            Fib_with_power(i);
            //cout << value << "-th Fibonacci number, WITH POWER." << endl;
            // cout << "Result: " << Fib_with_power(i) << endl;
            end = high_resolution_clock::now();
            elapsed3 = duration_cast<milliseconds>(end - start);
           // cout << "Took " << elapsed3.count() << " milliseconds" << endl;

            /**********************PRINT**********************/

            // TODO (task 5)

            cout <<  i  << "\t" << elapsed1.count() 
                        << "\t" << elapsed2.count()
                        << "\t" << elapsed3.count() << endl;
        }

}