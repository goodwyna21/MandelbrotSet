#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <fstream>
#include <string>
#include <iostream>
#include <cmath>
#include "/home/archer/Projects/ArcherStandardLibrary/Source/Outputs.h"
using namespace std;


struct Settings{
    double startX;
    double startY;
    double startWidth;
    double endX;
    double endY;
    double zoomAmount;
    int imgW;
    int imgH;
    int numFrames;
    string folderName;
    Color fillcolor;
    Color firstcolor;
    Color lastcolor;

    double aspectRatio;
    double startHeight;
    double endWidth;
    double endHeight;


    Settings(string configName)
    :fillcolor(0,0,0),
    firstcolor(0,0,0),
     lastcolor(0,0,0){
        ifstream input;
        input.open(configName);
        string line;
        string varname;
        string val;
        bool toggle;
        while(getline(input,line)){
            if(line.size()>1&&line[0]!='#'){
                varname = "";
                val = "";
                toggle=false;
                for(int i = 0; i < line.size(); i++){
                    if(line[i]=='\n'){continue;}
                    if(line[i]=='='){
                        toggle=true;
                        continue;
                    }
                    if(!toggle){
                        varname+=line[i];
                    }else{
                        val+=line[i];
                    }
                }
                if(varname=="startX"){
                    startX=stod(val);
                }else if(varname=="startY"){
                    startY=stod(val);
                }else if(varname=="startWidth"){
                    startWidth=stod(val);
                }else if(varname=="endX"){
                    endX=stod(val);
                }else if(varname=="endY"){
                    endY=stod(val);
                }else if(varname=="zoomAmount"){
                    zoomAmount=stod(val);
                }else if(varname=="imgW"){
                    imgW=stoi(val);
                }else if(varname=="imgH"){
                    imgH=stoi(val);
                }else if(varname=="numFrames"){
                    numFrames=stoi(val);
                }else if(varname=="folderName"){
                    folderName=val;
                }else if(varname=="fillcolorR"){
                    fillcolor[0]=stoi(val);
                }else if(varname=="fillcolorG"){
                    fillcolor[1]=stoi(val);
                }else if(varname=="fillcolorB"){
                    fillcolor[2]=stoi(val);
                }else if(varname=="firstcolorR"){
                    firstcolor[0]=stoi(val);
                }else if(varname=="firstcolorG"){
                    firstcolor[1]=stoi(val);
                }else if(varname=="firstcolorB"){
                    firstcolor[2]=stoi(val);
                }else if(varname=="lastcolorR"){
                    lastcolor[0]=stoi(val);
                }else if(varname=="lastcolorG"){
                    lastcolor[1]=stoi(val);
                }else if(varname=="lastcolorB"){
                    lastcolor[2]=stoi(val);
                }
            }
        }

        aspectRatio=(1.0*imgH)/imgW;
        startHeight=startWidth*aspectRatio;
        endWidth=startWidth/(1.0*zoomAmount);
        endHeight=endWidth*aspectRatio;
        input.close();
    }
};

#endif
