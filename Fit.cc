/*****************Please don't remove this part from the code*****************************/
// Author: Xuefeng Ding <xuefeng.ding.physics@gmail.com>
// Insitute: Physics Department, Princeton Unviersity, Princeton, NJ 08542, USA
// Date: 2020 June 25th.
// Version: v1.0
// Description: Phoenix, a binned likleihood fitter
// Liscence: MIT
/*****************Please don't remove this part from the code*****************************/
#include "Fit.h"
#include "TMinuit.h"
#include "FCN.h"
#include <memory>
#include <algorithm>
void Fit::setData(int _d[Phoenix::data_maxN]) {
  std::copy(_d,_d+Ndata,data);
}
void Fit::setModel(int i,Phoenix::dataArr _m) {
  std::copy(_m,_m+Ndata,model[i]);
}
void Fit::Load() {
  Phoenix::Nmodel = Nmodel;
  Phoenix::Ndata = Ndata;
  Phoenix::data = data;
  Phoenix::model = model;
  Phoenix::pull_centroid = parCentroid;
  Phoenix::pull_sigma = parSigma;
  fitter = std::make_unique<TMinuit>(Nmodel);
  fitter->SetFCN(Phoenix::FCN);
  for(int i = 0;i<Nmodel;++i)
    fitter->DefineParameter(i,parName[i].c_str(),parInit[i],parErr[i],parLL[i],parUL[i]);
  fitter->SetPrintLevel(printLevel);
  fitter->SetErrorDef(up);
  int ierflg;
  fitter->mnexcm("SET STR",(double []){2},1,ierflg);
}
void Fit::doFit() {
  int ierflg;
  fitter->mnexcm("MINIMIZE", (double []){5000},1,ierflg);
  fitter->mnexcm("HESSE", 0,0,ierflg);
}
void Fit::Execute(const std::string &cmd) {
  fitter->Command(cmd.c_str());
}
