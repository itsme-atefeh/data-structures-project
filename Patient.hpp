#ifndef PATIENT_HPP
#define PATIENT_HPP

class Patient
{
private:
    // we will calculate this elements later
    int bed_number;
    int insert_time;

public:
    int number_of_patient;
    int death_time;
    int process_time;
    int enter_time;

    Patient(int, int, int, int);
    void set_bed_number(int);
    int get_bed_number();
    void set_insert(int);
    int get_insert();
};

#endif