/* Program Name: Splash
 * Project Name: MinecraftSplash
 * Author: PiSaucer
 * Program Description: Reads in splash text file and outputs index.json file
 *
 * All rights reserved.
 */
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>
using namespace std;

// Fix Escape Characters
string escape(string const &s) {
  size_t n = s.length();
  string escaped;
  escaped.reserve(n * 2);
  for (size_t i = 0; i < n; ++i) {
    if (s[i] == '\\' || s[i] == '\"') {
      escaped += '\\';
    }
    escaped += s[i];
  }
  return escaped;
}

int main(int argc, char *argv[]) {

  // Make sure we have input file
  if (argc < 2) {
    cerr << "usage: ./splash input" << endl;
    return 1;
  }

  ifstream fin;
  ofstream fout;
  vector<string> splash;
  string tempSplash;
  string filename = argv[1];
  fin.open(filename);

  if (!fin.is_open()) {
    // fin.fail() could also error check. Failure reasons: doesn't exist, OR we don't have permission
    cout << "Could not open " << filename << endl;
    return 1;
  }

  // Read Input File
  int numLines = 0;
  while (getline(fin, tempSplash)) {
    tempSplash = escape(tempSplash);
    splash.push_back(tempSplash);
    numLines++;
  }
  fin.close();

  // Save to index.json file
  fout.open("index.json");
  fout << "{ \n \t\"splashes\": [\n";
  for (int i = 0; i < splash.size(); i++) {
    if (i != numLines - 1) {
      fout << "\t\t\"" << splash[i] << "\",\n";
    } else {
      fout << "\t\t\"" << splash[i] << "\"\n";
    }
  }
  fout << "\t] \n } \n";
}
