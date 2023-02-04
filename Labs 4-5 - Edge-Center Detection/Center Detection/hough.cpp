#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
#include <math.h>
#include <algorithm>
using namespace std;

int main()
{
    int width = 1440;
    int height = 810;
    int size = width * height;
    int (*all_nums) = new int[size]; 
    int (*all_nums_2) = new int[size]; 
    int (*votes) = new int[size]; 
    ifstream MyReadFile("path of canny ppm file"); //ignore header
    int r, g, b;
    for(int i = 0; i < size; i++){
        MyReadFile >> r >> g >> b;
        all_nums[i] = (int) r;
        all_nums_2[i] = (int) r;
        votes[i] = 0;
    }

    for(int k = 0; k < size; k++){
        if(k / width != 0 && k % width != (width - 1) && k % width != 0 && k / width != (height - 1)){
            if(all_nums[k] == 255){
                int g_x = (int) (-1*all_nums[k-(width + 1)] + 0*all_nums[k-width] + 1*all_nums[k-(width - 1)] + -2*all_nums[k-1] + 0*all_nums[k] + 2*all_nums[k+1] + -1*all_nums[k+(width - 1)] + 0*all_nums[k+width] + 1*all_nums[k+(width + 1)]);
                int g_y = (int) (-1*all_nums[k-(width + 1)] + -2*all_nums[k-width] + -1*all_nums[k-(width - 1)] + 0*all_nums[k-1] + 0*all_nums[k] + 0*all_nums[k+1] + 1*all_nums[k+(width - 1)] + 2*all_nums[k+width] + 1*all_nums[k+(width + 1)]);
                double angle_test = atan2(g_y, g_x);
                double r = 0.1;
                bool finish1 = false;
                bool finish2 = false;
                while(finish1 == false || finish2 == false){
                    int x = (int) ((k % width) + r * cos(angle_test));
                    int y = (int) ((k / width) + r * sin(angle_test));
                    int x2 = (int) ((k % width) - r * cos(angle_test));
                    int y2 = (int) ((k / width) - r * sin(angle_test));
                    if(x > 0 && x < width && y > 0 && y < height){
                        int k_val = (y * width) + x;
                        votes[k_val] = votes[k_val] + 1;
                    }
                    else{
                        finish1 = true;
                    }
                    if(x2 > 0 && x2 < width && y2 > 0 && y2 < height){
                        int k_val_2 = (y2 * width) + x2;
                        votes[k_val_2] = votes[k_val_2] + 1;
                    }
                    else{
                        finish2 = true;
                    }
                    r = r + 0.1;
                }
            }
        }
    }

    int max_pos = 0;
    int max_val = 0;
    for(int w = 0; w < size; w++){
        if(votes[w] > max_val){
            max_pos = w;
            max_val = votes[w];
        }
    }

    cout << "P3 1440 810 255" << endl ;
    int j;
    for( j = 0 ; j < size ; j++ ){
        if(all_nums[j] == 255){
            cout << 255 << " " << 0 << " " << 0 << endl;
        }
        else{
            double val1 = max_val - votes[j];
            double val2 = val1 / max_val;
            double val3 = val2 * 255;
            int val4 = (int) (val3);
            cout << val4 << " " << val4 << " " << val4 << endl;
        }
    }
    MyReadFile.close();
    return 0;
}