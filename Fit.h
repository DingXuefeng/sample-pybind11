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
    void Execute(const std::string &);
  public:
    void setNmodel(int n) { Nmodel = n; }
    void setNdata(int n) { Ndata = n; }
    void setData(int [Phoenix::data_maxN]);
    void setModel(int i,Phoenix::dataArr);
    void setPar(int i,std::string pName,double pI,double pE,double pL,double pU,double pC,double pS) {
      parName[i] = pName;
      parInit[i] = pI;
      parErr[i] = pE;
      parLL[i] = pL;
      parUL[i] = pU;
      parCentroid[i] = pC;
      parSigma[i] = pS;
    }
  private:
    int Nmodel;
    int Ndata;
    int data [Phoenix::data_maxN];
    Phoenix::dataArr model[Phoenix::model_maxN];
    std::unique_ptr<TMinuit> fitter;
    std::string parName[Phoenix::model_maxN];
    Phoenix::parArr parInit,parErr,parLL,parUL,parCentroid,parSigma;
    int printLevel = 0; // -1,0,1,2
    double up = 0.5;
};
