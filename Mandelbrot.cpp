#include <iostream>
#include <cmath>
#include "/home/archer/Projects/ArcherStandardLibrary/Source/Outputs.h"

using namespace std;

const int N = 500;
const int K = 2;

/*
const double startMinX = -1;
const double startMaxX = 0;
const double startMinY = 0;
const double startMaxY = 0.5;
const double endMinX = -0.54375;
const double endMaxX = -0.525;
const double endMinY = 0.521875;
const double endMaxY = 0.525;
const int imgW = 800;
const int imgH = 400;
const int numFrames = 1;
*/

const double startMinX = -2;
const double startMaxX = 1;
const double startMinY = -1;
const double startMaxY = 1;
const double endMinX = -2;
const double endMaxX = 1;
const double endMinY = -1;
const double endMaxY = 1;
const int imgW = 2000;
const int imgH = 1000;
const int numFrames = 1;

const Color fillcolor = {0,0,0};
const Color last = {0,255,255};
const Color first = {255,0,255};

struct Complex{
    double a;
    double b;
    Complex(double A, double B):a(A),b(B){}

    Complex square(){
        return Complex((a*a)-(b*b),2*a*b);
    }

    Complex operator+ (Complex c){
        return Complex(a+c.a,b+c.b);
    }

    bool inbounds(){
        return (a < K) || (b < K);
    }

    string toString(){
        return to_string(a)+"+"+to_string(b)+"i";
    }
};

int funct(Complex c){
    Complex n(0,0);
    for(int i = 0; i < N; i++){
        n = (n.square() + c);
        if(!n.inbounds()){
            return i;
        }
    }
    return -1;
}

int main(int argc, char* argv[]){
    Image img(0,0);
    double x, y;
    int j;
    int pix[imgW][imgH];
    int maxits;
    string txt;
    for(int i = 0; i < numFrames; i++){
        txt = to_string(i);
        cout << pad(txt,to_string(numFrames).size(),' ',"right") << "/" << to_string(numFrames) << " ";
        txt = to_string((int)((i*1.0/numFrames)*100));
        cout << pad(txt,3,' ',"right") << "%";
        cout.flush();
        maxits = 0;
        img = Image(imgW,imgH);
        for(int pxy = 0; pxy < imgH; pxy++){
            if(pxy%(imgH/10)==0){
                cout << "*";
                cout.flush();
            }
            for(int pxx = 0; pxx < imgW; pxx++){
                x = _compress(pxx,0,imgW,_compress(i,0,numFrames,startMinX,endMinX),_compress(i,0,numFrames,startMaxX,endMaxX));
                y = _compress(pxy,0,imgH,_compress(i,0,numFrames,startMinY,endMinY),_compress(i,0,numFrames,startMaxY,endMaxY));
                pix[pxx][pxy] = funct(Complex(x,y));
                if(pix[pxx][pxy] > maxits){
                    maxits = pix[pxx][pxy];
                }
            }
        }
        for(int pxy = 0; pxy < imgH; pxy++){
            for(int pxx = 0; pxx < imgW; pxx++){
                if(pix[pxx][pxy] == -1){
                    img(pxx,pxy) = fillcolor;
                }else{
                    img(pxx,pxy) = Color::gradient(pix[pxx][pxy],0,maxits,first,last);
                }
            }
        }
        for(int i = 0; i < (2*to_string(numFrames).size()) + 6; i++){
            cout << "\b \b";
        }
        //img.savePPM("Gif/"+to_string(i)+".ppm");
        img.savePPM("full.ppm");
    }
    cout << "done\n";


    return 0;
}
