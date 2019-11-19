#include "Editor.h"
// #include "Document.h"
#include <iostream>

using namespace std;

Editor::Editor():doc(){}

void Editor::loop(){
  string text;
  while(text.compare("Q")){
    doc.cmd(text);
    cin>>text;
    cout<<text<<endl;
  }
}
