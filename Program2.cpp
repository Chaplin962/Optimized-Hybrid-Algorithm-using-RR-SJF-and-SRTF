#include<iostream>
#include <cmath>
using namespace std;

//function is called to find waiting time according to the remaining time left per process
//and their arrival time
void findWaitingTime(int processes[], int n, int bt[], int wt[], int quantum,int art[])
{int rem_bt[n];
for(int i=0;i<n;i++)
rem_bt[i]=bt[i];
int t=0;
int temp;

while(1)
{bool done=true;

for(int i=0;i<n;i++)
{
//Swapping in ready queue according to remaining burst time
for(int k=0;k<n;k++)
{for(int j=k+1;j<n;j++)
{if(art[k]<=t&&art[j]<=t)
{if(rem_bt[k]>rem_bt[j])
{//cout<<"Swapped "<<processes[k]<<"("<<rem_bt[k]<<") and "<<processes[j]<<"("<<rem_bt[j]<<") at time "<<t<<"\n";
temp=art[k];
art[k]=art[j];
art[j]=temp;
temp=bt[k];
bt[k]=bt[j];
bt[j]=temp;
temp=rem_bt[k];
rem_bt[k]=rem_bt[j];
rem_bt[j]=temp;
temp=processes[k];
processes[k]=processes[j];
processes[j]=temp;
}}}}

//if process can be executed with remaining bt>t
if(art[i]<=t)
{if(rem_bt[i]>0)
{done=false;
if(rem_bt[i]>quantum)
{t+=quantum;
rem_bt[i]-=quantum;
//cout<<"executed "<<processes[i]<<" at time "<<t<<"\n";
/*if(rem_bt[i]<quantum)
{t+=rem_bt[i];
wt[i]=t-bt[i];
rem_bt[i]=0;
cout<<"finished2 "<<processes[i]<<" at time "<<t<<"\n";}*/
break;}
//finishing off processes with remaining bt<t
else
{t=t+rem_bt[i];
wt[i]=t-bt[i];
rem_bt[i]=0;
//cout<<"finished "<<processes[i]<<" at time "<<t<<"\n";
break;}}}
else{t+=quantum;}}
if(done==true)
break;}}

//function is called to find turn around time after finding waiting time
void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[])
{for(int i=0;i<n;i++)
tat[i]=bt[i]+wt[i];}

//this is the function first called which sends calls to the above two functions
//it manages output also
void findavgTime(int processes[], int n, int bt[], int quantum, int art[])
{int wt[n], tat[n], total_wt=0, total_tat=0;
findWaitingTime(processes, n, bt, wt, quantum, art);
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
int processes[n], burst_time[n], art[n];
for(int i=0;i<n;i++)
{cout<<"\nEnter Process Number: ";
cin>>processes[i];
cout<<"Enter Burst Time: ";
cin>>burst_time[i];
cout<<"Enter Arrival Time: ";
cin>>art[i];}
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

//arranging according to arrival time
for(int i=0;i<n;i++)
{for(int j=i+1;j<n;j++)
{if(art[i]>art[j])
{temp=art[i];
art[i]=art[j];
art[j]=temp;
temp=burst_time[i];
burst_time[i]=burst_time[j];
burst_time[j]=temp;
temp=processes[i];
processes[i]=processes[j];
processes[j]=temp;}}}

findavgTime(processes, n, burst_time, quantum, art);
return 0;}
