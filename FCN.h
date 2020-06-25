/*****************Please don't remove this part from the code*****************************/
// Author: Xuefeng Ding <xuefeng.ding.physics@gmail.com>
// Insitute: Physics Department, Princeton Unviersity, Princeton, NJ 08542, USA
// Date: 2020 June 25th.
// Version: v1.0
// Description: Phoenix, a binned likleihood fitter
// Liscence: MIT
/*****************Please don't remove this part from the code*****************************/
#pragma once
namespace Phoenix {
  constexpr int data_maxN = 2000;
  constexpr int model_maxN = 20;
  using pArray = double [Phoenix::model_maxN];
  extern int *data;
  extern pArray *model;
  extern int Nmodel;
  extern int Ndata;

  void FCN(int &npar, double *gin, double &f, double *par, int flag);
}
