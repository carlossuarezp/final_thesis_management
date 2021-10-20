
using namespace std;

class Director{
	private:
		string first;
		string last;
		string department;
		int officeNum;
		
	public:
		void setDirector(string cfirst, string clast){                        		//SETTERS
			first=cfirst;
			last=clast;
		}
		void setFirst(string cfirst){
			first=cfirst;
		}
		void setLast(string clast){
			last=clast;
		}
		void setDepartment(string cdepartment){
			department=cdepartment;
		}
		void setOfficeNum(int cofficeNum){
			officeNum=cofficeNum;
		}
		
		
		string getFirst(void){                                               		 //GETTERS
			return first;
		}
		string getLast(void){
			return last;
		}
		string getDepartment(void){
			return department;
		}
		int getOfficeNum(void){
			return officeNum;
		}
		
		Director(){};                                                    	 		 //DEFAULT CONSTRUCTOR
		Director(string cfirst, string clast);   									 //PARAMETRIZED CONSTRUCTOR
		~Director(){};                                                        		 //DESTRUCTOR
};

Director::Director(string cfirst, string clast){
	first=cfirst;
	last=clast;
}
