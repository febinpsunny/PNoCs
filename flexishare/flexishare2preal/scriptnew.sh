#!/bin/bash

./flexishare streamcluster_modified.txt bodytrack_modified.txt blackscholes_modified.txt vips_modified.txt >Result_updated_flexishare_wbf_2p.txt
./flexishare bodytrack_modified.txt dedup_modified.txt fluidanimate_modified.txt freqmine_modified.txt >>Result_updated_flexishare_wbf_2p.txt
./flexishare canneal_modified.txt x264_modified.txt ferret_modified.txt freqmine_modified.txt >>Result_updated_flexishare_wbf_2p.txt
./flexishare facesim_modified.txt swaptions_modified.txt vips_modified.txt fluidanimate_modified.txt >>Result_updated_flexishare_wbf_2p.txt
./flexishare streamcluster_modified.txt bodytrack_modified.txt blackscholes_modified.txt x264_modified.txt >>Result_updated_flexishare_wbf_2p.txt
./flexishare canneal_modified.txt facesim_modified.txt ferret_modified.txt fluidanimate_modified.txt >>Result_updated_flexishare_wbf_2p.txt
./flexishare streamcluster_modified.txt swaptions_modified.txt vips_modified.txt dedup_modified.txt >>Result_updated_flexishare_wbf_2p.txt
./flexishare streamcluster_modified.txt facesim_modified.txt swaptions_modified.txt canneal_modified.txt >>Result_updated_flexishare_wbf_2p.txt
./flexishare bodytrack_modified.txt blackscholes_modified.txt vips_modified.txt dedup_modified.txt >>Result_updated_flexishare_wbf_2p.txt
./flexishare x264_modified.txt ferret_modified.txt freqmine_modified.txt fluidanimate_modified.txt >>Result_updated_flexishare_wbf_2p.txt
./flexishare streamcluster_modified.txt facesim_modified.txt canneal_modified.txt blackscholes_modified.txt >>Result_updated_flexishare_wbf_2p.txt
./flexishare bodytrack_modified.txt x264_modified.txt freqmine_modified.txt fluidanimate_modified.txt >>Result_updated_flexishare_wbf_2p.txt

./flexishare bodytrack_modified.txt x264_modified.txt streamcluster_modified.txt vips_modified.txt >Result_simple.txt
