#include <bits/stdc++.h>
#include <fstream>

using namespace std;

struct allInfo {
  int wordCount, lineCount, charCount;
};

bool isWordDelim (wchar_t &c) {return iswspace(c);}

allInfo getAllin1Itr(string s) {
  int wordCount=0, lineCount=0, charCount=0;
  wifstream f(s); // wide-char input filestream- https://cplusplus.com/doc/tutorial/files/
  if (!f.is_open()) cout << "Error opening file";
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

void setFlags(string s, set<char> &flags) {
  int n = s.size();
  for(int i=0; i<n; ++i) if (s[i]=='c' || s[i]=='m' || s[i]=='w' || s[i]=='l') flags.insert(s[i]);
  return;
}

void showInfo(allInfo &res, set<char> &flags) {
  for (auto &f : flags) {
    switch (f) {
      case 'm':
        cout << res.charCount << " chars\t";
        break;
      case 'w':
        cout << res.wordCount << " words\t";
        break;
      case 'l':
        cout << res.lineCount << " lines\t";
        break;
    }
  }
}

bool getFlag(set<char> &flags, char c) {
  return flags.find(c) != flags.end();
}

ifstream stdFileInp (string name) {
  ofstream outFile(name);
  outFile << cin.rdbuf();
  outFile.close();
  ifstream inFile(name);
  return inFile;
}

int main(int argc, char* argv[]) {
  set<char> flags; 
  if (argc==3) { // ./main -<tags> <filepath>
    string s = string(argv[1]);
    if (!(s[0]=='-')) {
      cout << "Flag format: -<tags- c/m/w/l>\n";
      return 0;
    }

    setFlags(argv[1],flags);
    if (getFlag(flags, 'c')) {
      int fsize=getSize(argv[2]);
      cout << fsize << " B\t";
    }
    allInfo res=getAllin1Itr(argv[2]);
    showInfo(res,flags);
  }
  else if (argc==2) {
    string s = string(argv[1]);
    if (s[0]=='-') { // ./main -<tags>
      string name="foooo.txt";
      stdFileInp(name);

      setFlags(argv[1],flags);
      if(getFlag(flags,'c')) {
        int fsize=getSize(name);
        cout << fsize << " B\t";
      }
      allInfo res=getAllin1Itr(name);
      showInfo(res,flags);
    }
    else { // ./main <filepath>
      int fsize=getSize(argv[1]);
      cout << fsize << " B\t";
      allInfo res=getAllin1Itr(argv[1]);
      flags.insert('w'), flags.insert('l');
      showInfo(res,flags);
    }
  }
  else if (argc==1) {
    string name="foooo.txt";
    stdFileInp(name);
    int fsize=getSize(name);
    cout << fsize << " B\t";
    allInfo res=getAllin1Itr(name);
    flags.insert('w'), flags.insert('l');
    showInfo(res,flags);
  }
  cout << endl;
}
