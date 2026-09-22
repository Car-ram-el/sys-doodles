#include <bits/stdc++.h>
#include <fstream>

using namespace std;

struct allInfo {
  int wordCount, lineCount, charCount;
};

bool isWordDelim (wchar_t &c) {return iswspace(c);}

allInfo getAllin1Itr(string s) {
  int wordCount=0, lineCount=0, charCount=0;
  wifstream f(s); // wide-char input filestream
  f.imbue(locale("")); // set locale- en_US.UTF-8

  wchar_t c; bool isWordStart=false;
  while (f.get(c)) {
    charCount++;

    if (c == '\n') lineCount++;
    else if (!(isWordDelim(c) ^ isWordStart)) {
      if (isWordStart) isWordStart = false; 
      else isWordStart = true, wordCount++;
    }
  }

  f.close();

  allInfo allInfo1;
  allInfo1.wordCount=wordCount, allInfo1.lineCount=lineCount, allInfo1.charCount=charCount;

  return allInfo1;
}

int getSize(string s) {
  ifstream f(s);
  streampos begin, end;
  f.seekg(0,ios::beg);
  begin = f.tellg();
  f.seekg(0,ios::end);
  end = f.tellg();
  f.close();
  return end-begin;
}

int main(int argc, char* argv[]) {
  if (argc==3) { // ./main -<tags> <filepath>
    string s = string(argv[1]);
    int flagsCount = s.size(); // includes - prefix

    wifstream inpFile(argv[2]); // https://cplusplus.com/doc/tutorial/files/
    allInfo res=getAllin1Itr(argv[2]);
    int fsize=getSize(argv[2]);
    cout << fsize << " B\t" << res.charCount << " chars\t" << res.wordCount << " words\t" << res.lineCount << " lines";
  cout << endl;
}
}
