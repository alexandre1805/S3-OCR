#include <stdio.h>
#include <stdlib.h>
#include "sigmoid.h"
#include "neuron.h"
#include <string.h>
#include "whicharacter.h"
#include "Img-Proc.h"
#include "Matrix.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void chara_mat(char* dir,int * mat){
 SDL_Surface *sur = Load_Image(dir);
 Binarize(sur);
 int *res = malloc(60*60*sizeof(int));
 Sdl_To_Matrix(sur, res);
 for(int x = 0;x<28;x++){
  for(int y = 0;y<28;y++){
   int X = x*60/28;
   int Y = y*60/28;
   mat[x*28+y] = res[X*60+Y];
  }
 }

}

void readfile(char *path, double list[], int size){
  FILE* file = NULL;
  file = fopen(path, "r");
  list[0] = 0;
  printf("%i\n",size);
  if (file != NULL)
    {
     //for (int i = 0; i < size; i++)
     //{
        //char s;
	float f = 0.0;
	fscanf(file, "%f ", &f);
        //s = fgetc(file);
        printf("%f\n",f);
     //}
       fclose(file);
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier %s",path);
    }
}

double input1[784];
double input2[392];
double input3[196];
double input4[98];
double input5[49];
double error[814];
double weight1[307328];
double weight2[76832];
double weight3[19208];
double weight4[4802];
double weight5[3871];
double biasWeight[814];
struct Neuron neuronlist1[392];
struct Neuron neuronlist2[196];
struct Neuron neuronlist3[98];
struct Neuron neuronlist4[49];
struct Neuron neuronlist5[79];
double outneuron[79];

void init_Reseau(){
readfile("save_biasWeight.txt", biasWeight, 814);
readfile("save_weight1.txt", weight1, 307328);
readfile("save_weight2.txt", weight2, 76832);
readfile("save_weight3.txt", weight3, 19208);
readfile("save_weight4.txt", weight4, 4802);
readfile("save_weight5.txt", weight5, 3871);

for (int i = 0; i < 392; i++){
		struct Neuron trans = neuronlist1[i];
		trans.size = 784;
		trans.input = input1;
		trans.weight = weight1 + i*784;
		trans.error = error + i;
		trans.biasWeight = biasWeight + i;
 		randomizeWeights(trans);
		neuronlist1[i] = trans;}

for (int i = 0; i < 196; i++){
		struct Neuron trans = neuronlist2[i];
		trans.size = 392;
		trans.input = input2;
		trans.weight = weight2 + i*392;
		trans.error = error + i+392;
		trans.biasWeight = biasWeight +i + 392;
 		randomizeWeights(trans);
		neuronlist2[i] = trans;}

for (int i = 0; i < 98; i++){
		struct Neuron trans = neuronlist3[i];
		trans.size = 196;
		trans.input = input3;
		trans.weight = weight3 + i*196;
		trans.error = error + i+392+196;
		trans.biasWeight = biasWeight + i+ 392+196;
 		randomizeWeights(trans);
		neuronlist3[i] = trans;}
  
for (int i = 0; i < 49; i++){
		struct Neuron trans = neuronlist4[i];
		trans.size = 98;
		trans.input = input4;
		trans.weight = weight4 + i*98;
		trans.error = error + i+392+196+98;
		trans.biasWeight = biasWeight + i+392+196+98;
 		randomizeWeights(trans);
		neuronlist4[i] = trans;}

for (int i = 0; i < 79; i++){
		struct Neuron trans = neuronlist5[i];
		trans.size = 49;
		trans.input = input5;
		trans.weight = weight5 + i*49;
		trans.error = error + i+392+196+98+49;
		trans.biasWeight = biasWeight + i+392+196+98+49;
 		randomizeWeights(trans);
		neuronlist5[i] = trans;}
}
char answer(int input[]){
  for (size_t i = 0; i < 784; i++){
	    input1[i] = (double) input[i];}
  for (int i = 0; i < 392; i++){
      *(input2+i) = output(neuronlist1[i]);}
        
    for (int i = 0; i < 196; i++){
      *(input3+i) = output(neuronlist2[i]);}
        
    for (int i = 0; i < 98; i++){
      *(input4+i) = output(neuronlist3[i]);}
    
    for (int i = 0; i < 49; i++){
      *(input5+i) = output(neuronlist4[i]);}
    
    for (int i = 0; i < 79; i++){
      *(outneuron+i) = output(neuronlist5[i]);}

    double max = 0.0;
    int maxi = 0;
    for (int i = 0; i < 79; i++){
      if (outneuron[i] > max){
	      max = outneuron[i];
	      maxi = i;}}
    return characterwi(maxi+1);}
