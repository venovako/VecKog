#!/bin/bash
# !!! has to be run from this directory !!!
if [ -z "${TGT}" ]
then
	cd ../../libpvn/src
	make COMPILER=icx NDEBUG=3 SAFE=DET,SV2,NRM OPENMP=0 clean
	make COMPILER=icx NDEBUG=3 SAFE=DET,SV2,NRM OPENMP=0 -j
	cd -
	make clean all
else
	cd ../../libpvn/src
	make COMPILER=icx NATIVE=haswell MARCH=${TGT} NDEBUG=3 SAFE=DET,SV2,NRM OPENMP=0 clean
	make COMPILER=icx NATIVE=haswell MARCH=${TGT} NDEBUG=3 SAFE=DET,SV2,NRM OPENMP=0 -j
	cd -
	make clean all
fi
