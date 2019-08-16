#include "ConfigParser.h"

const string defaultDataFile="fullGen.txt";
const int K = 2;
const int maxIterations = 500;
const double interpolationExponent = 2;

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
};

int funct(Complex c){
    Complex n(0,0);
    for(int i = 0; i < maxIterations; i++){
        n = (n.square() + c);
        if(!n.inbounds()){
            return i;
        }
    }
    return -1;
}

double interpolate(double n, double inmax, double a, double b){
    return ((a-b)/pow(inmax,interpolationExponent))*pow(n-inmax,interpolationExponent) + b;
}

int main(int argc, char* argv[]){
    Settings Conf(((argc>1)?argv[1]:defaultDataFile));
    Image img(0,0);
    double x, y;
    int j;
    int pix[Conf.imgW][Conf.imgH];
    int maxits;
    string txt;
    for(int i = 0; i < Conf.numFrames; i++){
        txt = to_string(i);
        cout << pad(txt,to_string(Conf.numFrames).size(),' ',"right") << "/" << to_string(Conf.numFrames) << " ";
        txt = to_string((int)((i*1.0/Conf.numFrames)*100));
        cout << pad(txt,3,' ',"right") << "%";
        cout.flush();
        maxits = 0;
        img = Image(Conf.imgW,Conf.imgH);
        for(int pxy = 0; pxy < Conf.imgH; pxy++){
            for(int pxx = 0; pxx < Conf.imgW; pxx++){
                x = _compress(pxx,0,Conf.imgW,interpolate(i,Conf.numFrames-1,Conf.startX,Conf.endX),interpolate(i,Conf.numFrames-1,Conf.startX+Conf.startWidth,Conf.endX+Conf.endWidth));
                y = _compress(pxy,0,Conf.imgH,interpolate(i,Conf.numFrames-1,Conf.startY,Conf.endY),interpolate(i,Conf.numFrames-1,Conf.startY-Conf.startHeight,Conf.endY-Conf.endHeight));
                pix[pxx][pxy] = funct(Complex(x,y));
                if(pix[pxx][pxy] > maxits){
                    maxits = pix[pxx][pxy];
                }
            }
        }
        for(int pxy = 0; pxy < Conf.imgH; pxy++){
            for(int pxx = 0; pxx < Conf.imgW; pxx++){
                if(pix[pxx][pxy] == -1){
                    img(pxx,pxy) = Conf.fillcolor;
                }else{
                    img(pxx,pxy) = Color::gradient(pix[pxx][pxy],0,maxits,Conf.firstcolor,Conf.lastcolor);
                }
            }
        }
        for(int i = 0; i < (2*to_string(Conf.numFrames).size()) + 6; i++){
            cout << "\b \b";
        }
        img.savePPM(Conf.folderName+"/"+string(to_string(Conf.numFrames-1).size()-to_string(i).size(),'0')+to_string(i)+".ppm");
        //img.savePPM("full.ppm");
    }
    cout << "done\n";


    return 0;
}
