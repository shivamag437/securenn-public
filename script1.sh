#!/bin/bash
#Script to increase number of CNN layers starting from 1 while keeping number of filters constant
echo "CNN FILTER: 5X5 POOLING FILTER: 1X1"
echo "S.no,Input Image Size,Total Filters,Number of Layers,Number of filters in each layer,Input Size FCLayer1,Input Size FCLayer2,Exec Time (wall clock),Exec Time (CPU)\n" >> benchmarks.csv
k=0
num_cnn_layers=0
total_filters=32
num_filters=32
num_layers=0
#while [ $num_filters -ge 1 ]
#do
	#num_cnn_layers=$(($total_filters/$num_filters))
	#num_layers=$(($num_cnn_layers+3))
#	echo $k
	#echo $num_layers
#	echo $num_filters
#	num_filter=$(($num_filters/2))
#	k=$(($k+1))
	#sed -i "58s/.*/#define NUM_LAYERS $num_layers/" src/globals.h
	#sed -i "43s/.*/	int num_filters = $num_filters;/" src/main.cpp
	#sed -i "44s/.*/	int num_cnn_layers = $num_cnn_layers;/" src/main.cpp
	#sed -i "45s/.*/	int k = $k;/" src/main.cpp
	
#done

while [ $num_filters -ge 1 ]
do
	num_cnn_layers=$(($total_filters/$num_filters))
	num_layers=$(($num_cnn_layers+3))
	echo $k
	echo $num_filters
	echo $num_layers
	echo "-----"
	sed -i "58s/.*/#define NUM_LAYERS $num_layers/" src/globals.h
	sed -i "42s/.*/	int total_filters = $total_filters;/" src/main.cpp
	sed -i "43s/.*/	int num_filters = $num_filters;/" src/main.cpp
	sed -i "44s/.*/	int num_cnn_layers = $num_cnn_layers;/" src/main.cpp
	sed -i "45s/.*/	int k = $k;/" src/main.cpp
	make abcTerminal
	num_filters=$(($num_filters/2))
	k=$(($k+1))
done
