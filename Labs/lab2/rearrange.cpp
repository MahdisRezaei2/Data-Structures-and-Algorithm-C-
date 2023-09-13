#include <iostream>

// this method is to do the swapping job, when we need to swap index of two colors 
// keys is the name of the dynamic array
void swap(std::string* keys, int i, int j) {
    std::string temp = keys[i];
    keys[i] = keys[j];
    keys[j] = temp;
}
//this method is to rearrange the keys with calling the swap function when is needed
std::string* rearrangeKeys(std::string* keys, int size) {
    int low = 0;
    int middle = 0;
    int high = size - 1;

    while (middle <= high) {
        if (keys[middle] == "red") {
            swap(keys, low, middle);
            low++;
            middle++;
        } else if (keys[middle] == "blue") {
            middle++;
        } else if (keys[middle] == "white") {
            swap(keys, middle, high);
            high--;
        }
    }

    return keys;
}

int main() {
    //creating the dynamic array we need
    std::string* keys = new std::string[10];
    keys[0] = "white";
    keys[1] = "blue";
    keys[2] = "red";
    keys[3] = "red";
    keys[4] = "blue";
    keys[5] = "white";
    keys[6] = "blue";
    keys[7] = "white";
    keys[8] = "red";
    keys[9] = "red";
   
    
     //printing the original unsorted array
    std::cout << "keys before being rearranged: ";
    std::cout << std::endl;
    for (int i = 0; i < 10; i++) {
        std::cout << keys[i] << " ";
    }
    std::cout << std::endl;
    
    // calling the rearrangeKeys function
    std::string* rearrangedArrayKeys = rearrangeKeys(keys, 10);
    
    //printing the rearranged array
    std::cout << "keys after being rearranged: ";
    std::cout << std::endl;
    for (int i = 0; i < 10; i++) {
        std::cout << rearrangedArrayKeys[i] << " ";
    }
    std::cout << std::endl;
 //freeing the memory; after using the dynamic array, we need to deallocate the memory by using delete
    delete[] rearrangedArrayKeys;

    return 0;
}
