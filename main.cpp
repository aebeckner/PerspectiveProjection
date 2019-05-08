//
//  main.cpp
//  Assignment 5
//  A program that displays a 3D image using prespective projectoin.
//  Created by Autumn on 12/4/17.
//  Copyright © 2017 Autumn Beckner. All rights reserved.
//

#include <GLUT/glut.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159265

using namespace std;

void display(void);
void reshape(int, int);
void basic(double,double,double,double);
double** trans1(double,double,double);
double** trans2(double);
double** trans3(double, double);
double** trans4(double, double, double);
double** trans5(double, double, double);
double** translate(double,double,double);
double** scale(double,double,double,double,double,double);
double** vMatrix(double**, double**, double**, double**, double**);
double** nMatrix(double, double);
double** multi (double**, double**);
double** rotate (double);
double** rotate2 (double);
double** overall;
double vp;
string user, post;

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800,800); // sets the size of the window
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE); // sets the display mode to red/green/blue/alpha
    glutCreateWindow("Assignment 5"); // creates window and names it Assignment 1
    glutDisplayFunc(display); // will be called whenever window needs to be drawn
    glutReshapeFunc(reshape); // will be called whenever window is reshaped
    glClearColor(0,0,0,1); // sets the color of the window to black
    glutMainLoop(); // loop to process all window messages
    
} // main

