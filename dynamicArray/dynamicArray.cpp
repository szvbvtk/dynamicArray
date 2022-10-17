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

    string str(string (*func)(T so)) {

        string s = "Actual size : " + to_string(size) + "\nCapacity : " + to_string(capacity) + "\n";

        for (int i = 0; i < size; i++) {
            s += func(array[i]);
        }

        s += '\n';

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

string so_str(simple_object so) {
    return "First name: " + so.first_name + "; second name: " + so.second_name + "; age: " + to_string(so.age) + "\n";
}


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
    srand(time(NULL));
    //char alphabet[] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','y','x','z' };

    DynamicArray<simple_object>* array1 = new DynamicArray<simple_object>();
    //array1->add({ "Krystian", "Szabat", 21 });
    //array1->change(0, { "Patrick", "Gendeck", 22 });
    //array1->add({ "Paweł", "Rzepecki", 20 });
    //array1->add({ "Maciej", "Jankowski", 16 });
    //cout << array1->str(so_str);
    //cout << array1->get(0);
    //cout << array1->get(1);
    //cout << array1->get(2);

    //cout << '\n';
    //array1->sort(simple_object_comparator);
    //cout << array1->str(so_str);

    clock_t start = clock();

    double max_measured_time_per_element = 0.0;
    for (int i = 0; i < 10000000; i++) {
        simple_object obj{"Marcin", "Lew", rand() % 30};

        clock_t start_time = clock();
        array1->add(obj);
        clock_t end_time = clock();

        double measured_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

        if (measured_time > max_measured_time_per_element) {
            max_measured_time_per_element = measured_time;
            cout << "New worst time: " << measured_time << " index: " << i << ' ';
            measured_time = 0;
        }

    }

    clock_t stop = clock();

    cout << "\n\n\nExecution time: " << (double)(stop - start) / CLOCKS_PER_SEC << "\n\n\n";

    delete array1;
}


