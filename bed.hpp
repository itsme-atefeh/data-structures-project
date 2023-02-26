#ifndef BED_HPP
#define BED_HPP
#include "Patient.hpp"
using namespace std;
class bed
{
private:
    int number_of_bed;
    bool empty;
    Patient *patient;

public:
    bed();
    bool get_isempty();
    void set_empty(bool);
    void set_patient(Patient *);
    Patient *get_patient();
};

#endif