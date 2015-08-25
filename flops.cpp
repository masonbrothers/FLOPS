#include <ctime>
#include <cmath>
//#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct prefix
{
	string smallString;
	string largeString;
	double mag;
};

typedef unsigned long long int biggestIntSize;

prefix getPrefix(const double &number, const bool &notEngg);
double getAverage(const vector<double> &input);
double getSum(const vector<double> &input);
double getVariance(const vector<double> &input);
double getStanDev(const vector<double> &input);
string toHHMMSS(const double &seconds);
string removeWhiteSpace(const string &input);

int main()
{

	biggestIntSize cycles;
	biggestIntSize trials;

	const unsigned int recomendedCycles = 4294967295;//Must be smaller that 2^32-1 = 4294967295	1000000000


	const unsigned int recomendedTrials = 5;

	int byteSize = sizeof(biggestIntSize);
	biggestIntSize biggestNumber = pow(2, byteSize * 8);
	//const unsigned int recomendedTrials = 5;
	//const unsigned int maxCycles = 4294967295;
	//const unsigned int maxTrials = 4294967295;
	biggestIntSize maxCycles = biggestNumber;
	biggestIntSize maxTrials = biggestNumber;

	//cout << byteSize << "\t" << maxCycles << endl << endl;





	const bool stayOpen = true;
	cout << "(C) Copyright 2014. Mason Brothers. All Rights Reserved." << endl << endl << "This program calculates your computer's FLOPS." << endl << "FLOPS is Floating-point Operations Per Second." << endl << "This may not be accurate and no warranty is given. Possible errors can come as this program only calculates one processor. If your computer is very fast, an error may come showing the FLOPS at infinity. If this happens, none of the data is accurate. Depending on your computers speed, this program can take seconds, minutes or hours to run." << endl << endl;
	cout << "Would you like to use the recomended settings of " << recomendedCycles << " cycles with " << recomendedTrials << " Trials? Please enter \'Y\' or \'N\': ";
	string check;
	bool inputError = 0;
	cin >> check;
	check = removeWhiteSpace(check);
	while (!(check == "y" || check == "n" || check == "N" || check == "Y") || cin.fail())
	{
		cout << endl;
		cout << "Sorry! You did not enter Y or N." << endl << "Please enter \'Y\' if you would like to use the recomended settings of " << recomendedCycles << " cycles with " << recomendedTrials << " Trials." << endl << "Enter \'N\' if you would like to choose your own settings." << endl << "Please enter \'Y\' or \'N\': ";
		cin.clear();
		cin.ignore();
		cin >> check;
		check = removeWhiteSpace(check);
	}
	if (check == "y" || check == "Y")
	{
		cycles = recomendedCycles;
		trials = recomendedTrials;
	}
	else
	{
		cout << "You are editing the number of cycles and trials! Be careful! Small values may leave bad data. Large values may take a long time to compute!" << endl << endl;
		cout << "The number of cycles should be above 1 and below " << maxCycles << endl << "Please enter the number of cycles: ";
		cin.clear();
		cin >> cycles;

		/*
		inputError = false;
		if (cin.fail() == true)
		{
			inputError = true;
			cin.clear();
		}
		*/

		while (cycles < 1 || cycles > maxCycles || cin.fail())
		{
			cout << endl;
			cout << "Sorry! That value is not valid." << endl << "Please enter a number between 1 and " << maxCycles << " for the number of cycles: ";
			cin.clear();
			cin.ignore();
			cin >> cycles;
			//check = removeWhiteSpace(check);
		}
		cout << endl;
		cout << "The number of trials should be above 1 and below " << maxTrials << endl << "Please enter the number of trials: ";
		cin >> trials;
		while (trials < 1 || trials > maxTrials || cin.fail())
		{
			cout << endl;
			cout << "Sorry! That value is not valid." << endl << "Please enter a number between 1 and " << maxCycles << " for the number of trials: ";
			cin.clear();
			cin.ignore();
			cin >> trials;
			//check = removeWhiteSpace(check);
		}
	}




	cout << endl << endl;
	cout << "This computer will now attempt " << trials << " trials of " << cycles << " cycles." << endl;
	vector<double> clickDelays;

	for (biggestIntSize j = 0; j < trials; j++)
	{
		cout << "On trial " << j + 1 << "... ";
		double firstTime = clock();
		//chrono::high_resolution_clock::time_point firstTime  = chrono::high_resolution_clock::now();
		for (biggestIntSize i = 0; i < cycles; i++);
		//chrono::high_resolution_clock::time_point secondTime = chrono::high_resolution_clock::now();
		double secondTime = clock();
		//chrono::duration<double> timeDiff = chrono::duration_cast<duration<double> >(secondTime - firstTime);
		double Delay = secondTime - firstTime;
		clickDelays.push_back(Delay);
		cout << "Trial " << j + 1 << " done. Took " << Delay << "s." << endl;
	}

	double clickDelay = getAverage(clickDelays);
	//double clickDelay = secondTime - firstTime;
	double timeDelay = (double)clickDelay / CLOCKS_PER_SEC;
	double flops = cycles / timeDelay;
	double inverseFlops = timeDelay / cycles;
	prefix flopPrefix = getPrefix(flops, 0);
	prefix inverseFlopPrefix = getPrefix(inverseFlops, 0);
	double sciFlops = flops / flopPrefix.mag;
	double sciInverseFlops = inverseFlops / inverseFlopPrefix.mag;
	double error = ((double)2 / clickDelay + (double)1 / CLOCKS_PER_SEC) + (double)1 / cycles;
	double errorFlops = error * flops;
	double errorSciFlops = error * sciFlops;
	double errorInverseFlops = error * inverseFlops;
	double errorSciInverseFlops = error * sciInverseFlops;
	double variance = getVariance(clickDelays);
	double stanDev = getStanDev(clickDelays);

	cout << endl; //Match

	ofstream fout;
	fout.open("FLOPS.txt");
	if (fout.fail())
	{
		cout << "Could not make a save file." << endl << endl;
	}
	fout << "(C) Copyright 2014. Mason Brothers. All Rights Reserved." << endl << endl << "This program calculates your computer's FLOPS." << endl << "FLOPS is Floating-point Operations Per Second." << endl << "This may not be accurate and no warranty is given. Possible errors can come as this program only calculates one processor. If your computer is very fast, an error may come showing the FLOPS at infinity. If this happens, none of the data is accurate. Depending on your computers speed, this program can take seconds, minutes or hours to run." << endl << endl;

	fout << endl; //Match

	cout << "FLOPS:\t\t" << sciFlops << "+/-" << errorSciFlops << flopPrefix.smallString.c_str() << "FLOPS\t" << "(" << flops << "+/-" << errorFlops << "FLOPS)" << endl;
	fout << "FLOPS:\t\t" << sciFlops << "+/-" << errorSciFlops << flopPrefix.smallString.c_str() << "FLOPS\t" << "(" << flops << "+/-" << errorFlops << "FLOPS)" << endl;

	cout << "Inverse FLOPS:\t" << sciInverseFlops << "+/-" << errorSciInverseFlops << inverseFlopPrefix.smallString.c_str() << "Hz\t" << "(" << inverseFlops << "+/-" << errorInverseFlops << "Hz)" << endl;
	fout << "Inverse FLOPS:\t" << sciInverseFlops << "+/-" << errorSciInverseFlops << inverseFlopPrefix.smallString.c_str() << "Hz\t" << "(" << inverseFlops << "+/-" << errorInverseFlops << "Hz)" << endl;

	cout << "Trials:\t\t" << trials << endl;
	fout << "Trials:\t\t" << trials << endl;

	cout << "Error:\t\t" << error * 100 << "%" << endl;
	fout << "Error:\t\t" << error * 100 << "%" << endl;

	cout << "Variance:\t" << variance / getPrefix(variance, 0).mag << getPrefix(variance, 0).smallString << "FLOPS^2\t(" << variance << "FLOPS^2)" << endl;
	cout << "Variance:\t" << variance / getPrefix(variance, 0).mag << getPrefix(variance, 0).smallString << "FLOPS^2\t(" << variance << "FLOPS^2)" << endl;

	cout << "StandardDev:\t" << stanDev / getPrefix(stanDev, 0).mag << getPrefix(stanDev, 0).smallString << "FLOPS\t\t(" << stanDev << "FLOPS)" << endl;
	fout << "StandardDev:\t" << stanDev / getPrefix(stanDev, 0).mag << getPrefix(stanDev, 0).smallString << "FLOPS\t\t(" << stanDev << "FLOPS)" << endl;

	cout << "Time Delay:\t" << timeDelay << "s" << endl << "ClocksPerSec:\t" << CLOCKS_PER_SEC << endl;
	fout << "Time Delay:\t" << timeDelay << "s" << endl << "ClocksPerSec:\t" << CLOCKS_PER_SEC << endl;

	cout << "Cycles:\t\t" << cycles << endl;
	fout << "Cycles:\t\t" << cycles << endl;

	cout << "Time Elapsed:\t" << getSum(clickDelays) << "s" << endl;
	fout << "Time Elapsed:\t" << getSum(clickDelays) << "s" << endl;

	cout << "MeanTimPerTry:\t" << getAverage(clickDelays) << "s" << endl;
	fout << "MeanTimPerTry:\t" << getAverage(clickDelays) << "s" << endl;

	cout << endl;
	fout << endl;

	for (biggestIntSize i = 0; i < clickDelays.size(); i++)
	{
		cout << "Trial " << i + 1 << " took:\t" << clickDelays.at(i) << endl;
		fout << "Trial " << i + 1 << " took:\t" << clickDelays.at(i) << endl;
	}


	if (stayOpen)
	{
		cout << endl << endl << "Return any text to close." << endl;
		int tmp;
		cin >> tmp;
	}
	//cout << "FLOPS/s or " << timeDelay << "s/FLOPS";
	return 0;
}

