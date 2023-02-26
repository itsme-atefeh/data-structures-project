#include <iostream>
#include "Hospital.hpp"
#include "Patient.hpp"
#include "bed.hpp"
using namespace std;

Hospital::Hospital(int bed_num)
{
    this->bed_num = bed_num;
    alive_patients = 0;
    died_patients = 0;
    for (size_t i = 0; i < bed_num; i++)
    {
        beds.push_back(bed());
    }
    clock = 0;
}

void Hospital::set_Patients(int patient_num, int enter_time, int proccess_time, int death_time)
{
    Patient *patient = new Patient(patient_num, enter_time, proccess_time, death_time);
    waiting_line.push(patient);
}

void Hospital::FirstComeFirstServed()
{
    int patients_n = waiting_line.size();
    while (!waiting_line.empty() || full_bed())
    {
        if (!waiting_line.empty() && available_bed())
        {
            int i = number_available_bed();
            beds[i].set_empty(false);
            Patient *temp = waiting_line.front();
            beds[i].set_patient(temp);
            temp->set_insert(clock);
            temp->set_bed_number(i);
            waiting_line.pop();
            time_left += clock - temp->enter_time;
            // waiting_line.push(temp);
            // cout << " a patient got bed " << temp->get_bed_number() << endl;
        }
        for (size_t i = 0; i < bed_num; i++)
        {
            // cout << "  time elapsed   " << clock - beds[i].get_patient()->get_insert() << endl;
            // beds[i].get_isempty() ? cout << "is empty" : cout << "not empty" << endl;
            // cout << beds[i].get_patient()->get_insert() << endl;
            if (!beds[i].get_isempty() && beds[i].get_patient()->process_time <= clock - beds[i].get_patient()->enter_time)
            {
                beds[i].set_empty(true);
                alive_patients++;
                cout << "🔵 Patient number # " << beds[i].get_patient()->number_of_patient << " was discharged from bed # "
                     << beds[i].get_patient()->get_bed_number() << endl;
                delete beds[i].get_patient();

                if (!waiting_line.empty() && available_bed())
                {
                    int i = number_available_bed();
                    beds[i].set_empty(false);
                    Patient *temp = waiting_line.front();
                    beds[i].set_patient(temp);
                    temp->set_insert(clock);
                    temp->set_bed_number(i);
                    waiting_line.pop();
                    time_left += clock - temp->enter_time;
                    // waiting_line.push(temp);
                    // cout << " a patient got bed " << temp->get_bed_number() << endl;
                }
            }
        }

        for (size_t i = 0; i < waiting_line.size(); i++)
        {
            Patient *temp = waiting_line.front();
            if (temp->death_time <= clock - temp->get_insert())
            {
                died_patients++;
                cout << "🔵 Patient number # " << temp->number_of_patient << " was died" << endl;
                waiting_line.pop();
                delete temp;
            }
            else
            {
                waiting_line.pop();
                waiting_line.push(temp);
            }
        }
        clock++;
    }

    cout << "total waited time : " << time_left << endl;
    cout << "total died : " << died_patients << endl;
    cout << "total alive : " << alive_patients << endl;
}

void Hospital::SJF()
{
    int patients_n = waiting_line.size();
    while (!waiting_line.empty() || full_bed() || !sjfQueue.empty())
    {
        if (!sjfQueue.empty() && available_bed())
        {
            int i = number_available_bed();
            beds[i].set_empty(false);
            Patient *temp = sjfQueue.top();
            temp->set_insert(clock);
            temp->set_bed_number(i);
            beds[i].set_patient(temp);
            sjfQueue.pop();
            time_left += clock - temp->enter_time;
            // waiting_line.push(temp);
            // cout << " a patient got bed " << temp->get_bed_number() << endl;
        }
        else if (!waiting_line.empty())
        {
            waiting_line.front()->set_insert(clock);
            sjfQueue.push(waiting_line.front());
            waiting_line.pop();
        }
        for (size_t i = 0; i < bed_num; i++)
        {
            // cout << "  time elapsed   " << clock - beds[i].get_patient()->get_insert() << endl;
            // beds[i].get_isempty() ? cout << "is empty" : cout << "not empty" << endl;
            // cout << beds[i].get_patient()->get_insert() << endl;
            if (!beds[i].get_isempty() && beds[i].get_patient()->process_time <= clock - beds[i].get_patient()->enter_time)
            {
                beds[i].set_empty(true);
                alive_patients++;
                cout << "🔵 Patient number # " << beds[i].get_patient()->number_of_patient << " was discharged from bed # "
                     << beds[i].get_patient()->get_bed_number() << endl;
                delete beds[i].get_patient();

                if (!waiting_line.empty() && available_bed())
                {
                    int i = number_available_bed();
                    beds[i].set_empty(false);
                    Patient *temp = waiting_line.front();
                    beds[i].set_patient(temp);
                    temp->set_insert(clock);
                    temp->set_bed_number(i);
                    waiting_line.pop();
                    time_left += clock - temp->enter_time;
                    // waiting_line.push(temp);
                    // cout << " a patient got bed " << temp->get_bed_number() << endl;
                }
            }
        }
        for (size_t i = 0; i < sjfQueue.size(); i++)
        {
            Patient *temp = sjfQueue.top();
            if (temp->death_time <= clock - temp->get_insert())
            {
                died_patients++;
                cout << "🔵 Patient number # " << temp->number_of_patient << " was died" << endl;
                sjfQueue.pop();
                delete temp;
            }
            else
            {
                sjfQueue.pop();
                sjfQueue.push(temp);
            }
        }
        clock++;
    }

    cout << "total waited time : " << time_left << endl;
    cout << "total died : " << died_patients << endl;
    cout << "total alive : " << alive_patients << endl;
}

