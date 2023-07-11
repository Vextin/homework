#include "stack.hpp"

using namespace std;

bool isOperand(char c){
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int main(){
  freopen("input_postfixEval.txt", "r", stdin);
  string s;
  int solution;
  int line_counter = 0;
  while(cin>>solution){
    cin>>s;
    Stack<int> stack;
    
    // The input file is in the format "expected_solution postfix_expression"

    // We assume that all operands in the input are one digit (so they range from 0 to 9)
    for(int i=0; i<s.length(); ++i){
      int in = s[i] - '0';
      if(in >= 0 && in <= 9)
      {
        stack.push(in);
        
      } else
      {
        int b = stack.pop();
        int a = stack.pop();
        if(s[i] == '+')
        {
          stack.push(a+b);
        }
        else if(s[i] == '-')
        {
          stack.push(a-b);
        }
        else if(s[i] == '*')
        {
          stack.push(a*b);
        }
        else if(s[i] == '/')
        {
          stack.push(a/b);
        }
        else if(s[i] == '^')
        {
          stack.push(pow(a, b));
        }
      }
    }

    // Checking whether the value you calculated is correct ...
    int value = stack.pop();

    if(solution == value){
      cout << "line " << line_counter << ": OK [" << solution << " " << value << "]" << endl;
    }else{
      cout << "line " << line_counter << ": ERROR [" << solution << " " << value << "]" << endl;
    }
    line_counter++; 
  }
}
