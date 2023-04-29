# Name: Maddie Waldie
# Date: 4/26/23
# Title: Lab4
# Description: Shell File to Run All Phases of Lab 4

#!/bin/bash
echo "Running Lab 4 Step 1"
echo " "
./1
echo "Step 1 Completed"
sleep 5
echo " "

echo "Running Lab 4 Step 4 - with N = 2, M = 3, L = 2"
echo " "
./4 2 3 2
echo "Step 4 Completed"
sleep 5
echo " "

echo "Running Lab 4 Step 4 - with N = 1024, M = 512, L = 1024"
echo " "
./4 1024 512 1024
echo "Step 4 Completed"
sleep 5
echo " "

echo "Running Lab 4 Step 5 - with N = 1024, M = 1024, L = 1024"
echo " "
./5 1024 1024 1024
echo "Step 4 Completed"
sleep 5
echo " "

echo "Running Lab 4 Step 5 - with smaller values"
echo " "
./5 2 3 2
echo "Step 4 Completed"
sleep 5
echo " "