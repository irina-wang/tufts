/*
 * Filename: Patient.cpp
 * Author: Hayden Wolff
 * Contains: Implementation for Patient class
 * Comp 15 Lab 10 Fall 2018: Heaps
 *
 */

#include <iostream>
#include "Patient.h"
using namespace std;

// Function: constructor
// Parameters: none
// Returns: nothing
// Does: default constructor, creates a standard patient
Patient::Patient()
{
    fname = "Jane";
    lname = "Doe";
    chest_pain = false;
    head_wound = false;
    temp = 98.6;
    pulse = 0;
    priority = FIVE;
}

// Function: constructor
// Parameters: string first name, string last name
// Returns: none
// Does: parameterized constructor, creates a patient with
//       a first name and last name
Patient::Patient(string f, string l)
{
    fname = f;
    lname = l;
}

// Function: calculate_priority
// Parameters: bool cp (chest pain), bool hw (head wound), 
//             double t (temp), unsigned p (pulse)
// Returns: nothing
// Does: calculates priority based on chest pain, head wound,
//       temperature, and pulse
void Patient::calculate_priority(bool cp, bool hw, double t, unsigned p)
{
    head_wound = hw;
    chest_pain = cp;
    temp = t;
    pulse = p;
    
    if(p == 0){
        priority = ONE;
    }
    else if(cp) {
        priority = TWO;
    }
    else if(hw) {
        priority = THREE;
    }
    else if(p > 150) {
        priority = FOUR;
    } else {
        priority = FIVE;
    }
}    

// Function: comparison operator
// Parameters: Patient 1 (by reference), patient 2 (by reference)
// Returns: bool, true if patient 1 priority less than patient 2
// Does: overloads less than comparison operator
bool operator < (const Patient &p1, const Patient &p2)
{
    if (p1.priority < p2.priority)
        return true;
    else if (p1.priority > p2.priority)
        return false;
    else
        return (p2.arrived_earlier_than(p1));
}

// Function: comparison operator
// Parameters: Patient 1 (by reference), patient 2 (by reference)
// Returns: bool, true if patient 1 priority greater than patient 2
// Does: overloads greater than than comparison operator
bool operator > (const Patient &p1, const Patient &p2)
{
    if (p1.priority > p2.priority)
        return true;
    else if (p1.priority < p2.priority)
        return false;
    else
        return (p2.arrived_earlier_than(p1));
}

// Function: ostream operator
// Parameters: ostream output (by reference), patient (by reference)
// Returns: none
// Does: prints the patient
ostream & operator << (ostream &out, const Patient &p)
{
    out << p.fname << " " << p.lname << endl;
    out << ((p.head_wound) ? "Head wound\n" : "");
    out << ((p.chest_pain) ? "Chest pain\n" : "");
    out << "Pulse: " << p.pulse << endl;
    out << "Temp: " << p.temp << endl;
    out << "PRIORITY " << p.priority << endl;
    return out;
}

// Function: arrived_earlier_than
// Parameters: Patient p
// Returns: bool
// Does: determines which of two patients arrived first
bool Patient::arrived_earlier_than(Patient p) const
{
    return (time_in < p.time_in);
}