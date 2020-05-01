#ifndef VALUE_LIST_H
#define VALUE_LIST_H
#include <cstddef>
#include "real.h"

struct Value_List {
private:
	real * table;
	size_t size;
public:
	Value_List(size_t s);
	Value_List();
	~Value_List();
	Value_List(Value_List && v) noexcept;
	Value_List& operator=(Value_List&& other);
	real & operator[](size_t index);
	real operator[](size_t index) const;
	Value_List operator*(const real d);
	Value_List operator+(const Value_List& v);
	Value_List operator-(const Value_List& v);
	Value_List& operator+=(const Value_List& v);
	Value_List& operator-=(const Value_List& v);
	size_t get_size() const;
};

Value_List operator*(real d, const Value_List& vl);

#endif
