
using namespace std;

class Student{
	private:
		int NIA;
		string first;
		string last;
		
	public:
		void setStudent(int cNIA, string cfirst, string clast){                 //SETTERS
			NIA=cNIA;
			first=cfirst;
			last=clast;
		}
	
		void setNIA(int cNIA){
			NIA=cNIA;
		}
		void setFirst(string cfirst){
			first=cfirst;
		}
		void setLast(string clast){
			last=clast;
		}
		

		int getNIA(void){														//GETTERS
			return NIA;
		}
		string getFirst(void){
			return first;
		}
		string getLast(void){
			return last;
		}
	
		Student(){
			setStudent(0, "0", "0");
		};                                                    	                //DEFAULT CONSTRUCTOR
		Student(int cNIA, string cfirst, string clast);                         //PARAMETRIZED CONSTRUCTOR
		~Student(){};                                                           //DESTRUCTOR
};

Student::Student(int cNIA, string cfirst, string clast){             
	NIA=cNIA;
	first=cfirst;
	last=clast;
}

