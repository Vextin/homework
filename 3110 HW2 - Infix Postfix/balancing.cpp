#include "stack.hpp"

using namespace std;

int main(){
  freopen("input_balanced.txt", "r", stdin);
  string s,r;
  int line_counter;
  while(cin >> r){
    cin>>s;
    Stack<char> stack;
    bool isBalanced = true;
    bool solution;
    if(r[0] == 'Y' || r[0] == 'y'){
      solution = true;
    }else{
      solution = false;
    }

    // The input file is in the format "expected_solution expression"
    // so variable solution tells you whether 'expression' is balanced or not

    for(int i=0; i<s.length(); ++i){
        stack.push(s[i]);
        if(s[i] == ')') 
        {
          while(stack.size() != 0)
          {
            if(stack.pop() == '(') break;
            else if(stack.size() == 0) isBalanced = false; 
          }
            
        }
        if(s[i] == ']') 
        {
          while(stack.size() != 0)
          {
            if(stack.pop() == '[') break;
            else if(stack.size() == 0) isBalanced = false; 
          }
            
        }
        if(s[i] == '}') 
        {
          while(stack.size() != 0)
          {
            if(stack.pop() == '{') break;
            else if(stack.size() == 0) isBalanced = false; 
          }
            
        }
    }    
    if(stack.size() > 0) isBalanced = false;
    // checking if you stored in isBalanced the correct value
    if(isBalanced == solution){
      cout << "line " << line_counter << ": OK [" << solution << " " << isBalanced << "]" << endl;
    }else{
      cout << "line " << line_counter << ": ERROR [" << solution << " " << isBalanced << "]" << endl;
    }
    line_counter++;
  }
}
