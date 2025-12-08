#pragma comment(lib, "ws2_32.lib") 
int main() { 
SOCKET s = socket(AF_INET, SOCK_STREAM, 0); 
struct sockaddr_in a = {0}; a.sin_family=AF_INET; 
a.sin_port=htons(5000); a.sin_addr.s_addr=INADDR_ANY; 
printf("Test server ready\\n"); 
while(1) { SOCKET c = accept(s,0,0); 
printf("Client connected\\n"); 
send(c, "RESULT:99.000000\\n", 18, 0); 
closesocket(c); } return 0; } 
#pragma comment(lib, "ws2_32.lib") 
int main() { 
SOCKET s = socket(AF_INET, SOCK_STREAM, 0); 
struct sockaddr_in a = {0}; a.sin_family=AF_INET; 
a.sin_port=htons(5000); a.sin_addr.s_addr=INADDR_ANY; 
printf("Test server ready\\n"); 
while(1) { SOCKET c = accept(s,0,0); 
printf("Client connected\\n"); 
send(c, "RESULT:99.000000\\n", 18, 0); 
closesocket(c); } return 0; } 
