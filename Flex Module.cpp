#include<iostream>
#include<fstream>
#include<iomanip>

using namespace std;

// Forward Decleration
class EvaluationModule;

// Global Functions' Prototypes
EvaluationModule* ReadDataFromFile();
inline void PrintAll(EvaluationModule*);
inline void PrintAll(EvaluationModule**);
EvaluationModule** SearchStudentsByKeyWord(EvaluationModule*);
inline void SortListByTotal(EvaluationModule*);
EvaluationModule* StudentInformationFinder(EvaluationModule*);

// Class
class EvaluationModule
{
private:
	static const int ROLL_NUMBER_SIZE = 9;
	// Arrays
	char rollNumber[ROLL_NUMBER_SIZE] = "0";
	char* firstName;
	char* lastName;
	float* assignmentsObtained;
	float* quizzesObtained;
	// Variables
	float totalObtained;

	// Static Members
	static int totalQuizzes, totalAssignments, totalStudents;
	static float* assignmentsTotalMarks, * quizzesTotalMarks, * maximumQuizzes, * maximumAssignments,
		* minimumQuizzes, * minimumAssignments, * averageQuizzes, * averageAssignments;

	// Methods

	// It will Calculate Total Marks of Every Student
	inline void TotalCalculator();

	// It will Search String in Roll Number
	inline bool SearchRollNumber(char*);

	// It will Search String in First Name
	inline bool SearchFirstName(char*);

	// It will Search String in Last Name
	inline bool SearchLastName(char*);

public:

	// Default Constructor with Initialization List
	EvaluationModule();

	// Copy Constructor
	EvaluationModule(EvaluationModule&);

	// Destructor
	~EvaluationModule();

	// Assignment Operator
	inline void operator=(EvaluationModule&);
	// Methods

	// It will Read Input From File
	inline void ReadDataFromFile(ifstream& fin);

	// It will Print Data
	inline void PrintAll();

	// It will Take String and Search it
	inline bool SearchStudentsByKeyWord(char*);

	// It will Sort Student List with respec to Total Marks
	inline void SortListByTotal();

	// It will search in list and return address
	inline bool StudentInformationFinder(char*);

	// It will print Student's Information
	inline void StudentInformationPrinter();

	// It will read static data from file
	static void ReadStaticDataFromFile(ifstream&);

	// Getter of Total Students
	static int GetTotalStudents();

	// Getter of Total Assignments
	static int GetTotalAssignments();

	// Getter of Total Quizzes
	static int GetTotalQuizzes();

	// It will Deallocate the Memory
	static void Deallocator();

	// It will Finder Maximum Numbers in Quizzes and Assignments
	static void StatisticsFinder(EvaluationModule*);


	// It will Find Statistics
	static void StatisticsPrinter();
};

// Helper Functions Class
class Helper
{
public:
	// It will get array and Reduce it extra size
	inline static char* SizeAdjuster(char*);

	// It will Calculate the Length of character Array
	inline static int ArrayLength(char*);

	// It will copy 2D class Array
	inline static void Array2DCopy(EvaluationModule**, EvaluationModule**, const int);
};

// Main Function
int main()
{
	cout << "\n-----------------------------------------------------------Orignal List--------------------------------------------" << endl;
	EvaluationModule* studentList = ReadDataFromFile();
	PrintAll(studentList);

	cout << "\n\n-----------------------------------------------------------Filtered List--------------------------------------------\n" << endl;
	EvaluationModule** filteredList = SearchStudentsByKeyWord(studentList);
	if (filteredList != 0)
	{
		PrintAll(filteredList);
		delete[] filteredList;
		filteredList = 0;
	}
	else
	{
		cout << "No Record Found!!" << endl;
	}

	cout << "\n\n-----------------------------------------------------------Sorted List--------------------------------------------\n" << endl;
	SortListByTotal(studentList);
	PrintAll(studentList);

	cout << "\n\n----------------------------------------------------Student Information--------------------------------------\n" << endl;
	EvaluationModule* studentInformationList = StudentInformationFinder(studentList);
	if (studentInformationList != 0)
	{
		studentInformationList->StudentInformationPrinter();
	}
	else
	{
		cout << "\n\nStudent not Found" << endl;
	}

	cout << "\n\n----------------------------------------------------------Statistics----------------------------------------------\n" << endl;
	EvaluationModule::StatisticsFinder(studentList);
	EvaluationModule::StatisticsPrinter();

	EvaluationModule::Deallocator();
	delete[] studentList;

	return 0;
}

