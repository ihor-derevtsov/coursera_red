#pragma once

#include <cstdlib>

// Реализуйте шаблон SimpleVector
template<typename T>
class SimpleVector {
public:
	SimpleVector();
	explicit SimpleVector(size_t size);
	~SimpleVector();

	T& operator[](size_t index);

	T *begin();
	T *end();

	const T *begin() const;
	const T *end() const;

	size_t Size() const;
	size_t Capacity() const;
	void PushBack(const T& value);

private:
	// Добавьте поля для хранения данных вектора
	T *data;
	T *end_;
	size_t size_;
	size_t capacity_;
};

template<typename T>
SimpleVector<T>::SimpleVector() {
	data = nullptr;
	end_ = data;
	size_ = 0;
	capacity_ = 0;
}

template<typename T>
SimpleVector<T>::SimpleVector(size_t size) {
	size_ = size;
	capacity_ = size_ * 2;
	data = new T[capacity_];
	end_ = data + capacity_;
}

template<typename T>
SimpleVector<T>::~SimpleVector() {
	if (data != nullptr) { delete[] data; /* [здесь было delete end_; ] */ }
	capacity_ = 0;
	size_ = 0;
}

template<typename T>
T& SimpleVector<T>::operator[](size_t index) {
	return data[index];
}

template<typename T>
T *SimpleVector<T>::begin() {
	return data;
}

template<typename T>
T *SimpleVector<T>::end() {
	return end_;
}

template<typename T>
const T *SimpleVector<T>::begin() const {
	return data;
}

template<typename T>
const T *SimpleVector<T>::end() const {
	return end_;
}

template<typename T>
size_t SimpleVector<T>::Size() const {
	return size_;
}

template<typename T>
size_t SimpleVector<T>::Capacity() const {
	return capacity_;
}

template<typename T>
void SimpleVector<T>::PushBack(const T& value) {
	if (Capacity() == Size()) {
		if (capacity_ == 0) { capacity_ = 2; }
		else { capacity_ *= 2; }
		T *new_data = new T[capacity_];
		for (auto i = 0; i < size_; ++i) {
			new_data[i] = data[i];
		}

		delete[] data;
		data = new_data;
		data[size_++] = value;
		end_ = data + size_;
	} else {
		data[size_++] = value;
		end_ = data + size_;
	}
}



