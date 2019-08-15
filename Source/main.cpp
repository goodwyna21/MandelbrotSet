#include <iostream>
#include <cmath>
#include "/home/archer/Projects/ArcherStandardLibrary/Source/Outputs.h"

using namespace std;

const int N = 500;

const double startX = -2;
const double startY = 1;
const double startWidth = 3;
const double startHeight = 2;
const double endX = -0.85;
const double endY = 0.25;
const double endWidth = 0.3;
const double endHeight = 0.2;

const int imgW = 900;
const int imgH = 600;
const int numFrames = 100;
const int startFrame = 0;

const string FolderName = "Gif2/";

const Color fillcolor = {0,0,0};
const Color first = {0,255,255};
const Color last = {255,0,255};
/*
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
*/

const int K = 2;

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
        return (abs(a) < K) || (abs(b) < K);
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
            for(int pxx = 0; pxx < imgW; pxx++){
                x = _compress(pxx,0,imgW,_compress(i,0,numFrames,startX,endX),_compress(i,0,numFrames,startX+startWidth,endX+endWidth));
                y = _compress(pxy,0,imgH,_compress(i,0,numFrames,startY,endY),_compress(i,0,numFrames,startY-startHeight,endY-endHeight));
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
                    img(pxx,pxy) = Color::gradient(pix[pxx][pxy],0,maxits,firstcolor,lastcolor);
                }
            }
        }
        for(int i = 0; i < (2*to_string(numFrames).size()) + 6; i++){
            cout << "\b \b";
        }
        img.savePPM(FolderName+"/"+to_string(startFrame+i)+".ppm");
        //img.savePPM("full.ppm");
    }
    cout << "done\n";


    return 0;
}
