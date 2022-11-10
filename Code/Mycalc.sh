#Dylan Carroll
#Lab 9
#40995018
#mycalc.sh
#April 12
#Allows the user to perform basic + and - operations though running the file with params or with none

#!/bin/bash
#Forces the use of the bash shell

#for if the user runs the script with parameter

#add function to add the parameters and display the proper answer
add ( )
{

        fNum=$f
        lNum=$s
        ((aNum = $fNum+$lNum))
        echo "The sum of $fNum plus $lNum equals $aNum "
        exit
}

#subtract function to subtract the parameters from each other and to show proper answer
subtract ( )
{

        fNum=$f
        lNum=$s
        ((aNum = $fNum-$lNum))
        echo "The sum of $fNum minus $lNum is $aNum "
        exit
}
f=$1
s=$3


#if statement to call proper function depending on if user wants to add or subtract

if [[ $2 = "+" ]]
then
add
elif [[ $2 = "-" ]]
then
subtract
elif [[ $4 -ge 1 ]]
then
        echo " Error, only three parameters are allowed. Quitting now..."
        exit
elif [[ $5 -ge 1 ]]
then
        echo " Error, only three parameters are allowed. Quitting now..."
        exit

else

#if there is no params used when script is run does the following below...


#while loop to prompt user until proper input to quit or calculate is found

while [[ $temp != "C" ]] && [[ $temp != "X" ]] && [[ $temp != "c" ]] && [[ $temp != "x" ]]      
do
        echo "C) Calculation"
read -p "X) Exit: " temp
done


#if statement for when user chooses to calculate
if [[ $temp = "C" ]] || [[ $temp = "c" ]]
then
        #clears the screen
        clear
        while [[ $num != "X" ]] && [[ $num != "x" ]] && [[ $num -le 0 ]] 
        do
        read -p "Please enter an integer number or X to exit: " num
        done
        #nested if statement for if user decides to go on with calc or quit from here
        if [[ $num = "X" ]] || [[ $num = "x" ]]
        then
        echo "Exiting program now..."
        #exits the program if chosen so by the user
        exit
        else
        #if user enters a value is displays the value entered then moves on after a one second delay

echo "First value set as $num"
        sleep 1
        clear
        fi
        while [[ $test != "+" ]] && [[ $test != "-" ]] && [[ $test != "X" ]] && [[ $test != "x" ]]
        do
        echo "+) Add "
        echo "-) Subtract "

        #Here is where the user chooses the type of operation they wish to use 
        read -p "X) Exit: " test
        done


        #if user chooses to exit here then this if statement catches the x and quits
        if [[ $test = "X" ]] || [[ $test = "x" ]]
        then
        echo "Exiting program now..."
        exit
        else
                #Shows user that operation type is set and delays by three seconds 
  echo "type of operation set... "
                sleep 3
        fi
                #prompts the user for second value, and displayed the recieved value if                 the user has not chosen to exit
                while [[ $num2 != "X" ]] && [[ $num2 != "x" ]] && [[ $num2 -le 0 ]] 
        do
                read -p "Please enter a second integer number or X to exit: " num2
        done
                 if [[ $num2 = "X" ]] || [[ $num2 = "x" ]]
        then
        echo "Exiting program now..."
                 exit
                 #above exits program if chosen so, if not code goes to else and continues
        else
        echo "Second value set as $num2"
                 fi
                 #statement to do proper type of operation and to check if proper input wa                      was used
                if [[ $test = "+" ]]
                then
                        ((final = $num+$num2))
 echo "$num added to $num2 is $final"
                elif [[ $test = "-" ]]
                then
                ((final = $num-$num2))
                echo "$num subtracted by $num2 is $final"
                else
                  echo "incorrect operand type entered."
                  exit
fi

#if the user chooses to exit    
elif [[ $temp = "X" ]] || [[ $temp = "x" ]]
then
        echo "Quitting now..."
        #if user does not use proper input
else
        echo "input error..."
fi

fi


