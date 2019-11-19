#include "Document.h"
#include <iostream>
#include <algorithm>

// using namespace Document;
using namespace std;

Document::Document(): currentLine(-1), lastSearch(""){}
//  command redirection
int Document::cmd (string newStr){

  char optLetter = newStr[0];
  if(optLetter == 'p'){
    printCurrentLine();
  }
  if(optLetter == 'n'){
    printLineNumber();
  }
  if(optLetter == '%'){
    if(newStr[1] == 'p'){
      for(auto i : lines){
        cout<<i<<endl;
      }
    }
  }
  if(optLetter >= '0' && optLetter <= '9'){
    setCurrentLine(stoi(newStr));
  }
  if(optLetter == 'a'){
    writeAfterCurrentLine();
  }
  if(optLetter == 'i'){
    writeBeforeCurrentLine();
  }
  if(optLetter == 'c'){
    changeText();
  }
  if(optLetter == 'd'){
    deleteCurrentLine();
  }
  if(optLetter == '/'){
    if(newStr.size() == 1){
      currentLine++;
      searchAfterCurrentLine(lastSearch);
    }
    else{
      searchAfterCurrentLine(newStr.substr(1));
    }
  }
  if(optLetter == '?'){
    searchBack(newStr.substr(1));
  }
  if(optLetter == 's'){
    string temp = newStr.substr(2);
    int index = temp.find("/");
    string oldText = temp.substr(0,index);
    string newText = temp.substr(index+1);
    newText.pop_back();
    replaceStrings(oldText,newText);
  }
}
//  (p) print line
void Document::printCurrentLine (){
  cout<<lines[currentLine]<<endl;
}
//  (n) print line number --> TAB --> print line text
void Document::printLineNumber (){
  cout<<currentLine+1<<"  ";
  printCurrentLine();
}
//  (%p)  print all lines
void Document::printALL (){
  for(auto line : lines){
     cout<<line<<endl;
  }
}
//  (#number) set line and print
void Document::setCurrentLine (int newLine){
  currentLine = newLine-1;
  printCurrentLine();
}
//  (a) insert line after current line
void Document::writeAfterCurrentLine (){
  string text;
  int flag = 1;
  cin.ignore(1);
  if(lines.empty()){
    while(flag){
      getline(cin, text);
      cout<<text<<endl;
      flag = text.compare(".");
      if(flag){
        lines.push_back(text);
        currentLine++;
      }
    }
  }
  else{
    while(flag){
      getline(cin, text);
      cout<<text<<endl;
      flag = text.compare(".");
      if(flag){
        lines.insert(lines.begin()+currentLine + 1,text);
        currentLine++;
      }
    }
  }
}
//  (i) insert line before current line
void Document::writeBeforeCurrentLine (){
  string text;
  int flag = 1;
  cin.ignore(1);
  if(lines.empty()){
    while(flag){
      getline(cin, text);
      cout<<text<<endl;
      flag = text.compare(".");
      if(flag){
        lines.push_back(text);
        currentLine++;
      }
    }
  }
  else{
    while(flag){
      getline(cin, text);
      cout<<text<<endl;
      flag = text.compare(".");
      if(flag){
        lines.insert(lines.begin()+currentLine,text);
        currentLine++;
      }
    }
  }
}
//  (c) change current line with follow text
void Document::changeText(){
  writeBeforeCurrentLine();
  deleteCurrentLine();
}
//  (d) deletes current line
void Document::deleteCurrentLine(){
  lines.erase(lines.begin()+currentLine);
  if(currentLine != 0){
    currentLine--;
  }
}
/*  (/text) search for text, if found: print line number, line and setline.
            else: print error
    (/)     repeat last search  */
void Document::searchAfterCurrentLine (string text){
  int foundIndex = 0;
  auto lineIt = lines.begin()+currentLine;
  foundIndex = (*lineIt).find(text);
  int i;
  for(i = 0; i < lines.size() && foundIndex == string::npos; i++){
    lineIt++;
    if(lineIt == lines.end()){
      lineIt = lines.begin();
    }
    foundIndex = (*lineIt).find(text);
  }
  if (foundIndex == string::npos){
      pError();
  }
  else{
    currentLine = (currentLine + i)%(lines.size());
    printCurrentLine();
  }

}

/*  (?text) search backwards for text     */
void Document::searchBack(string text){
  int foundIndex = 0;
  auto lineIt = lines.rbegin()+(lines.size()-currentLine-1);
  foundIndex = (*lineIt).find(text);
  int i;
  for(i = 0; i < lines.size() && foundIndex == string::npos; i++){
    lineIt++;
    if(lineIt == lines.rend()){
      lineIt = lines.rbegin();
    }
    foundIndex = (*lineIt).find(text);
  }
  if (foundIndex == string::npos){
      pError();
  }
  else{
    currentLine = (currentLine - i)%(lines.size()-1);
    // cout<<currentLine<<endl;
    printCurrentLine();
  }
}
/*  (s/old/new) replace 'old' text with 'new' text    */
void Document::replaceStrings(string old, string replacement){
  // cout<<old<<","<<old.size()<<"  "<<replacement<<endl;
  int found = lines[currentLine].find(old);
  string tempStr = "";
  if (found == string::npos){
    pError();
  }
  else{
    lines[currentLine].replace(found, old.size(), replacement);
    // printCurrentLine();
  }
}
/*  print '?'  */
void Document::pError(){cout<<'?'<<endl;}
