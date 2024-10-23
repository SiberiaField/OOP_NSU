#include "CircularBuffer.hpp"
#include <cstring>

//Private
int CircularBuffer::normalize(int idx) const{
	if (idx < 0)
		idx = capacity - abs(idx);
	else idx %= capacity;

	return idx;
}

value_type* CircularBuffer::make_copy(){
	value_type* copy = new value_type[size];
	for(int i = beg, j = 0; j < size; i++, j++){
		i = normalize(i);
	    copy[j] = buffer[i];
    }
    return copy;
}
	
//Public
CircularBuffer::CircularBuffer(){
	buffer = new value_type[1];
	size = 0;
	capacity = 1;
	beg = end = 0;
}

CircularBuffer::~CircularBuffer(){
	delete[] buffer;
	buffer = nullptr;
	size = capacity = 0;
	beg = end = 0;
}

CircularBuffer::CircularBuffer(const CircularBuffer & cb){
	delete[] buffer;
	buffer = nullptr;
	if(!cb.empty()){
		buffer = new value_type[cb.getCapacity()];
		for(int i = 0; i < cb.capacity; i++){
			buffer[i] = cb.buffer[i];
		}
	}
	beg = cb.beg;
	end = cb.end;
	size = cb.size;
	capacity = cb.capacity;
	std::cout << "Copyied succsessfully" << std::endl;
}

//Конструирует буфер заданной ёмкости.
CircularBuffer::CircularBuffer(int capacity){
    if(capacity > 0){
        this->capacity = capacity;
        buffer = new value_type[capacity];
        size = 0;
        beg = end = 0;
	}
	else throw std::invalid_argument("Capacity must be > 0");
}
		
//Конструирует буфер заданной ёмкости, целиком заполняет его элементом elem.
CircularBuffer::CircularBuffer(int capacity, const value_type & elem){
	if(capacity > 0){
		this->capacity = capacity;
		buffer = new value_type[capacity];
		for(int i = 0; i < capacity; i++){
			buffer[i] = elem;
		}
		size = capacity;
		beg = 0;
		end = capacity - 1;
	}
	else throw std::invalid_argument("Capacity must be > 0");
}

//Доступ по индексу. Не проверяют правильность индекса.
value_type & CircularBuffer::operator[](int i){
	if(this->empty()){
		throw std::runtime_error("Empty buffer");
	}
	return buffer[normalize(beg + i)];
}
const value_type & CircularBuffer::operator[](int i) const{
	if(this->empty()){
		throw std::runtime_error("Empty buffer");
	}
	return buffer[normalize(beg + i)];
}
		
//Доступ по индексу. Методы бросают исключение в случае неверного индекса.
value_type & CircularBuffer::at(int i){
	if(this->empty()){
		throw std::runtime_error("Empty buffer");
	}
	if(0 <= i && i < size){
		return buffer[normalize(beg + i)];
	}
	else throw std::out_of_range("Index out of range.");
}
const value_type & CircularBuffer::at(int i) const{
	if(this->empty()){
		throw std::runtime_error("Empty buffer");
	}
	if(0 <= i && i < size){
		return buffer[normalize(beg + i)];
	}
	else throw std::out_of_range("Index out of range.");
}

//Ссылка на первый элемент.
value_type & CircularBuffer::front(){
	if(this->empty()){
		throw std::runtime_error("Empty buffer");
	}
	return buffer[beg];
}
//Ссылка на последний элемент.
value_type & CircularBuffer::back(){
	if(this->empty()){
		throw std::runtime_error("Empty buffer");
	}
	return buffer[end];
} 
const value_type & CircularBuffer::front() const{
	if(this->empty()){
		throw std::runtime_error("Empty buffer");
	}
	return buffer[beg];
}
const value_type & CircularBuffer::back() const{
	if(this->empty()){
		throw std::runtime_error("Empty buffer");
	}
	return buffer[end];
}

//Линеаризация - сдвинуть кольцевой буфер так, что его первый элемент
//переместится в начало аллоцированной памяти. Возвращает указатель 
//на первый элемент.
value_type * CircularBuffer::linearize(){
	if(this->empty()){
		throw std::runtime_error("Empty buffer");
	}
	value_type* copy = make_copy();
	for(int i = 0; i < size; i++){
		buffer[i] = copy[i];
	}
	delete[] copy;
	beg = 0;
	end = beg + size - 1;
	return buffer;
}
//Проверяет, является ли буфер линеаризованным.
bool CircularBuffer::is_linearized() const{
	return beg == 0;
}
//Сдвигает буфер так, что по нулевому индексу окажется элемент 
//с индексом new_begin.
void CircularBuffer::rotate(int new_begin){
	if(0 <= new_begin && new_begin < size){
		int new_begin = normalize(beg + new_begin);
		value_type* copy = make_copy();
		for(int i = normalize(beg - new_begin), j = 0; j < size; i++, j++){
			i = normalize(i);
			buffer[i] = copy[j];
		}
		beg = normalize(beg - new_begin);
		end = normalize(end - new_begin);
		delete[] copy;
	}
	else throw std::out_of_range("Index out of range.");
}
//Количество элементов, хранящихся в буфере.
int CircularBuffer::getSize() const{
	return size;
}
bool CircularBuffer::empty() const{
	return size == 0;
}
//true, если size() == capacity().
bool CircularBuffer::full() const{
	return size == capacity;
}
//Количество свободных ячеек в буфере.
int CircularBuffer::reserve() const{
	return capacity - size;
}
//ёмкость буфера
int CircularBuffer::getCapacity() const{
	return capacity;
}

