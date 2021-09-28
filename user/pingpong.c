#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int 
main(int argc, char *argv[])
{
  int to_parent[2]; // 0 - čítací deskriptor, 1 - zapisovací
  int to_child[2];

  pipe(to_parent);
  pipe(to_child);
  int pid = fork();

  if(pid == 0){
    //child
    char recieved;
    read(to_child[0], &recieved, 1);
    printf("%d: received ping\n", getpid());

    write(to_parent[1], "p", 1);    
  }
  else{
    //parent
    write(to_child[1], "b", 1);   

    char recieved;
    read(to_parent[0], &recieved, 1);
    printf("%d: received pong\n", getpid());
  }
 
  exit(0);
}