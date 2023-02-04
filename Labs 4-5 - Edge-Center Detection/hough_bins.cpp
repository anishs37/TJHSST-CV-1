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
    int (*votes_bins) = new int[size / 100];
    ifstream MyReadFile("path of canny ppm file"); //ignore header
    int r, g, b;
    for(int i = 0; i < size; i++){
        MyReadFile >> r >> g >> b;
        all_nums[i] = (int) r;
    }
    for(int p = 0; p < size / 100; p++){
        votes_bins[p] = 0;
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
                        int x_v = (int)(x / 10);
                        int y_v = (int)(y / 10);
                        int k_val_test = (y_v * (width / 10)) + x_v;
                        votes_bins[k_val_test] = votes_bins[k_val_test] + 1;
                    }
                    else{
                        finish1 = true;
                    }
                    if(x2 > 0 && x2 < width && y2 > 0 && y2 < height){
                        int x_v_2 = (int)(x2 / 10);
                        int y_v_2 = (int)(y2 / 10);
                        int k_val_test_2 = (y_v_2 * (width / 10)) + x_v_2;
                        votes_bins[k_val_test_2] = votes_bins[k_val_test_2] + 1;
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
    for(int w = 0; w < size / 100; w++){
        if(votes_bins[w] > max_val){
            max_pos = w;
            max_val = votes_bins[w];
        }
    }

    cout << "P3 1440 810 255" << endl ;
    int j;
    for( j = 0 ; j < size ; j++ ){
        if(all_nums[j] == 255){
            cout << 255 << " " << 0 << " " << 0 << endl;
        }
        else{
            int x_out = j % width;
            int y_out = j / width;
            int row = (int) (y_out / 10);
            int col = (int) (x_out / 10);
            int j_index = (row * (width / 10)) + col;
            double val1 = max_val - votes_bins[j_index];
            double val2 = val1 / max_val;
            double val3 = val2 * 255;
            int val4 = (int) (val3);
            cout << val4 << " " << val4 << " " << val4 << endl;
        }
    }
    MyReadFile.close();
    return 0;
}