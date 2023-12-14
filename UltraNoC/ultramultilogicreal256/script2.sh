#!/bin/bash

./ultramulti_32 streamcluster_modified.txt bodytrack_modified.txt blackscholes_modified.txt vips_modified.txt >Result_updated_ultramulti_256_32.txt
./ultramulti_32 bodytrack_modified.txt dedup_modified.txt fluidanimate_modified.txt freqmine_modified.txt >>Result_updated_ultramulti_256_32.txt
./ultramulti_32 canneal_modified.txt x264_modified.txt ferret_modified.txt freqmine_modified.txt >>Result_updated_ultramulti_256_32.txt
./ultramulti_32 facesim_modified.txt swaptions_modified.txt vips_modified.txt fluidanimate_modified.txt >>Result_updated_ultramulti_256_32.txt
./ultramulti_32 streamcluster_modified.txt bodytrack_modified.txt blackscholes_modified.txt x264_modified.txt >>Result_updated_ultramulti_256_32.txt
./ultramulti_32 canneal_modified.txt facesim_modified.txt ferret_modified.txt fluidanimate_modified.txt >>Result_updated_ultramulti_256_32.txt
./ultramulti_32 streamcluster_modified.txt swaptions_modified.txt vips_modified.txt dedup_modified.txt >>Result_updated_ultramulti_256_32.txt
./ultramulti_32 streamcluster_modified.txt facesim_modified.txt swaptions_modified.txt canneal_modified.txt >>Result_updated_ultramulti_256_32.txt
./ultramulti_32 bodytrack_modified.txt blackscholes_modified.txt vips_modified.txt dedup_modified.txt >>Result_updated_ultramulti_256_32.txt
./ultramulti_32 x264_modified.txt ferret_modified.txt freqmine_modified.txt fluidanimate_modified.txt >>Result_updated_ultramulti_256_32.txt
./ultramulti_32 streamcluster_modified.txt facesim_modified.txt blackscholes_modified.txt canneal_modified.txt >>Result_updated_ultramulti_256_32.txt
./ultramulti_32 bodytrack_modified.txt x264_modified.txt freqmine_modified.txt fluidanimate_modified.txt >>Result_updated_ultramulti_256_32.txt
