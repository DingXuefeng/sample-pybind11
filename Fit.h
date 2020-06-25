/*****************Please don't remove this part from the code*****************************/
// Author: Xuefeng Ding <xuefeng.ding.physics@gmail.com>
// Insitute: Physics Department, Princeton Unviersity, Princeton, NJ 08542, USA
// Date: 2020 June 25th.
// Version: v1.0
// Description: Phoenix, a binned likleihood fitter
// Liscence: MIT
/*****************Please don't remove this part from the code*****************************/
#pragma once
#include <memory>
#include <string>
#include "FCN.h"
#include "TMinuit.h"
class Fit {
  public:
    void Load();
    void doFit();
  public:
    void setNmodel(int n) { Nmodel = n; }
    void setNdata(int n) { Ndata = n; }
    void setData(int [Phoenix::data_maxN]);
    void setModel(int i,Phoenix::pArray);
    void setPar(int i,double pI,double pE,double pL,double pU) {
      parInit[i] = pI;
      parErr[i] = pE;
      parLL[i] = pL;
      parUL[i] = pU;
    }
  private:
    int Nmodel;
    int Ndata;
    int data [Phoenix::data_maxN];
    Phoenix::pArray model[Phoenix::model_maxN];
    std::unique_ptr<TMinuit> fitter;
    std::string parName[Phoenix::model_maxN];
    Phoenix::pArray parInit,parErr,parLL,parUL;
    int printLevel = 0; // -1,0,1,2
    double up = 0.5;
};
