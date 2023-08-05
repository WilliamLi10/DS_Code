#include<iostream>
#include<fstream>
#include<string>


/*#include <stdio.h>

int main(void)
{
   FILE* inFile;
   FILE* outFile;
   
   char fname[50];
   
   char header1[50];
   char header2[50];
   int weight1;
   int weight2;
   
   printf("Provide an input file name: \n");
   scanf("%s", fname);
   
   inFile = fopen(fname, "r");
   if (inFile == NULL) {
      printf("Could not open file %s.\n", fname);
      return -1; // -1 indicates error
   }
   
   outFile = fopen("out.txt", "w");
   if (outFile == NULL) {
      printf("Could not open file out.txt.\n");
      fclose(inFile);
      return -1; // -1 indicates error
   }  
   
   // read and write header first
   fscanf(inFile, "%s %s", header1, header2);
   fprintf(outFile, "%s %s\n", header2, header1);
   
   while (!feof(inFile)) {
      fscanf(inFile, "%d %d", &weight1, &weight2);
      fprintf(outFile, "%d %d\n", weight2, weight1);
   }
   
   fclose(inFile);
   fclose(outFile);
   
   return 0;
}*/

int main()
{
    std::ifstream inFile;
    std::ofstream outFile;
    std::string FileName;
    std::string header1;
    std::string header2;
    int weight1;
    int weight2;
    std::cout << "Provide an input file name: " << std::endl;
    std::cin >> FileName;
    FileName.open(FileName);
    if (!inFile)
    {
        std::cout << "Could not open file " << FileName << std::endl;
        return 1;
    }
    outFile.open("out.txt");
    if (!outFile)
    {
        std::cout << "Could not open file out.txt" << std::endl;
        return 1;
    }
    inFile >> header1 >> header2;
    outFile << header1 << " " << header2 << std::endl;
    while (inFile >> weight1 >> weight2)
    {
        outFile << weight1 << " " << weight2 << std::endl;
    }
    inFile.close();
    outFile.close();


    return 0;
}