#!/bin/bash

export LD_LIBRARY_PATH=/app/libbpu/hbdk3/x5:$LD_LIBRARY_PATH

OUTPUT_0_0=/userdata/model-2k_00/
OUTPUT_0_1=/userdata/model-2k_01/

HBM_FILE=/app/libbpu/HBDK3_MODEL_2K/gen_I2004_ForTest2k_1x1088x2048x3.hbm
SRC_FILE=/app/libbpu/HBDK3_MODEL_2K/input_0_feature_1x1088x2048x3_ddr_native.bin
MODEL_NAME=I2004_ForTest2k_1x1088x2048x3

if [ ! -d $OUTPUT_0_0 ];then
	mkdir $OUTPUT_0_0
else
	rm $OUTPUT_0_0 -r
	mkdir $OUTPUT_0_0
fi
if [ ! -d $OUTPUT_0_1 ];then
	mkdir $OUTPUT_0_1
else
	rm $OUTPUT_0_1 -r
	mkdir $OUTPUT_0_1
fi

bpu_task_test -b 0 -l 4  -f $HBM_FILE -i $SRC_FILE -n $MODEL_NAME -o $OUTPUT_0_0,$OUTPUT_0_1 -t 200
