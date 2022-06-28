#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
using namespace std;

int main()
{
  string from, to;
  cin >> from >> to;

  ifstream                 is(from);
  istream_iterator<string> ii(is);
  istream_iterator<string> eos;

  ofstream                 os(to);
  ostream_iterator<string> oo(os, "\n");

  vector<string> b(ii, eos);
  sort(b.begin(), b.end());

  unique_copy(b.begin(), b.end(), oo);

  cout << b.size() << endl;

  for (int i = 0; i < b.size() - 1; ++i) {
    cout << i + 1 << ":" << b[i] << endl;
  }

  return !is.eof() || !os;
}
