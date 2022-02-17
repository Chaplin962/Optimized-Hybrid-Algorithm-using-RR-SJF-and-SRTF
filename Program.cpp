#include<iostream>
#include <cmath>
using namespace std;

//function is called to find waiting time according to the remaining time left per process
void findWaitingTime(int processes[], int n, int bt[], int wt[], int quantum)
{int rem_bt[n];
for(int i=0;i<n;i++)
rem_bt[i]=bt[i];
int t=0;
while(1)
{bool done=true;
for(int i=0;i<n;i++)
//if process can be executed with remaining bt>t
{if(rem_bt[i]>0)
{done=false;
if(rem_bt[i]>quantum)
{//cout<<processes[i];
t+=quantum;
rem_bt[i]-=quantum;
//cout<<"executed "<<processes[i]<<" at time "<<t<<"\n";
}
//finishing off processes with remaining bt<t
else
{t=t+rem_bt[i];
//cout<<processes[i];
wt[i]=t-bt[i];
rem_bt[i]=0;
//cout<<"finished "<<processes[i]<<" at time "<<t<<"\n";
}}}
if(done==true)
break;}}

//function is called to find turn around time after finding waiting time
void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[])
{for(int i=0;i<n;i++)
tat[i]=bt[i]+wt[i];}

//this is the function first called which sends calls to the above two functions
//it manages output also
void findavgTime(int processes[], int n, int bt[], int quantum)
{int wt[n], tat[n], total_wt=0, total_tat=0;
findWaitingTime(processes, n, bt, wt, quantum);
findTurnAroundTime(processes, n, bt, wt, tat);

//Output in table format
cout<<"\n--------------------------------------------------------------------\n| Process No \t| Burst time \t|  Waiting time | Turn around time |\n";

for(int i=0;i<n;i++)
{total_wt=total_wt+wt[i];
total_tat=total_tat+tat[i];
cout << "| " << processes[i] << "\t\t| " << bt[i] <<"\t\t| "<< wt[i] <<"\t\t| " << tat[i]<<"\t\t   |" <<endl;}
cout<<"--------------------------------------------------------------------\n";
cout << "\nEfficient Time Quantum: "<<quantum;
cout << "\nAverage waiting time: "<< (float)total_wt / (float)n;
cout << "\nAverage turn around time: "<< (float)total_tat / (float)n;}

int main()
{int n;
cout<<"Enter Number of Processes: ";
cin>>n;
int processes[n], burst_time[n];
for(int i=0;i<n;i++)
{cout<<"\nEnter Process Number: ";
cin>>processes[i];
cout<<"Enter Burst Time: ";
cin>>burst_time[i];}
float mean=0;
int min=9999, temp;

//calculating etq
for(int i=0;i<n;i++)
{if(burst_time[i]<min)
{min=burst_time[i];}
mean+=burst_time[i];}
mean=mean/n;
float etq=(mean+min)/2;
int quantum=ceil(etq);

//arranging in ready queue according to burst time
for(int i=0;i<n;i++)
{for(int j=i+1;j<n;j++)
{if(burst_time[i]>burst_time[j])
{temp=burst_time[i];
burst_time[i]=burst_time[j];
burst_time[j]=temp;
temp=processes[i];
processes[i]=processes[j];
processes[j]=temp;}}}

findavgTime(processes, n, burst_time, quantum);
return 0;}
