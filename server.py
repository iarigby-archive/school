import socket; import select
serv_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serv_sock.bind(('localhost',12345))
serv_sock.listen(1)
inputs = [ serv_sock ]
outputs = [ ]
timeout=1
while True:
	readable, writable, exceptional = select.select(inputs, outputs, inputs, timeout)

	for s in readable:
		if s is serv_sock:    #new client connect
			connection, client_address = serv_sock.accept()
			print('New client from %s:%d' % client_address)
			inputs.append( connection )
		else:
			data = s.recv(1024)
			if data:
				print "Received: ", data
				s.sendall('ACK')
			else:
				s.close()
				inputs.remove(s)				
