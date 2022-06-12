/*
 * Filename: Patient.h
 * Author: Hayden Wolff
 * Contains: Interface for patient class
 * Comp 15 Lab 10 Fall 2018: Heaps
 *
 */

#include <string>
using namespace std;

#ifndef PATIENT_H_
#define PATIENT_H_

enum Priority { ONE=1, TWO=2, THREE=3, FOUR=4, FIVE=5 };
const unsigned MIN_PULSE = 90;
const double MAX_TEMP = 100;

class Patient
{
public:
    Patient();
    Patient(string, string);

    void calculate_priority(bool, bool, double, unsigned);
    bool arrived_earlier_than(Patient) const;

    friend bool operator < (const Patient &, const Patient &);
    friend bool operator > (const Patient &, const Patient &);
    friend ostream & operator << (ostream &, const Patient &);

private:
    string fname, lname;
    bool head_wound;
    bool chest_pain;
    double temp;
    unsigned pulse;
    int time_in;
    Priority priority;
};

#endif
