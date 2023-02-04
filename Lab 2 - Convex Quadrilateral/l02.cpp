#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <bits/stdc++.h>

using namespace std ;

void fill_arr(int result[][400]){
    int l, k;
    for( l = 0 ; l < 400 ; l++ )
		for( k = 0 ; k < 400 ; k++ )
			result[l][k] = 0 ;
}

void f(int result[][400], int x, int y){
    if(x > 0 and x < 400 and y > 0 and y < 400)
        result[y][x] = 2;
}

void draw_circle(int r, int incenter_x, int incenter_y, int result[][400]){
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

void drive_x_diag_2(int x1, int y1, int x2, int y2, int result[][400]){
    if(x1 > x2){
        int temp = x1, temp_y = y1;
        x1 = x2, x2 = temp, y1 = y2, y2 = temp_y;
    }
    
    int delx = x2 - x1, dely = y2 - y1;
    int i, j = y1, e = dely - delx;

    if(dely > 0){
        for(i = x1; i < x2; i++) {
            result[j][i] = 2;
            if(e >= 0){
                j += 1;
                e -= delx;
            }
            e += dely;
        }
    } else {
        for(i = x1; i < x2; i++) {
            result[j][i] = 2;
            if(e >= 0){
                j -= 1;
                e -= delx;
            }
            e -= dely;
        }
    }
}

void drive_y_diag_2(int x1, int y1, int x2, int y2, int result[][400]){
    if(y1 > y2){
        int temp = x1, temp_y = y1;
        x1 = x2, x2 = temp, y1 = y2, y2 = temp_y;
    }
    
    int delx = x2 - x1, dely = y2 - y1;
    int i, j = x1, e = dely - delx;

    if(delx > 0){
        for(i = y1; i < y2; i++) {
            result[i][j] = 2;
            if(e >= 0){
                j += 1;
                e -= dely;
            }
            e += delx;
        }
    } else {
        for(i = y1; i < y2; i++) {
            result[i][j] = 2;
            if(e >= 0){
                j -= 1;
                e -= dely;
            }
            e -= delx;
        }
    }
}

void drive_x_diag_1(int x1, int y1, int x2, int y2, int result[][400]){
    if(x1 > x2){
        int temp = x1, temp_y = y1;
        x1 = x2, x2 = temp, y1 = y2, y2 = temp_y;
    }
    
    int delx = x2 - x1, dely = y2 - y1;
    int i, j = y1, e = dely - delx;

    if(dely > 0){
        for(i = x1; i < x2; i++) {
            result[j][i] = 3;
            if(e >= 0){
                j += 1;
                e -= delx;
            }
            e += dely;
        }
    } else {
        for(i = x1; i < x2; i++) {
            result[j][i] = 3;
            if(e >= 0){
                j -= 1;
                e -= delx;
            }
            e -= dely;
        }
    }
}

void drive_y_diag_1(int x1, int y1, int x2, int y2, int result[][400]){
    if(y1 > y2){
        int temp = x1, temp_y = y1;
        x1 = x2, x2 = temp, y1 = y2, y2 = temp_y;
    }
    
    int delx = x2 - x1, dely = y2 - y1;
    int i, j = x1, e = dely - delx;

    if(delx > 0){
        for(i = y1; i < y2; i++) {
            result[i][j] = 3;
            if(e >= 0){
                j += 1;
                e -= dely;
            }
            e += delx;
        }
    } else {
        for(i = y1; i < y2; i++) {
            result[i][j] = 3;
            if(e >= 0){
                j -= 1;
                e -= dely;
            }
            e -= delx;
        }
    }
}

void drive_x(int x1, int y1, int x2, int y2, int result[][400]){
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

void drive_y(int x1, int y1, int x2, int y2, int result[][400]){
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

int main() {
    srand(time(0));
    int (*result)[400] = new int[400][400];
    fill_arr(result);
    bool isConvex = false;
    int p1x, p2x, p3x, p4x, p1y, p2y, p3y, p4y;
    double all_angs[4] = {};
    double final_angs[4] = {};
    while(isConvex == false){
        p1x = rand() % 200, p1y = rand() % 200, p2x = rand() % 200, p2y = rand() % 200, p3x = rand() % 200, p3y = rand() % 200, p4x = rand() % 200, p4y = rand() % 200;
        double centroidx = (p1x + p2x + p3x + p4x) / 4, centroidy = (p1y + p2y + p3y + p4y) / 4;
        double dx1 = p1x - centroidx, dy1 = p1y - centroidy, dx2 = p2x - centroidx, dy2 = p2y - centroidy, dx3 = p3x - centroidx, dy3 = p3y - centroidy, dx4 = p4x - centroidx, dy4 = p4y - centroidy;
        double ang1 = atan2(dy1, dx1), ang2 = atan2(dy2, dx2), ang3 = atan2(dy3, dx3), ang4 = atan2(dy4, dx4);
        all_angs[0] = ang1;
        all_angs[1] = ang2;
        all_angs[2] = ang3;
        all_angs[3] = ang4;
        double arr[] = {ang1, ang2, ang3, ang4};
        int n = sizeof(arr) / sizeof(arr[0]);
        sort(arr, arr + n);
        if(arr[3] < 3 & arr[3] > -3)
            isConvex = true;
            final_angs[0] = arr[0];
            final_angs[1] = arr[1];
            final_angs[2] = arr[2];
            final_angs[3] = arr[3];
    }

    int pts_x[4]; 
    int pts_y[4];
    for (int i = 0; i < 4; ++i){
        double val = final_angs[i];
        if(val == all_angs[0]){
            pts_x[i] = p1x;
            pts_y[i] = p1y;
        }
        else if(val == all_angs[1]){
            pts_x[i] = p2x;
            pts_y[i] = p2y;
        }
        else if(val == all_angs[2]){
            pts_x[i] = p3x;
            pts_y[i] = p3y;
        }
        else{
            pts_x[i] = p4x;
            pts_y[i] = p4y;
        }
    }

    for (int i = 0; i < 4; ++i){
        int x1, x2, y1, y2;
        if(i < 3)
            x1 = pts_x[i], x2 = pts_x[i + 1], y1 = pts_y[i], y2 = pts_y[i + 1];
        else
            x1 = pts_x[i], x2 = pts_x[0], y1 = pts_y[i], y2 = pts_y[0];
        int delx = abs(x2 - x1), dely = abs(y2 - y1);
        if(dely > delx)
            drive_y(x1, y1, x2, y2, result);
        else
            drive_x(x1, y1, x2, y2, result);
    }

    int x1_diag_1 = pts_x[1], x2_diag_1 = pts_x[3], y1_diag_1 = pts_y[1], y2_diag_1 = pts_y[3];
    double diag_dist = sqrt(pow(x2_diag_1 - x1_diag_1, 2) + pow(y2_diag_1 - y1_diag_1, 2));
    int delx_diag1 = abs(x2_diag_1 - x1_diag_1), dely_diag1 = abs(y2_diag_1 - y1_diag_1);
    if(dely_diag1 > delx_diag1)
        drive_y_diag_1(x1_diag_1, y1_diag_1, x2_diag_1, y2_diag_1, result);
    else
        drive_x_diag_1(x1_diag_1, y1_diag_1, x2_diag_1, y2_diag_1, result);

    draw_circle(2, pts_x[0], pts_y[0], result);
    draw_circle(2, pts_x[1], pts_y[1], result);
    draw_circle(2, pts_x[2], pts_y[2], result);
    draw_circle(2, pts_x[3], pts_y[3], result);

    int x1 = pts_x[1], x2 = pts_x[3], y1 = pts_y[1], y2 = pts_y[3], x3 = pts_x[2], y3 = pts_y[2];
    cout << x1 << " " << y1 << endl;
    cout << x2 << " " << y2 << endl;
    cout << x3 << " " << y3 << endl;
    double dx = x2 - x1;
    double dy = y2 - y1;
    double mag = sqrt(dx*dx + dy*dy);
    dx /= mag;
    dy /= mag;
    int x4, y4;
    double lambda = (dx * (x3 - x1)) + (dy * (y3 - y1));
    x4 = (dx * lambda) + x1;
    y4 = (dy * lambda) + y1;

    int delx_diag = abs(x4 - x3), dely_diag = abs(y4 - y3);
    double perp_dist = sqrt(pow(x4 - x3, 2) + pow(y4 - y3, 2));
    double dist_div = diag_dist / perp_dist;
    int new_delx = round(dist_div * delx_diag), new_dely = round(dist_div * dely_diag);
    int new_x = x3 + new_delx, new_y = y3 + new_dely;

    draw_circle(2, new_x, new_y, result);

    if(dely_diag > delx_diag)
        drive_y_diag_2(x3, y3, x4, y4, result);
    else
        drive_x_diag_2(x3, y3, x4, y4, result);

    int one_side_pt_x = pts_x[0], one_side_pt_y = pts_y[0];
    int del_x_one_side = abs(new_x - one_side_pt_x), del_y_one_side = abs(new_y - one_side_pt_y);

    if(dely_diag > delx_diag)
        drive_y_diag_2(x3, y3, x4, y4, result);
    else
        drive_x_diag_2(x3, y3, x4, y4, result);

    int xx1 = pts_x[0], xx2 = new_x, yy1 = pts_y[0], yy2 = new_y, xx3 = pts_x[1], yy3 = pts_y[1], xx5 = pts_x[3], yy5 = pts_y[3];
    double dxx = xx2 - xx1;
    double dyy = yy2 - yy1;
    double mag1 = sqrt(dxx*dxx + dyy*dyy);
    dxx /= mag1;
    dyy /= mag1;
    int xx4, yy4, xx6, yy6;
    double lambda1 = (dxx * (xx3 - xx1)) + (dyy * (yy3 - yy1));
    double lambda2 = (dxx * (xx5 - xx1)) + (dyy * (yy5 - yy1));
    xx4 = (dxx * lambda1) + xx1;
    yy4 = (dyy * lambda1) + yy1;
    xx6 = (dxx * lambda2) + xx1;
    yy6 = (dyy * lambda2) + yy1;

    int delx_diag_1 = abs(xx4 - xx3), dely_diag_1 = abs(yy4 - yy3);
    int delx_diag_2 = abs(xx6 - xx5), dely_diag_2 = abs(yy6 - yy5);
    
    draw_circle(2, xx4, yy4, result);
    draw_circle(2, xx6, yy6, result);

    x1 = pts_x[3], x2 = xx6, y1 = pts_y[3], y2 = yy6, x3 = pts_x[2], y3 = pts_y[2];
    cout << x1 << " " << y1 << endl;
    cout << x2 << " " << y2 << endl;
    cout << x3 << " " << y3 << endl;
    dx = x2 - x1;
    dy = y2 - y1;
    mag = sqrt(dx*dx + dy*dy);
    dx /= mag;
    dy /= mag;
    lambda = (dx * (x3 - x2)) + (dy * (y3 - y2));
    x4 = (dx * lambda) + x2;
    y4 = (dy * lambda) + y2;
    cout << x4 << " " << y4 << endl;
    draw_circle(2, x4, y4, result);
    draw_circle(2, xx5, yy5, result);
    delx_diag = abs(x4 - x3), dely_diag = abs(y4 - y3);

    int final_delx = xx6 - x4, final_dely = yy6 - y4;
    int final_xpos = xx4 - final_delx, final_ypos = yy4 - final_dely;
    draw_circle(2, final_xpos, final_ypos, result);
    float dx21 = x2-x1;
    float dx31 = x4-x3;
    float dy21 = y2-y1;
    float dy31 = y4-y3;
    float m12 = sqrt( dx21*dx21 + dy21*dy21 );
    float m13 = sqrt( dx31*dx31 + dy31*dy31 );
    float theta = acos( (dx21*dx31 + dy21*dy31) / (m12 * m13) );
    cout << theta << endl;
    int slope = (y4 - y3) / (x4 - x3);
    int when_x_0 = (slope * (-1 * x3)) + y3;
    int when_y_0 = x3 - (y3 / slope);
    int when_x_great = (slope * (399 - x3)) + y3;
    int when_y_great = ((399 - y3) / slope) + x3;
    bool pt1_x, pt2_x;
    int point1x, point2x, point1y, point2y;
    if(when_x_0 >= 0 and when_x_0 <= 400){
        point1x = 0;
        point1y = (int) when_x_0;
    }
    else{
        point1x = (int) when_y_0;
        point1y = 0;
    }

    if(when_x_great <= 400 and when_x_great >= 0){
        point2y = (int) when_x_great;
        point2x = 399;
    }
    else{
        point2x = (int) when_y_great;
        point2y = 399;
    }

    cout << "P3 400 400 1" << endl ;
    int j, k;
    for( j = 0 ; j < 400 ; j++ )
		for( k = 0 ; k < 400 ; k++ )
            if( result[j][k] == 0 ){
                cout << "0 0 0" << endl ;
            }
            else if( result[j][k] == 2 ) {
                cout << "1 0 0" << endl ;
            }
            else if( result[j][k] == 3 ) {
                cout << "1 1 0" << endl ;
            }
            else {
                cout << "0 1 0" << endl;
            }

    return 0;
}