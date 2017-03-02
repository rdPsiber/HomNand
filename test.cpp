#include <iostream>
#include <cstdlib>
#include "LWE.h"
#include "FHEW.h"
#include "distrib.h"

using namespace std;

int HomXOR (LWE::CipherText *res,FHEW::EvalKey Ek,LWE::CipherText ct1,LWE::CipherText ct2)
{
  LWE::CipherText i1,i2,i3;
  
  FHEW::HomNAND(&i1,Ek,ct1,ct2);
  FHEW::HomNAND(&i2,Ek,ct1,i1);
  FHEW::HomNAND(&i3,Ek,ct2,i1);
  FHEW::HomNAND(res,Ek,i3,i2);
  return 0;
 
}  

int FullAdd(LWE::CipherText *res,FHEW::EvalKey Ek,LWE::CipherText ct1,LWE::CipherText ct2)


int main()
{
  //FHEW::Setup();
  FHEW::Setup();
  //generate a secret key
  LWE::SecretKey sk;
  LWE::KeyGen(sk);


  //Encrypt a message
  int message1=1;
  int message2=0;
  LWE::CipherText ct1;
  LWE::CipherText ct2, res;
  LWE::Encrypt(&ct1, sk, message1);
  LWE::Encrypt(&ct2, sk, message2);

  //generate Evaluation key
  FHEW::EvalKey EK;
  FHEW::KeyGen(&EK, sk);
  HomXOR(&res, EK, ct1, ct2);
  int  r = LWE::Decrypt(sk,res);
  printf("%d\n",r);

}

