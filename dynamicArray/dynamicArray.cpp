#include <iostream>
#include <string>

using namespace std;

template <typename T>
struct DynamicArray {

    int size{};
    int capacity{ 1 };
    T* array = new T[capacity];

    void add(T data) {
        if (size == capacity) {

            capacity *= 2;

            T* tmp_array = new T[capacity];

            for (int i = 0; i < size; i++)
                tmp_array[i] = array[i];

            delete[] array;
            array = tmp_array;

        }

        array[size] = data;
        size++;

    }

    T get(int index) {

        if (index < size) {
            return array[index];
        }
        else {
            throw out_of_range("Błędny zakres");
        }

    }

    void change(int index, T newData) {

        if (index < size) {
            array[index] = newData;
        }
        else {
            throw out_of_range("Błędny zakres");
        }

    }

    void clear() {
        delete[] array;
        size = 0;
        capacity = 1;
        array = new T[capacity];
    }

    string str() {

        string s = "Actual size : " + to_string(size) + "\nCapacity : " + to_string(capacity) + "\n";

        return s;

    }
    
    void sort(int (*func)(T*, T*)) {
        for(int i = 0; i < size - 1; i++)
            for (int j = 0; j < size - i - 1; j++) {
                if (func(&array[j], &array[j + 1]) == 1) {
                    T tmp = array[j + 1];
                    array[j + 1] = array[j];
                    array[j] = tmp;
                }
            }
    }

};

struct simple_object {

    string first_name;
    string second_name;
    int age;

    friend ostream& operator<<(ostream& os, simple_object so);

};

int simple_object_comparator(simple_object * so1, simple_object * so2) {
    if (so1->age == so2->age)
        return 0;
    else if (so1->age < so2->age)
        return -1;
    else
        return 1;
}

ostream& operator<<(ostream& os, simple_object so) {
    os << "First name: " << so.first_name << "; second name: " << so.second_name << "; age: " << so.age << "\n";
    return os;
}

int main()
{
    setlocale(LC_ALL, "");
    DynamicArray<simple_object>* array1 = new DynamicArray<simple_object>();
    //cout << array1->str();
    //array1->add(5);
    //cout << array1->str();
    //array1->add(6);
    //cout << array1->str();
    //array1->add(7);
    //cout << array1->str();
    //array1->add(9);
    //cout << array1->str();
    //array1->add(10);
    //cout << array1->str();

    //cout << array1->get(0) << endl;
    //cout << array1->get(4);

    //array1->clear();
    //cout << array1->str();

    array1->add({ "Krystian", "Szabat", 21 });
    array1->add({ "Patrick", "Gendeck", 22 });
    array1->add({ "Paweł", "Rzepecki", 20 });
    array1->add({ "Maciej", "Jankowski", 16 });
    cout << array1->str();
    cout << array1->get(0);
    cout << array1->get(1);
    cout << array1->get(2);
    cout << array1->get(3);

    cout << '\n';
    array1->sort(simple_object_comparator);
    cout << array1->get(0);
    cout << array1->get(1);
    cout << array1->get(2);
    cout << array1->get(3);

    delete array1;
}


