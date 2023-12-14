#!/bin/bash
export SC_SIGNAL_WRITE_CHECK=DISABLE

file_name="UltraMulti"
current_time=$(date "+%Y.%m.%d-%H.%M.%S")
new_filename="$file_name-$current_time.txt" 

#./ultramulti streamcluster_modified.txt bodytrack_modified.txt blackscholes_modified.txt vips_modified.txt >Result_updated_ultramulti_16.txt
#./ultramulti bodytrack_modified.txt dedup_modified.txt fluidanimate_modified.txt freqmine_modified.txt >>Result_updated_ultramulti_16.txt
./ultramulti canneal_modified.txt >> $new_filename
#x264_modified.txt ferret_modified.txt freqmine_modified.txt >> $new_filename
#./ultramulti facesim_modified.txt swaptions_modified.txt vips_modified.txt fluidanimate_modified.txt >>Result_updated_ultramulti_16.txt
#./ultramulti streamcluster_modified.txt bodytrack_modified.txt blackscholes_modified.txt x264_modified.txt >>Result_updated_ultramulti_16.txt
#./ultramulti canneal_modified.txt facesim_modified.txt ferret_modified.txt fluidanimate_modified.txt >>Result_updated_ultramulti_16.txt
#./ultramulti streamcluster_modified.txt swaptions_modified.txt vips_modified.txt dedup_modified.txt >>Result_updated_ultramulti_16.txt
#./ultramulti streamcluster_modified.txt facesim_modified.txt swaptions_modified.txt canneal_modified.txt >>Result_updated_ultramulti_16.txt
#./ultramulti bodytrack_modified.txt blackscholes_modified.txt vips_modified.txt dedup_modified.txt >>Result_updated_ultramulti_16.txt
#./ultramulti x264_modified.txt ferret_modified.txt freqmine_modified.txt fluidanimate_modified.txt >>Result_updated_ultramulti_16.txt
#./ultramulti streamcluster_modified.txt facesim_modified.txt blackscholes_modified.txt canneal_modified.txt >>Result_updated_ultramulti_16.txt
#./ultramulti bodytrack_modified.txt x264_modified.txt freqmine_modified.txt fluidanimate_modified.txt >>Result_updated_ultramulti_16.txt
