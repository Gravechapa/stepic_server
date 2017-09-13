#include <unistd.h>
#include <signal.h>
#include <iostream>
#include <boost/filesystem.hpp>
#include <fstream>
#include "crow.h"

int main(int argc, char* argv[])
{
    std::string ip;
    int port;
    std::string directory;
    int opt;
    while ((opt = getopt(argc, argv, "h:p:d:")) != -1) {
        switch (opt) {
        case 'h':
            ip = optarg;
            break;
        case 'p':
            port = atoi(optarg);
            break;
        case 'd':
            directory = optarg;
            break;
        default:
            std::cout << "Usage: final -h <ip> -p <port> -d <directory>\n";
            exit(EXIT_FAILURE);
        }
    }
    if (fork() == 0)
            {
                signal(SIGHUP, SIG_IGN);
                crow::SimpleApp app;

                if (directory[directory.size() - 1] != '/')
                    {
                        directory += '/';
                    }
                CROW_ROUTE(app, "/")
                ([directory](const crow::request& req){
                        std::string temp = req.url;
                        temp.erase(0, 1);
                        std::string path = directory + temp;
                        if (path != "./" && path != "/")
                            {
                                std::ifstream file(path);
                                if (file.is_open())
                                    {
                                        temp = "";
                                        char c;
                                        while (file.get(c))
                                            {
                                                temp += c;
                                            }
                                        file.close();
                                        return crow::response(200, temp);
                                    }
                            }
                        return crow::response(404);
                        });

                app.port(port).bindaddr(ip).multithreaded().run();
            }
    return 0;
}
