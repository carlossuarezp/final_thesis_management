#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <algorithm>


#include "date.cpp"
#include "student.cpp"
#include "director.cpp"
#include "functions.cpp"
#include "FDP.cpp"
#include "FDPCollection.cpp"


using namespace std;

void menu(){
	
	cout<<"\n\nWelcome to the main menu!"<<endl;
	cout<<"1. Add a new project" <<endl;
	cout<<"2. Search a project" <<endl;
	cout<<"3. Search a student" <<endl;    
	cout<<"4. Assign a FDP to a student" <<endl; 
	cout<<"5. Delete a FDP from the list" <<endl;       
	cout<<"6. Delete all FDPs" <<endl;
	cout<<"7. Show the projects supervised by a particular director" <<endl;
	cout<<"8. Display a list of directors with the number of FDP that have been presented"  <<endl;
	cout<<"9. Show the list of directors that supervise a project" <<endl;
	cout<<"10. Unassign a student from a project" <<endl;
	cout<<"11. Remove a director from a project" <<endl;
	cout<<"12. Display all information about a project" <<endl;
	cout<<"13. Save and Exit" <<endl;
}


int main(void){
	
	FDPCollection projects = FDPCollection();
	
	while(1){					//Main menu, it just asks for the user to select an option from the list
		
		menu();
		int option;
		string option2;
		bool invalid;
		cout<<"Select the desired action: ";
		try{
		
			getline(cin, option2);
			option=stoi(option2);
			invalid=false;
		}
		catch (...){
			invalid=true;
		}
		
		while(option<1 or option>13 or invalid){
			cout<<"Invalid option number. Please take a look at the menu and pick again: ";
			try{
				
					getline(cin, option2);
					option=stoi(option2);
					invalid=false;
				}catch (...){
					invalid=true;
				}
				
		}
		
		
		if(option==1){            
			//Since it is new project and it is not in the database, we will (1) ask the user for its data, (2) build it using classes and (3) use the function we previously built in order to add it to the list
			string ptitle, pdescription;
			string pday,pmonth, pyear, pofficenum, pNIA, pdirectnum;
			int day, month, year, officenum, NIA;
			string studfirst, studlast, directfirst, directlast, department;
			
			cout<<"You have chosen to add a new project. Please specify its characteristics: ";
			cout<<"Tile, description, presentation day, presentation month, presentation year, student first name, student last name, student NIA" <<endl;
			cout<<"Title: ";
			getline(cin, ptitle);
			bool exists;
			try{
				projects.searchFDP(ptitle);                      
				exists=true;
			}catch (...){
				exists=false;
			}
			if (exists){
				cout<<"This project already exists\n";
			}else{
				cout<<"Description: ";
				getline(cin, pdescription);
				cout<<"Date settings:\nDay (ex: 26)): ";
				getline(cin, pday);
				cout<<"Month (ex: 7): ";
				getline(cin, pmonth);
				cout<<"Year (ex: 2020): ";
				getline(cin, pyear);
				
				cout<<"\nStudent Settings\nFirst Name: ";
				getline(cin, studfirst);
				cout<<"Last Name: ";
				getline(cin, studlast);
				cout<<"NIA: ";
				getline(cin, pNIA);
				
				NIA=stoi(pNIA);
				day=stoi(pday);
				month=stoi(pmonth);
				year=stoi(pyear);
				
				
				try{
					projects.searchStudent(studfirst, studlast);
					exists=true;
				}catch (...){
					exists=false;
				}
				if (exists){
					cout<<"This student is already in another project\n";
				}else{
					Student pstudent(NIA, studfirst, studlast);
				
					Date pdate(day, month, year);
					
					vector<Director> pdirectors;
					int directnum;
					cout<<endl <<"\nHow many directors does the project have? ";
					getline(cin, pdirectnum);
					directnum=stoi(pdirectnum);
					
					for(int i=0; i<directnum; i++){
						cout<<endl <<"\nPlease introduce the following characteristics about director number " <<i <<":";
						cout<<"First name: ";
						getline(cin, directfirst);
						cout<<"Last name: ";
						getline(cin, directlast);
						cout<<"Department name: ";
						getline(cin, department);
						cout<<"Office Number: ";
						getline(cin, pofficenum);
						officenum=stoi(pofficenum);
						Director pdirector= setAll(directfirst, directlast, department, officenum);
						pdirectors.push_back(pdirector);
					}
					
					FDP newproject(ptitle, pdescription, pdirectors, pstudent, pdate);
					projects.addProject(newproject);
					
					cout<<"Your project was added succesfully!" <<endl;
				}
			}
			
			
			
			
			
			
		}else if(option==2){	//WORKS
			
			string ptitle, pdescription;
			cout<<"You have decided to search a project. Please enter its TITLE: ";
			getline(cin, ptitle);
			FDP projectfound;
			try{
				projectfound = *projects.searchFDP(ptitle);                      //The return type of this function is an FDP class, so we have to find a way to print some data about it in the main function If instead we get an error, it means that the project does not exist
				pdescription=projectfound.getDescription();
				cout<<"\nYour project was found successfully! This is its description:\n" <<pdescription <<endl;
			}catch (...){
				cout<<"Your project was not found!";
			}
			
			
			
		}else if(option==3){	//WORKS
			
			string studfirst, studlast;
			int pNIA;
			cout<<"You have decided to search a student.\n";
			cout<<"Their first name: ";
			getline(cin, studfirst);
			cout<<endl <<"Their last name: ";
			getline(cin, studlast);
			Student studfound;
			try{
				studfound = projects.searchStudent(studfirst, studlast);       //The return type of this function is an Student class, so we have to find a way to print some data about it in the main function If instead we get an error, it means that the student does not exist
				pNIA = studfound.getNIA();
				cout<<"\n\nYour student was found successfully! " <<studfirst <<" " <<studlast <<"'s NIA is: " <<pNIA <<endl;
			}catch (...){
				cout<<"\n\nYour student was not found!";
			}
			
			
		
		}else if(option==4){	//WORKS
			int NIA;
			string studfirst, studlast, ptitle, pNIA;
			cout<<"You have decided to assign a project to a student. Please introduce the following: ";
			cout<<endl <<"Student first name: ";
			getline(cin, studfirst);
			cout<<endl <<"Student last name: ";
			getline(cin, studlast);
			cout<<endl <<"Student NIA: ";
			getline(cin, pNIA);
			NIA=stoi(pNIA);
			
			cout<<endl <<"Title of the project: ";
			getline(cin, ptitle);
			try{
				Student mystudent = Student(NIA,studfirst, studlast);	//we create the student class
				FDP* myFDP = projects.searchFDP(ptitle);
				
				bool result;   
				result = projects.assignFDPtoStudent(myFDP, mystudent);	//asign it to the fdp and report the outcome of the function
				
				if(result==true){
					cout<<endl <<"Your student and project have been assigned  successfully" <<endl;
				}else{
					cout<<endl <<"The student is already assigned to another project or this project already has a student assigned" <<endl;
				}
			}catch (...){
				cout<<endl <<"The project was not found" <<endl;
			}
			
			
				
		}else if(option==5){	//WORKS
					
			string ptitle;
			cout<<"You want to erase a project from the list. Please introduce its TITLE: ";
			getline(cin, ptitle);
			
			projects.deleteFDP(ptitle);					//Removes the project with that title from the database
			cout<<endl <<"The project has been successfully removed from the list!" <<endl;
		
		
		}else if(option==6){	//WORKS
			
			cout<<"You have chosen to delete all projects. Please, exit right after" <<endl;
			projects.deleteAll();						//removes all items in the vector that holds the projects
		
		
		}else if(option==7){	//WORKS
			
			string directfirst, directlast;
			cout<<"You have requested to display information about the projects supervised by a director, please introduce: " <<endl;
			cout<<"Their first name: ";
			getline(cin, directfirst);
			cout <<"Their last name: ";
			getline(cin, directlast);
			
			projects.showProjectsByDirector(directfirst, directlast);			//Ths promts a search in every project for that direcor and outputs the title of that project
			
			
		}else if(option==8){	//WORKS
			
			cout<<"You have decided to display information about all directors with their particular projects: " <<endl;
			projects.showFDPByDirector();						//Displays all the directors with the number of assigned projects
			
			
		}else if(option==9){	//WORKS
			
			cout<<"You have chosen to display the list of directors that supervise a particular project. Please introduce its TITLE: ";
			string ctitle;
			getline(cin, ctitle);
			FDP myFDP;
			try{
				myFDP = *projects.searchFDP(ctitle);			//This displays the directors of a specific project
				myFDP.showDirectors();
			}catch(...){
				cout<<"That project was not found";
			}
			
			
			
		}else if(option==10){	//WORKS
			
			cout<<"You have chosen to unassign a student from a project. Please introduce the TITLE of the PROJECT: ";
			string ctitle;
			getline(cin, ctitle);
			FDP* myFDP;
			try{
				myFDP = projects.searchFDP(ctitle);				//Remvoes the student from the project
				myFDP -> unassignStudent();
				cout<<"Student unasigned";
			}catch (...){
				cout<<"The project does not exist";
			}
		
			
			
		}else if(option==11){	//WORKS
			string directfirst,directlast;
			cout<<"You wish to remove a particular director from a particular project. Please enter: " <<endl;
			cout<<"Their first name: ";
			getline(cin, directfirst);
			cout<<"Their last name: ";
			getline(cin, directlast);
			
			cout<<"Now introduce the title of the project: ";
			string ptitle;
			getline(cin, ptitle);
			try{
				FDP* myFDP = projects.searchFDP(ptitle);
				myFDP->removeDirector(directfirst, directlast);			//This is a rather dificult function since it involed a workaround that avoided changing the size of the vecotr while it it iterating
				cout<<"Director removed";
			}catch (...){
				cout<<"The project does not exist";
			}
			

			
			
		}else if(option==12){	//WORKS
			
			cout<<"You have chosen to display information about a particular project. Please introduce its title: ";
			string ptitle;
			getline(cin, ptitle);
			
			FDP myFDP;
			try{
				myFDP=*projects.searchFDP(ptitle);
				myFDP.displayFDP();										//If the project exists, it displays all of the information inside it
			}catch(...){
				cout<<"The project does not exist";
			}
				
			
		}else if(option==13){	//WORKS
			projects.saveProjects();
			return 0;
		}
		
		
	}


	return 0;
}
