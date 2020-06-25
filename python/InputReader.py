#!/usr/bin/env python

import ROOT
class BXInputReader:
    def __init__(self):
        pass

    def loadFitterInput(self,inputRootFileName):
        file = ROOT.TFile(inputRootFileName)
        hist = file.Get("pp/final_nhits_pp_0")
        self.data = list(map(lambda i:int(hist.GetBinContent(i)), range(hist.GetNbinsX())))

    def loadMCPDFs(self,MCPDFName):
        file = ROOT.TFile(MCPDFName)
        self.model = []

    def loadIcc(self,IccName):
        file = open(IccName)
        self.pars=[]
        for line in file.readlines():
            if line.strip()[0] != '{':
                continue
            self.pars.append([x.strip('" ') for x in line.strip(' {},\n').split(',')])
        print(self.pars)
        
    def getNdata(self):
        return len(self.data)

    def getData(self):
        return self.data

    def getNmodel(self):
        return len(self.model)

    def getPars(self):
        return self.pars
