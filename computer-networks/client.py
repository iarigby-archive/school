import socket; import select
client_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_sock.connect(('localhost',12345))
while True:
	message = raw_input('Message: ')
	if message == 'EXIT':
		client_sock.close()
		break
	else:
		client_sock.sendall(message)
		print client_sock.recv(1024)
	
