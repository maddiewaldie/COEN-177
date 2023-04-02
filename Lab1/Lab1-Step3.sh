# Name: Madeleine Waldie
# Date: April 5, 2023
# Title: Lab1 – Step 3: Area & perimeter of circle
# Description: This program computes the area and perimeter of a circle,
# given a user input of the radius of the circle. 

#!/bin/sh
echo Executing $0
echo $(/bin/ls | wc -l) files
wc -l $(/bin/ls)
echo "HOME="$HOME
echo "USER="$USER
echo "PATH="$PATH
echo "PWD="$PWD
echo "\$\$"=$$
user=`whoami`
numusers=`who | wc -l`
echo "Hi $user! There are $numusers users logged on."
if [ $user = "maddie" ]
then
    echo "Now you can proceed!"
else
    echo "Check who logged in!"
    exit 1
fi

calculatePerimeterOfCircle() {
    pi=3.14
    perimeter=$(echo "scale=2; $1*$pi*2" | bc -l)
    echo "The perimeter of the rectangle is $perimeter"
}

calculateAreaOfCircle() {
    r2=$(echo "$1*$1" | bc -l)
    pi=3.14
	area=$(echo "scale=2; $r2*$pi" | bc -l)
    echo "The area of the circle is $area"
}

response="Yes"
while [ $response != "No" ]
do
    echo "Enter radius of circle: "
    read radius
    calculatePerimeterOfCircle $radius
    calculateAreaOfCircle $radius
    
    echo "Would you like to repeat for another circle [Yes/No]?"
    read response
done