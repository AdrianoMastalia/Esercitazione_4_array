#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Utils.hpp" 

using namespace std;

int main()
{
	string inputFile = "data.txt";
	size_t n;
	double Sum;
	double *ptr1 = nullptr;
	double *ptr2 = nullptr;
	double total_rate;
	double S_tot;
	ImportVectors(inputFile, n,Sum, ptr1, ptr2);
	total_rate = DotProduct(n, ptr1, ptr2);
	S_tot = total_value(total_rate, Sum);
	ExportResult("result.txt",n,ptr1,ptr2,Sum,total_rate,S_tot);
	
	/*I have to release the memory occupied by ptr1 and ptr2 */
	
	delete [] ptr1;
	delete [] ptr2;
    return 0;
}