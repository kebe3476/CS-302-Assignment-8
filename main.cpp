/*
CS 302 Assignment 8

Name: Keith Beauvais, 5005338658, CS 302 Assignment 8
*/
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "priorityQ.h"
#include <iomanip>



int main(){
    
    std::ifstream infile;
    std::string line= "", wordInLine= "", numberInLine= "", inputFile= "", nameOfCompany= "", firstInput = "";
    std::string dayValues = "";
    double initialDiv = 0.0, capitalAmount= 0.0, priceOfStock= 0.0, mapDiv= 0.0, priceOfCompany= 0.0,tempCapitalAmount= 0.0;
    std::vector<std::string> backupNames;
    std::vector<std::string> tempNames;
    int numberOfDays = 0 , counter=0;
    priorityQ<stockType> putIntoPriorityQ;
    int dayCounter = 1, inputLineCounter = 1;
    double endTotal = 0.0;


    std:: unordered_map<std::string, double> stockMap;
    std:: unordered_map<std::string, double> tempMap;
    std:: unordered_map<std::string, double> tempMapForProfit;
    std:: unordered_map<std::string, int> amountBought;

    // reads in stocks.csv file
    std::cout<<std::endl;
    std::cout<<"Stocks file: ";
    std::cin >> firstInput;
    infile.open(firstInput);
    //getline(infile, line);

    /*
    parse through stocks.csv file and creates an unordered map with stock name as the key and dividend as the value.
    also creates another unordered map amountBought to 0 and creates a vector of all the stock names in order they 
    are read in. 
    */
    while(!infile.eof()){
        getline(infile, line);
        std::stringstream ss(line);
        getline(ss, wordInLine, ',');
        getline(ss, numberInLine, ',');
        initialDiv = std::stod(numberInLine);
        stockMap[wordInLine] = initialDiv;
        amountBought[wordInLine] = 0;
        backupNames.push_back(wordInLine);
        //getline(infile, line);
    }

    infile.close();

    // reads in the sim file the amount of days to simulate, and the initial brokerage amount
    std::cout<<std::endl;
    std::cout<<"Sim file: ";
    std::cin >> inputFile;
    infile.open(inputFile);
    std::cout<<std::endl;
    std::cout<<"Amount of days to simulate: ";
    std::cin >> numberOfDays;
    std::cout<<std::endl;
    std::cout<<"Amount you wish to transfer into brokerage account: ";
    std::cin >> capitalAmount;
    tempCapitalAmount = capitalAmount;
    std::cout<<std::endl;

    /*
    reads in the different stock reports and saves them to unordered map tempMapForProfit, saves the 
    different variables to the object stockInfom and inserts into priority heap (min heap)
    */
    getline(infile, line);
    std::cout<<"Day "<<dayCounter<< " Current balance $ " << std::fixed<<std::setprecision(2)<<capitalAmount<<std::endl;
    std::cout<<std::endl;
    while(!infile.eof() && (dayCounter <= numberOfDays)){
        std::stringstream ss(line); 
        while(getline(ss,numberInLine, ',')){
            stockType stockInfo;
            priceOfStock = std::stod(numberInLine);
            tempMapForProfit[backupNames[counter]]= priceOfStock;
            stockInfo.price = priceOfStock;
            stockInfo.name = backupNames[counter];
            mapDiv = stockMap[backupNames[counter]];
            stockInfo.dividend = mapDiv;
            putIntoPriorityQ.insert(stockInfo);
            counter++;
        }

        // based on inputLineCounter if it is odd then it is a day time price
        if(inputLineCounter % 2!= 0){

            int outOfBoundsCounter = backupNames.size();
            while(tempCapitalAmount > 0 && (outOfBoundsCounter > 0)){
                nameOfCompany = putIntoPriorityQ.getPriority().name;
                priceOfCompany = putIntoPriorityQ.getPriority().price;
                tempCapitalAmount = tempCapitalAmount - priceOfCompany;
                if(tempCapitalAmount < 0){
                    break;
                }
                tempMap[nameOfCompany]= priceOfCompany;
                tempNames.push_back(nameOfCompany);
                putIntoPriorityQ.deletePriority();
                outOfBoundsCounter--;
            }
            
            tempCapitalAmount = capitalAmount;
            for(int i = 0; i<tempNames.size();i++){
                std::cout<<"Buying one share of "<<tempNames[i]<<" valued at $ "
                         << std::fixed<<std::setprecision(2)<<tempMap[tempNames[i]]<< " per share"<<std::endl;
                amountBought[tempNames[i]]++;
            }

            while(!putIntoPriorityQ.isEmpty()){
                putIntoPriorityQ.deletePriority();
            }
        }
        // based on inputLineCounter if it is even then it is a end of day time price
        if(inputLineCounter % 2 == 0){
            double tempDayInt= 0.0, tempNightInt= 0.0, tempTotal= 0.0, runningTempTotal = 0.0;

            for(int i = 0; i< tempNames.size(); i++ ){
                tempNightInt = tempMapForProfit[tempNames[i]];
                tempDayInt = tempMap[tempNames[i]];
                tempTotal = tempNightInt - tempDayInt;
                runningTempTotal = runningTempTotal + tempTotal;
            }

            capitalAmount = runningTempTotal+capitalAmount;
            std::cout<<std::endl;
            dayCounter++;
            if(dayCounter <= numberOfDays){
                std::cout<<"Profit made today $ "<< std::fixed<<std::setprecision(2)<<runningTempTotal<<std::endl;
                std::cout<<std::endl;
                std::cout<<"Day "<<dayCounter<< " Current balance $ " << std::fixed<<std::setprecision(2) << capitalAmount<<std::endl;
                std::cout<<std::endl;
            }
            tempNames.clear();
            tempCapitalAmount = capitalAmount;

            while(!putIntoPriorityQ.isEmpty()){
                putIntoPriorityQ.deletePriority();
            }
            endTotal = runningTempTotal;
        }

        getline(infile, line);
        counter = 0;
        inputLineCounter++;
    }

    // outputs the profit made and the balance after n amount of days
    std::cout<<"Profit made today $ "<<std::fixed<<std::setprecision(2)<<endTotal<<std::endl;
    std::cout<<std::endl;
    std::cout<<"Balance after "<<numberOfDays<<" days $ "<<std::fixed<<std::setprecision(2)<<capitalAmount<<std::endl;
    double endDiv= 0.0, totalDiv = 0.0, tempTotalDiv = 0.0;
    int timesBought = 0;

    // calculates the dividends amount 
    for(int i = 0; i < backupNames.size(); i++){
        endDiv = stockMap[backupNames[i]];
        timesBought = amountBought[backupNames[i]];

        tempTotalDiv = endDiv * timesBought;

        totalDiv = tempTotalDiv +totalDiv;
        
    }
    
    std::cout<<"Amount in dividends $"<< std::fixed<<std::setprecision(2)<<totalDiv<<std::endl;
    return 0;

}


