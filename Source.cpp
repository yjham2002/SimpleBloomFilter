/****************************************************************
* Dongguk University - Dept. of Computer Science and Engineering
* Network Security - Professor. Moon Bong Kyo
* Code By Ham Eui Jin
*****************************************************************/

#include <iostream> // CPP Input-Output Standard Header
#include <cmath> // CPP math related function library

class DataSlice{ // Data Unit for Handling
public: // Public Access Modifier
	DataSlice(int d1, int d2, int d3, int d4) : Data_1(d1), Data_2(d2), Data_3(d3), Data_4(d4){}
	int Data_1, Data_2, Data_3, Data_4;
	void Print() { // Function for Print entire data set
		std::cout << Data_1 << "," << Data_2 << "," << Data_3 << "," << Data_4;
	}
};

class BloomFilter{ // Bloom Filter Class
private: // Private Access Modifier
	int *FilterArray; // Filtering Bit Array
	static const int M = 18; // THe number of bit Array for BloomFilter - Constant M
	static const int K = 3; // The number of Hash Function - Constant K
	typedef int(BloomFilter::*HashFunc)(DataSlice&); // Type Definition for Function Pointer
	static HashFunc hash[]; // Function Pointer Array
public:
	BloomFilter(){ // Default Constructor for Bloom Filter
		this->FilterArray = new int[M] {0,}; // Initializing and Constructing Filter bit array
	}
	~BloomFilter() {} // Default Destructor

	void PrintBits() { // Function for Printing entire bit of filter bit array
		for (int i = 0; i < M; i++) std::cout << FilterArray[i] << "/";
	}
	void Add(DataSlice &Data) { // Function for Addition
		for (int i = 0; i < K; ++i) FilterArray[(this->*hash[i])(Data)] = 1;
		Data.Print();
		std::cout << " Added" << std::endl;
	}
	bool Contains(DataSlice &Data) { // Function for Checking if the Hash Table contains Param
		Data.Print(); // Printing Data
		for (int i = 0; i < K; ++i) if (!FilterArray[(this->*hash[i])(Data)]) {
			std::cout << " doesn't exist" << std::endl; // Message
			return false;
		}
		std::cout << " exists" << std::endl; // Message
		return true;
	}

	int Hash_1(DataSlice& Data) { return (abs(Data.Data_1 + Data.Data_2 + Data.Data_3 + Data.Data_4)) % M; }
	int Hash_2(DataSlice& Data) { return (abs(Data.Data_1 - Data.Data_2 + Data.Data_3 - Data.Data_4)) % M; }
	int Hash_3(DataSlice& Data) { return (abs(Data.Data_1 * Data.Data_2 - Data.Data_3 + Data.Data_4)) % M; }
	int Hash(int mode, DataSlice& Data) { (this->*hash[mode])(Data); }
};

BloomFilter::HashFunc BloomFilter::hash[]{
	&BloomFilter::Hash_1,
	&BloomFilter::Hash_2,
	&BloomFilter::Hash_3,
};

int main(char *argv[], int argc){
	
	BloomFilter bloomFilter;
	DataSlice D1(1, 2, 3, 4), D2(2, 4, 6, 8), D3(3, 5, 7, 9), D4(1, 3, 5, 7);

	bloomFilter.Add(D1);
	bloomFilter.Add(D2);

	bloomFilter.Contains(D1);
	bloomFilter.Contains(D2);
	bloomFilter.Contains(D3);
	bloomFilter.Contains(D4);

	return EXIT_SUCCESS;

}