double getVariance(const vector<double> &input)
{
	double sum = 0;
	for (biggestIntSize i = 0; i < input.size(); i++)
	{
		sum += pow(input.at(i),2);
	}
	double variance = sum / (input.size() - 1);
	return variance;
}

double getStanDev(const vector<double> &input)
{
	return sqrt(getVariance(input));
}


double getAverage(const vector<double> &input)
{
	double sum = 0;
	for (biggestIntSize i = 0; i < input.size(); i++)
	{
		sum += input.at(i);
	}
	double average = sum / input.size();
	return average;
}

double getSum(const vector<double> &input)
{
	double sum = 0;
	for (biggestIntSize i = 0; i < input.size(); i++)
	{
		sum += input.at(i);
	}
	return sum;
}

string removeWhiteSpace(const string &input)
{
	string output;
	for (int i = 0; i < input.size(); i++)
	{
		if (!(input.at(i) == '\t' || input.at(i) == '\n' || input.at(i) == '\f' || input.at(i) == '\r'))
		{
			output.push_back(input.at(i));
		}
	}
	return output;
}

prefix getPrefix(const double &number, const bool &notEngg)
{
	string smallString, largeString;
	double mag;
	if (number >= 1e24)
	{
		smallString = "Y";
		largeString = "yotta";
		mag = 1e24;
	}
	else if (number >= 1e21)
	{
		smallString = "Z";
		largeString = "zetta";
		mag = 1e21;
	}
	else if (number >= 1e18)
	{
		smallString = "E";
		largeString = "exa";
		mag = 1e18;
	}
	else if (number >= 1e15)
	{
		smallString = "P";
		largeString = "peta";
		mag = 1e15;
	}
	else if (number >= 1e12)
	{
		smallString = "T";
		largeString = "tera";
		mag = 1e12;
	}
	else if (number >= 1e9)
	{
		smallString = "G";
		largeString = "giga";
		mag = 1e9;
	}
	else if (number >= 1e6)
	{
		smallString = "M";
		largeString = "mega";
		mag = 1e6;
	}
	else if (number >= 1e3)
	{
		smallString = "k";
		largeString = "kilo";
		mag = 1e3;
	}
	else if (number >= 1e2 && notEngg == true)
	{
		smallString = "h";
		largeString = "hecto";
		mag = 1e2;
	}
	else if (number >= 1e1 && notEngg == true)
	{
		smallString = "da";
		largeString = "deca";
		mag = 1e1;
	}
	else if (number >= 1 && notEngg == true)
	{
		smallString = "";
		largeString = "";
		mag = 1;
	}
	else if (number >= 1e-1 && notEngg == true)
	{
		smallString = "d";
		largeString = "deci";
		mag = 1e-1;
	}
	else if (number >= 1e-2 && notEngg == true)
	{
		smallString = "c";
		largeString = "centi";
		mag = 1e-2;
	}
	else if (number >= 1e-3)
	{
		smallString = "m";
		largeString = "milli";
		mag = 1e-3;
	}
	else if (number >= 1e-6)
	{
		//ASCII 230
		smallString.push_back(230);
		//smallString = "u";
		largeString = "micro";
		mag = 1e-6;
	}
	else if (number >= 1e-9)
	{
		smallString = "n";
		largeString = "nano";
		mag = 1e-9;
	}
	else if (number >= 1e-12)
	{
		smallString = "p";
		largeString = "pico";
		mag = 1e-12;
	}
	else if (number >= 1e-15)
	{
		smallString = "f";
		largeString = "femto";
		mag = 1e-15;
	}
	else if (number >= 1e-18)
	{
		smallString = "a";
		largeString = "atto";
		mag = 1e-18;
	}
	else if (number >= 1e-21)
	{
		smallString = "z";
		largeString = "zepto";
		mag = 1e-21;
	}
	else if (number >= 1e-24)
	{
		smallString = "y";
		largeString = "yocto";
		mag = 1e-24;
	}
	else
	{
		smallString = "";
		largeString = "";
		mag = 1;
	}
	prefix pre;
	pre.largeString = largeString;
	pre.smallString = smallString;
	pre.mag = mag;
	return pre;
}
/*
string toHHMMSS(const double &seconds)
{
	int hours;
	int mins;
	hours = seconds / 3600;
	mins = (seconds - hours * 3600) / 60;
	string output;

	output.append(to_string(hours));
	output.append(":");
	output.append(to_string(mins));
	output.append(":");
	output.append(to_string(seconds));
	return output;
}
*/
