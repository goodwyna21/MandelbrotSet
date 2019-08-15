#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <fstream>

using namespace std;

const string configName="params.txt";

const double startX,startY,startWidth,
startHeight,endX,endY,endWidth,endHeight;
const int imgW,imgH,numFrames,startFrame;
const string FolderName;
const Color fillcolor,firstcolor,lastcolor;

void popVars(string configName){
    ifstream confin;
    confin.open(configName);
    string line;
    string varname;
    string val;
    bool toggle;
    while(getline(confin,line)){
        varname = "";
        val = "";
        toggle=false;
        for(int i = 0; i < line.size(); i++){
            if(line[i]=="="){
                toggle=true;
                continue;
            }
            if(toggle){
                
            }
        }
    }
}

#endif
