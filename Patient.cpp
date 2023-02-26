#include <iostream>
#include "Patient.hpp"
using namespace std;

Patient::Patient(int number_of_patient, int enter_time, int process_time, int death_time)
{
    this->number_of_patient = number_of_patient;
    this->death_time = death_time;
    this->process_time = process_time;
    this->enter_time = enter_time;
    insert_time = 0;
}

void Patient::set_bed_number(int bed)
{
    bed_number = bed;
}
int Patient::get_bed_number()
{
    return bed_number;
}
void Patient::set_insert(int insert)
{
    insert_time = insert;
}
int Patient::get_insert()
{
    return insert_time;
}