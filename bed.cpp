#include <iostream>
#include "bed.hpp"
using namespace std;

bed::bed()
{
    number_of_bed = 0;
    empty = true;
    patient = nullptr;
}

bool bed::get_isempty()
{
    return empty;
}

void bed::set_empty(bool empty)
{
    this->empty = empty;
}

void bed::set_patient(Patient *newpatient)
{
    this->patient = newpatient;
    // patient->number_of_patient = newpatient->number_of_patient;
    // patient->death_time = newpatient->death_time;
    // patient->enter_time = newpatient->enter_time;
    // patient->process_time = newpatient->process_time;
}
Patient *bed::get_patient()
{
    return patient;
}