void Hospital::priority_scheduling()
{
    int patients_n = waiting_line.size();
    while (!waiting_line.empty() || full_bed() || !psQueue.empty())
    {
        if (!psQueue.empty() && available_bed())
        {
            int i = number_available_bed();
            beds[i].set_empty(false);
            Patient *temp = psQueue.top();
            temp->set_insert(clock);
            temp->set_bed_number(i);
            beds[i].set_patient(temp);
            psQueue.pop();
            time_left += clock - temp->enter_time;
            // waiting_line.push(temp);
            // cout << " a patient got bed " << temp->get_bed_number() << endl;
        }
        else if (!waiting_line.empty())
        {
            waiting_line.front()->set_insert(clock);
            psQueue.push(waiting_line.front());
            waiting_line.pop();
        }
        for (size_t i = 0; i < bed_num; i++)
        {
            // cout << "  time elapsed   " << clock - beds[i].get_patient()->get_insert() << endl;
            // beds[i].get_isempty() ? cout << "is empty" : cout << "not empty" << endl;
            // cout << beds[i].get_patient()->get_insert() << endl;
            if (!beds[i].get_isempty() && beds[i].get_patient()->process_time <= clock - beds[i].get_patient()->enter_time)
            {
                beds[i].set_empty(true);
                alive_patients++;
                cout << "🔵 Patient number # " << beds[i].get_patient()->number_of_patient << " was discharged from bed # "
                     << beds[i].get_patient()->get_bed_number() << endl;
                delete beds[i].get_patient();

                if (!waiting_line.empty() && available_bed())
                {
                    int i = number_available_bed();
                    beds[i].set_empty(false);
                    Patient *temp = waiting_line.front();
                    beds[i].set_patient(temp);
                    temp->set_insert(clock);
                    temp->set_bed_number(i);
                    waiting_line.pop();
                    time_left += clock - temp->enter_time;
                    // waiting_line.push(temp);
                    // cout << " a patient got bed " << temp->get_bed_number() << endl;
                }
            }
        }
        for (size_t i = 0; i < psQueue.size(); i++)
        {
            Patient *temp = psQueue.top();
            if (temp->death_time <= clock - temp->get_insert())
            {
                died_patients++;
                cout << "🔵 Patient number # " << temp->number_of_patient << " was died" << endl;
                psQueue.pop();
                delete temp;
            }
            else
            {
                psQueue.pop();
                psQueue.push(temp);
            }
        }
        clock++;
    }

    cout << "total waited time : " << time_left << endl;
    cout << "total died : " << died_patients << endl;
    cout << "total alive : " << alive_patients << endl;
}

bool Hospital::available_bed()
{
    for (size_t i = 0; i < bed_num; i++)
    {
        if (beds[i].get_isempty())
        {
            return true;
        }
    }
    return false;
}
bool Hospital::full_bed()
{
    for (size_t i = 0; i < bed_num; i++)
    {
        if (!beds[i].get_isempty())
        {
            return true;
        }
    }
    return false;
}
int Hospital::number_available_bed()
{
    for (size_t i = 0; i < bed_num; i++)
    {
        if (beds[i].get_isempty())
        {
            return i;
        }
    }
    return -1;
}