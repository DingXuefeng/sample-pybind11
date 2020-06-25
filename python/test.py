#!/usr/bin/env python

from Phoenix import Fit
from InputReader import BXInputReader
from mpi4py import MPI

comm = MPI.COMM_WORLD
rank = comm.Get_rank()

if rank == 0:
    data = {'a': 7, 'b': 3.14}
    req = comm.isend(data,dest=1, tag=11)
    req.wait()
elif rank >0:
    req = comm.irecv(source=0,tag=11)
    data = req.wait()
    print(f'{data["a"]} and {data["b"]}')

    fit = Fit()
    inputReader = BXInputReader()
    inputReader.loadFitterInput("../../../BOREXINO/BX-Analysis/bx-stats/fit_Data/fitMVdirectly/v512_P3Large_pepMI_nhits_CMV_2b17.root")
    inputReader.loadMCPDFs("../../../BOREXINO/BX-Analysis/bx-stats/fit_Data/fitMVdirectly/MCspectra_FVpep_Period_Phase3Large.root")
    inputReader.loadIcc("../../../BOREXINO/BX-Analysis/bx-GooStats/CNOfit/charge/species_list_Bi210UL.icc")
    fit.setNdata(inputReader.getNdata())
    fit.setData(inputReader.getData())
    fit.setNmodel(inputReader.getNmodel())
    for i,parModel in enumerate(inputReader.getPars()):
        par,model = parModel
        fit.setModel(i,model)
        fit.setPar(i,par.init,par.Err,par.LL,par.UL)
