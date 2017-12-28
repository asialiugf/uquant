#include <Base.h>
#include <thread>
#include <unistd.h>

int main()
{

    uGG::Base b;

    //std::thread t(b.MainHubInit);
    //t.detach();

    //b.MainHubInit();
    b.Init();

    usleep(1000000);

	b.getTick();
	b.getTick();
	b.getTick();
	b.getTick();
	b.getTick();

    while(1) {
       // b.cs[0]->send("------------------------from main -----------");
        usleep(1);
    }
    usleep(8000000);


}
