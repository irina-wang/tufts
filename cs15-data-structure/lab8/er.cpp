/*
 * Filename: er.cpp (solution)
 * Author: Hayden Wolff
 * Contains: Driver for heap lab, calculates patient priority
 * Comp 15 Lab 10 Fall 2018: Heaps
 *
 */

#include <iostream>
#include <fstream>
#include <string>
#include "Patient.h"
#include "MinHeap.h"
#include "Queue.h"
using namespace std;

const string PATIENT_FILE = "patients.txt";

int read_in_patients(Queue<Patient> &, string);
void heapsort(Queue<Patient> &, MinHeap<Patient>);
void print_patients(Queue<Patient>);

int main()
{
    Queue<Patient> patients;
    int count = read_in_patients(patients, PATIENT_FILE);
    cout << "read in " << count << " patients\n";

    
    MinHeap<Patient> patient;

    while(!patients.is_empty()){
        patient.insert_item(patients.dequeue());
    }

    heapsort(patients, patient); 

    cout << "Most important patient to see:\n";

    cout << patients.dequeue() << endl;

    cout << "\n\nEveryone else, in priority order:\n";
    print_patients(patients);

    return 0;
}

// Function: read_in_patients
// Parameters: Queue of Patients by reference, string for file
// Returns: int number of patients read in
// Does: Enqueues patients in order
int read_in_patients(Queue<Patient> &p, string filename)
{
    ifstream infile;
    infile.open(filename.c_str());
    if (!infile.is_open())
        return 0;

    string fname, lname;
    char chest, head;
    unsigned pulse;
    double temp;

    int count = 0;
    while (!infile.eof())
    {
        infile >> fname;
        if (fname == "-1")
            return count;
        infile >> lname >> chest >> head >> pulse >> temp;

        Patient pat(fname, lname);
        pat.calculate_priority((chest == 'C' ? true : false), 
                               (head == 'H' ? true : false),
                               temp, pulse);

        try
        {
            p.enqueue(pat);
        }
        catch (FullQueue exception)
        {
            return 0;
        }

        count++;
    }
    infile.close();
    return count;
}

// Function: heapsort
// Parameters: Queue of Patients by reference, MinHeap of Patients
// Returns: none
// Does: enqueues from patient queue after extracting from heap
void heapsort(Queue<Patient> &p, MinHeap<Patient> h)
{
    p.make_empty();
    while (!h.is_empty())
    {
        try
        {
            p.enqueue(h.extract());
        }
        catch (EmptyHeap exception)
        {
            cerr << exception.what();
        }
    }
}

// Function: print_patients
// Parameters: Queue of Patients
// Returns: none
// Does: prints patients by dequeuing off patient queue
void print_patients(Queue<Patient> p)
{
    try
    {
        while (!p.is_empty())
        {
            cout << p.dequeue();
            cout << endl;
        }
    }
    catch (EmptyQueue exception)
    {
        cerr << exception.what();
    }
}
