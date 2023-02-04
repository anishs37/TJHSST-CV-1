#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
#include <math.h>
using namespace std;

void keep_adding(int a_test, int lowtreshold, int hightreshold, int all_nums_2[1166400], int all_nums_3[1166400], int width, int height)
{
    if(a_test / width != 0 && a_test % width != (width - 1) && a_test % width != 0 && a_test / width != (height - 1)){
        int g_x = (int) (-1*all_nums_2[a_test-(width + 1)] + 0*all_nums_2[a_test-width] + 1*all_nums_2[a_test-(width - 1)] + -2*all_nums_2[a_test-1] + 0*all_nums_2[a_test] + 2*all_nums_2[a_test+1] + -1*all_nums_2[a_test+(width - 1)] + 0*all_nums_2[a_test+width] + 1*all_nums_2[a_test+(width + 1)]);
        int g_y = (int) (-1*all_nums_2[a_test-(width + 1)] + -2*all_nums_2[a_test-width] + -1*all_nums_2[a_test-(width - 1)] + 0*all_nums_2[a_test-1] + 0*all_nums_2[a_test] + 0*all_nums_2[a_test+1] + 1*all_nums_2[a_test+(width - 1)] + 2*all_nums_2[a_test+width] + 1*all_nums_2[a_test+(width + 1)]);
        int g = sqrt((g_x * g_x) + (g_y * g_y));
        if(g < hightreshold && g > lowtreshold && all_nums_3[a_test] != 0){
            all_nums_3[a_test] = 0;
            double angle_test = atan2(g_y, g_x);
            double deg_angle = (angle_test * (180 / 3.14159265358979323846264338327950));
            if(deg_angle < 0){
                deg_angle += 360;
            }
            //cout << angle_test << " " << deg_angle << endl;
            if((deg_angle >= 22.5 && deg_angle < 67.5) || (deg_angle >= 202.5 && deg_angle < 247.5)){
                keep_adding(a_test - (width - 1), lowtreshold, hightreshold, all_nums_2, all_nums_3, width, height);
                keep_adding(a_test + (width + 1), lowtreshold, hightreshold, all_nums_2, all_nums_3, width, height);
            }
            if(deg_angle >= 67.5 && deg_angle < 112.5 || (deg_angle >= 247.5 && deg_angle < 292.5)){
                keep_adding(a_test - width, lowtreshold, hightreshold, all_nums_2, all_nums_3, width, height);
                keep_adding(a_test + width, lowtreshold, hightreshold, all_nums_2, all_nums_3, width, height);
            }
            if(deg_angle >= 112.5 && deg_angle < 157.5 || (deg_angle >= 292.5 && deg_angle < 337.5)){
                keep_adding(a_test - (width + 1), lowtreshold, hightreshold, all_nums_2, all_nums_3, width, height);
                keep_adding(a_test + (width + 1), lowtreshold, hightreshold, all_nums_2, all_nums_3, width, height);
            }
            if(deg_angle >= 157.5 && deg_angle < 202.5 || (deg_angle >= 337.5 || deg_angle < 22.5)){
                keep_adding(a_test - 1, lowtreshold, hightreshold, all_nums_2, all_nums_3, width, height);
                keep_adding(a_test + 1, lowtreshold, hightreshold, all_nums_2, all_nums_3, width, height);
            }
        }
    }
}

int main()
{
    int width = 1440;
    int height = 810;
    int size = width * height;
    int (*all_nums) = new int[size]; 
    int (*all_nums_2) = new int[size]; 
    int (*all_nums_3) = new int[size]; 
    int (*all_nums_4) = new int[size]; 
    ifstream MyReadFile("path of blur ppm file"); //ignore header
    string myText;
    int curr_count = 0;
    int r, g, b;
    int high_treshold = 200;
    int low_treshold = 100;
    for(int i = 0; i < size; i++){
        MyReadFile >> r >> g >> b;
        all_nums[i] = (int) r;
        all_nums_2[i] = (int) r;
        all_nums_4[i] = (int) r;
    }

    for(int k = 0; k < size; k++){
        if(k / width != 0 && k % width != (width - 1) && k % width != 0 && k / width != (height - 1)){
            int new_val = (int) (-1*all_nums[k-(width + 1)] + 0*all_nums[k-width] + 1*all_nums[k-(width - 1)] + -2*all_nums[k-1] + 0*all_nums[k] + 2*all_nums[k+1] + -1*all_nums[k+(width - 1)] + 0*all_nums[k+width] + 1*all_nums[k+(width + 1)]);
            int new_val_2 = (int) (-1*all_nums[k-(width + 1)] + -2*all_nums[k-width] + -1*all_nums[k-(width - 1)] + 0*all_nums[k-1] + 0*all_nums[k] + 0*all_nums[k+1] + 1*all_nums[k+(width - 1)] + 2*all_nums[k+width] + 1*all_nums[k+(width + 1)]);
            int new_val_final = sqrt((new_val * new_val) + (new_val_2 * new_val_2));
            if(new_val_final > high_treshold)
                all_nums_2[k] = 0;
        }
    }
    for(int y = 0; y < size; y++){
        all_nums_3[y] = all_nums_2[y];
    }

    for(int a = 0; a < size; a++){
        if(a / width != 0 && a % width != (width - 1) && a % width != 0 && a / width != (height - 1)){
            if(all_nums_2[a] != 0){
                keep_adding(a, low_treshold, high_treshold, all_nums_2, all_nums_3, width, height);
            }
        }
    }

    cout << "P3 1440 810 255" << endl ;
    int j;
    for( j = 0 ; j < size ; j++ ){
        if(all_nums_3[j] != 0){
            cout << all_nums_4[j] << " " << all_nums_4[j] << " " << all_nums_4[j] << endl;
        }
        else{
            cout << 255 << " " << 0 << " " << 0 << endl;
        }
    }
    MyReadFile.close();
    return 0;
}