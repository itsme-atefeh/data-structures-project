#ifndef HOSPITAL_HPP
#define HOSPITAL_HPP

#include <queue>
#include <array>
#include <vector>
#include "Patient.hpp"
#include "bed.hpp"

using namespace std;
class CompareSfj
{
public:
    bool operator()(Patient *first, Patient *second)
    {
        return first->process_time > second->process_time;
    }
};

class ComparePs
{
public:
    bool operator()(Patient *first, Patient *second)
    {
        // if two patients have the same process time compare based on death time
        if (first->process_time == second->process_time)
        {
            return first->death_time > second->death_time;
        }
        else
        {
            return first->process_time > second->process_time;
        }
    }
};

class Hospital
{
private:
    vector<bed> beds;
    int bed_num;
    int died_patients;
    int alive_patients;
    int time_left;
    queue<Patient *> waiting_line;
    int clock;

    // second algorithm
    priority_queue<Patient *, vector<Patient *>, CompareSfj> sjfQueue;
    // third algorithm
    priority_queue<Patient *, vector<Patient *>, ComparePs> psQueue;

public:
    Hospital(int);
    void set_Patients(int, int, int, int);
    void FirstComeFirstServed();
    void priority_scheduling();
    void SJF();
    bool available_bed();
    int number_available_bed();
    bool full_bed();
};

#endif