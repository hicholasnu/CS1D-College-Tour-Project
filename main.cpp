
#include "CollegeClass.h"


int main()
{
	PlanTrip myTrip;

	string startAt;

	myTrip.ReadFile();


	cout << "\nPlanning Trip #1: " ;
	startAt = "Arizona State University";

	cout << myTrip.planTrip(startAt, 14);


	cout << "Planning Trip #2: ";
	startAt = "University of California, Irvine (UCI)";

	cout << myTrip.planTrip(startAt, 11);


	cout << "Planning Trip #3: ";
	startAt = "Saddleback College";

	cout << myTrip.planTrip(startAt, 13);

	

	return 0;
}
