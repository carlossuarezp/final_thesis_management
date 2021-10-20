
using namespace std;

class Date{
	
	private:
		int day;
		int month;
		int year;
		
	public:
		
		int getDay(){                         		//GETTERS
		return day;
		}
		int getMonth(){
		return month;
		}	
		int getYear(){
		return year;
		}
		
		void setDay(int x){                   		//SETTERS
			if (x < 1 or x > 31){
			throw "Invalid day";
			}	
			day=x;
		}
		void setMonth(int x){
			if (x < 1 or x > 12){
			throw "Invalid month";
			}
			month=x;
		}
		void setYear(int x){
			if (x < 1000 or x > 2020){
			throw "Invalid year";
			}
			year=x;
		}
		void setAll(int x, int y, int z){
			day=x;
			month=y;
			year=z;
		}
		
		Date(int x, int y, int z);				   //Parametrized constructor
		Date();									   //Default constructor
		~Date(){};                                   //Destructor
		
		int compare(Date date);                    //FUNCTIONS USED MOSTLY IN PREVIOUS COMPUTERSCIENCE PROJECTS
		int convert(void);
		bool isLeapYear(void);
		string showDate();
};

Date::Date(){                                      //Default constructor
	day = 0;
	month = 0;
	year = 0;
}

Date::Date(int x, int y, int z){			 	   //Parametrized constructor
		//if (day < 1 || day > 31)   throw "Invalid day";
		//if (month < 1 || month > 12)   throw "Invalid month";
		//if (year < 1000 || year > 2020) throw "Invalid year";
		day = x;
		month = y;
		year = z;
		}



int Date::convert(void){
    return (this -> year * 10000) + (this -> month * 100) + this -> day;
}

int Date::compare(Date date){
	if ( this -> convert() < date.convert() )
		return -1;
	else if ( this -> convert() > date.convert() ) 
		return 1;
	else if ( this -> convert() == date.convert() )
		return 0;
}

bool Date::isLeapYear(void){
	if ((this -> year)%4 == 0){
    	return true;
    }else{
    	return false;
    }
}

string Date::showDate(){
	string sday = to_string(this -> day);
	string smonth = to_string(this -> month);
	string syear = to_string(this -> year);
	if (day<10){
	sday = '0'+ sday;
	}
	if (month<10){
	smonth = '0'+ smonth;
	}
	string sdate = sday+ "/"+ smonth+ "/"+ syear; 
	return sdate;
}