void CircularBuffer::set_capacity(int new_capacity){
	if(buffer == nullptr){
		throw std::runtime_error("buffer == nullptr");
	}
	if(new_capacity != capacity){
		value_type *new_buffer = new value_type[new_capacity];
		if(new_capacity > capacity){
			for(int i = 0; i < capacity; i++){
				new_buffer[i] = buffer[i];
			}

			if(end < beg){
				for(int i = capacity - 1, j = 1; i >= beg; i--, j++){
					new_buffer[new_capacity - j] = new_buffer[i];
				}
				beg += new_capacity - capacity;
			}
		}
		else{
			int i = beg, j = 0;
			for(; j < new_capacity && i != end + 1; i++, j++){
				i = normalize(i);
				new_buffer[j] = buffer[i];
			}
			beg = 0;
			end = j - 1;
			size = j + 1;
		}
		delete[] buffer;
		capacity = new_capacity;
		buffer = new_buffer;
	}
}
//Изменяет размер буфера.
//В случае расширения, новые элементы заполняются элементом item.
void CircularBuffer::resize(int new_size, const value_type & item){
	if(buffer == nullptr){
		throw std::runtime_error("buffer == nullptr");
	}
	if(new_size != size && new_size <= capacity){
		if(new_size > size){
			if(size == 0){
				for(int i = 0; i < new_size; i++){
					int j = normalize(beg + i);
					buffer[j] = item;
				}
				end += new_size - 1;
			}
			else{
				for(int i = 1; i <= new_size - size; i++){
					int j = normalize(end + i);
					buffer[j] = item;
				}
				end += new_size - size;
			}
			end = normalize(end);
		}
		else {
			end -= (size - new_size);
			end = normalize(end);
		}
		size = new_size;
	}
}
//Оператор присваивания.
CircularBuffer & CircularBuffer::operator=(const CircularBuffer & cb){
	delete[] buffer;
	buffer = nullptr;
	if(!cb.empty()){
		buffer = new value_type[cb.capacity];
		for(int i = 0; i < cb.capacity; i++){
			buffer[i] = cb.buffer[i];
		}
	}
	beg = cb.beg;
	end = cb.end;
	size = cb.size;
	capacity = cb.capacity;
    return *this;
}
//Обменивает содержимое буфера с буфером cb.
void CircularBuffer::swap(CircularBuffer & cb){
	CircularBuffer tmp;
	tmp = cb;
	cb = *this;
	*this = tmp;
}

//Добавляет элемент в конец буфера. 
//Если текущий размер буфера равен его ёмкости, то переписывается
//первый элемент буфера (т.е., буфер закольцован). 
void CircularBuffer::push_back(const value_type & item){
	if (this->full()){
		buffer[beg] = item;
	}
	else{
		if(!this->empty()){
			end++;
			end = normalize(end);
		}
		buffer[end] = item;
		size++;
	}
}
//Добавляет новый элемент перед первым элементом буфера. 
//Аналогично push_back, может переписать последний элемент буфера.
void CircularBuffer::push_front(const value_type & item){
	if (this->full()){
		buffer[end] = item;
	}
	else{
		if(!this->empty()){
			beg--;
			beg = normalize(beg);
		}
		buffer[beg] = item;
		size++;
	}
}
//удаляет последний элемент буфера.
void CircularBuffer::pop_back(){
    if(!this->empty()){
		end = normalize(end - 1);
		size--;
	}
}
//удаляет первый элемент буфера.
void CircularBuffer::pop_front(){
	if(!this->empty()){
		beg = normalize(beg + 1);
		size--;
	}
}

//Вставляет элемент item по индексу pos. Ёмкость буфера остается неизменной.
void CircularBuffer::insert(int pos, const value_type & item){
	if(0 <= pos && pos < size){
		if(!this->empty()){
			pos = normalize(beg + pos);
			buffer[pos] = item;
		}
	}
	else throw std::out_of_range("Index out of range.");
}
//Удаляет элементы из буфера в интервале [first, last).
void CircularBuffer::erase(int first, int last){
	if(first < last && !this->empty()){
		if(0 <= first && first < size && 0 <= last && last < size + 1){
			int dels = last - first;
			if(dels < size){
				if(first == 0){
					beg = normalize(beg + last);
				}
				else if(last == size){
					end = normalize(beg + first - 1);
				}
				else{
					for(int i = beg; i != normalize(first + beg); i++){
						i = normalize(i);
						int j = normalize(i + dels);
						buffer[j] = buffer[i];
					}
					beg = normalize(beg + dels);
				}
				size -= dels;
			}
			else{
				beg = 0;
				end = 0;
				size = 0;
			}
		}
		else throw std::out_of_range("Index out of range.");
	}
}
//Очищает буфер.
void CircularBuffer::clear(){
	delete[] buffer;
	buffer = nullptr;
	size = capacity = 0;
	end = beg = 0;
}

bool operator==(const CircularBuffer & a, const CircularBuffer & b);
bool operator!=(const CircularBuffer & a, const CircularBuffer & b);