// calculates the new points of the image to be displayed in 2D
double* plot(double arr[]) {
    double userX, userY, userZ, xc, yc, zc, xs, ys;
    double point [1][4];
    double point2 [1][4];
    // if user asks for the deafault cube to be displayed
    if(user == "DF") {
        if(post == "a") {
            point[0][0] = -1;
            point[0][1] = 1;
            point[0][2] = -1;
            point[0][3] = 1;
        } // if
        else if(post == "b") {
            point[0][0] = 1;
            point[0][1] = 1;
            point[0][2] = -1;
            point[0][3] = 1;
        } // else if
        else if (post == "c") {
            point[0][0] = 1;
            point[0][1] = -1;
            point[0][2] = -1;
            point[0][3] = 1;
        } // else if
        else if(post == "d") {
            point[0][0] = -1;
            point[0][1] = -1;
            point[0][2] = -1;
            point[0][3] = 1;
        } // else if
        else if (post == "e") {
            point[0][0] = -1;
            point[0][1] = 1;
            point[0][2] = 1;
            point[0][3] = 1;
        } // else if
        else if(post == "f") {
            point[0][0] = 1;
            point[0][1] = 1;
            point[0][2] = 1;
            point[0][3] = 1;
        } // else if
        else if (post == "g") {
            point[0][0] = 1;
            point[0][1] = -1;
            point[0][2] = 1;
            point[0][3] = 1;
        } // else if
        else {
            point[0][0] = -1;
            point[0][1] = -1;
            point[0][2] = 1;
            point[0][3] = 1;
        } // else
        
    } // if
    
    // if the user wants to create a new image
    else {
        cout << "x: ";
        cin >> userX;
        point[0][0] = userX;
        cout << "y: ";
        cin >> userY;
        point[0][1] = userY;
        cout <<"z: ";
        cin >> userZ;
        point[0][2] = userZ;
        point[0][3] = 1;
        
    } // else
    
    // for loops to multiply the overall matrix with the points specified by the user
    for(int a = 0; a < 1; a++){
        for (int b = 0; b < 4; b++){
            for (int c = 0; c < 4; c++){
                point2[a][b] += point[a][c] * overall[c][b];
            } // for
        } // for
    } // for
    
    // sets the xc, yc, and zc values for calculation xs and ys
    xc = point2[0][0];
    yc = point2[0][1];
    zc = point2[0][2];
    
    // calculates xs and ys; what will be plotted to the screen
    xs = (xc/zc) * vp +vp;
    ys = (yc/zc) * vp + vp;
    
    // sets spaces in array to the xs and ys value; to be returned
    arr[0] = xs;
    arr[1] = ys;
    
    // resets matrix values to 0
    point2[0][0] = 0;
    point2[0][1] = 0;
    point2[0][2] = 0;

    return arr; // array with xs and ys values returned
    
} // plot
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // resets window to black
    
    // several variables to be used for calculations
    double** m1;
    double** m2;
    double** m3;
    double** m4;
    double** m5;
    double** v;
    double** n;
    double** matrix;
    double *a2;
    double *b2;
    double *c2;
    double *d2;
    double *e2;
    double *f2;
    double *g2;
    double *h2;
    double a1[2] , b1[2], c1[2], d1[2], e1[2], f1[2], g1[2], h1[2];
    double d, s, vpX, vpY, vpZ, i1, i2, i3, i4, i5, i6;
    string transform, figure;
    
    matrix = 0;
    
    cout << "Would you like to display default cube or a new figure? Enter DF for default: ";
    cin >> user;
    
    // default cube information to be plotted to the screen to save time for demo
    if (user == "DF") {
        vp = 200;
        m1 = trans1(6, 8, 7.5);
        m2 = trans2(-90);
        m3 = trans3(6, 8);
        m4 = trans4(6,8,7.5);
        m5 = trans5(1,1,-1);
        v = vMatrix(m1,m2,m3,m4,m5);
        n = nMatrix(60,15);
        overall = multi(v,n);
        post = "a";
        a2 = plot(a1);
        post = "b";
        b2 = plot(b1);
        post = "c";
        c2 = plot(c1);
        post = "d";
        d2 = plot(d1);
        post = "e";
        e2 = plot(e1);
        post = "f";
        f2 = plot(f1);
        post = "g";
        g2 = plot(g1);
        post = "h";
        h2 = plot(h1);
    
    } // if
    
    else {
        cout << "What is the position of the viewport?" << endl;
        cout << "Enter x: ";
        cin >> vpX;
        cout << "Enter y: ";
        cin >> vpY;
        cout <<  "Enter z: ";
        cin >> vpZ;
        cout << "What size is the screen? ";
        cin >> s;
        s = s/2;
        cout << "How far away from screen? ";
        cin >> d;
        cout << "What is the coordinate system of the screen? ";
        cin >> vp;
        vp = (vp + 1)/2;
        
        cout << "Would you like to add a transformation? Basic Translate (BT), Basic Scale (BS), Scale (S), Rotate on X access (RX), Rotate on Y (RY), Rotate on Z (RZ)or none" << endl;
        cin >> transform;
        
        // ask for values if user specifies for a translation or basic scale transformation
        if((transform == "BT")||(transform == "BS")) {
            cout << "Enter 3 values for transformation: " << endl;
            cout << "Value 1: ";
            cin >> i1;
            cout << "Value 2: ";
            cin >> i2;
            cout << "Value 3: ";
            cin >> i3;
            if(transform == "BT") {
                matrix = translate(i1, i2, i3);
            } // if
            if(transform == "BS") {
                matrix = trans5(i1,i2,i3);
            } // if
            
        } // if
        
        // asks for values if the user specifies for a scale transformation
        else if (transform == "S") {
            cout << "Enter 6 values for transformation: " << endl;
            cout << "Value 1: ";
            cin >> i1;
            cout << "Value 2: ";
            cin >> i2;
            cout << "Value 3: ";
            cin >> i3;
            cout << "Value 4: ";
            cin >> i4;
            cout << "Value 5: ";
            cin >> i5;
            cout << "Value 6: ";
            cin >> i6;
            matrix = scale(i1, i2, i3, i4, i5, i6);
            
        } // else if
        else if (transform == "RX") {
            cout << "Enter 1 value for transformation: " << endl;
            cout << "Value 1: ";
            cin >> i1;
            matrix = trans2(i1);
        }
        
        else if (transform == "RY") {
            cout << "Enter 1 value for transformation: " << endl;
            cout << "Value 1: ";
            cin >> i1;
            matrix = rotate(i1);
        }
        
        else if (transform == "RZ") {
            cout << "Enter 1 value for transformation: " << endl;
            cout << "Value 1: ";
            cin >> i1;
            matrix = rotate2(i1);
            
        }
        m1 = trans1(vpX,vpY,vpZ); // first translation
        m2 = trans2(-90); // second translation
        m3 = trans3(vpX,vpY); // 3rd translation
        m4 = trans4(vpX,vpY,vpZ); // 4th translation
        m5 = trans5(1,1,-1); // 5th translation
        v = vMatrix(m1,m2,m3,m4,m5); // martix v for calculation
        n = nMatrix(d,s); // // matrix n for calculation
        overall = multi(v, n); // final matrix for calculation
        if((transform == "S") || (transform == "BS") || (transform == "BT") || (transform == "RX") || (transform == "RY")||(transform == "RZ")) {
            overall = multi(overall,matrix);
        }
        
        // asks for user input for points of the image
        cout << "Enter Values for A." << endl;
        a2 = plot(a1);
        cout << "Enter Values for B." << endl;
        b2 = plot(b1);
        cout << "Enter Values for C." << endl;
        c2 = plot(c1);
        cout << "Enter Values for D." << endl;
        d2 = plot(d1);
        cout << "Enter Values for E." << endl;
        e2 = plot(e1);
        cout << "Enter Values for F." << endl;
        f2 = plot(f1);
        cout << "Enter Values for G." << endl;
        g2 = plot(g1);
        cout << "Enter Values for H." << endl;
        h2 = plot(h1);
        
    } // else
    
    // scan conversion of the points created to form cube
    basic(a2[0], a2[1], b2[0], b2[1]);
    basic(b2[0], b2[1], c2[0], c2[1]);
    basic(c2[0], c2[1], d2[0], d2[1]);
    basic(d2[0], d2[1], a2[0], a2[1]);
    basic(e2[0], e2[1], f2[0], f2[1]);
    basic(f2[0], f2[1], g2[0], g2[1]);
    basic(g2[0], g2[1], h2[0], h2[1]);
    basic(h2[0], h2[1], e2[0], e2[1]);
    basic(a2[0], a2[1], e2[0], e2[1]);
    basic(b2[0], b2[1], f2[0], f2[1]);
    basic(c2[0], c2[1], g2[0], g2[1]);
    basic(d2[0], d2[1], h2[0], h2[1]);

    glutSwapBuffers(); // swaps back and front buffers to display drawings
    
} // display

