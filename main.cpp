#include <iostream>
#include <queue>
#include "Patient.hpp"
#include "Hospital.hpp"

using namespace std;

int main()
{
    int bed_number, patient_num;
    cout << "🔴 Capacity of hospital beds : ";
    cin >> bed_number;

    Hospital hospital = Hospital(bed_number);
    cout << "🟠 How many Patients do we have? ";
    cin >> patient_num;
    for (size_t i = 0; i < patient_num; i++)
    {
        int patient_num, enter_time, proccess_time, death_time;
        cout << "📋 patients number >>> ";
        cin >> patient_num;
        cout << "📋 patients enter time >>> ";
        cin >> enter_time;
        cout << "📋 patients process time >>> ";
        cin >> proccess_time;
        cout << "📋 patients death time >>> ";
        cin >> death_time;
        cout << "------------------------------------------------------------" << endl;
        hospital.set_Patients_fcfs(patient_num, enter_time, proccess_time, death_time);
    }
    // hospital.set_Patients_fcfs(1, 0, 3, 10);
    // hospital.set_Patients_fcfs(2, 0, 3, 7);
    // hospital.set_Patients_fcfs(3, 1, 2, 5);
    // hospital.set_Patients_fcfs(4, 1, 5, 11);
    // hospital.set_Patients_fcfs(5, 2, 3, 6);

    hospital.FirstComeFirstServed();

    return 0;
}