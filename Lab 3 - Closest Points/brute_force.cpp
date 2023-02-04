#include <iostream>
#include <cmath>
#include <chrono>
using namespace std;

void fill_arr(int result[][800]){
    int l, k;
    for( l = 0 ; l < 800 ; l++ )
		for( k = 0 ; k < 800 ; k++ )
			result[l][k] = 0 ;
}

void f(int result[][800], int x, int y){
    if(x > 0 and x < 800 and y > 0 and y < 800)
        result[y][x] = 1;
}

void drive_x(int x1, int y1, int x2, int y2, int result[][800]){
    if(x1 > x2){
        int temp = x1, temp_y = y1;
        x1 = x2, x2 = temp, y1 = y2, y2 = temp_y;
    }
    
    int delx = x2 - x1, dely = y2 - y1;
    int i, j = y1, e = dely - delx;

    if(dely > 0){
        for(i = x1; i < x2; i++) {
            result[j][i] = 1;
            if(e >= 0){
                j += 1;
                e -= delx;
            }
            e += dely;
        }
    } else {
        for(i = x1; i < x2; i++) {
            result[j][i] = 1;
            if(e >= 0){
                j -= 1;
                e -= delx;
            }
            e -= dely;
        }
    }
}

void drive_y(int x1, int y1, int x2, int y2, int result[][800]){
    if(y1 > y2){
        int temp = x1, temp_y = y1;
        x1 = x2, x2 = temp, y1 = y2, y2 = temp_y;
    }
    
    int delx = x2 - x1, dely = y2 - y1;
    int i, j = x1, e = dely - delx;

    if(delx > 0){
        for(i = y1; i < y2; i++) {
            result[i][j] = 1;
            if(e >= 0){
                j += 1;
                e -= dely;
            }
            e += delx;
        }
    } else {
        for(i = y1; i < y2; i++) {
            result[i][j] = 1;
            if(e >= 0){
                j -= 1;
                e -= dely;
            }
            e -= delx;
        }
    }
}

void draw_circle(int r, int incenter_x, int incenter_y, int result[][800]){
    int x, y, xmax, y2_1, y2_new, ty;
    xmax = (int) (r * 0.70710678); // maximum x at radius/sqrt(2)
    y = r;
    y2_1 = y * y;
    ty = (2 * y) - 1; y2_new = y2_1;
    for (x = 0; x <= xmax; x++) {
        if ((y2_1 - y2_new) >= ty) {
            y2_1 -= ty;
            y -= 1;
            ty -= 2;
        }
        f( result , x + incenter_x , y + incenter_y) ;
        f( result , x + incenter_x, -1 * y  + incenter_y) ;
        f( result , -1 * x + incenter_x, y  + incenter_y) ;
        f( result , -1 * x + incenter_x, -1 * y  + incenter_y) ;
        f( result , y + incenter_x, x  + incenter_y) ;
        f( result , y + incenter_x, -1 * x  + incenter_y) ;
        f( result , -1 * y + incenter_x, x  + incenter_y) ;
        f( result , -1 * y + incenter_x, -1 * x  + incenter_y) ;
        y2_new -= (2 * x) - 3;
    }
}

int main()
{
    srand(time(0));
    int (*result)[800] = new int[800][800] ;
    int total_run = 20000;
    int pts_x[total_run]; 
    int pts_y[total_run];
    int i, j, k;

    for(i = 0; i < total_run; i++){
        int pt_x = rand() % 799 + 1, pt_y = rand() % 799 + 1;
        pts_x[i] = pt_x;
        pts_y[i] = pt_y;
        draw_circle(2, pt_x, pt_y, result);
    }

    int lowest_j = 0, lowest_k = 0;
    double lowest_dist = 10000;
    for(j = 0; j < total_run; j++){
        for(k = 0; k < total_run; k++){
            int pt1_x = pts_x[j], pt1_y = pts_y[j], pt2_x = pts_x[k], pt2_y = pts_y[k];
            double dist = sqrt(pow(pt2_x - pt1_x, 2) + pow(pt2_y - pt1_y, 2));
            if(dist < lowest_dist & j != k){
                lowest_dist = dist;
                lowest_j = j;
                lowest_k = k;
            }
        }
    }

    int fin_pt1_x = pts_x[lowest_j], fin_pt1_y = pts_y[lowest_j], fin_pt2_x = pts_x[lowest_k], fin_pt2_y = pts_y[lowest_k];
    int dely = abs(fin_pt2_y - fin_pt1_y), delx = abs(fin_pt2_x - fin_pt1_x);
    if(dely > delx)
        drive_y(fin_pt1_x, fin_pt1_y, fin_pt2_x, fin_pt2_y, result);
    else
        drive_x(fin_pt1_x, fin_pt1_y, fin_pt2_x, fin_pt2_y, result);

    cout << "P3 800 800 1" << endl ;
    int a, b;
    for( a = 0 ; a < 800 ; a++ )
		for( b = 0 ; b < 800 ; b++ )
            if( result[a][b] == 0 )
                cout << "0 0 0" << endl ;
            else
                cout << "0 1 0" << endl ;

    return 0;
}