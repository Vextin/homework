/*
*   Work of Austin Carlin  |  ajc0325  |  austincarlin@my.unt.edu
*   Check readme.txt for info
*/
#include "hw4.h"
#define DISPLAY 1
int main(int argc, char* argv[])
{
    //Open the input file, defaulting to "input.txt" if not provided
    std::string filename;
    std::fstream file;
    if(argc > 1)
        filename = std::string(argv[1]);
    else 
        filename = "input.txt";
    file.open(filename);

    //Initialize variables
    std::string line = "";
    int node = 0;
    int dim = 0;
    std::vector<std::vector<int>> matrix;
    highestNum = 0;
    int num = 0;
    
    //Get the highest node - used to determine size of matrix
    while(file >> num)
    {
        if(num > highestNum)
            highestNum = num;
    }
    //Create matrix
    while(matrix.size() < highestNum) matrix.push_back(std::vector<int>());

    //Create each sub-vector
    for(int i = 0; i < highestNum; i++)
    {
        while(matrix[i].size() < highestNum) matrix[i].push_back(0);
    }

    //Reopen the file now that setup is done. 
    file.close();
    file.open(filename);
    while(std::getline(file, line))
    {   
        //Turn each line into a stream so we can use extraction operator to pull out each token
        std::stringstream ss(line);
        ss >> node;
        int connectedNode = 0;
        //big brain time
        while(ss >> connectedNode)
        {
            //Set the element, but also its reflection for completeness' sake
            matrix[node-1][connectedNode-1] = 1;
            matrix[connectedNode-1][node-1] = 1;
        }

    }
    //Display output
    if(DISPLAY) display(matrix);
    
    printf("Breadth-First Search:\n");
    bfs(matrix);

    printf("\nDepth First Search:\n");
    
    bool visited[matrix.size()] = {true};
    dfs(0, visited, matrix);
    printf("\n");
}

void display(std::vector<std::vector<int>> matrix)
{
    std::cout << "Adjacency matrix:\n";

    //Print x-axis labels
    for(int x = 0; x <= matrix.size(); x++)
        if(x!= 0)
        {
            //Ternary used to add less space for double-digit numbers
            x > 9 ? std::cout << x << " " : std::cout << x << "  "; 
        }
        else std::cout << "   ";
    std::cout << std::endl;

    for(int y = 0; y < matrix.size(); y++)
    {
        //Print y-axis labels, ternary for double digits again
        y > 8 ? std::cout << y+1 << " " : std::cout << y+1 << "  ";

        //I don't think this does anything anymore but im too scared to remove it
        for(int x = 0; x < matrix.size(); x++){
            if(x >= matrix[y].size()) 
                std::cout << matrix[x][y] << "  ";
            else    //Print the 1/0, or a star if it's along the diagonal
                x == y ? std::cout << "*  " : std::cout << matrix[y][x] << "  ";
        }
        std::cout << std::endl;
    }

    printf("\n");
}

void bfs(std::vector<std::vector<int>> matrix)
{
    bool visited[matrix.size()] = {true};
    for(int i=0;i<matrix.size();i++) visited[i] = false;
    int node = 0;
    visited[0] = true;
    //We are always gonna start at 1
    printf("1");
    for(node = 0; node < matrix.size(); node++)
    {
        //If there is no edge to this node, we don't care about it
        if(!visited[node]) continue; 
        for(int i = 0; i < matrix.size(); i++)
        {
            //if there is an edge to a node we haven't visited,
            if(matrix[node][i] == 1 && !visited[i])
            {
                //Visit it! 
                visited[i] = true;
                printf(", %d",i+1);
            }
        }
    }
}

void dfs(int start, bool visited[], std::vector<std::vector<int>> matrix)
{
    //recursion time baybeeee
    //If this is node 1, print the 1
    if(start == 0) printf("1");
    for(int i = 0; i < matrix.size(); i++)
    {
        //Waiting for the smallest node with an edge
        if(matrix[start][i])
        {
            //If we haven't visited it,
            if(!visited[i])
            {
                //Visit, then search again starting from here.
                printf(", %d", i+1);
                visited[i] = true;
                dfs(i, visited, matrix);
            }
        }
    }
}