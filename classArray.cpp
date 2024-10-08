#include <iostream>
using namespace std;

class ArrayF{
    float *data{nullptr};
    int length{0};
    public:
        int getLength(){
            return length;
        }
        ArrayF(): data(nullptr), length(0){
    /*         cout<<this<<" Def con\n";
    */    };
        ArrayF(int length){
    /*         cout<<this<<" paran con\n";
    */        newArray(length);
        }
        ArrayF(ArrayF &ar){
            if (this != &ar){
                newArray(ar.length);
                copyAr(ar.data);
    /*             cout<<this<<" copy con\n";
    */        }
        }
    private:
        void copyAr(float *ar){
            for (int i = 0; i < length;i++){
                data[i] = ar[i];
            }
        }
        void newArray(int l){
            length = 0;
            if (l <= 0){
                data = NULL;
                return;
            }
            else{
                length = l;
                data = new float[l]; 
            }
        }
        void deleteArrayF(){
            if (data != NULL){
                delete[]data;
            }
            data = NULL;
            length = 0;
        }
    public:
        ~ArrayF(){
            deleteArrayF();
    /*         cout<<this<<" destr\n";
    */    }
        ArrayF& operator=(ArrayF& arr){
            float* new_data = new float[arr.length];
            for (int i = 0; i<=arr.length; i++){
                new_data[i] = arr.data[i];
            }
            delete[] data;
            data = new_data;
            length = arr.length;
            return *this;

        }
        ArrayF& operator+=(int value){
            for (int i = 0; i <= length; i++){
                data[i] += value;
            }
            return *this;
        }
        float &operator[](int i){
            return data[i];
        }
};

/* void F1(ArrayF ar);
void F2(ArrayF &ar); */

int main()
{
    ArrayF arr{5};
    arr[1] = 28;
    cout<<arr[1]<<endl;
    ArrayF first{2};
    first[0] = 8;
    ArrayF second{2};
    second = first;
    cout<<second[0]<< endl;
    first[0] += 8;
    cout<< first[0]<< endl;

}

/* void F1(ArrayF ar){
    cout<<"F1 "<< &ar<< endl;
}
void F2(ArrayF &ar){
    cout<<"F2 "<< &ar<< endl;
} */











//конструктор перемещения
//оператор присваивания