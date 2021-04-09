#include <iostream>
#ifndef DATA
#define DATA 1

using std::ostream;
using std::cout;
using std::string;



class Data{
	private:
		int giorno;
		int mese;
		int anno;
	
	public:
		
		Data(int=0, int=0, int=0);
		
		int getGiorno() const;

		int getMese() const;

		int getAnno() const;
	
		string ToString() const;
		

};
#endif
