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

int HomNOT (LWE::CipherText *res,FHEW::EvalKey Ek,LWE::CipherText ct1)
{
  
  FHEW::HomNAND(res,Ek,ct1,ct1);
  return 0;
 
}  

int HomAND (LWE::CipherText *res,FHEW::EvalKey Ek,LWE::CipherText ct1,LWE::CipherText ct2)
{
  LWE::CipherText i1;
  FHEW::HomNAND(&i1,Ek,ct1,ct2);
  HomNOT(res,Ek,i1);
  return 0;
 
}  

int HomOR (LWE::CipherText *res,FHEW::EvalKey Ek,LWE::CipherText ct1,LWE::CipherText ct2)
{
  LWE::CipherText i1,i2;
  HomNOT(&i1,Ek,ct1);
  HomNOT(&i2,Ek,ct2);  
  FHEW::HomNAND(res,Ek,i1,i2);
  return 0;
}  

int FullAdd(LWE::CipherText *sum,LWE::CipherText *cout,FHEW::EvalKey Ek,LWE::CipherText a,LWE::CipherText b,LWE::CipherText cin)
{
  LWE::CipherText i1,i2,i3;
  HomXOR(&i1,Ek,a,b);
  HomXOR(sum,Ek,i1,cin);
  //  HomAND(&i2,Ek,a,b);
  // HomAND(&i3,Ek,cin,i1);
  //HomOR(cout,Ek,i3,i2);
  return 0;
  
}


int main()
{
  //FHEW::Setup();
  FHEW::Setup();
  //generate a secret key
  LWE::SecretKey sk;
  LWE::KeyGen(sk);
  //Encrypt a message
  int message1=0;
  int message2=0;
  int message3=0;
  LWE::CipherText ct1;
  LWE::CipherText ct2,ct3,sum,cout;
  LWE::Encrypt(&ct1, sk, message1);
  LWE::Encrypt(&ct2, sk, message2);
  LWE::Encrypt(&ct3, sk, message3);
  //generate Evaluation key
  FHEW::EvalKey EK;
  FHEW::KeyGen(&EK, sk);
  FullAdd(&sum,&cout, EK, ct1, ct2,ct3);
  int  r = LWE::Decrypt(sk,sum);
  printf("%d\n",r);

}

