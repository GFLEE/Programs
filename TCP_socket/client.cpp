#include<WINSOCK2.H>  
#include<stdio.h>  
#include<iostream>  
#include<cstring>  
using namespace std;  
#pragma comment(lib, "ws2_32.lib")  
  
int main()  
{  
    cout<<"==========CLIENT==========";
    WORD sockVersion = MAKEWORD(2, 2);  
    WSADATA data;  
    if(WSAStartup(sockVersion, &data)!=0)  
    {  
        return 0;  
    }  
    while(true){
	 cout<<"\n";  
        SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  
        if(sclient == INVALID_SOCKET)  
        {  
            cout<<"invalid socket!";
            return 0;  
        }  
          
        sockaddr_in serAddr;  
        serAddr.sin_family = AF_INET;  
        serAddr.sin_port = htons(8888);  
        serAddr.sin_addr.S_un.S_addr = inet_addr("192.168.43.23");   //server IP
        if(connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)  
        {  //����ʧ��   
            cout<<"connect error !"; 
            closesocket(sclient);  
            return 0;  
        }  
          
		   cout<<"\n";
		  cout<<"Input you message: ";
		  
        string data;
		getline(cin,data);  
          
        const char * sendData;  
        sendData = data.c_str();  
 
        send(sclient, sendData, strlen(sendData), 0);  
   
          
        char recData[255];  
        int ret = recv(sclient, recData, 255, 0);  
        if(ret>0){  
            recData[ret] = 0x00;  
           cout<<recData;
        }   
        closesocket(sclient);  
    }  
      
      
    WSACleanup();  
    return 0;  
      
}  

