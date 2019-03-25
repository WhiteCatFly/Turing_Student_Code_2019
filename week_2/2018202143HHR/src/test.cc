// #include <iostream>
#include <filesystem>

// #include "AsyncRequestPool.h"

int main() {
	/*
    AsyncRequestPool pool;
    for (int i = 0; i < 100; i++)
        pool.addTask("http://info.ruc.edu.cn", [](std::string &standardError, std::string &responseBody) {
            std::cout << "response body: " << responseBody << std::endl;
            std::cout << "standard error: " << standardError << std::endl;
        });

    pool.runEventLoop();
	*/

	std::filesystem::create_directories("output/info.ruc.edu.cn");
}
