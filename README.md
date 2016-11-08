# Simple Bloom Filter Implementation
- This Project refers "Hashing and Data Fingerprinting in Digital Forensics".
- (IEEE Security & Privacy, vol. 7, no. , pp. 49-55, March/April 2009)


## Dongguk University
### Dept. of Computer Science and Engineering
#### Network Security

##### Calculation Code - C++
```cpp
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
```

This is [on GitHub](https://github.com/yjham2002/SimpleBloomFilter).

### Team
* EuiJin Ham (Leader)
* SeungHyun Kang
* SangEon Park

