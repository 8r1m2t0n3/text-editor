#ifndef MY_STRING_H
#define MY_STRING_H

#include <string>

class MyString {
public:
	MyString();
	MyString(const char* str);
	MyString(std::string& str);
	MyString(const char* str, int count);
	MyString(int count, char chr);
	MyString(const MyString& str);
	void ToNewString(const char* str);
	~MyString();
	MyString operator +(const MyString& str);
	MyString operator +(const char* str);
	void operator +=(const MyString& str);
	void operator +=(const char* str);
	void operator =(const MyString& str);
	void operator =(const char chr);
	friend bool operator >(const MyString& str1, const MyString& str2);
	friend bool operator ==(const MyString& str1, const MyString& str2);
	friend bool operator <(const MyString& str1, const MyString& str2);
	friend bool operator >=(const MyString& str1, const MyString& str2);
	friend bool operator <=(const MyString& str2, const MyString& str1);
	friend bool operator !=(const MyString& str1, const MyString& str2);
	char operator [](int ind);
	char* c_str() const;
	char* data() const;
	int length() const;
	int size() const;
	bool empty() const;
	int capacity() const;
	void shrink_to_fit();
	void erase(int ind, int cnt);
	void clear();
	void insert(int ind, int cnt, char chr);
	void insert(int ind, const char* str);
	void insert(int ind, const char* str, int cnt);
	void insert(int ind, std::string str);
	void insert(int ind, std::string str, int cnt);
	void append(int cnt, char chr);
	void append(const char* str);
	void append(const char* str, int ind, int cnt);
	void append(std::string str);
	void append(std::string str, int ind, int cnt);
	void replace(int ind, int cnt, const char* str);
	void replace(int ind, int cnt, std::string str);
	MyString substr(int ind) const;
	MyString substr(int ind, int cnt) const;
	int find(const char* str) const;
	int find(const char* str, int ind) const;
	int find(std::string str) const;
	int find(std::string str, int ind) const;
	friend std::ostream& operator <<(std::ostream& out, const MyString& str);
	friend std::istream& operator >>(std::istream& in, MyString& str);

private:
	char* str;
	int len;
	int cap;
};

#endif