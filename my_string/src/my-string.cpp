#include "my_string/include/my-string.h"
#include <string>
#include <iostream>
#include <string.h>

MyString::MyString() {
	str = nullptr;
	len = 0;
	cap = 0;
}

MyString::MyString(const char* str) : len(strlen(str)), cap(len + 1) {
	ToNewString(str);
}

MyString::MyString(std::string& str) : str(&str[0]), len(std::size(str)), cap(len + 1) {
	ToNewString(this->str);
}

MyString::MyString(const char* str, int count) : len(count), cap(len + 1) {
	ToNewString(str);
}

MyString::MyString(int count, char chr) : len(count), cap(len + 1) {
	this->str = new char[len + 1];
	for (int i = 0; i < len; i++)
		this->str[i] = chr;
	this->str[len] = '\0';
}

MyString::MyString(const MyString& str) : len(str.len), cap(len + 1) {
	ToNewString(str.str);
}

void MyString::ToNewString(const char* str) {
	this->str = new char[len + 1];
	for (int i = 0; i < len; i++)
		this->str[i] = str[i];
	this->str[len] = '\0';
}

MyString::~MyString() {
	delete[] str;
}

MyString MyString::operator +(const MyString& str) {
	MyString s(this->str);
	s.append(str.str);
	return s;
}

MyString MyString::operator +(const char* str) {
	MyString s(this->str);
	s.append(str);
	return s;
}

void MyString::operator +=(const MyString& str) {
	append(str.str);
}

void MyString::operator +=(const char* str) {
	append(str);
}

void MyString::operator =(const MyString& str) {
	clear();
	append(str.str);
}

void MyString::operator =(const char chr) {
	clear();
	append(1, chr);
}

bool operator >(const MyString& str1, const MyString& str2) {
	if (str1.empty() && str2.empty()) return 0;
	if (str1.empty()) return 0;
	if (str2.empty()) return 1;
	if (str1.str[0] > str2.str[0]) return 0;
	if (str1.str[0] < str2.str[0]) return 1;
	int i = 1;
	while (str1.str[i] == str2.str[i]) {
		i++;
		if (i >= str1.len || i >= str2.len) {
			if (str1.len > str2.len) return 1;
			return 0;
		}
	}
	if (str1.str[i] - str2.str[i] > 0) return 1;
	return 0;
}

bool operator ==(const MyString& str1, const MyString& str2) {
	if (str1.len != str2.len) return 0;
	if (str1.str[0] != str2.str[0] && str1.len - str2.len == 0) return 0;
	int i = 1;
	while (str1.str[i] == str2.str[i]) {
		if (i >= str1.len) break;
		i++;
	}
	return !(i != str1.len) && (str1.len != 0);
}

bool operator <(const MyString& str1, const MyString& str2) {
	return str2 > str1;
}

bool operator >=(const MyString& str1, const MyString& str2) {
	return !(str1 < str2);
}

bool operator <=(const MyString& str1, const MyString& str2) {
	return !(str1 > str2);
}

bool operator !=(const MyString& str1, const MyString& str2) {
	return !(str1 == str2);
}

char MyString::operator [](int ind) {
	return str[ind];
}

char* MyString::c_str() const {
	return str;
}

char* MyString::data() const {
	return str;
}

int MyString::length() const {
	return len;
}

int MyString::size() const {
	return this->length();
}

bool MyString::empty() const {
	return len == 0;
}

int MyString::capacity() const {
	return cap;
}

void MyString::shrink_to_fit() {
	if (!empty()) {
		MyString str(this->str);
		delete[] this->str;
		len = str.size();
		this->str = new char[len + 1];
		cap = len + 1;
		for (int i = 0; i < len; i++)
			this->str[i] = str.str[i];
		this->str[len] = '\0';
	}
}

void MyString::erase(int ind, int cnt) {
	if (abs(ind) - cnt > size()) return;
	if (cnt < 0) return;
	MyString s;
	s.append(str, 0, ind);
	s.append(str, ind + cnt, len - ind - cnt);
	clear();
	this->insert(0, s.str);
}

void MyString::clear() {
	if (!empty())
		str[0] = '\0';
	len = 0;
}

