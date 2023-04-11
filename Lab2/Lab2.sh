# Name: Maddie Waldie
# Date: 4/12/23
# Title: Lab2 
# Description: Shell File to Run All Phases of Lab 2

#!/bin/bash
echo "Running Lab 2 Step 1"
echo " "
./1
echo "Step 1 Completed"
sleep 5
echo " "

echo "Running Lab 2 Step 3"
echo " "
./3 3000
echo "Step 3 Completed"
sleep 5
echo " "

echo "Running Lab 2 Step 4 (500 ms)"
echo " "
./3 500
echo "Step 4 (500 ms) Completed"
sleep 5
echo " "

echo "Running Lab 2 Step 4 (5000 ms)"
echo " "
./3 5000
echo "Step 4 (5000 ms) Completed"
sleep 5
echo " "

echo "Running Lab 2 Step 5"
echo " "
./5 3000 3000 3000 3000
echo "Step 5 Completed"
sleep 5
echo " "

echo "Running Lab 2 Step 6"
echo " "
./6 3000 3000 3000 3000 3000
echo "Step 6 Completed"
sleep 5
echo " "

echo "Running Lab 2 Step 7"
echo " "
./7
echo "Step 7 Completed"
sleep 5
echo " "

echo "Running Lab 2 Step 8"
echo " "
./8 3000
echo "Step 8 Completed"
sleep 5
echo " "