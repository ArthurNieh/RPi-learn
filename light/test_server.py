import socket

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(("127.0.0.1", 9002))
server.listen(5)
client,addr = server.accept()

message = 'hello'
client.send(message.encode())

server.close