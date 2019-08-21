#!/bin/bash

generate_map()
{
	#maps/generator --flow-one > tmp.map
	#maps/generator --flow-ten > tmp.map
	#maps/generator --flow-thousand > tmp.map
	#maps/generator --big > tmp.map
	#maps/generator --big-superposition > tmp.map
	if [ $1 -eq 1 ]
	then
		maps/generator --flow-one > tmp.map
	elif [ $1 -eq 2 ]
	then
		maps/generator --flow-ten > tmp.map
	elif [ $1 -eq 3 ]
	then
		maps/generator --flow-thousand > tmp.map
	elif [ $1 -eq 4 ]
	then
		maps/generator --big > tmp.map
	elif [ $1 -eq 5 ]
	then
		maps/generator --big-superposition > tmp.map
	fi
}

single_test()
{
#	LI=`./lem-in < tmp.map | tail -3 | grep "turn" | cut -d ' ' -f5`
	LI=`./lem-in < tmp.map > tmp ; diff tmp tmp.map | wc -l`
	rm tmp
	LI=`echo "($LI) - 1" | bc`
	MAP=`tail -1 tmp.map | grep "line" | cut -d ' ' -f8`
	echo "$(($LI - $MAP))"
}

clear

echo "//================================\\\\"
printf "|| Script by \033[36msregnard\033[0m \033[31m&&\033[0m \033[36mchrhuang\033[0m ||\n"
echo "\\\\================================//"

read -n 1 -s -r -p "Press any key to continue"

clear
echo "//============================\\\\"
printf "|| [1] : \033[36m%-20s\033[0m ||\n" "flow-one"
printf "|| [2] : \033[32m%-20s\033[0m ||\n" "flow-ten"
printf "|| [3] : \033[33m%-20s\033[0m ||\n" "flow-thousand"
printf "|| [4] : \033[31m%-20s\033[0m ||\n" "big"
printf "|| [5] : \033[35m%-20s\033[0m ||\n" "big-superposition"
echo "\\\\============================//"
read -p "Choose your generator : " gen
if [ $gen -gt 5 ]
then
	echo "Invalid generator"
	exit 1
fi
read -p "Number of tests       : " nb_test
read -p "Test time ? [y][n]    : " FLAG_TIME
if [ "$FLAG_TIME" != "y" ] && [ "$FLAG_TIME" != "n" ]
then
	echo "Invalid"
	exit 1
fi
sum=0
sum_t=0
i=0
while [ $i -lt $nb_test ]
do
	printf "Generating next test... "
	generate_map "$gen"
	printf "Testing..."
	before=`date +%s`
	res=`single_test`
	after=`date +%s`
	res_t=`echo "($after) - ($before)" | bc -l`
	if [ $i -eq 0 ]
	then
		min=$res
		max=$res
		min_t=$res_t
		max_t=$res_t
	else
		if [ $res -le $min ]
		then
			min=$res
		fi
		if [ $max -le $res ]
		then
			max=$res
		fi
		if [ $res_t -le $min_t ]
		then
			min_t=$res_t
		fi
		if [ $max_t -le $res_t ]
		then
			max_t=$res_t
		fi
	fi
	clear
	sum=`echo "($res) + ($sum)" | bc`
	sum_t=`echo "($res_t) + ($sum_t)" | bc`
	let "i++"
	moy=`echo "($sum) / ($i)" | bc -l`
	moy_t=`echo "($sum_t) / ($i)" | bc -l`
	printf "Test no. \033[32m%s\033[0m/%s\n\n" $i $nb_test
	printf "Nb of turns :\n" $i $nb_test
	echo "//===========================\\\\"
	printf "||         Res : \033[36m%-7d\033[0m     ||\n" $res
	printf "||         Min : \033[32m%-7d\033[0m     ||\n" $min
	printf "||         Moy : \033[33m%-7.1f\033[0m     ||\n" $moy
	printf "||         Max : \033[31m%-7d\033[0m     ||\n" $max
	echo "\\\\===========================//"
	if [ "$FLAG_TIME" == "y" ]
	then
		printf "\nTime :\n" $i $nb_test
		echo "//===========================\\\\"
		printf "||         Time: \033[31m%-7d\033[0m     ||\n" $res_t
		printf "||         Min : \033[32m%-7d\033[0m     ||\n" $min_t
		printf "||         Moy : \033[33m%-7.1f\033[0m     ||\n" $moy_t
		printf "||         Max : \033[31m%-7d\033[0m     ||\n" $max_t
		echo "\\\\===========================//"
	fi
done
