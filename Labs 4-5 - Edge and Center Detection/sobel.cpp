#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
using namespace std;

int main()
{
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    int width = 1440;
    int height = 810;
    int size = width * height;
    int (*all_nums) = new int[size]; 
    int (*all_nums_2) = new int[size]; 
    int (*all_nums_3) = new int[size]; 
    ifstream MyReadFile("path of blur ppm file"); //ignore header
    string myText;
    int curr_count = 0;
    int r, g, b;
    int treshold = 150;
    for(int i = 0; i < size; i++){
        MyReadFile >> r >> g >> b;
        all_nums[i] = (int) r;
    }
    
    for(int z = 0; z < size; z++){
        all_nums_2[z] = all_nums[z];
    }

    for(int k = 0; k < size; k++){
        if(k / width != 0 && k % width != (width - 1) && k % width != 0 && k / width != (height - 1)){
            int new_val = (int) (-1*all_nums[k-(width + 1)] + 0*all_nums[k-width] + 1*all_nums[k-(width - 1)] + -2*all_nums[k-1] + 0*all_nums[k] + 2*all_nums[k+1] + -1*all_nums[k+(width - 1)] + 0*all_nums[k+width] + 1*all_nums[k+(width + 1)]);
            int new_val_2 = (int) (-1*all_nums[k-(width + 1)] + -2*all_nums[k-width] + -1*all_nums[k-(width - 1)] + 0*all_nums[k-1] + 0*all_nums[k] + 0*all_nums[k+1] + 1*all_nums[k+(width - 1)] + 2*all_nums[k+width] + 1*all_nums[k+(width + 1)]);
            int new_val_final = sqrt((new_val * new_val) + (new_val_2 * new_val_2));
            if(new_val_final > treshold){
                all_nums_2[k] = 0;
            }
        }
    }

    cout << "P3 1000 1333 255" << endl ;
    int j;
    for( j = 0 ; j < size ; j++ ){
        if(all_nums_2[j] != 0){
            cout << all_nums_2[j] << " " << all_nums_2[j] << " " << all_nums_2[j] << endl;
        }
        else{
            cout << 255 << " " << 0 << " " << 0 << endl;
        }
    }
    MyReadFile.close();
}