void reshape (int width, int height) {
    glViewport(0, 0, width, height); // display in a rectangle the same size as the window
    glMatrixMode(GL_PROJECTION); // switches to a projection matrix
    glLoadIdentity(); // clear the projection matrix
    gluOrtho2D(0, width, 0, height); // sets the camera view ortho projection to 2D
    glMatrixMode(GL_MODELVIEW); // switches back to the model view matirx
    
} // reshape

// fills a 4x4 array with zeros
void fillArray(double** myArray) {
    for(int n = 0; n < 4; n++){
        myArray[n] = new double [4];
        for(int m = 0; m < 4; m++){
            myArray[n][m] = 0;
        } // for
    } // for
} // fillArray

// translation of the moving eye coordinate system to equal world coordinate system
double** trans1(double x1, double y1, double z1) {
    double** t1 = 0;
    t1 = new double *[4]; // sets size to a 4x4
    fillArray(t1); // fills array with zeros
    
    // changes select spaces in matrix for calculations
    t1[0][0] = 1;
    t1[1][1] = 1;
    t1[2][2] = 1;
    t1[3][0] = x1 * -1;
    t1[3][1] = y1 * -1;
    t1[3][2] = z1 * -1;
    t1[3][3] = 1;
    return t1; // returns first translation matrix
    
} // trans1

// rotation about the x axis for a select degree
double** trans2(double degree) {
    double** t2 = 0;
    t2 = new double *[4]; // sets size to a 4x4
    fillArray(t2); // fills array with zeros
    
    // changes select spaces in matrix for calculations
    
    if ((degree == 90) || (degree == -90)) {
        t2[1][1] = 0;
        t2[2][2] = 0;
    } // if
    else {
        t2[1][1] = cos (degree * PI / 180);
        t2[2][2] = cos (degree * PI / 180);
    } // else
    
    t2[0][0] = 1;
    t2[1][2] = sin (degree * PI / 180);
    t2[2][1] = -(sin (degree * PI / 180));
    t2[3][3] = 1;
    return t2; // returns 2nd translation matrix
    
} // trans2

