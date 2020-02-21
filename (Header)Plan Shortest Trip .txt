/*
 * CollegeClass.h
 *
 *  Created on: Feb 16, 2020
 *      Author: licab
 */

#ifndef COLLEGECLASS_H_
#define COLLEGECLASS_H_

#include <iostream>		// cin, cout
#include <iomanip>		// setw(), fixed etc.
#include <string>		// string class
#include <fstream>

#include <deque>

using namespace std;

struct College
{
	string startCollege;
	string endCollege;
	int distance;
	int marker;

};

class PlanTrip
{
public:

	PlanTrip();
	~PlanTrip();

void ReadFile();

string planTrip(string starting, int numColleges);

bool findClosest(College &target, const deque<College> &list);

bool AlrdyInList(string target);

string Display(const deque<College> &list);

deque<College> GroupedList(string college);

void displayTotal();

private:
deque<College> colleges;

int collegeListCount;

deque<College> plan;

};





#endif /* COLLEGECLASS_H_ */
