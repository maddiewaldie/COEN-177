#!/bin/bash
echo "----------Make--------"
make; 

echo
echo "----------Creating Files----------"
cat /dev/urandom | head -c 100000 > file1.txt
cat /dev/urandom | head -c 1000000 > file2.txt
cat /dev/urandom | head -c 10000000 > file3.txt
cat /dev/urandom | head -c 100000000 > file4.txt
cat /dev/urandom | head -c 10000000000 > file5.txt


echo  "----------Running steps----------"
echo "Step 2"
for file in file1.txt file2.txt file3.txt file4.txt 
do
	echo "Step2 $file"
	time ./step2 $file
	echo " "
done

echo "Step 3"
for file in file1.txt file2.txt file3.txt file4.txt 
do
	for buffer in 100 1000 10000 100000
	do
		echo "Step3 $file $buffer"
		time ./step3 $file $buffer
		echo " "
	done
done

echo "Step 4"
for file in file1.txt file2.txt file3.txt file4.txt 
do
	for buffer in 100 1000 10000 100000
	do
		echo "Step4 $file $buffer"
		time ./step4 $file $buffer
		echo " "
	done
done

echo "Step 5"
for file in file1.txt file2.txt file3.txt file4.txt 
do
	for buffer in 100 1000 10000 100000
	do
		for thread in 2 8 32 64
		do
			echo "Step5 $file $buffer $thread"
			time ./step5 $file $buffer $thread
			echo " "
		done
	done
done

make clean;
echo