// rotation about the y axis by 0 degrees
double** trans3(double x3, double y3) {
    double** t3 = 0;
    t3 = new double *[4]; // sets size to 4x4
    fillArray(t3); // fills array with zeros
    
    // changes select spaces in matrix for calculations
    t3[0][0] = ((y3)/(sqrt(pow(x3,2) + pow(y3,2)))) * -1;
    t3[0][2] = (x3)/(sqrt(pow(x3,2) + pow(y3,2)));
    t3[1][1] = 1;
    t3[2][0] = ((x3)/(sqrt(pow(x3,2) + pow(y3,2)))) * -1;
    t3[2][2] = ((y3)/(sqrt(pow(x3,2) + pow(y3,2)))) * -1;
    t3[3][3] = 1;
    return t3; // returns 3rd translation matrix

} // trans3

double** rotate(double degree) {
    double** t2 = 0;
    t2 = new double *[4]; // sets size to a 4x4
    fillArray(t2); // fills array with zeros
    
    // changes select spaces in matrix for calculations
    
    if ((degree == 90) || (degree == -90)) {
        t2[0][0] = 0;
        t2[2][2] = 0;
    } // if
    else {
        t2[0][0] = cos (degree * PI / 180);
        t2[2][2] = cos (degree * PI / 180);
    } // else
    
    t2[1][1] = 1;
    t2[2][0] = sin (degree * PI / 180);
    t2[0][2] = -(sin (degree * PI / 180));
    t2[3][3] = 1;
    return t2; // returns 2nd translation matrix
    
} // trans2

double** rotate2(double degree) {
    double** t2 = 0;
    t2 = new double *[4]; // sets size to a 4x4
    fillArray(t2); // fills array with zeros
    
    // changes select spaces in matrix for calculations
    
    if ((degree == 90) || (degree == -90)) {
        t2[0][0] = 0;
        t2[1][1] = 0;
    } // if
    else {
        t2[0][0] = cos (degree * PI / 180);
        t2[1][1] = cos (degree * PI / 180);
    } // else
    
    t2[2][2] = 1;
    t2[0][1] = sin (degree * PI / 180);
    t2[1][0] = -(sin (degree * PI / 180));
    t2[3][3] = 1;
    return t2; // returns 2nd translation matrix
    
} // trans2
// rotation about the x axis
double** trans4(double x4, double y4, double z4) {
    double** t4 = 0;
    t4 = new double *[4]; // sets size to 4x4
    fillArray(t4); // fills array with zeros
    
    // changes select spaces in matrix for calculations
    t4[0][0] = 1;
    t4[1][1] = (sqrt(pow(x4,2) + pow(y4, 2)))/(sqrt(pow(x4,2)+pow(y4, 2)+pow(z4,2)));
    t4[1][2] = (z4)/(sqrt(pow(x4,2)+pow(y4, 2)+pow(z4,2)));
    t4[2][1] = ((z4)/(sqrt(pow(x4,2)+pow(y4, 2)+pow(z4,2)))) * -1;
    t4[2][2] = (sqrt(pow(x4,2) + pow(y4, 2)))/(sqrt(pow(x4,2)+pow(y4, 2)+pow(z4,2)));
    t4[3][3] = 1;
    return t4;

} // trans4

// scale transformation
double** trans5(double x5, double y5, double z5) {
    double** t5 = 0;
    t5 = new double *[4]; // sets size to 4x4
    fillArray(t5); // fills array with zeros
    
    // sets select spaces in matrix for calculations
    t5[0][0] = x5;
    t5[1][1] = y5;
    t5[2][2] = z5;
    t5[3][3] = 1;
    return t5;

} // trans5

