#include <string>
#include <vector>

using namespace std;
/*
  @lines: vector of strings, each index = line
  @currentLine: holds current line number (like pointer)
  @lastSearch: holds last search request
 */
class Document{
  public:
    //initiator
    Document();
    //decision maker
    int cmd(string);


  private:
    vector<string> lines;
    int currentLine;
    string lastSearch;

    //cmds:
    /* print line */
    void printCurrentLine ();
    /* print line number */
    void printLineNumber ();
    /* print all lines */
    void printALL ();
    /* set line to @number */
    void setCurrentLine (int);
    /* appeand after current line */
    void writeAfterCurrentLine ();
    /* appeand before current line */
    void writeBeforeCurrentLine ();
    /* delete line */
    void deleteCurrentLine();
    /* changes current line to new text */
    void changeText();
    /* search */
    void searchAfterCurrentLine (string);
    /* search back */
    void searchBack(string);
    /* replace @old for @new */
    void replaceStrings(string, string);
    /* print error ("?") */
    void pError();
};
