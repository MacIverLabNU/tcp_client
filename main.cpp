#include <easy_tcp.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <cell_world.h>

using namespace easy_tcp;
using namespace std::chrono_literals;
using namespace std;
using namespace cell_world;

char message[3];
Timer timer;

struct MyClient : Client {
    void received_data(char *data, size_t s) {
        cout << *data << " " << s << " time (ms): " << timer.to_seconds() * 1000 << endl;
    }
};


int main ( ){
    MyClient c;
    std::cout << c.connect("192.168.137.155", 4500) << std::endl; //    std::cout << c.connect("192.168.1.1", 4500) << std::endl;
    std::this_thread::sleep_for(1s);
    message[0] = (char) 0;
    message[1] = (char) 0;
    message[2] |= 1UL << 3;
    bool sent = false;
    while (true) {
        if (!sent) {
            sent = true;
            cout << "Send data: " << c.easy_tcp::Connection::send_data(message, 3) << endl;
            timer.reset();
        }
    }

    c.disconnect();
}




// for checking message overload error
//std::cout << c.connect("192.168.137.155", 4500) << std::endl;
//std::this_thread::sleep_for(10s);
//
//int i;
//while (i < 90000* 2) {
//message[0] = (char) i;
//message[1] = (char) i;
//if (i % 500 == 0) message[2] |= 1UL << 3;
//else message[2] &= ~(1UL << 3);
//cout << "Send data: " <<c.easy_tcp::Connection::send_data(message, 3) << " " << i  <<  endl;
//i ++;
//if (i > 100) i = 0;
//std::this_thread::sleep_for(20ms);