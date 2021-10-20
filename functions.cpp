
using namespace std;

Director setAll(string cfirst, string clast, string cdepartment, int cofficeNum){		//Function used to assemble a director with more parameters
	Director director=Director(cfirst,clast);
	director.setOfficeNum(cofficeNum);
	director.setDepartment(cdepartment);
	return director;
}


void tokenize(string const &str, const char delim, vector<string> &out){				//EXTRACTED FROM https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
	size_t start;
	size_t end = 0;

	while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
	{
		end = str.find(delim, start);
		out.push_back(str.substr(start, end - start));
	}
}
