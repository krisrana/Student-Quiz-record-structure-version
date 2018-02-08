/*
     Name:      Krishna rana 
     Course:    CIS 161 ME1
     Date:      11/21/2016
     Program:   Student Quiz record
     Description:  This program uses an array of structures with data member Id, 3 test score
	 			calculated average. Also program has different critria for searching and
				 sorting, pointers.  			
*/
#include <iostream>//Standard Input/output streams libary
#include <iomanip>//Header providing parametric manipulators
#include <fstream>//Header providing file stream classes
using namespace std;
//declaring Array size
const int SIZE = 25;
//Structure Defination
typedef struct Student
{
	//Structure members, fields
	int StudId;
	int Quiz1;
	int Quiz2;
	int Quiz3;
	float StudAvg;	
}studarray[SIZE];
//typedef to create an alias name for another data type.
typedef Student *studptr;
//function prototype
int getdata(studptr, ifstream&);
void findstavg(studptr, int);
void OutputOne(studptr, int);
void averagefinder(studptr, int);
void sortarray_Avg(studarray, int);
void output();
void binarysearch(studarray, int);
void selectshow(studarray, int, int, int);
int selectsort_id(studarray, int,int&);
void binarysearch_two(studarray, int);
void output_two();
//Main() Function Defination
//This function runs the whole program with step by step intruction written below.
//main() has calls and parameters of other function in the program.
int main()
{	
	//Local Definations/ Declarlations
	int size, result, counter, comparisoncounter;
	//Initialization of structure student value.
	studarray stud;
	//This are type associated with fstream,
	//ifstream get file info and ofstrem give info to file.
	ifstream infile("pr2data.txt");
	//file error check, checks if the file exist or not.	
	if(!infile)
	//if the file does not exist. prints the message.
	cout<<"file Error: file not present"<<endl;
	else
	{	//if file exist, follows this steps
		//function calls
		//size is the counter to count the number of times the array is used.
		size = getdata(stud, infile);
		findstavg(stud,size);
		OutputOne(stud, size);
		averagefinder(stud, size);
		sortarray_Avg(stud, size);
		binarysearch(stud, size);
		counter = selectsort_id(stud, size,comparisoncounter);
		selectshow(stud, size, counter,comparisoncounter);
		binarysearch_two(stud, size);
	}
	//close all file after data is updated
	infile.close();
	return 0;
}
//Question 1 (part 1)
//getdata() Function Defination
//This function is used to get input from the file.
//The input from file consist of student Id number, three Quiz scores.
//The input is stored to array passed to pointer and pointer arithmetic is used
//It's return type is int and acts as the counter of array as many time the getdata() is called.
int getdata(studptr stud, ifstream& fin)
{
	//initializing i to 0
	int i = 0;
	fin>>stud->StudId;
	//loop to read data until the trailing value 0 for student ID is encountered.
	while(stud->StudId != 0)
	{
		fin>>stud->Quiz1;
		fin>>stud->Quiz2;
		fin>>stud->Quiz3;
		i++,stud++;
		fin>>stud->StudId;
	}
	//returns the i, here i is used for counting purpose for the number of time loop is executed
	return i;
}
//Question 1 (part 2)
//findstavg() Function Defination
//This Function is used to calculate average of three quizzes of a student.
void findstavg(studptr s, int size)
{
	//loop to add three quiz score for every student Id encounterd.
	for(int i = 0; i < size; i++)
	{
		s[i].StudAvg  = float(s[i].Quiz1+s[i].Quiz2+s[i].Quiz3)/3;
	}
}
//Questoin 1 (Part 3)
//This funciton is for output purpose only for getdata() and findstavg()
void OutputOne(studptr stud, int size)
{
	cout<<"This Output is for Question 1 :"<<endl;
	cout<<"-----------------------------------------------------------------------"<<endl;
	cout<<"Student"<<setw(15)<<"Quiz 1"<<setw(15)<<"Quiz 2"<<setw(15)<<"Quiz 3"<<setw(15)<<"Average"<<endl;
	cout<<"-----------------------------------------------------------------------"<<endl;
	cout<<fixed<<showpoint<<setprecision(2);
	for (int i = 0; i < size; i++)
	{
		cout<<stud[i].StudId<<setw(15)<<stud[i].Quiz1<<setw(15)<<stud[i].Quiz2<<setw(15)<<stud[i].Quiz3
		<<setw(18)<<stud[i].StudAvg<<endl;
	}
	cout<<"***********************************************************************"<<endl<<endl;
}
//Question 2
//averagefinder() Function Defination
//This Function is used to find average which is greater than or equals to 85%.
//It outputs the Id and Average which are greater than or equals to 85%.
//pointer arithmetic is used.
void averagefinder(studptr s, int size)
{
	//Local Definations/ Declarlations
	const float NUM = 85;
	cout<<"This Output is for Question 2 :"<<endl;
	cout<<"----------------------------"<<endl;
	cout<<"Student"<<setw(15)<<"Average"<<endl;
	cout<<"----------------------------"<<endl;
	cout<<fixed<<showpoint<<setprecision(2);
	//loop to find average >=85 for every student average encounterd.
	for(int i = 0; i < size; i++,s++)
		{
			if (s->StudAvg >= NUM)
			{
				cout<<s->StudId<<setw(18)<<s->StudAvg<<endl;
			}
		}
	cout<<"****************************"<<endl<<endl;
}
//Question 3 (Part 1)
//sortarray_Avg() Function Defination
//This function is used to sort the structure of array based on average greater than or equals to 85%.
//This sort type is called Bubble sort
void sortarray_Avg(studarray s, int size)
{
	//Local Definations/ Declarlations
	Student temp;
	bool swap;
	do
	{
		swap=false;
		//loop to sort the structure of array based every student average encounterd.
	    for(int i=0;i<(size-1);i++)
	        { if (s[i].StudAvg>s[i+1].StudAvg)      
    		      {   
            		temp=s[i];            
               		s[i]=s[i+1];
               		s[i+1]=temp;
               		swap=true;
                  }  
        	} 
	}while(swap);
}
//Question 3 (Part 2)
//binarysearch() Function Defination
//This function is used to search the structure of array based on average greater than or equals to 85%.
//This function is in realtion to sortarray_Avg().
void binarysearch(studarray s, int size)
{
	//Local Definations/ Declarlations
	const float NUM = 85;
	int first = 0,
		last = size -1,
		middle,
		position = -1;
	bool found = false;
	//output function for header purpose.
	output();
	//loop to find average >=85 for every student average encounterd from the sortted array.
	for(int i = 0; i < size; i++)
		if (s[i].StudAvg >= NUM)
		{
			while(!found && first <= last)
			{
				middle = (first + last) / 2 ;
				if(s[middle].StudAvg >= NUM)
				{
				found = true;
				position = middle;
				}
				else if(s[middle].StudAvg >= NUM)
				last = middle - 1;
				else
				first = middle + 1;
			}
			cout<<s[i].StudId<<setw(15)<<s[i].StudAvg<<endl;
		}
	cout<<"****************************"<<endl<<endl;
}
//Question 3 (Part 3)
//This function is only for output of header to binarysearch().
void output()
{
	cout<<"This Output is for Question 3 :"<<endl;
	cout<<"----------------------------"<<endl;
	cout<<"Student"<<setw(15)<<"Average"<<endl;
	cout<<"----------------------------"<<endl;
	cout<<fixed<<showpoint<<setprecision(2);
}
//Question 4 (Part 1)
//Selectsort_id() Function Defination
//This function is used to sort the structure of array based on Id
//This sort type is called Selection sort
int selectsort_id(studarray s, int size,int& comparisoncounter)
{	
	//Local Definations/ Declarlations
  	Student temp;
  	int startscan, minValue;
  	//counter for comparison intiallization
  	comparisoncounter = 0;
  	//loop for sorting the array based on id
  	for(startscan = 0; startscan < (size - 1); startscan++)
  	{
  		minValue = startscan;
  		for(int j = startscan + 1; j < size; j++)
  		{
  			//counter for comparison
  			comparisoncounter++;
  			if(s[j].StudId < s[minValue].StudId)
  			{
  				minValue = j;  				
			}
		  }
		  //swapping take place over here
		temp = s[startscan]; 
		s[startscan] = s[minValue];
		s[minValue] = temp;
	  }
	//returns the number of time swap was done
	return startscan;
}
//Question 4 (Part 2)
//selectshow() Function Defination
//This function is used display purpose to selectsort_id().
void selectshow(studarray s, int size, int counter, int comparisoncounter)
{
	cout<<"This Output is for Question 4 :"<<endl;
	cout<<"-----------------------------------------------------------------------"<<endl;
	cout<<fixed<<showpoint<<setprecision(2);
	for (int i = 0; i < size; i++)
	{
		cout<<s[i].StudId<<setw(15)<<s[i].Quiz1<<setw(15)<<s[i].Quiz2<<setw(15)<<s[i].Quiz3
		<<setw(18)<<s[i].StudAvg<<endl;
	}
	cout<<"-----------------------------------------------------------------------"<<endl;
	//Number of Swap
	cout<<"This is the number of time swapping took place: "<< counter << endl;
	//Number of comparison
	cout<<"This is the number of time comparision takes place: "<< comparisoncounter<<endl;
	cout<<"***********************************************************************"<<endl<<endl;
}
//Question 5 (Part 1)
//binarysearch_two() Function Defination
//This function is used to search the Id inputed from user.
//Once the Id is found it will output the Id along with 3 test score and average associated with the id.
void binarysearch_two(studarray s, int size)
{
	cout<<"This Output is for Question 5 :"<<endl;
	cout<<"-----------------------------------------------------------------------"<<endl;
	//Local Definations/ Declarlations
	int num;
	int position = -1;
	char response;
	cout<<"Do you have Student's ID?";
	cout<<"\n(Type 'Y'for yes, If you have student's ID or type 'N' for no to exit): ";
	cin>>response;
	response = toupper(response);
	//loop to check response
	//loop will run untill user enters 'n' or 'N' as response to prompt.
	while(response!='N')
	{
		cout<<"Enter the Student's ID number: ";
		cin>>num;
		int first = 0,
		last = size -1,
		middle;
		bool check = false;
		bool found = false;
		//output function for header purpose.
		output_two();
		for(int i = 0; i < size; i++)
		{
			if (s[i].StudId == num)
			{
				while(!found && first <= last)
				{
					middle = (first + last) / 2 ;
					if(s[middle].StudId == num)
					{
					found = true;
					position = middle;
					}
					else if(s[middle].StudId >= num)
					last = middle - 1;
					else
					first = middle + 1;
				}
				cout<<s[i].StudId<<setw(15)<<s[i].Quiz1<<setw(15)<<s[i].Quiz2<<setw(15)<<s[i].Quiz3
				<<setw(18)<<s[i].StudAvg<<endl;
				check = true;
			}
		}
		if(check == false)
			cout<< "ID not present"<<endl;
	cout<<"***********************************************************************"<<endl;
	cout<<"Do you have another Student's ID?";
	cout<<"\n(Type 'Y'for yes, If you have another student's ID or type 'N' for no to exit): ";
	cin>>response;
	response = toupper(response);
	}
}
//Question 5 (Part 2)
//This function is only for output of header to binarysearch_Two().
void output_two()
{
	cout<<"-----------------------------------------------------------------------"<<endl;
	cout<<"Student"<<setw(15)<<"Quiz 1"<<setw(15)<<"Quiz 2"<<setw(15)<<"Quiz 3"<<setw(15)<<"Average"<<endl;
	cout<<"-----------------------------------------------------------------------"<<endl;
	cout<<fixed<<showpoint<<setprecision(2);
}


