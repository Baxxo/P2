#include <iostream>

using std::ostream;
using std::cout;


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

		//int setGiorno(int);

		//int setMese(int);

		//int setAnno(int);
				
		friend ostream& operator<<(ostream &os, const Data &d);

};

		


