#include <iostream>
#include <fstream>
#include <sstream>
#include<iomanip>
#include<string>
#include "Utils.hpp"

using namespace std;

/* Here, I pass double *& w and double *& v because the program has to modify the pointer both 
in the function body and in the main, I'll allocate memory for w and r, to memorize lines of the
files in the two vectors, without knowing the length of the file (which is not a compile-time known constant) */

bool ImportVectors(const string& inputFilePath, size_t& n, 
				   double&S, double*& w, double*& r)
{	
	ifstream file(inputFilePath);
	if(file.fail())
	{
		cout<<"File not found"<<endl;
		return false;
	}
	
	/* I take the first line of the file up to ; character to ignore that part */
	/* tmp is used as a temporary string to ignore parts of the file */
	
	std::string tmp; 
	getline(file, tmp,';');
	
	/* here, I memorize the part of the first line after the ; char inside S */
	
	file>>S;
	
	/*then, I have to ignore the \n added by the >> operator */
	file.ignore();
	
	/* repeat the procedure */
	
	getline(file,tmp,';');
	file >> n;
	file.ignore();
	getline(file, tmp);
	
	/*I don't know the length of the files, so I have to use dynamic memory, because standard 
	 arrays can't be used when we don't know the length of the file a priori*/
	
	w = new double[n];
	r = new double[n];
	double pos;
	for(unsigned int i = 0; i<n; i++)
	{
		getline(file,tmp);
		
		/* here, I find the position of ; in the line */
		 
		pos = tmp.find(';');
		
		/* I extract the substring before the ; (components of w) and then convert them to double,
		then I do the same with r*/
		 
		w[i] = stod(tmp.substr(0,pos));
		r[i] = stod(tmp.substr(pos+1));
	} 
	file.close();
    return true;
}

/*Here I calculate the scalar product of w and v, which is mathematically equivalent to the calculation
of the total rate of return of the portfolio, the script is the same as the one seen in classroom,
we used const double * const & w because neither w or its pointed values have to be modified by this
function, but we only need to access those datas */

double DotProduct(const size_t& n, const double* const& w, 
				  const double* const& r)
{
	double DotPr = 0;
	for(unsigned int i = 0; i<n; i++)
    {
		DotPr += w[i]*r[i];
	}
   return DotPr;
}
 /* in this function, I calculate the total value of the portfolio, applying the formula given 
 in the README file */
 
double total_value(const double &r, const double &S)
{
	return (1+r)*S;
}

/*The following function is used to print both in the output file and on the terminal the results, 
everything is passed by const reference because I don't have to modify anything, and this is 
optimal in terms of memory */

bool ExportResult(const string& outputFilePath, const size_t& n,
                  const double* const& w, const double* const& r,
                  const double &S, const double rate, const double &V)
{
    ofstream file;
    file.open(outputFilePath);

    if (file.fail())
    {
        cerr<< "file open failed"<< endl;
        return false;
    }
	/*In the following lines, the "ArrayToString" is called, to convert the Array in a single
	string */
    file << "S = "<< S <<", n = "<<n<<endl;
    file << "w = " <<ArrayToString(n,w)<<endl;
	file<<"r = " <<ArrayToString(n,r)<<endl;
    file << "Rate of return of the portfolio: "<<rate<< endl;
	file<<"V: "<<fixed<<setprecision(2)<<V<<endl;  
    file.close();
	cout << "S = "<< S <<", n = "<<n<<endl;
    cout << "w = " <<ArrayToString(n,w)<<endl;
	cout<<"r = " <<ArrayToString(n,r)<<endl;
    cout << "Rate of return of the portfolio: "<<rate<< endl;
	
	/*Here, I print the V value in decimal notation with 2 digits of precision 
	by keeping trailing zeros */
	
	cout<<"V: "<<fixed<<setprecision(2)<<V<<endl;  
    return true;
}

string ArrayToString(const size_t& n, const double* const& v)
{
    string str;
    ostringstream toString;
    toString << "[ ";
    for (unsigned int i = 0; i < n; i++)
        toString<< v[i]<< " ";
    toString << "]";

    return toString.str();
}
