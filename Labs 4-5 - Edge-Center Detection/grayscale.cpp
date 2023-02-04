#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
using namespace std;

int main()
{
    int width = 1440;
    int height = 810;
    int size = width * height;
    int (*all_nums) = new int[size]; 
    ifstream MyReadFile("path of original image ppm file"); //ignore header
    string myText;

    int r, g, b;
    for(int i = 0; i < size; i++){
        MyReadFile >> r >> g >> b;
        all_nums[i] = (int) (0.3 * r + 0.59 * g + 0.11 * b);
    }

    cout << "P3 1440 810 255" << endl ;
    int j;
    for( j = 0 ; j < size ; j++ )
        cout << all_nums[j] << " " << all_nums[j] << " " << all_nums[j] << endl;

    MyReadFile.close();

    return 0;
}