// translation function to move image across the screen
double** translate(double x1, double y1, double z1) {
    double** trans = 0;
    trans = new double *[4]; // sets size to a 4x4
    fillArray(trans); // fills array with zeros
    
    // changes select spaces in matrix for calculations
    trans[0][0] = 1;
    trans[1][1] = 1;
    trans[2][2] = 1;
    trans[3][0] = x1;
    trans[3][1] = y1;
    trans[3][2] = z1;
    trans[3][3] = 1;
    return trans; // returns first translation matrix
    
} // trans

// scale functions that allows the user to scale the image about a specified point
double** scale(double sx, double sy, double sz, double tx, double ty, double tz) {
    double** tMatrix;
    double** sMatrix;
    double** uMatrix;
    
    tMatrix = trans1(tx,ty,tz); // first translation, moves image to origin
    sMatrix = trans5(sx,sy,sz); // scaling the image
    uMatrix = translate(tx,ty,tz); // second translation, moves image to point specified
    
    double** sc = 0;
    sc = new double *[4];
    fillArray(sc);
    
    // multiplys the matrices together to form scale matrix
    sc = multi(tMatrix,sMatrix);
    sc = multi(sc,uMatrix);
    
    return sc;
} // scale

// multiplication function that multiplies two matrices of size 4x4 together
double** multi(double** m1, double** m2) {
    int i, j, k;
    double** mult = 0;
    mult = new double *[4];
    fillArray(mult);
    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            for(k = 0; k < 4; k++){
                mult[i][j] += m1[i][k] * m2[k][j];
                if (abs(mult[i][j]) < 0.000000001) mult[i][j] = 0;
            } // for
        } // for
    } // for
    return mult;

} // multiply

// creates the view Matrix to be used for calcultaion; a matrix of all the multiplications of the different transformations
double** vMatrix(double** m1, double** m2, double** m3, double** m4, double** m5) {
    double** v;
    v = multi(m1, m2); // multiplys the 1st and 2nd transformation
    v = multi(v,m3); // multiplys lst 2nd and 3rd transformation
    v = multi(v, m4); // multiplys 1st 2nd 3rd and 4th transformation
    v = multi(v, m5); // multiplys all 5 transforamtions

    return v;
    
} // vMatrix

// matrix that hold the information for the size of the screen and the distance away
double** nMatrix(double d, double s) {
    double** n = 0;
    n = new double *[4];
    fillArray(n);
    
    n[0][0] = d/s; // distance over size
    n[1][1] = d/s; // distance over size
    n[2][2] = 1;
    n[3][3] = 1;
    return n;

} // nMatrix

// basic line draing algorithm function used notes from class and https: //www.thecrazyprogrammer.com/2017/01/dda-line-drawing-algorithm-c-c.html
// to help with implementation of this algorithm
void basic(double x0, double y0, double x1, double y1) {
    
    // various variables to be used in this algorithm
    float x = x0;
    float y = y0;
    float deltax = x1-x0; // change in x
    float deltay = y1-y0; // change in y
    float slope; // to be used to calculate the slope of the line
    
    // if statement - if the abs val of deltax is greater than delta y then set slope = to abs val of delta x
    // i.e. when line is more horizontal
    if(abs(deltax) >= abs(deltay)){
        slope = abs(deltax);
    } // if
    // otherwise set the slope = to the abs val of deltay, i.e. when line is more vertical
    else {
        slope = abs(deltay);
    } // else
    
    // if statement to check if the "line" given is a single pixel
    if ((deltax == 0) && (deltay == 0)) {
        slope = 1;
    } // if
    
    // sets delta values equal to the slope of the line
    deltax = deltax/slope;
    deltay = deltay/slope;
    
    // for loop to plot pixels of the line
    for(int i = 1; i <= abs(slope); i++) {
        // set pixel equivalent
        // reference to this code can be found at https: //stackoverflow.com/questions/42405420/how-to-draw-a-single-pixel-in-opengl
        glBegin(GL_POINTS); // begins plotting
        glColor3f(1,1,1); // sets color of pixel to white
        glVertex2i(x, y); // plots pixel at specified (x,y) point
        glEnd(); // ends
        // increments x and y values by slope of the line
        x = x + deltax;
        y = y + deltay;
    } // for
    
} // basic
