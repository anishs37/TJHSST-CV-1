#include <iostream>
#include <cmath>
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
            // cout << j << "," << i << endl;
            result[j][i] = 1;
            if(e >= 0){
                j += 1;
                e -= delx;
            }
            e += dely;
        }
    } else {
        for(i = x1; i < x2; i++) {
            // cout << j << "," << i << endl;
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
            // cout << i << "," << j << endl;
            result[i][j] = 1;
            if(e >= 0){
                j += 1;
                e -= dely;
            }
            e += delx;
        }
    } else {
        for(i = y1; i < y2; i++) {
            // cout << i << "," << j << endl;
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
    //srand(1662769128);
    //cout << time(0) << " " << endl;
    int x, y, xmax, y2_1, y2_new, ty, s;
    float r, r_cap, r_cap_div;
    float theta_a, theta_b, theta_c, theta_a_deg, theta_b_deg, theta_c_deg;
    int (*result)[800] = new int[800][800] ;
    int x1 = rand() % 799 + 1, y1 = rand() % 799 + 1, x2 = rand() % 799 + 1, y2 = rand() % 799 + 1, x3 = rand() % 799 + 1, y3 = rand() % 799 + 1;
    //cout << x1 << " " << y1 << endl;
    //cout << x2 << " " << y2 << endl;
    //cout << x3 << " " << y3 << endl;
    int delx12 = abs(x2 - x1), dely12 = abs(y2 - y1), delx13 = abs(x3 - x1), dely13 = abs(y3 - y1), delx23 = abs(x3 - x2), dely23 = abs(y3 - y2);
    fill_arr(result);

    if(dely12 > delx12)
        drive_y(x1, y1, x2, y2, result);
    else
        drive_x(x1, y1, x2, y2, result);
    // cout << "__________" << endl;
    //(x1, y1) to (x3, y3)
    if(dely13 > delx13)
        drive_y(x1, y1, x3, y3, result);
    else
        drive_x(x1, y1, x3, y3, result);
    // cout << "__________" << endl;
    //(x2, y2) to (x3, y3)
    if(dely23 > delx23)
        drive_y(x2, y2, x3, y3, result);
    else
        drive_x(x2, y2, x3, y3, result);

    double a, b, c, circumcenter_x, circumcenter_y, incenter_x, incenter_y, orthocenter_x, orthocenter_y, ninepoint_x, ninepoint_y, centroid_x, centroid_y, euler_slope, euler_slope_1, when_x_0, when_y_0, when_x_great, when_y_great;
    centroid_x = (x1 + x2 + x3) / 3;
    centroid_y = (y1 + y2 + y3) / 3;
    a = sqrt(pow(x3 - x2, 2) + pow(y3 - y2, 2));
    b = sqrt(pow(x3 - x1, 2) + pow(y3 - y1, 2));
    c = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    //cout << a << " " << b << " " << c << endl;
    s = (a + b + c) / 2;
    r = sqrt(((s - a) * (s - b) * (s - c) / s));
    incenter_x = ((a * x1) + (b * x2) + (c * x3)) / (a + b + c);
    incenter_y = ((a * y1) + (b * y2) + (c * y3)) / (a + b + c);
    // r = sqrt(pow(incenter_x - x1, 2) + pow(incenter_y - y1, 2));
    draw_circle(r, incenter_x, incenter_y, result);
    r_cap = (a * b * c) / (4 * r * s);
    r_cap_div = r_cap / 2;
    theta_c = acos(((pow(c, 2) - pow(a, 2) - pow(b, 2))) / (-2 * a * b));
    theta_b = acos(((pow(b, 2) - pow(a, 2) - pow(c, 2))) / (-2 * a * c));
    theta_a = acos(((pow(a, 2) - pow(b, 2) - pow(c, 2))) / (-2 * b * c));
    // double pi = 3.14159;
    // theta_c_deg = theta_c * (180 / pi);
    // theta_b_deg = theta_b * (180 / pi);
    // theta_a_deg = 180 - theta_c_deg - theta_b_deg;
    //cout << theta_a << " " << theta_b << " " << theta_c << endl;
    circumcenter_x = ((x1 * sin(2 * theta_a) + x2 * sin(2 * theta_b) + x3 * sin(2 * theta_c)) / (sin(2 * theta_a) + sin(2 * theta_b) + sin(2 * theta_c)));
    circumcenter_y = ((y1 * sin(2 * theta_a) + y2 * sin(2 * theta_b) + y3 * sin(2 * theta_c)) / (sin(2 * theta_a) + sin(2 * theta_b) + sin(2 * theta_c)));
    orthocenter_x = ((x1 * tan(theta_a) + x2 * tan(theta_b) + x3 * tan(theta_c)) / (tan(theta_a) + tan(theta_b) + tan(theta_c)));
    orthocenter_y = ((y1 * tan(theta_a) + y2 * tan(theta_b) + y3 * tan(theta_c)) / (tan(theta_a) + tan(theta_b) + tan(theta_c)));
    ninepoint_x = (circumcenter_x + orthocenter_x) / 2;
    ninepoint_y = (circumcenter_y + orthocenter_y) / 2;
    euler_slope = (orthocenter_y - circumcenter_y) / (orthocenter_x - circumcenter_x);
    // cout << circumcenter_x << " " << circumcenter_y << endl;
    // cout << orthocenter_x << " " << orthocenter_y << endl;
    // cout << euler_slope << " " << endl;
    euler_slope_1 = euler_slope * -1;
    when_x_0 = (euler_slope * (-1 * circumcenter_x)) + circumcenter_y;
    when_y_0 = circumcenter_x - (circumcenter_y / euler_slope);
    when_x_great = (euler_slope * (799 - circumcenter_x)) + circumcenter_y;
    when_y_great = ((799 - circumcenter_y) / euler_slope) + circumcenter_x;
    // cout << when_x_0 << " " << when_y_0 << endl;;
    // cout << when_x_great << " " << when_y_great << endl;
    bool pt1_x, pt2_x;
    int point1x, point2x, point1y, point2y;
    if(when_x_0 >= 0 and when_x_0 <= 800){
        point1x = 0;
        point1y = (int) when_x_0;
    }
    else{
        point1x = (int) when_y_0;
        point1y = 0;
    }

    if(when_x_great <= 800 and when_x_great >= 0){
        point2y = (int) when_x_great;
        point2x = 799;
    }
    else{
        point2x = (int) when_y_great;
        point2y = 799;
    }

    // cout << point1x << " " << point1y << endl;
    // cout << point2x << " " << point2y << endl;
    int delx, dely;
    dely = point2y - point1y;
    delx = point2x - point1x;
    if(dely > delx)
        drive_y(point1x, point1y, point2x, point2y, result);
    else
        drive_x(point1x, point1y, point2x, point2y, result);

    // r = sqrt(pow(incenter_x - x1, 2) + pow(incenter_y - y1, 2));
    //cout << r_cap << " " << endl;
    draw_circle(r_cap, circumcenter_x, circumcenter_y, result);
    draw_circle(r_cap_div, ninepoint_x, ninepoint_y, result);

    cout << "P3 800 800 1" << endl ;
    int j, k;
    for( j = 0 ; j < 800 ; j++ )
		for( k = 0 ; k < 800 ; k++ )
            if( result[j][k] == 0 )
                cout << "0 0 0" << endl ;
            else
                cout << "0 1 0" << endl ;

    return 0;
}