// Default Constructor with Initialization List
EvaluationModule::EvaluationModule() :firstName(0), lastName(0), assignmentsObtained(0), quizzesObtained(0), totalObtained(0)
{
	quizzesObtained = new float[totalQuizzes];
	assignmentsObtained = new float[totalAssignments];
}

// Copy Constructor
EvaluationModule::EvaluationModule(EvaluationModule& std)
{

	int i = 0;

	// For Roll Number
	while (i < ROLL_NUMBER_SIZE)
	{
		this->rollNumber[i] = std.rollNumber[i];
		i++;
	}

	// For First Name
	i = 0;

	firstName = new char[Helper::ArrayLength(std.firstName) + 1];

	while (std.firstName[i] != '\0')
	{
		this->firstName[i] = std.firstName[i];
		i++;
	}

	this->firstName[i] = '\0';

	// For Last Name
	i = 0;

	lastName = new char[Helper::ArrayLength(std.lastName) + 1];

	while (std.lastName[i] != '\0')
	{
		this->lastName[i] = std.lastName[i];
		i++;
	}

	this->lastName[i] = '\0';

	// For Assignments
	i = 0;

	assignmentsObtained = new float[totalAssignments];

	while (i < totalAssignments)
	{
		this->assignmentsObtained[i] = std.assignmentsObtained[i];
		i++;
	}

	// For Quizzes
	i = 0;

	quizzesObtained = new float[totalQuizzes];

	while (i < totalQuizzes)
	{
		this->quizzesObtained[i] = std.quizzesObtained[i];
		i++;
	}

	this->totalObtained = std.totalObtained;
}

// Destructor
EvaluationModule::~EvaluationModule()
{
	delete[] firstName;
	delete[] lastName;
	delete[] assignmentsObtained;
	delete[] quizzesObtained;
}

// Class Operators

// Assignment Operator
inline void EvaluationModule::operator=(EvaluationModule& std1)
{

	int i = 0;

	// For Roll Number
	while (i < ROLL_NUMBER_SIZE)
	{
		this->rollNumber[i] = std1.rollNumber[i];
		i++;
	}

	// For First Name
	i = 0;

	if (firstName != 0)
	{
		delete[] firstName;
		firstName = 0;
	}

	firstName = new char[Helper::ArrayLength(std1.firstName) + 1];

	while (std1.firstName[i] != '\0')
	{
		this->firstName[i] = std1.firstName[i];
		i++;
	}

	this->firstName[i] = '\0';

	// For Last Name
	i = 0;

	if (lastName != 0)
	{
		delete[] lastName;
		lastName = 0;
	}

	lastName = new char[Helper::ArrayLength(std1.lastName) + 1];

	while (std1.lastName[i] != '\0')
	{
		this->lastName[i] = std1.lastName[i];
		i++;
	}

	this->lastName[i] = '\0';

	// For Assignments
	i = 0;

	while (i < totalAssignments)
	{
		this->assignmentsObtained[i] = std1.assignmentsObtained[i];
		i++;
	}

	// For Quizzes
	i = 0;

	while (i < totalQuizzes)
	{
		this->quizzesObtained[i] = std1.quizzesObtained[i];
		i++;
	}

	this->totalObtained = std1.totalObtained;
}


// Class' Methods

