#include <cstdio>
#include <vector>
#include <iostream>
#include <string>
#include <cmath>

#define MAX(a,b) (a) < (b) ? (b) : (a) 
#define MIN(a,b) (a) > (b) ? (b) : (a) 

using namespace std;

bool corrIndex (int i, vector<int> v) {
  return (i >= 0 && i < v.size() );
}

void correctSize (vector<int> *w) {
  int i = (*w).size() - 1;
  while( (*w)[i] == 0)
    i--;
  (*w).resize(i + 1);
}

class Bignum {
public:
  vector<int> number; 

  Bignum() {
    number = vector<int> (1,0);
    for (int i = 0; i < number.size(); i++)
      number[i] = 0;
  }

  Bignum(unsigned int n) {
    number = vector<int> (MAX (ceil(log10((double)n)), 1) + 1, 0);
    int i = 0;    
    while(n > 0) {
      number[i] = n % 10;
      n /= 10;
      i++;
    }
  }

  Bignum(vector<int> v) {
    number = v;
  }

  string toString() {
    string str = string(number.size(),'0');
    int length = number.size();
    for (int i = 0; i < length; i++) {
      str[i] = number[length - i - 1] + '0';
    }
    return str;
  }

  void corSize() {
    correctSize(&(number));
  }
  
};

void correctBignumSize (Bignum *b) {
  correctSize( & ( (*b).number ) );
}

Bignum operator+ (Bignum a, Bignum b) {
  int length = (MAX( (a.number.size()), (b.number.size())));
  vector<int> res = vector<int> ();
  int tmp,shift = 0;
  
  for (int i = 0; i <= length; i++) {
    if(corrIndex(i,a.number) && corrIndex(i,b.number) )
      tmp = a.number[i] + b.number[i] + shift;
    else if (corrIndex(i,a.number))
      tmp = a.number[i] + shift;
    else if (corrIndex(i,b.number))
      tmp = b.number[i] + shift;
    else
      tmp = shift;
    
    res.push_back (tmp % 10);
      if (tmp >= 10) shift = 1; else shift = 0;
  }
  
  correctSize(&res);

  return Bignum(res);  
}

Bignum operator* (Bignum a, Bignum b) {
  vector<int> tmp = vector<int> ();
  int tmp2;
  Bignum tmp3;
  Bignum res = Bignum(0);
  Bignum res2 = Bignum(0);
  int shift = 0;

  a.corSize();
  b.corSize();

  for(int i = 0; i < b.number.size(); i++) {
    shift = 0;
    for(int k = 0; k < i; k++)
      tmp.push_back(0);
    for(int j = 0; j < a.number.size(); j++) {
      tmp2 = b.number[i] * a.number[j] + shift;
      tmp.push_back(tmp2 % 10); 
      shift = tmp2 / 10;
    }
    if (shift > 0) tmp.push_back(shift);
    // printf("Mnoze razy %d \n",b.number[i]);
    // for(int i = tmp.size() - 1; i >= 0; i--)
    //   printf("%d ",tmp[i]);
    // printf("\n");

    res = res + Bignum(tmp);
    tmp.resize(0);
  }

  res.corSize();
  
  return res;
}

int main() {
  Bignum mybig,mybig2,mybig3;
  mybig = Bignum(13);
  mybig2 = Bignum(13);
  mybig3 = Bignum(1);

  for(int i = 0; i <= 50; i++) {
    
    // cout << i << " " << mybig3.toString() << " = " << mybig.toString() << " * "
    // 	 << mybig2.toString() << endl;
    
    cout << i << " " << mybig3.toString() << endl;

    mybig = mybig3;
    mybig3 = mybig3 * mybig2;
  }

  // mybig3 = Bignum(1);
  // mybig = Bignum(13);
  // mybig2 = Bignum(371293);
  // mybig3 = mybig * mybig2;

  // cout << mybig3.toString() << endl;
  

  //mybig3 = mybig3 * mybig3;
  //cout << mybig3.toString() << endl;

return 0;
}
