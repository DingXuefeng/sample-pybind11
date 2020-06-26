#!/usr/bin/env python

import ROOT
import re
import numpy as np

class BXInputReader:
    def __init__(self):
        self.keys = ['name','parameter','color','style','thickness','init','fixed','LL','UL','Err','pull_centroid','pull_sigma']
        self.valtype = [str,str,str,str,int,float,str,float,float]

    def __loadHist(self,f,hname,T = float):
        hist = f.Get(hname)
        return np.array(list(map(lambda i:T(hist.GetBinContent(i)), range(hist.FindBin(self.Emin+1e-5),hist.FindBin(self.Emax-1e-5)))))

    def loadFitterInput(self,inputRootFileName):
        f = ROOT.TFile(inputRootFileName)
        self.data = self.__loadHist(f,"pp/final_nhits_pp_0",int)
        f.Close()

    def loadMCPDFs(self,MCPDFName):
        f = ROOT.TFile(MCPDFName)
        self.models = {}
        for spc in self.pars:
            newname = re.sub('nu\((.*)\)',r'\1',spc['name'].lower().split('_2')[0]+"_nhits")
            self.models[spc['name']] = self.__loadHist(f,newname)*500
        f.Close()

    def loadIcc(self,IccName):
        f = open(IccName)
        self.pars=[]
        for line in f.readlines():
            if line.strip()[0] != '{':
                continue
            values = [f(x.strip('" ')) for x,f in zip(line.strip(' {},\n').split(','),self.valtype)]
            pars = dict(zip(self.keys,values + [(values[-1]-values[-2])/100,-1,0]))
            if pars['name'].find('_2')>0: continue
            if pars['fixed'] == 'fixed':
                pars['UL'] = pars['LL'] = pars['init']
                pars['Err'] = 0
            elif pars['fixed'] == 'penalty':
                pars['pull_centroid'] = pars['LL']
                pars['pull_sigma'] = pars['UL']
                pars['Err'] = abs(pars['pull_sigma'])
                pars['LL'] = (lambda x: x if x>0 else -x )(pars['pull_centroid']-pars['Err']*10)
                pars['UL'] = pars['pull_centroid']+pars['Err']*10
            self.pars.append(pars)

    def setFitRange(self,Emin,Emax):
        self.Emin = Emin
        self.Emax = Emax
        
    def getNdata(self):
        return self.data.size

    def getData(self):
        return self.data

    def getNmodel(self):
        return len(self.models)

    def getPars(self):
        return self.pars

    def getModels(self):
        return self.models
