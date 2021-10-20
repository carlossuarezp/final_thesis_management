
using namespace std;


class FDPCollection{	
	public:
		vector<FDP> projects;
		
		FDPCollection(){
			loadProjects();
		};
		~FDPCollection(){};
		
		void loadProjects();
		
		void saveProjects();
		
		void addProject(FDP fdp);
		
		FDP* searchFDP(string title);
		
		Student searchStudent(string firstName, string lastName);
		
		bool assignFDPtoStudent(FDP* fdp, Student student);
		
		void deleteFDP(string title);
		
		void deleteAll();
		
		void showProjectsByDirector(string firstName, string lastName);
		
		void showFDPByDirector();
		
};

void FDPCollection::loadProjects(){								//Loads projects from file, it uses 3 token delimiters [,{,\n to parse the file
	string line;
	ifstream database;
	database.open("projects.txt");
	
	
	if (database.is_open()){
		while ( getline (database,line) ){
			vector<string> parse1;
			vector<string> parse2;
			vector<string> parse3;
			vector<Director> directors;
			tokenize(line, '{', parse1);
			tokenize(parse1[0], '[', parse2);
			
			string title=parse2[0];
			string desc = parse2[1];

			int day=stoi(parse2[2]);

			int month=stoi(parse2[3]);

			int year=stoi(parse2[4]);
			
			Date date = Date(day,month,year);
			
			parse2.clear();
			tokenize(parse1[1], '[', parse2);
			
			Student student =Student(stoi(parse2[0]),parse2[1],parse2[2]);
			Director director;
			for (int i=2; i<parse1.size(); i++){
				directors.clear();
				parse2.clear();
				tokenize(parse1[i], '[', parse2);
				director = Director(parse2[0],parse2[1]);
				if (parse2.size()>2){
					director.setDepartment(parse2[2]);
				}
				if (parse2.size()>3){
					director.setOfficeNum(stoi(parse2[3]));
				}
				directors.push_back(director);
			}
			FDP fdp = FDP(title,desc,directors,student,date);
			projects.push_back(fdp);
		}
		database.close();
	}
	
}


void FDPCollection::saveProjects(){						//Saves the projects to the file for storage, it uses the same format as the save format so they are reloadable
	string line;
	ofstream database;
	database.open("projects.txt");
	FDP project;
	Date date;
	Student student;
	Director director;
	vector<Director> directors;
	for (int i; i<projects.size(); i++){
		project = projects[i];
		
		database<<project.getTitle()<<"[";
		database<<project.getDescription()<<"[";
		
		date = project.getDate();
		database<<date.getDay()<<"[";
		database<<date.getMonth()<<"[";
		database<<date.getYear()<<"{";
		
		student = project.getStudent();
		database<<student.getNIA()<<"[";
		database<<student.getFirst()<<"[";
		database<<student.getLast();
		
		directors=project.getDirectors();
		for (int i=0; i<directors.size(); i++){
			director=directors[i];
			database<<"{"<<director.getFirst()<<"[";
			database<<director.getLast()<<"[";
			database<<director.getDepartment()<<"[";
			database<<director.getOfficeNum();
		}
		database<<"\n";
	}
	database.close();
}


FDP* FDPCollection::searchFDP(string title){
	for (int i; i<projects.size(); i++){
		if (projects[i].getTitle().compare(title)==0){
			return &projects[i];
		}
	}	
	throw 0;															    		//If the project is not found, this function returns a NONE value
}

Student FDPCollection::searchStudent(string firstName, string lastName){
	for (int i; i<projects.size(); i++){
		if ((projects[i].getStudent().getFirst().compare(firstName)==0) and (projects[i].getStudent().getLast().compare(lastName)==0)){
			return projects[i].getStudent();
		}
	}	
	throw 0;														    		//If the student is not found, this function returns a NONE value
}

void FDPCollection::addProject(FDP fdp){
	try {
		FDP* ret = searchFDP(fdp.getTitle());                   						//We use the ret value to check if the project is already in the collection
		
	}
	catch (int n){
		projects.push_back(fdp);
	}
}

bool FDPCollection::assignFDPtoStudent(FDP* fdp, Student student){               						                         
	string firstname = student.getFirst();
	string lastname = student.getLast();
	int bfound = 0;                                                             //Now we check whether the student is already assigned to another project                                 
	for(int i=0; i<projects.size(); i++){
		if(projects[i].getStudent().getFirst().compare(firstname)==0 and projects[i].getStudent().getLast().compare(lastname)==0){
			cout<<projects[i].getTitle();
			bfound = 1;
			break;
		}
	}
	if(bfound==0){
		if (fdp->getStudent().getNIA()==0){
			fdp -> assignStudent(student);
			return true;
		} else{
			return false;
		}
	}else{
		return false;
	}
}

void FDPCollection::deleteFDP(string title){
	vector<FDP> copy;

	for (int i=0; i<projects.size(); i++) 										//We create a copy of the array to workaround the array changing size during iteration as it was giving us many errors
        copy.push_back(projects[i]);
        
    projects.clear();
	for(int i=0; i<copy.size(); i++){
		if (copy[i].getTitle().compare(title)!=0){
			projects.push_back(copy[i]);					

		}
	}
}

void FDPCollection::deleteAll(){
	projects.clear();
}

void FDPCollection::showProjectsByDirector(string firstName, string lastName){
	vector<Director> directors;
	for(int i=0; i<projects.size(); i++){
		directors = projects[i].getDirectors();
		for (int j=0; j<directors.size(); j++){
			if (directors[j].getFirst().compare(firstName)==0 and directors[j].getLast().compare(lastName)==0){
				cout<<projects[i].getTitle()<<"\n";									 //This way we show the data of the project corresponding to that specific director
				//projects[i].showDirectors();                                         //This way we show the data of the project corresponding to that specific director, we chose to not show it because it is too much information
				break;
			}
		}
	}
}

void FDPCollection::showFDPByDirector(){
	vector<string> directors_names;
	vector<Director> temp_directors;                                                 //We will copy the vector of directors of each project in this new vector, once at a time
	string key;                                                                      //Each key string incorporates the full name of each director
	for(int i=0; i<projects.size(); i++){
		temp_directors = projects[i].getDirectors();
		for (int j=0; j<temp_directors.size(); j++){
			key=temp_directors[j].getFirst()+", "+temp_directors[j].getLast() +", "+temp_directors[j].getDepartment()+ ", "+to_string(temp_directors[j].getOfficeNum());
			directors_names.push_back(key);                                                //Each key is an element of the directors vector, we then can count the keys and see how many times each director apeared
		}
	}
	vector<string> sent;
	
	for (int j=0; j<directors_names.size(); j++){
		if (find(sent.begin(), sent.end(), directors_names[j]) == sent.end()){
			sent.push_back(directors_names[j]);											//This ensures we only output once per unique director, since it will only runonce per director
			cout<< directors_names[j] << ": "<<count(directors_names.begin(), directors_names.end(), directors_names[j])<<"\n";  //This line outputs the director, the relevant information about it and the number of times it is listed
		}
	}
}
