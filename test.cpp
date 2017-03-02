#include <iostream>
#include <cstdlib>
#include "LWE.h"
#include "FHEW.h"
#include "distrib.h"

using namespace std;


int main()
{
  //FHEW::Setup();
  FHEW::Setup();
  //generate a secret key
  LWE::SecretKey sk;
  LWE::KeyGen(sk);


  //Encrypt a message
  int message1=0;
  int message2=1;
  LWE::CipherText ct1;
  LWE::CipherText ct2, res;
  LWE::Encrypt(&ct1, sk, message1);
  LWE::Encrypt(&ct2, sk, message2);

  //generate Evaluation key
  FHEW::EvalKey EK;
  FHEW::KeyGen(&EK, sk);
  FHEW::HomNAND(&res, EK, ct1, ct2);
  int  r = LWE::Decrypt(sk,res);
  printf("%d\n",r);

}

