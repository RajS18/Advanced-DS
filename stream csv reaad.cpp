#include <fstream>
#include <bits/stdc++.h>
#include <sstream>
using namespace std;
int main() {
  ifstream file("market_data1.csv");
  if (!file) {
    cout << "Error opening file.\n";
    return 1;
  }
  string line, col1;
  bool first=true;
  cout<<0<<endl;
  float prev=0;
  while (std::getline(file, line)) {
      // Read the first column only
    std::istringstream ss(line);
    std::getline(ss, col1, ',');
    if(first){
      first=false;continue;
    }else{
      int value = int(stof(col1));
      if(value>prev){
        cout<<value<<endl;
        prev=value;
      }
    }
    //break;
  }

  return 0;
}