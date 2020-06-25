/*****************Please don't remove this part from the code*****************************/
// Author: Xuefeng Ding <xuefeng.ding.physics@gmail.com>
// Insitute: Physics Department, Princeton Unviersity, Princeton, NJ 08542, USA
// Date: 2020 June 25th.
// Version: v1.0
// Description: Phoenix, a binned likleihood fitter
// Liscence: MIT
/*****************Please don't remove this part from the code*****************************/
#include "FCN.h"
#include <functional>
#include <cmath>
namespace Phoenix {
  int *data;
  pArray *model;
  int Nmodel;
  int Ndata;
  void transform(double out[data_maxN],int maxN,std::function<double(int rank)> f) {
    for(int i = 0;i<maxN;++i)
      out[i] = f(i);
  }
  double reduce(const double in[data_maxN],int maxN) {
    double sum = 0;
    for(int i = 0;i<maxN;++i)
      sum += in[i];
    return sum;
  }
  void FCN(int &npar, double *gin, double &f, double *par, int flag) {
    double model_sum[data_maxN];
    transform(model_sum,Ndata,[=](int rank) {
        double sum = 0;
        for(int i = 0;i<Nmodel;++i)
        sum += model[i][rank]*par[i];
        return sum;
        });
    switch(flag) {
      case 1: // init
        break;
      case 2: // get dLL/dpar
        double dFdp[data_maxN];
        for(int i = 0;i<Nmodel;++i) {
          transform(dFdp,Ndata,[=](int rank) {
              double fij = model[i][rank];
              int k = data[rank];
              double lambda = model_sum[rank];
              return fij*(1-k/lambda);
              });
          gin[i] = reduce(dFdp,Ndata);
        }
        break;
      case 3: // finish
        break;
      default:
        double LL[data_maxN];
        transform(LL,Ndata,[=](int rank) {
          int k = data[rank];
          double lambda = model_sum[rank];
          return -k*log(lambda)+lgamma(k+1)+lambda;
        });
        f = reduce(LL,Ndata);
    }
  }
}
