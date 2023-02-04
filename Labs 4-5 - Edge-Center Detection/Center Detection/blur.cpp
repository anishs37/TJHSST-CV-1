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
    int (*all_nums_2) = new int[size]; 
    int (*all_nums_3) = new int[size]; 
    ifstream MyReadFile("path of grayscale ppm file"); //ignore header
    string myText;
    int curr_count = 0;
    int r, g, b;
    for(int i = 0; i < size; i++){
        MyReadFile >> r >> g >> b;
        all_nums[i] = (int) r;
        all_nums_2[i] = (int) r;
    }

    for(int k = 0; k < size; k++){
        if(k / width != 0 && k % width != (width - 1) && k % width != 0 && k / width != (height - 1)){
            int new_val = (int) ((all_nums[k-(width + 1)] + all_nums[k-width] + all_nums[k-(width - 1)] + all_nums[k-1] + all_nums[k] + all_nums[k+1] + all_nums[k+(width - 1)] + all_nums[k+width] + all_nums[k+(width + 1)])/9);
            all_nums_2[k] = new_val;
        }
    }
    for(int y = 0; y < size; y++){
        all_nums_3[y] = all_nums_2[y];
    }
    for(int h = 0; h < size; h++){
        if(h / width != 0 && h % width != (width - 1) && h % width != 0 && h / width != (height - 1)){
            int new_val_2 = (int) ((all_nums_2[h-(width + 1)] + 2*all_nums_2[h-width] + all_nums_2[h-(width - 1)] + 2*all_nums_2[h-1] + 4*all_nums_2[h] + 2*all_nums_2[h+1] + 1*all_nums_2[h+(width - 1)] + 2*all_nums_2[h+width] + 1*all_nums_2[h+(width + 1)])/16);
            all_nums_3[h] = new_val_2;
        }
    }

    cout << "P3 1440 810 255" << endl;
    int j;
    for( j = 0 ; j < size ; j++ )
        cout << all_nums_3[j] << " " << all_nums_3[j] << " " << all_nums_3[j] << endl;

    MyReadFile.close();
    return 0;
}