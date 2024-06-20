#include<bits/stdc++.h>
#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
using namespace std;


stack<char>st;
set<string> constant , keyword,header_string,iden_string,fun;
set<char>arith, pun_string,parenthesis;
string token_p;

int keyword_library(char temp[]);
int const_library(char tem[]);
int main()
{
      char ch, temp[40], arithmetic_operator[] = "=+%*/-" , pun[]=";:,";
      FILE *file_pointer;
      int count, x = 0;
      file_pointer = fopen("demo.txt","r");
      if(file_pointer == NULL)
      {
            printf("file not found.\n");
            exit(0);
      }
      int comment_flag=0;
      while((ch = fgetc(file_pointer)) != EOF)
      {
            if (comment_flag==1 && ch!='\n')
            continue;
            else comment_flag=0;

            if(ch=='/')
            {
              ch = fgetc(file_pointer);
              if(ch=='/')
                comment_flag=1;
              else
              arith.insert('/');
            }

            count = 0;
            while(count < 6)
            {
                  if(ch == arithmetic_operator[count])
                  {
                       arith.insert(ch);
                       iden_string.insert(temp);
                       temp[x] = '\0';
                       x=0;
                       token_p=temp;
                       break;
                  }
                  count = count + 1;
            }

            count = 0 ;
            while(count < 3)
            {
                if(ch == pun[count])
               {
                   pun_string.insert(ch);

               }
               count = count + 1 ;

            }
            if(isalnum(ch))
            {
                  temp[x++] = ch;
            }
            else if((ch == '\n' || ch == ' ') && (x != 0))
            {
                  temp[x] = '\0';
                  x = 0;
                  token_p=temp;
                  if(keyword_library(temp) == 1)
                  {
                       keyword.insert(temp);

                  }

                  else if(const_library(temp) == 1)
                  {
                      constant.insert(temp);

                  }
                  else
                  {
                      int len = 0;
                      while (temp[len] != '\0') {
                          len++;
                      }
                      int ok = 0 ;
                      string in = "include";
                      for (int i = 0 ; i < 7 ; i++) {
                          if (temp[i] == in[i])ok++;
                      }
                      if (ok == 7 && temp[len - 1] == 'h') {
                          string ans = "";
                          for (int i = 7 ; i < len - 1 ; i++) {
                              ans += temp[i];
                          }
                          ans += ".h";
                          header_string.insert(ans);
                      }
                      else
                          iden_string.insert(temp);
                  }
            }
            else if (ch =='(' || ch==')' || ch=='{'|| ch=='}' || ch =='[' || ch == ']')
            {
                if(ch=='(' && (token_p=="int" || token_p=="void" || token_p=="float" || token_p=="double") )
                {
                    temp[x]='\0';
                    fun.insert(temp);
                }
                x=0;
                parenthesis.insert(ch);

            }

      }
      cout<<"\nIdentifier ("<<iden_string.size()<<") : ";
      for(auto i : iden_string)cout<<i << " ";
      cout <<'\n';
      cout<< "puncuation ("<<pun_string.size()<<") : ";
      for(auto i: pun_string)cout << i << ' ';
      cout<<"\n";
      cout<<"constant ("<<constant.size()<<") : ";
      for(auto i : constant)cout<<i << " ";
      cout << "\n";
      cout<<"parenthesis ("<<parenthesis.size()<<") : ";
      for(auto i : parenthesis)cout<<i << " ";
      cout << "\n";
      cout<<"Arithmatic ("<<arith.size()<<"): ";
      for(auto i : arith)cout<<i << " ";
      cout << "\n";
      cout<<"keyword ("<<keyword.size()<<") : ";
      for(auto i : keyword)cout<<i << " ";
      cout <<'\n';
      cout<<"Header ("<<header_string.size()<<") : ";
      for(auto i : header_string)cout<<i << " ";
      cout <<'\n';
      cout<<"Functions ("<<fun.size()<<") : ";
      for(auto i : fun)cout<<i << " ";
      cout <<'\n';
      fclose(file_pointer);
      return 0;
}

int keyword_library(char temp[])
{
      int count = 0, flag = 0;
      char keywords[32][12] = {"return", "continue", "extern", "static", "long", "signed",
                               "switch", "char", "else", "unsigned", "if", "struct",
                               "union", "goto", "while", "float", "enum", "sizeof", "double", "volatile",
                               "const", "case", "for", "break", "void", "register", "int",
                               "do", "default", "short", "typedef", "auto"};
      while(count <= 31)
      {
            if(strcmp(keywords[count], temp) == 0)
            {
                  flag = 1;
                  break;
            }
            count = count + 1;
      }
      return (flag);
}

int const_library(char temp[]){
    int count = 0 ,i = 0 ,  flag = 0 ;
    char constant []= {'0','1','2','3','4','5','6','7','8','9'};
    int size = 0 ;
    while(temp[size]!='\0'){
        size++;
    }
    while(temp[i]!='\0'){
            count = 0 ;
        while(count < 10){
            if(constant[count] == temp[i]){
                flag++;

                break;
            }
            count += 1 ;
        }
        i++;
    }
    if(flag == size)
        return 1 ;
    return 0 ;
}
