#include "String.h"

String::String(): strSize(0), strcapacity(0), cstrPtr(new char[0])
{
	Invariant();
}

String::String(const String& rhs): strSize(rhs.size()), strcapacity(rhs.size())
{
	if (rhs.cstrPtr != nullptr)
	{
		this->cstrPtr = new char[strSize]; //allocate
		std::copy(rhs.cstrPtr, rhs.cstrPtr + rhs.size(), this->cstrPtr); //copy
	}
	else
	{
		this->cstrPtr = nullptr;
	}
	Invariant();
}

String::String(const char* cstr): strSize(strlen(cstr)), strcapacity(strlen(cstr)), cstrPtr(new char[strSize])
{
	std::copy(cstr, cstr + strSize, cstrPtr);
	Invariant();
}

String::~String()
{
	Invariant();
	delete[] cstrPtr;
}

String& String::operator=(const String& rhs)
{
	if (this == &rhs) // check self assignment
	{
		Invariant();
		return *this;
	}
	if (strcapacity >= rhs.size()) //check if needs resizing;
	{
		//just copy
		strSize = rhs.size(); //assign new size
		std::copy(rhs.cstrPtr, rhs.cstrPtr + rhs.size(), cstrPtr);
		Invariant();
		return *this;
	}
	//resize
	char* tempPtr;
	delete[] cstrPtr; //deallocate memory
	strSize = rhs.size(); //assign new size
	strcapacity = rhs.size() + 10; //new capacity of strings size + 10 empty spaces
	tempPtr = new char[strcapacity]; //allocate memory
	std::copy(rhs.cstrPtr, rhs.cstrPtr + rhs.size(), tempPtr);
	cstrPtr = tempPtr;
	Invariant();
	return *this;
}

char& String::operator[](size_t i)
{
	if (i < strSize) 
	{
		return cstrPtr[i];
	}
	else 
	{
		char null = '\0';
		return null;
	}
}

const char& String::operator[](size_t i) const
{
	if (i < strSize) //within string range
	{
		return cstrPtr[i];
	}
	else 
	{
		char null = '\0';
		return null;
	}
}

size_t String::size() const
{
	return strSize;
}

size_t String::capacity() const
{
	return strcapacity;
}

void String::print() const
{
	for (const char* ptr = cstrPtr; ptr != cstrPtr + strSize; ptr++)
	{
		std::cout << *ptr;
	}
	std::cout << std::endl;
}

void String::push_back(char c)
{
	if (strSize < strcapacity) //check if there is capacity to add char
	{
		//push letter
		cstrPtr[strSize] = c;
		strSize++;
		Invariant();
	}
	else
	{
		//increase array size;
		char* tempPtr;
		strcapacity += 10;
		tempPtr = new char[strcapacity]; //allocate memory
		std::copy(cstrPtr, cstrPtr + strSize, tempPtr);
		delete[] cstrPtr; //deallocate memory
		cstrPtr = tempPtr;
		cstrPtr[strSize] = c;
		strSize++;
		Invariant();
	}
}

const char* String::data() const
{
	return cstrPtr;
}

bool operator==(const String& lhs, const String& rhs)
{
	if (lhs.size() == rhs.size()) //are string of same size?
	{
		size_t strsize = lhs.size();
		for (size_t i = 0; i < strsize; i++)
		{
			if (lhs.cstrPtr[i] != rhs.cstrPtr[i]) //are chars same at indexes?
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool operator!=(const String& lhs, const String& rhs)
{	
	if (&lhs == &rhs) //check if it is itself
	{
		return false;
	}
	if (lhs.size() != rhs.size()) //if size are different then strings are different
	{
		return true;
	}
	else //if same size then check for same chars
	{
		for (size_t i = 0; i < lhs.size(); i++)
		{
			if (lhs.cstrPtr[i] != rhs.cstrPtr[i])
			{
				return true;
			}
		}
		return false;
	}
}

std::ostream& operator<<(std::ostream& out, const String& rhs)
{
	for (size_t i = 0; i < rhs.size(); ++i)
		out << rhs[i];
	return out;
}

void String::Invariant() //assert checks
{
	assert(size() <= capacity());
	assert(this->size() == strSize);
	assert(this->capacity() == strcapacity);
	assert(cstrPtr != nullptr);
}