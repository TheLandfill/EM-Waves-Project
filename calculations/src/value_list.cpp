#include "value_list.h"
#include "real.h"
#include <utility>
#include <string>
#include <stdexcept>

Value_List::Value_List(size_t s) : size(s) {
	table = new real[size];
	for (size_t i = 0; i < size; i++) {
		table[i] = 0;
	}
}

Value_List::Value_List() : size(0) {
	table = nullptr;
}

Value_List::~Value_List() {
	delete[] table;
}

Value_List::Value_List(Value_List && vl) noexcept : table(std::move(vl.table)), size(vl.size) {
	vl.table = nullptr;
}

Value_List& Value_List::operator=(Value_List&& other) {
	table = other.table;
	other.table = nullptr;
	size = other.size;
	return *this;
}

real & Value_List::operator[](size_t index) {
	return table[index];
}

real Value_List::operator[](size_t index) const {
	return table[index];
}

size_t Value_List::get_size() const {
	return size;
}

void value_list_error(const size_t first_size, const size_t second_size) {
		std::string error("You are trying to add together two Value_Lists of different sizes."
		"\nSize of first Value_List:\t");
		error += first_size;
		error += "Size of second Value_List:\t";
		error += second_size;
		error += "\n";
		throw std::invalid_argument(error);
}

Value_List Value_List::operator*(const real d){
	Value_List new_vl(size);
	for (size_t i = 0; i < size; i++) {
		new_vl[i] = table[i] * d;
	}
	return new_vl;
}

Value_List operator*(real d, const Value_List& vl) {
	Value_List new_vl(vl.get_size());
	for (size_t i = 0; i < vl.get_size(); i++) {
		new_vl[i] = vl[i] * d;
	}
	return new_vl;
}

Value_List Value_List::operator+(const Value_List& v){
	if (size != v.get_size()) {
		value_list_error(size, v.get_size());
	}
	Value_List new_vl(size);
	for (size_t i = 0; i < size; i++) {
		new_vl[i] = table[i] + v[i];
	}
	return new_vl;
}

Value_List Value_List::operator-(const Value_List& v){
	if (size != v.get_size()) {
		value_list_error(size, v.get_size());
	}
	Value_List new_vl(size);
	for (size_t i = 0; i < size; i++) {
		new_vl[i] = table[i] - v[i];
	}
	return new_vl;
}

Value_List& Value_List::operator+=(const Value_List& v){
	if (size != v.get_size()) {
		value_list_error(size, v.get_size());
	}
	for (size_t i = 0; i < size; i++) {
		table[i] += v[i];
	}
	return *this;
}

Value_List& Value_List::operator-=(const Value_List& v){
	if (size != v.get_size()) {
		value_list_error(size, v.get_size());
	}
	for (size_t i = 0; i < size; i++) {
		table[i] -= v[i];
	}
	return *this;
}
