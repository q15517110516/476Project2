#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;
using namespace cv;
static double angle(Point pt1, Point pt2, Point pt0)
{
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2));
}

void drawRect(Mat& rec, string c, vector<Point>& rim)
{
    Rect r = boundingRect(rim);
    Point pt1(r.x - 10,r.y - 10);
    Point pt2(r.x + r.width + 10,r.y + r.height + 10);
    int c1, c2, c3;
    if (c == "red"){
        c1 = 255;
        c2 = 0;
        c3 = 0;
    }
    else if (c == "pink"){
        c1 = 255;
        c2 = 0;
        c3 = 255;
    }
    else if (c == "blue"){
        c1 = 0;
        c2 = 0;
        c3 = 255;
    }
    else if (c == "azure"){
        c1 = 0;
        c2 = 255;
        c3 = 255;
    }
    else if (c == "green"){
        c1 = 0;
        c2 = 255;
        c3 = 0;
    }
    else if (c == "yellow"){
        c1 = 255;
        c2 = 255;
        c3 = 0;
    }
    else if (c == "black"){
        c1 = 0;
        c2 = 0;
        c3 = 0;
    }
    rectangle(rec, pt1, pt2, CV_RGB(c1, c2, c3), 1,8,0);
}

int main()
{
    string name;
    string shape;
    string color;
    cout << "What shape are you looking for?" << endl << "Choose from: triangle, quadrilateral， square, rectangle, pentagon, hexagon, circle, ellipse" << endl;;
    getline (cin, shape);
    while (shape != "triangle" && shape != "quadrilateral" && shape != "square" && shape != "rectangle" && shape != "pentagon" && shape != "hexagon" && shape != "circle" && shape != "ellipse"){
        cout << "Invalid input! Please select a shape from: triangle, quadrilateral， square, rectangle, pentagon, hexagon, circle, ellipse" << endl;
        getline (cin, shape);
    }
    cout << "What directory do you want to save your output file?" << endl;
    getline (cin, name);
    cout<< name <<endl;
    cout << "What color do you want for the rectangle? Please select from: " << endl;
    cout << "red, pink, blue, azure, green, yellow, black" << endl;
    getline (cin, color);
    while (color != "red" & color != "pink" & color != "blue" & color != "azure" & color != "green" & color != "yellow" & color != "black"){
        cout << "Invalid input! Please select a color from: red, pink, blue, azure, green, yellow, black" << endl;
        getline (cin, color);
    }
    
    const char* image = "/Users/liyifan/Desktop/ShapeFinder/ShapeFinder/complex3.png";
    Mat output = imread(image);
    if (output.empty()){
        cout << "No image found under this directory" << endl;
        return -1;
    }
    Mat temp;
    Canny(output, temp, 5, 15, 5);
    
    vector<vector<Point> > rim;
    findContours(temp, rim, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
    
    
    
    vector<Point> vertex;
    for (int i = 0; i < rim.size(); i++)
    {
        approxPolyDP(Mat(rim[i]), vertex, arcLength(Mat(rim[i]), true)*0.02, true);
        
        if (vertex.size() == 3){
            if (shape == "triangle"){
                drawRect(output, color, rim[i]);    // Triangles
            }
        }
        else if (vertex.size() > 3 && vertex.size() < 7)
        {
            
            if(vertex.size()==4){
                vector<double> cos;
                for (int j = 0; j < vertex.size()-1; j++)
                    cos.push_back(angle(vertex[(j + 2) % vertex.size()], vertex[j], vertex[j + 1]));
                
                sort(cos.begin(), cos.end());
                
                int len1x = (vertex[0].x) - (vertex[1].x);
                int len1y = (vertex[0].y) - (vertex[1].y);
                int len2x = (vertex[1].x) - (vertex[2].x);
                int len2y = (vertex[1].y) - (vertex[2].y);
                if ((cos.front() == cos.back()) & (len1x * len1x + len1y *len1y == len2x * len2x +len2y * len2y) & shape == "square"){
                    drawRect(output, color, rim[i]);
                }
                else if ((cos.front() == cos.back())
                         & (len1x * len1x + len1y *len1y != len2x * len2x +len2y * len2y) & shape == "rectangle"){
                    drawRect(output, color, rim[i]);
                }
                else if ((cos.front() != cos.back()) & shape == "quadrilateral"){
                    drawRect(output, color, rim[i]);
                }
            }
            if((vertex.size()==5) & shape == "pentagon"){
                drawRect(output, color, rim[i]);
            }
            if((vertex.size()==6) &shape == "hexagon"){
                drawRect(output, color, rim[i]);
            }
        }
        else
        {
            double area = contourArea(rim[i]);
            Rect r = boundingRect(rim[i]);
            
            if (r.width == r.height & 4.0 * area/(r.width*r.height)>3.1 & 4.0 * area/(r.width*r.height)<3.17 & shape == "circle"){
                drawRect(output, color, rim[i]);
            }
            else if (shape == "ellipse" & (r.width != r.height | 4.0 * area / (r.width * r.height) > 3.17 | 4.0 * area / (r.width * r.height) < 3.1)){
                drawRect(output, color, rim[i]);
            }
        }
    }
    imshow("output",output);
    imwrite(name, output);
    waitKey();
    return 0;
}