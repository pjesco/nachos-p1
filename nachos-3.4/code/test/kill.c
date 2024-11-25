#include "syscall.h"

void infinity(){
	int i = 0;
	for (; ;) Yield();
}

int main()
{
	int ret;
	int id = Fork(infinity);
	Yield();
	Kill(-1);
	ret = Kill(id);
	Exit(ret);
        return ret;
}