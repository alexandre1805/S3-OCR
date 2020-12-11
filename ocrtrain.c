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

void chara_mat(char* dir,int * mat){// Ne pas toucher merci :)
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

void savefile(char* path,double list[],int size){
  FILE* file = NULL;
  file = fopen(path, "w");
  for (int i = 0; i < size; i++){
	  fprintf(file, "%lf ", list[i]);}
  fclose(file);}

int main(){
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

  int epoc = 0;
  double outneuron[79];
  double outresult[79];

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

  while(epoc < 140000){
    
    int *chara = malloc(28*28*sizeof(int));
    int cha = epoc % 79+1;
    int whi = rand() % 20 + 1;
    char* dir = wicharacter(cha,whi);
    printf("%li and %li\n",cha, whi);
    chara_mat(dir,chara);// !!!nom de l'image a change ou a automatiser!!!
    /*
    for(int x = 0;x<28;x++){
      for(int y = 0;y<28;y++){
	printf("%i",chara[x*28+y]);// exemple d'accès a chaque pixel avec un printf
      }
      printf("\n");
    }*/
    
    
    for (size_t i = 0; i < 784; i++){
	    input1[i] = (double) chara[i];}
    

    for (int i = 0; i < 79; i++){
	*(outresult+i) = 0.01;}
    
    *(outresult + cha-1) = 0.99;

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
    
    for (int i = 0; i < 79; i++){
	    if (outneuron[i] > 0.1)
		    printf("%li == %lf ", i, outneuron[i]);}

    printf("%li == %lf\n", cha-1, outneuron[cha-1]);
    

    for (int i = 0; i < 79; i++){
			struct Neuron trans = neuronlist5[i];
			*trans.error = deriv_sigmoid(output(trans)) * (output(trans) - outresult[i]);
			adjustWeights(trans);
			neuronlist5[i] = trans;}
    
    for (int i = 0 ; i < 49; i++){
			struct Neuron trans = neuronlist4[i];
			double globaerror;
			struct Neuron transerror;
			globaerror = 0;
			for (int l = 0; l < 79; l++){
				transerror = neuronlist5[l];
				globaerror += *transerror.error * *(transerror.weight + i);}
			*trans.error = deriv_sigmoid(output(trans))*globaerror;
			adjustWeights(trans);
			neuronlist4[i] = trans;}

    for (int i = 0 ; i < 98; i++){
			struct Neuron trans = neuronlist3[i];
			double globaerror;
			struct Neuron transerror;
			globaerror = 0;
			for (int l = 0; l < 49; l++){
				transerror = neuronlist4[l];
				globaerror += *transerror.error * *(transerror.weight + i);}
			*trans.error = deriv_sigmoid(output(trans))*globaerror;
			adjustWeights(trans);
			neuronlist3[i] = trans;}
    
    for (int i = 0 ; i < 196; i++){
			struct Neuron trans = neuronlist2[i];
			double globaerror;
			struct Neuron transerror;
			globaerror = 0;
			for (int l = 0; l < 98; l++){
				transerror = neuronlist3[l];
				globaerror += *transerror.error * *(transerror.weight + i);}
			*trans.error = deriv_sigmoid(output(trans))*globaerror;
			adjustWeights(trans);
			neuronlist2[i] = trans;}
    
    for (int i = 0 ; i < 392; i++){
			struct Neuron trans = neuronlist1[i];
			double globaerror;
			struct Neuron transerror;
			globaerror = 0;
			for (int l = 0; l < 196; l++){
				transerror = neuronlist2[l];
				globaerror += *transerror.error * *(transerror.weight + i);}
			*trans.error = deriv_sigmoid(output(trans))*globaerror;
			adjustWeights(trans);
			neuronlist1[i] = trans;}

  		epoc++;}
  savefile("save_error.txt", error, 814);
  savefile("save_biasWeight.txt", biasWeight, 814);
  savefile("save_weight1.txt", weight1, 307328);
  savefile("save_weight2.txt", weight2, 76832);
  savefile("save_weight3.txt", weight3, 19208);
  savefile("save_weight4.txt", weight4, 4802);
  savefile("save_weight5.txt", weight5, 3871);
  return 1;
}
