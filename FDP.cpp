
using namespace std;

class FDP{
	
	private:
		
		string title;
		string description; 
		vector<Director> directors;                                                
		Student student;
		Date presentdate;                               																//We use the Date class on which we already worked
		
	public:
		
		void setTitle(string ctitle){                                                                          		    //SETTERS or assigners
			title=ctitle;
		}
		void setDescription(string cdescription){
			description=cdescription;
		}
		void assignDirectors(vector<Director> cdirectors);
		void assignStudent(Student cstudent){
			student=cstudent;
		}
		void setPresentationDate(Date date){
			presentdate = date;
		}
		
		string getTitle(void){																						    //GETTERS
			return title;
		}
		string getDescription(void){
			return description;
		}
		Date getDate(void){
			return presentdate;
		}
		Student getStudent(void){
			return student;
		}
		vector<Director> getDirectors(void){
			return directors;
		}
		
		void showDirectors();                                                                                           //We are never asked to display/return information the student or the presentation date
		
		FDP(){};																										//DEFAULT CONSTRUCTOR
		FDP(string ctitle, string cdescription, vector<Director> cdirectors, Student cstudent, Date cpresentdate);		//PARAMETRIZED CONSTRUCTOR
		~FDP(){};																										//DESTRUCTOR
		
		void unassignStudent();                                                                                         //FUNCTIONS
		void removeDirector(string firstName, string lastName);
		void displayFDP();
		
};

FDP::FDP(string ctitle, string cdescription, vector<Director> cdirectors, Student cstudent, Date cpresentdate){
	title=ctitle;
	description=cdescription;
	directors =  cdirectors;
	student=cstudent;
	presentdate=cpresentdate;
}

void FDP::assignDirectors(vector<Director> cdirectors){      //Since we are being ask to give a list (vector) of directors as the paremeter, instead of having  
	for(int i=0; i<cdirectors.size(); i++){                  //the possibility to add directors one by one; in the main function we will to form the vector cdirectors 
		Director newdirector = cdirectors[i];                //with the different directors and then assign the vector to the FDR
		directors.push_back(newdirector);			    
	}
}

void FDP::removeDirector(string firstname, string lastname){
	vector<Director> copy;

	for (int i=0; i<directors.size(); i++) 					//We create a copy of the array to workaround the array changing size during iteration as it was giving us many errors
        copy.push_back(directors[i]);
        
    directors.clear();
	for(int i=0; i<copy.size(); i++){
		if ((copy[i].getFirst().compare(firstname)!=0) or (copy[i].getLast().compare(lastname)!=0)){
			directors.push_back(copy[i]);					
		}
	}
}

void FDP::showDirectors(){
	if (directors.size()>0){
		for(int i=0; i<(this->directors.size()-1); i++){
			Director currentdirector = (this->directors[i]);
			cout <<currentdirector.getFirst() <<" " <<currentdirector.getLast()<<", ";
		}
		int j=this->directors.size()-1;
		cout <<(this->directors[j]).getFirst() <<" " <<(this->directors[j]).getLast() <<".";            //This way we avoid a comma after the last director
	}
}

void FDP::unassignStudent(){                                                            			//We will use the ZEROS to identify unassigned projects
	student.setStudent(0, "0", "0");                                                   
}

void FDP::displayFDP(){
	string thisdescription = getDescription();
	cout <<thisdescription <<endl <<"Director(s): ";
	showDirectors();
	cout <<endl <<"Status: ";
	if(student.getNIA()==0){
		cout <<"unassigned" <<endl;
	}else{
		cout <<"assigned to " <<student.getFirst() <<" " <<student.getLast() <<endl;
	}
}
