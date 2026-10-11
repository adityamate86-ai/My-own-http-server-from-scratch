
#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

using namespace std;

int main(int argc, char **argv) {
    cout << unitbuf;
    cerr << unitbuf;

    cout << "Logs from your program will appear here!\n";

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        cerr << "Failed to create server socket\n";
        return 1;
    }

    int reuse = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR,
                   &reuse, sizeof(reuse)) < 0) {
        cerr << "setsockopt failed\n";
        close(server_fd);
        return 1;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(4221);

    if (bind(server_fd, (sockaddr *)&server_addr,
             sizeof(server_addr)) != 0) {
        cerr << "Failed to bind to port 4221\n";
        close(server_fd);
        return 1;
    }

    if (listen(server_fd, 5) != 0) {
        cerr << "listen failed\n";
        close(server_fd);
        return 1;
    }

    cout << "Waiting for a client to connect...\n";

    while (true) {
        sockaddr_in client_addr{};
        socklen_t client_addr_len = sizeof(client_addr);

        int client_socket = accept(
            server_fd,
            (sockaddr *)&client_addr,
            &client_addr_len
        );

        if (client_socket < 0) {
            perror("accept failed");
            continue;
        }

        
        cout << "Client connected\n";
              
        string response = "HTTP/1.1 200 OK\r\n\r\n";
              
        cout << "Response length: " << response.size() << "\n";
              
        ssize_t bytes_sent = send(
            client_socket,
            response.data(),
            response.size(),
            0
        );
        
        if (bytes_sent == -1) {
            perror("send");
        } else {
            cout << "Bytes sent: " << bytes_sent << "\n";
        }
        
        close(client_socket);

    }

    close(server_fd);
    return 0;
}