// It will read static data from file
void EvaluationModule::ReadStaticDataFromFile(ifstream& fin)
{
	fin >> totalStudents;

	if (totalStudents > 0)
	{

		fin >> totalQuizzes;

		fin >> totalAssignments;

		// Allocation of Arrays

		quizzesTotalMarks = new float[totalQuizzes];
		assignmentsTotalMarks = new float[totalAssignments];

		int i = 0;

		// Input For Total Marks of Quizzes
		while (i < totalQuizzes)
		{
			fin >> quizzesTotalMarks[i];
			i++;
		}

		// Input For Total Marks of Assignments
		i = 0;
		while (i < totalAssignments)
		{
			fin >> assignmentsTotalMarks[i];
			i++;
		}
	}
}

// It will Read Input From File
inline void EvaluationModule::ReadDataFromFile(ifstream& fin)
{
	char buffer[80];

	fin >> rollNumber;

	fin >> buffer;
	firstName = Helper::SizeAdjuster(buffer);

	fin >> buffer;
	lastName = Helper::SizeAdjuster(buffer);

	for (int i = 0;i < totalQuizzes;i++)
	{
		fin >> quizzesObtained[i];
	}

	for (int i = 0;i < totalAssignments;i++)
	{
		fin >> assignmentsObtained[i];
	}
	TotalCalculator();
}

// It Will Print Data
inline void EvaluationModule::PrintAll()
{
	cout << rollNumber << "\t" << firstName << " " << lastName << "\t\t";
	for (int i = 0;i < totalQuizzes;i++)
	{
		cout << quizzesObtained[i] << "\t";
	}

	for (int i = 0;i < totalAssignments;i++)
	{
		cout << assignmentsObtained[i] << "\t";
	}

	cout << totalObtained;
	cout << endl;
}

// It will Calculate Total Marks of Every Student
inline void EvaluationModule::TotalCalculator()
{
	for (int i = 0;i < totalQuizzes;i++)
	{
		totalObtained += quizzesObtained[i];
	}
	for (int i = 0;i < totalAssignments;i++)
	{
		totalObtained += assignmentsObtained[i];
	}
}

