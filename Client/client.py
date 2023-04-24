import socket

SERVER_ADDR = '127.0.0.1'

def get_port() -> int:
    while True:
        port = input("Enter port number (1024-65535): ")
        try:
            port = int(port)
            if port >= 1024 and port <= 65535:
                return port
            else:
                print("Invalid port number. Try again.")
        except ValueError:
            print("Invalid input. Please try again.")

def connect_to_server(port:int) -> socket:
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_address = (SERVER_ADDR, port)
    client_socket.connect(server_address)
    return client_socket

def send_msg(client_socket):
    while True:
        message = input("Enter message to send: ")
        if len(message) > 0:
            client_socket.sendall(message.encode('utf-8'))
            break

def print_response(client_socket):
    data = client_socket.recv(1024).decode('utf-8')
    if data == "Hello":
        print("Hello")

def main():
    
    port = get_port()
    client_socket = connect_to_server(port)
    send_msg(client_socket)
    print_response(client_socket)
    client_socket.close()

if __name__ == "__main__":
    main()