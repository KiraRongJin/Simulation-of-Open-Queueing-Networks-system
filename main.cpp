#include<iostream>
#include"rv.h"
#include"event.h"

int main()
{
    using namespace std;
    EventList Elist;
    enum{ARR,DEP1,DEP2,DEP3};

    double rs1,rs2,r11,r13,r3d,r32,mu1,mu2,mu3;
    double clock;                 // System clock
    double EN1;
    double EN2;
    double EN3;
    int N1;                      // Number of customers in queue1
    int N2;
    int N3;
    int Ndep1;                   // Number of departures from queue1
    int Ndep2;
    int Ndep3;
    int Ndep_system;                //# of departures from system
    double U1;
    double U2;
    double U3;
	double lambda;


    cout << "Please input a lambda value(1 to 10): "<< endl;
	cin >> lambda;
    cout << "Please input the rs1 : " << endl;
	cin >> rs1;
	cout << "Please input the rs2 : " << endl;
	cin >> rs2;
	cout << "Please input the r11 : " << endl;
	cin >> r11;
	cout << "Please input the r13 : " << endl;
	cin >> r13;
	cout << "Please input the r3d : " << endl;
	cin >> r3d;
	cout << "Please input the r32 : " << endl;
	cin >> r32;
	cout << "Please input the mu1 : " << endl;
	cin >> mu1;
	cout << "Please input the mu2 : " << endl;
	cin >> mu2;
	cout << "Please input the mu3 : " << endl;
	cin >> mu3;

    int done = 0;                   // End condition satisfied?
    int i;

   
		clock = 0.0;
		N1 = 0;
		N2 = 0;
		N3 = 0;
		EN1 = 0.0;
        EN2 = 0.0;
        EN3 = 0.0;
		Ndep1 = 0;
		Ndep2 = 0;
		Ndep3 = 0;
		Ndep_system = 0;
		U1 = 0.0;
		U2 = 0.0;
		U3 = 0.0;        

		Event* CurrentEvent;
		
		Elist.insert(exp_rv(lambda),ARR);

		while (!done)
		{

		    CurrentEvent = Elist.get();               // Get next Event from list
            double prev = clock;                      // Store old clock value
            clock = CurrentEvent->time;                 // Update system clock
            EN1 += N1*(clock-prev);
            EN2 += N2*(clock-prev);
            EN3 += N3*(clock-prev);
            if(N1>0) U1+=1*(clock-prev);
            if(N2>0) U2+=1*(clock-prev);
            if(N3>0) U3+=1*(clock-prev);

            switch (CurrentEvent->type){
            case ARR:
               if(uni_rv()<rs1)
               {
			      ///EN1 += N1*(clock-prev);  /////
                  N1 += 1;
                  Elist.insert(clock+exp_rv(lambda),ARR);
                  if(N1==1)
                  {
                    Elist.insert(clock+exp_rv(mu1),DEP1);  // A DEPARTURE FROM QUEUE1
                  }
               }
              else
               {
                  N2+=1;
                  Elist.insert(clock+exp_rv(lambda),ARR);
                  if(N2==1)
                  {
                    Elist.insert(clock+exp_rv(mu2),DEP2);  //A DEPARTURE FROM QUEQUE2
                  }
               }
               break;

            case DEP1:
			    ///EN1 += N1*(clock-prev);  
                N1-=1;
                Ndep1+=1;
                if(N1>0)
                {
                     Elist.insert(clock+exp_rv(mu1),DEP1);
                }
                if(uni_rv()<r11)
                {
                    N1+=1;
                    if(N1==1)
                    {
                      Elist.insert(clock+exp_rv(mu1),DEP1);
                    }
                }
                else{
                    N3+=1;
                    if(N3==1)
                    {
                        Elist.insert(clock+exp_rv(mu3),DEP3);  //A DEPARTURE FROM QUEQUE3
                    }
                }
                break;

            case DEP2:
			     ///EN2 += N2*(clock-prev); 
                 N2-=1;
                 Ndep2+=1;
                 N3+=1;
                 if(N3==1)
                 {
                    Elist.insert(clock+exp_rv(mu3),DEP3);
                 }
                 if(N2>0)
                 {
                     Elist.insert(clock+exp_rv(mu2),DEP2);
                 }
                 break;

            case DEP3:
			      ///EN3 += N3*(clock-prev);
                  N3-=1;
                  Ndep3+=1;
                  if(uni_rv()<=r3d)
                  {
                      Ndep_system+=1;
                  }
                  else{
                    N2+=1;
                    if(N2==1)
                    {
                        Elist.insert(clock+exp_rv(mu2),DEP2);
                    }
                  }
                  if(N3>0)
                  {
                      Elist.insert(clock+exp_rv(mu3),DEP3);
                  }
                  break;
            }

            delete CurrentEvent;

            if (Ndep_system > 500000)   done=1;
		}
		// output simulation results
  cout << "lambda: " << lambda << endl;
  cout << "Throughput of each queue(simulation): \n" << Ndep1/clock << endl << Ndep2/clock << endl << Ndep3/clock<< endl;
  cout << "Expected # of each queue(simulation): \n" << EN1/clock <<endl << EN2/clock << endl << EN3/clock << endl;
  cout << "Expected time of each queue(simulation): \n" << EN1/(double)Ndep1 << endl << EN2/(double)Ndep2 << endl << EN3/(double)Ndep3 <<endl;
  cout << "Utilization of each queue(simulation): \n" << U1/clock << endl << U2/clock << endl << U3/clock << endl;
 

}
