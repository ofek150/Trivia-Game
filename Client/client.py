import socket
import json

SERVER_ADDR = '127.0.0.1'

# Define codes for login and registration
LOGIN_CODE = b'\x01'
REGISTRATION_CODE = b'\x00'

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

def connect_to_server(port: int) -> socket:
    try:
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server_address = (SERVER_ADDR, port)
        client_socket.connect(server_address)
    except Exception as e:
        client_socket = -1
        print(e)
    return client_socket

def send_msg(client_socket, data_bytes):
    try:
        # Prepend code and data length to the data_bytes
        data_with_header = b''.join([bytes([data_bytes[0]]), len(data_bytes[1:]).to_bytes(4, byteorder='big'), data_bytes[1:]])
        client_socket.sendall(data_with_header)
        print(data_with_header)
    except Exception as e:
        print(e)


def receive_msg(client_socket):
    try:
        # Receive the response header first
        header = client_socket.recv(5)
        response_code = header[0]
        data_length = int.from_bytes(header[1:], byteorder='big')

        # Then receive the JSON data
        data = client_socket.recv(data_length).decode('utf-8')
        return (response_code, json.loads(data))
    except Exception as e:
        print(e)

def login(client_socket, username, password):
    # Create login JSON data
    #username = input("Enter username: ")
    #password = input("Enter password: ")
    data = {"Username": username, "Password": password}

    # Send the data to the server with the login code
    data_bytes = LOGIN_CODE + json.dumps(data).encode('utf-8')
    send_msg(client_socket, data_bytes)

    # Receive the response from the server and print it
    response_code, response_data = receive_msg(client_socket)
    print(f"Response code: {response_code}")
    print(f"Response data: {response_data}")

def registration(client_socket, username, password, email):
    # Create registration JSON data
    #username = input("Enter username: ")
    #password = input("Enter password: ")
    #email = input("Enter email: ")
    data = {"username": username, "password": password, "email": email}

    # Send the data to the server with the registration code
    data_bytes = REGISTRATION_CODE + json.dumps(data).encode('utf-8')
    send_msg(client_socket, data_bytes)

    # Receive the response from the server and print it
    response_code, response_data = receive_msg(client_socket)
    print(f"Response code: {response_code}")
    print(f"Response data: {response_data}")

def main():
    port = get_port()
    client_socket = connect_to_server(port)
    if client_socket == -1:
        return 0

    #case 1 : login with user that is not signed up
    #login(client_socket, "user0000",  "00000")
    #case 1 fixed: sign up and then log in
    #registration(client_socket, "user0000", "00000", "user00000@gmail.com")
    #login(client_socket, "user0000",  "00000")

    #case 2 : user cant register twice in a row
    #registration(client_socket, "user0000", "00000", "user00000@gmail.com")
    #registration(client_socket, "user0000", "00000", "user00000@gmail.com")

    #case 3 : user cant login twice in a row
    registration(client_socket, "user0000", "00000", "user00000@gmail.com")
    login(client_socket, "user0000",  "00000")
    login(client_socket, "user0000",  "00000")


    client_socket.close()

if __name__ == "__main__":
    main()
