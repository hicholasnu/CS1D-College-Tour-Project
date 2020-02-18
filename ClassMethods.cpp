#include "CollegeClass.h"

//#define DEBUG;

PlanTrip::PlanTrip()
{
	collegeListCount = 0;
	colleges.clear();
	plan.clear();
}
PlanTrip::~PlanTrip()
{
	colleges.clear();
	plan.clear();
}

void PlanTrip::ReadFile()
{
	ifstream infile;
	College newNode =  {"", "", 0};

	int counter = 1;

	infile.open("Infile.txt");
	//infile.open("InputFile.txt");

	cout<< "Reading from file\n";


	while(infile)
	{

		getline (infile, newNode.startCollege);

		getline (infile, newNode.endCollege);

		infile >> newNode.distance;
		infile.ignore(10000, '\n');
		infile.ignore(10000, '\n');

		newNode.marker = counter++;

		colleges.push_back(newNode);
		collegeListCount++;

		newNode.startCollege.clear();
		newNode.endCollege.clear();
		newNode.distance = -1;
	}
	cout << "Totaling " << collegeListCount << endl;

	infile.close();
}

string PlanTrip::planTrip(string starting, int numColleges)
{
	ostringstream output;
	deque<College> listings;
	College node;
	string target = starting;
	plan.clear();

	output << "Starting at " << starting << "and trying to find " << numColleges << " colleges."  <<endl;

	for(int i = 0; i < numColleges; i++)
	{

		listings = GroupedList(target);

		if(findClosest(node, listings))
		{
			plan.emplace_back(node);
			output 	<< "#" << i+1
					<< ") We will go FROM \""<< node.startCollege <<"\"\n\t\tTO  \""
					<< node.endCollege << "\"\nWhich is " << node.distance << "  miles away\n\n";

			target = node.endCollege;

#ifdef DEBUG
cerr << "\t closest is " << node.endCollege << "with "<< colleges.size() << " left!" << endl;
cerr << "Now looking for " << target << endl;
#endif

		}
		else
		{
			i = numColleges;
		}
	}

#ifdef DEBUG
cerr << Display(plan);
#endif

	plan.clear();

	return output.str();
}

bool PlanTrip::findClosest(College &target,const deque<College> &list)
{
	int index = 0;
	bool found = false;
	int closest = 1000000000;

	for(unsigned int i = 0; i < list.size(); i++)
	{

#ifdef DEBUG
cerr << list[i].distance << "|\t";
#endif
		if( list[i].distance < closest)
		{

			closest = list[i].distance;
			index = i;

			found = true;
		}
	}
	if(found)
	{
		target = list[index];
	}
#ifdef DEBUG
if(found)
	cerr << "\nFound for "<< target.startCollege <<" the closest is " << target.endCollege << " at " << target.distance << endl;

else
	cerr << "NOT FOUND!\n\n";

#endif


	return found;
}

// TRUE if the target (the college) is already in the list
bool PlanTrip::AlrdyInList(string target)
{
	bool inList = false;

	for(unsigned int i = 0; i < plan.size() && !inList; i++)
	{
		if(plan[i].startCollege == target)
			inList = true;
	}

	return inList;
}

deque<College> PlanTrip::GroupedList(string college)
{
	deque<College> group;
#ifdef DEBUG
cerr << "Creating Listings:\n";
#endif
	for(int index = 0; index < collegeListCount; index++)
	{
		if(colleges[index].startCollege == college && !AlrdyInList(colleges[index].endCollege))
		{
			group.emplace_back(colleges[index]);
#ifdef DEBUG
cerr << "Adding " << colleges[index].startCollege << " that ends at " << colleges[index].endCollege  << endl;
#endif
		}
	}
#ifdef DEBUG
cerr <<endl;
#endif


	return group;
}


string PlanTrip::Display(const deque<College> &list)
{
	ostringstream output;

	for(unsigned int i = 0; i < list.size(); i++)
	{
		output << "#"<< i+1 <<" College #"<< list[i].marker << endl;
		output << "\t" << list[i].startCollege << endl;
		output << "\t" << list[i].endCollege << endl;
		output << "\t" << list[i].distance << endl << endl;
	}

	return output.str();
}

void PlanTrip::displayTotal()
{
	cout << "Totalling " << collegeListCount << " | " << colleges.size();
}