// It will Take String and Search it
inline bool EvaluationModule::SearchStudentsByKeyWord(char* string)
{
	if (SearchRollNumber(string))
	{
		return true;
	}
	else
	{
		if (SearchFirstName(string))
		{
			return true;
		}
		else
		{
			if (SearchLastName(string))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

}

// It will Search String in Roll Number
inline bool EvaluationModule::SearchRollNumber(char* string)
{
	int i = 0, j = 0, size = Helper::ArrayLength(string);
	while (rollNumber[i] != '\0')
	{
		if (rollNumber[i] == string[j])
		{
			j++;
		}
		else
		{
			j = 0;
		}
		if (string[j] == '\0')
		{
			break;
		}
		i++;
	}

	if (j == size)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// It will Search String in First Name
inline bool EvaluationModule::SearchFirstName(char* string)
{
	int i = 0, j = 0, size = Helper::ArrayLength(string);
	while (firstName[i] != '\0')
	{
		if (firstName[i] == string[j])
		{
			j++;
		}
		else
		{
			j = 0;
		}
		if (string[j] == '\0')
		{
			break;
		}
		i++;
	}

	if (j == size)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// It will Search String in Last Name
inline bool EvaluationModule::SearchLastName(char* string)
{
	int i = 0, j = 0, size = Helper::ArrayLength(string);
	while (lastName[i] != '\0')
	{
		if (lastName[i] == string[j])
		{
			j++;
		}
		else
		{
			j = 0;
		}
		if (string[j] == '\0')
		{
			break;
		}
		i++;
	}

	if (j == size)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// It will Sort Student List with respec to Total Marks
inline void EvaluationModule::SortListByTotal()
{
	EvaluationModule temp;

	if (this->totalObtained > (*(this + 1)).totalObtained)
	{
		temp = *this;
		*this = (*(this + 1));
		(*(this + 1)) = temp;
	}
}

// It will search in list and return address
inline bool EvaluationModule::StudentInformationFinder(char* string)
{
	int i = 0, j = 0, size = Helper::ArrayLength(rollNumber);
	while (rollNumber[i] != '\0')
	{
		if (rollNumber[i] == string[j])
		{
			j++;
		}
		else
		{
			j = 0;
		}
		if (string[j] == '\0')
		{
			break;
		}
		i++;
	}

	if (j == size)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// It will print Student's Information
inline void EvaluationModule::StudentInformationPrinter()
{
	float total = 0.0;

	cout << "\n\nStudent Information:\n\nRoll No.:\t" << rollNumber << endl
		<< "Name:\t\t" << firstName << " " << lastName << "\nQuizzes Marks:\n\n";
	for (int i = 0;i < totalQuizzes;i++)
	{
		cout << "\t\tQ" << i + 1 << ":\t" << quizzesObtained[i] << " / " << quizzesTotalMarks[i] << endl;
		total += quizzesTotalMarks[i];
	}
	cout << "Assignments Marks:\n" << endl;
	for (int i = 0;i < totalAssignments;i++)
	{
		cout << "\t\tA" << i + 1 << ":\t" << assignmentsObtained[i] << "/" << assignmentsTotalMarks[i] << endl;
		total += assignmentsTotalMarks[i];
	}
	cout << "\nTotal:\t\t\t" << totalObtained << "/" << total << endl;
}

// Total Students getter
int EvaluationModule::GetTotalStudents()
{
	return totalStudents;
}

// Total Assignments getter
int EvaluationModule::GetTotalAssignments()
{
	return totalAssignments;
}

// Total Quizzes getter
int EvaluationModule::GetTotalQuizzes()
{
	return totalQuizzes;
}

// It will Finder Maximum Numbers in Quizzes and Assignments
void EvaluationModule::StatisticsFinder(EvaluationModule* studentList)
{
	int j = 0, temp = 0;
	float sum = 0;

	// Allocation
	maximumAssignments = new float[totalAssignments];
	maximumQuizzes = new float[totalQuizzes];
	minimumAssignments = new float[totalAssignments];
	minimumQuizzes = new float[totalQuizzes];
	averageAssignments = new float[totalAssignments];
	averageQuizzes = new float[totalQuizzes];

	while (j < totalQuizzes && j < totalAssignments)
	{
		if (j < totalAssignments)
		{
			sum = 0;
			// Maximum
			for (int i = 0;i < totalStudents;i++)
			{
				if (temp <= studentList[i].assignmentsObtained[j])
				{
					maximumAssignments[j] = studentList[i].assignmentsObtained[j];
					temp = studentList[i].assignmentsObtained[j];
				}
				sum += studentList[i].assignmentsObtained[j];
			}
			averageAssignments[j] = sum / totalStudents;

			temp = 0;
			// Minimum
			for (int i = 0;i < totalStudents;i++)
			{
				if (temp >= studentList[i].assignmentsObtained[j])
				{
					minimumAssignments[j] = studentList[i].assignmentsObtained[j];
					temp = studentList[i].assignmentsObtained[j];
				}
			}
		}

		// Quizzes
		if (j < totalQuizzes)
		{
			temp = 0;
			sum = 0;
			// Maximum
			for (int i = 0;i < totalStudents;i++)
			{
				if (temp <= studentList[i].quizzesObtained[j])
				{
					maximumQuizzes[j] = studentList[i].quizzesObtained[j];
					temp = studentList[i].quizzesObtained[j];
				}
				sum += studentList[i].assignmentsObtained[j];
			}
			averageQuizzes[j] = sum / totalStudents;

			// Minimum
			temp = 0;
			for (int i = 0;i < totalStudents;i++)
			{
				if (temp >= studentList[i].assignmentsObtained[j])
				{
					minimumQuizzes[j] = studentList[i].assignmentsObtained[j];
					temp = studentList[i].assignmentsObtained[j];
				}
			}
		}
		j++;
	}
}

// It will Find Statistics
void EvaluationModule::StatisticsPrinter()
{
	cout << "\n\t\t";
	for (int i = 0;i < totalQuizzes;i++)
	{
		cout << "Q" << i + 1 << "\t";
	}

	for (int i = 0;i < totalAssignments;i++)
	{
		cout << "A" << i + 1 << "\t";
	}
	cout << endl << endl;

	cout << "Total:\t\t";
	for (int i = 0;i < totalQuizzes;i++)
	{
		cout << quizzesTotalMarks[i] << "\t";
	}

	for (int i = 0;i < totalAssignments;i++)
	{
		cout << assignmentsTotalMarks[i] << "\t";
	}
	cout << endl;

	cout << "Maximum:\t";
	for (int i = 0;i < totalQuizzes;i++)
	{
		cout << maximumQuizzes[i] << "\t";
	}

	for (int i = 0;i < totalAssignments;i++)
	{
		cout << maximumAssignments[i] << "\t";
	}
	cout << endl;

	cout << "Minimum:\t";
	for (int i = 0;i < totalQuizzes;i++)
	{
		cout << minimumQuizzes[i] << "\t";
	}

	for (int i = 0;i < totalAssignments;i++)
	{
		cout << minimumAssignments[i] << "\t";
	}
	cout << endl;

	cout << "Average:\t";
	for (int i = 0;i < totalQuizzes;i++)
	{
		cout << setprecision(4) << averageQuizzes[i] << "\t";
	}

	for (int i = 0;i < totalAssignments;i++)
	{
		cout << setprecision(4) << averageAssignments[i] << "\t";
	}
	cout << endl;
}

// It will Deallocate the Memory
void EvaluationModule::Deallocator()
{
	delete[] assignmentsTotalMarks;
	delete[] quizzesTotalMarks;
	delete[] maximumAssignments;
	delete[] maximumQuizzes;
	delete[] minimumAssignments;
	delete[] minimumQuizzes;
	delete[] averageAssignments;
	delete[] averageQuizzes;

}


// Global Functions

// It will load data from file
EvaluationModule* ReadDataFromFile()
{
	ifstream fin;
	fin.open("gradesheet.txt");

	EvaluationModule* studentList = 0;

	if (fin.is_open())
	{

		EvaluationModule::ReadStaticDataFromFile(fin);

		int totalStudents = EvaluationModule::GetTotalStudents();

		if (totalStudents != 0)
		{

			int i = 0;

			studentList = new EvaluationModule[totalStudents];

			i = 0;
			while (i < totalStudents)
			{
				studentList[i].ReadDataFromFile(fin);
				i++;
			}
		}
	}
	fin.close();

	return studentList;
}

// It will Take String and Search it
EvaluationModule** SearchStudentsByKeyWord(EvaluationModule* studentList)
{
	char* tempString = new char[80];
	cout << "\n\nEnter Keyword Here:";
	cin >> tempString;
	//tempString[] = { '4','3','\0' };

	//tempString[0] = '4';
	//tempString[1] = '3';
	//tempString[2] = '\0';

	char* string = Helper::SizeAdjuster(tempString);

	delete[] tempString;
	tempString = 0;

	int totalStudents = EvaluationModule::GetTotalStudents();

	EvaluationModule** tempFiltered = new EvaluationModule * [totalStudents];
	int j = 0;

	for (int i = 0;i < totalStudents;i++)
	{
		if (studentList[i].SearchStudentsByKeyWord(string))
		{
			tempFiltered[j] = (studentList + i);
			j++;
		}
	}

	delete[] string;
	string = 0;

	if (j != 0)
	{
		EvaluationModule** filteredArray = new EvaluationModule * [j + 1];
		Helper::Array2DCopy(tempFiltered, filteredArray, j);
		filteredArray[j] = 0;
		delete[] tempFiltered;

		return filteredArray;
	}
	else
	{
		delete[] tempFiltered;
		return 0;
	}

}

// It will sort Student List with respect to Total Marks
void SortListByTotal(EvaluationModule* studentList)
{

	int totalStudents = EvaluationModule::GetTotalStudents();

	for (int i = 0;i < totalStudents;i++)
	{
		for (int j = 0;j < totalStudents - 1;j++)
		{
			studentList[j].SortListByTotal();
		}
	}
}

// It will take roll number and return the student Information
EvaluationModule* StudentInformationFinder(EvaluationModule* studentList)
{
	char rollNumber[9];
	cout << "Enter Roll Number Here: ";
	cin >> rollNumber;


	int totalStudents = EvaluationModule::GetTotalStudents();

	for (int i = 0;i < totalStudents;i++)
	{
		if (studentList[i].StudentInformationFinder(rollNumber))
		{
			return (studentList + i);
		}
	}
	return 0;
}

// It will Print Data
inline void PrintAll(EvaluationModule* studentList)
{
	cout << "\n\nRoll Number\tName\t\t\t";

	int totalQuizzes = EvaluationModule::GetTotalQuizzes();

	for (int i = 0;i < totalQuizzes;i++)
	{
		cout << "Q" << i + 1 << "\t";
	}

	int totalAssignments = EvaluationModule::GetTotalAssignments();

	for (int i = 0;i < totalAssignments;i++)
	{
		cout << "A" << i + 1 << "\t";
	}

	cout << "Total";
	cout << endl << endl;

	int totalStudents = EvaluationModule::GetTotalStudents();

	for (int i = 0;i < totalStudents;i++)
	{
		studentList[i].PrintAll();
	}
}

// It will Print Data of 2D Array
inline void PrintAll(EvaluationModule** studentList)
{
	cout << "\n\nRoll Number\tName\t\t\t";

	int totalQuizzes = EvaluationModule::GetTotalQuizzes();

	for (int i = 0;i < totalQuizzes;i++)
	{
		cout << "Q" << i + 1 << "\t";
	}

	int totalAssignments = EvaluationModule::GetTotalAssignments();

	for (int i = 0;i < totalAssignments;i++)
	{
		cout << "A" << i + 1 << "\t";
	}

	cout << "Total";
	cout << endl << endl;

	int i = 0;
	while (studentList[i] != 0)
	{
		(**(studentList + i)).PrintAll();
		i++;
	}
}

// Helper Class Functions

// It will get array and Reduce it extra size
inline char* Helper::SizeAdjuster(char* array)
{
	int size = ArrayLength(array);
	char* reducedArray = new char[size + 1];

	for (int i = 0;i < size;i++)
	{
		reducedArray[i] = array[i];
	}

	reducedArray[size] = '\0';

	return reducedArray;
}

// It will Calculate the Length of character Array
inline int Helper::ArrayLength(char* array)
{
	int length = 0;

	while (array[length] != '\0')
	{
		length++;
	}

	return length;
}

// It will copy 2D class Array
inline void Helper::Array2DCopy(EvaluationModule** arrayToBeCopied, EvaluationModule** arrayCopied, const int SIZE)
{
	for (int i = 0;i < SIZE;i++)
	{
		arrayCopied[i] = arrayToBeCopied[i];
	}
}


// Static Variable Initilization
int EvaluationModule::totalAssignments = 0;
int EvaluationModule::totalQuizzes = 0;
int EvaluationModule::totalStudents = 0;

// Static Pointers
float* EvaluationModule::assignmentsTotalMarks = 0;
float* EvaluationModule::quizzesTotalMarks = 0;
float* EvaluationModule::maximumAssignments = 0;
float* EvaluationModule::maximumQuizzes = 0;
float* EvaluationModule::minimumAssignments = 0;
float* EvaluationModule::minimumQuizzes = 0;
float* EvaluationModule::averageQuizzes = 0;
float* EvaluationModule::averageAssignments = 0;