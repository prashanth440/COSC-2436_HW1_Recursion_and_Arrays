#include <iostream>
#include <fstream>
#include <vector>
#include "ArgumentManager.h"
using namespace std;

struct records
{
    string name, age, dept;
};


void searchData(string text, records data[], int size, int start, int end, int level, string outFile)
{
    ofstream output;
    output.open(outFile, ios::app);
    int i;
    
    if(size == 1)
    {
        for(i = start; i <= end; i++)
        {
            bool foundName, foundAge, foundDept;
            foundName = false;
            foundAge = false;
            foundDept = false;
            
            
            
            if((data[i].name.find(text) >= 0) && data[i].name.find(text) < 100)
            {
                foundName = true;
            }
            else if((data[i].age.find(text) >= 0) && data[i].age.find(text) < 100)
            {
                foundAge = true;
            }
            else if((data[i].dept.find(text) >= 0) && data[i].dept.find(text) < 100)
            {
                foundDept = true;
            }
            
            if(text == "")
            {
                return;
            }
            
            if(foundName == true)
            {
                cout << "Level " << level << ": {";
                output << "Level " << level << ": {";
                    cout << data[i].name;
                    output << data[i].name;
                
                cout << ",";
                output << ",";
                
                    cout << data[i].age;
                    output << data[i].age;
                
                cout << ",";
                output << ",";
                
                    cout << data[i].dept;
                    output << data[i].dept;
                
                cout << "}";
                cout << "\n";
                output << "}";
                output << "\n";
            }
            else if(foundAge == true)
            {
                cout << "Level " << level << ": {";
                output << "Level " << level << ": {";
                    cout << data[i].name;
                    output << data[i].name;
                
                cout << ",";
                output << ",";
                
                    cout << data[i].age;
                    output << data[i].age;
                
                cout << ",";
                output << ",";
                
                    cout << data[i].dept;
                    output << data[i].dept;
                
                cout << "}";
                cout << "\n";
                output << "}";
                output << "\n";
            }
            else if(foundDept == true)
            {
                cout << "Level " << level << ": {";
                output << "Level " << level << ": {";
                    cout << data[i].name;
                    output << data[i].name;
                
                cout << ",";
                output << ",";
                
                    cout << data[i].age;
                    output << data[i].age;
                
                cout << ",";
                output << ",";
                
                    cout << data[i].dept;
                    output << data[i].dept;
                
                cout << "}";
                cout << "\n";
                output << "}";
                output << "\n";
            }
            foundName = false;
            foundAge = false;
            foundDept = false;
        }
    }
    else if((size % 2) == 0) // Even number of elements
    {
        level++;
        searchData(text, data, size/2, start, (start + end)/2, level, outFile);
        searchData(text, data, size/2, ((start + end)/2) + 1, end, level, outFile);
    }
    else // Odd number of elements
    {
        level++;
        searchData(text, data, ((size/2) + 1), start, (start + end)/2, level, outFile);
        searchData(text, data, (size/2), ((start+end)/2) + 1, end, level, outFile);
    }
    output.close();
}






int main(int argc, char * argv[])
{
    if (argc < 2)
    {
        return -1;
    }
      
    ArgumentManager am(argc, argv);
    std::string infilename = am.get("input");
    std::string command_File = am.get("command");
    std::string outfilename = am.get("output");
    
    
    ifstream input, commandFile;
    input.open(infilename);
    commandFile.open(command_File);
    
    
    
    
    
    
    
    
    records *data = new records[10000];
    vector<char> line;
    char a;
    int j, k, numRecords;
    
    // Read data from file
    while(!input.eof())
    {
        input >> a;
        if(a != ' ' && a != '\r' && a != '\t' && a != '\n')
        {
            line.push_back(a);
        }
    }
    
    // Transfer data to the structure
    j = 0;
    k = 0;
    numRecords = 0;
    for(auto i = line.begin(); i != line.end(); ++i)
    {
        if(*i == '{' && *(i + 1) == 'n' && *(i + 2) == 'a' && *(i + 3) == 'm' && *(i + 4) == 'e')
        {
            i++;
            while(*i != ',')
            {
                data[j].name.push_back(tolower(*i));
                ++i;
            }
        }
        else if(*i == 'a' && *(i + 1) == 'g' && *(i + 2) == 'e')
        {
            while(*i != ',')
            {
                data[j].age.push_back(tolower(*i));
                ++i;
            }
        }
        else if(*i == 'd' && *(i + 1) == 'e' && *(i + 2) == 'p' && *(i + 3) == 't')
        {
            while(*i != '}')
            {
                data[j].dept.push_back(tolower(*i));
                ++i;
            }
        }
        else if(*i == ',' && *(i + 1) == '{')
        {
            j++;
            numRecords++;
        }
        else if(*i == '}' && *(i + 1) == '}')
        {
            break;
        }
    }
    numRecords++;
    
    
    // Read text to be searched from the command file
    
    
    string textToSearch;
    getline(commandFile, textToSearch);
    
    for(j = 0; j < (int) textToSearch.length(); j++)
    {
        textToSearch[j] = tolower(textToSearch[j]);
    }
    
    
    int start, end, level;
    start = 0;
    end = numRecords - 1;
    level = 0;
    
    searchData(textToSearch, data, numRecords, start, end, level, outfilename);
    
    input.close();
    commandFile.close();
}