void MyString::insert(int ind, const char* str) {
	if (ind > this->len) return;
	if (str != nullptr) {
		int z = 0;
		while (ind + z != 0 && ind < 0) {
			z++;
		}
		int lenstr = strlen(str);
		int len = this->len + lenstr;
		char* newStr = new char[len + 1];
		for (int i = 0, j = 0; i < len; i++) {
			if (i < ind || i >= ind + lenstr)
				newStr[i] = this->str[j++];
			else newStr[i] = str[z++];
		}
		this->str = new char[len + 1];
		for (int i = 0; i < len; i++) {
			this->str[i] = newStr[i];
		}
		this->str[len] = '\0';
		this->len = len;
		delete[] newStr;
	}
	else {
		this->cap = 0;
		this->len = 0;
		delete[] this->str;
		this->str = nullptr;
	}
}

void MyString::insert(int ind, int cnt, char chr) {
	if (cnt < 0) return;
	char* str = new char[cnt + 1];
	for (int i = 0; i < cnt; i++)
		str[i] = chr;
	str[cnt] = '\0';
	insert(ind, str);
	delete[] str;
}

void MyString::insert(int ind, const char* str, int cnt) {
	if (abs(ind) - cnt > size()) return;
	if (cnt < 0) return;
	char* newStr = new char[cnt + 1];
	for (int i = 0; i < cnt; i++)
		newStr[i] = str[i];
	newStr[cnt] = '\0';
	insert(ind, newStr);
	delete[] newStr;
}

void MyString::insert(int ind, std::string str) {
	insert(ind, str.c_str());
}

void MyString::insert(int ind, std::string str, int cnt) {
	if (abs(ind) - cnt > size()) return;
	if (cnt < 0) return;
	str.erase(cnt, str.size());
	insert(ind, str.c_str());
}

void MyString::append(int cnt, char chr) {
	insert(len, cnt, chr);
}

void MyString::append(const char* str) {
	insert(len, str);
}

void MyString::append(const char* str, int ind, int cnt) {
	insert(len, &str[ind], cnt);
}

void MyString::append(std::string str) {
	insert(len, str);
}

void MyString::append(std::string str, int ind, int cnt) {
	insert(len, &str[ind], cnt);
}

void MyString::replace(int ind, int cnt, const char* str) {
	int len = strlen(str);
	if (ind > this->len) return;
	if (cnt > this->len - ind) cnt = this->len - ind;
	if (cnt < 0) return;
	int size = this->size();
	for (int i = ind, j = ind + cnt; j < size; i++, j++)
		this->str[i] = this->str[j];
	this->str[this->len - cnt] = '\0';
	insert(ind, str);
}

void MyString::replace(int ind, int cnt, std::string str) {
	replace(ind, cnt, str.c_str());
}

MyString MyString::substr(int ind) const {
	if (ind < 0) return *this;
	MyString str;
	str.append(this->str, ind, len - ind);
	return str;
}

MyString MyString::substr(int ind, int cnt) const {
	if (cnt > len - ind) cnt = len - ind;
	if (cnt < 0) cnt = 0;
	if (ind < 0) return *this;
	MyString str;
	str.append(this->str, ind, cnt);
	return str;
}

int MyString::find(const char* str, int ind) const {
	if (ind > this->len || ind < 0) return -1;
	int len = strlen(str);
	for (int i = ind; i < this->len; i++) {
		int j = 0;
		for (int k = i; j < len; j++, k++) {
			if (str[j] != this->str[k]) break;
			if (j == len - 1) return i;
		}
	}
	return -1;
}

int MyString::find(const char* str) const {
	return find(str, 0);
}

int MyString::find(std::string str) const {
	return find(&str[0], 0);
}

int MyString::find(std::string str, int ind) const {
	return find(&str[0], ind);
}

std::ostream& operator <<(std::ostream& out, const MyString& str) {
	if (str.str != 0) return out << str.str;
	return out << "";
}

std::istream& operator >>(std::istream& in, MyString& str) {
	MyString s = new char[1000];
	in >> s.str;
	str.clear();
	str.append(s.str);
	return in;
}