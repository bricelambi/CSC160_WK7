#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include "csc160.h"

using namespace std;
using std::ifstream;
using std::stringstream;

vector<string> splitLine(string line) {
  stringstream lineStream(line);
  string cell;
  vector<string> result;
  while(getline(lineStream, cell, ','))
  {
      result.push_back(cell);
  }
  return result;
}


double parseDouble(string value) {
  size_t sz;
  double val = stod(value, &sz);
  return val;
}


int main(){

  //open file stream that reads this file (already in our replit)
  ifstream str("snod.csv");

  //data will go here
  vector<vector<double>> data;

  string line;

  //loop until we get to the end of the file
  while (true) {
    getline(str,line);

    //line length will be zero when we get to end of file
    if (line.length() == 0) {
      //break exits the loop
      break;
    }

    vector<string> row = splitLine(line);
    vector<double> rowValues;
    for (int i = 0; i < row.size(); i++) {
      rowValues.push_back(parseDouble(row[i]));
    }
    data.push_back(rowValues);
  }


   FILE *imageFile;
   int x,y,pixel,height=data.size(),width=data[0].size();

   imageFile=fopen("image.pgm","wb");
   if(imageFile==NULL){
      perror("ERROR: Cannot open output file");
      exit(EXIT_FAILURE);
   }

   fprintf(imageFile,"P5\n");           // P5 filetype
   fprintf(imageFile,"%d %d\n",width,height);   // dimensions
   fprintf(imageFile,"255\n");          // Max pixel

   /* Now write a greyscale ramp */
   for(x=0;x<height;x++){
      for(y=0;y<width;y++){
         pixel=(int)(data[x][y]*100);
         fputc(pixel,imageFile);
      }
   }

   fclose(imageFile);
}