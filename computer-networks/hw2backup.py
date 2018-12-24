"""
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('localhost', 10000))
s.sendall(b'Hello, world')
data = s.recv(1024)
printmsg('received' + data)
# unpacker = struct.Struct('I 2s f')
# unpacked_data = unpacker.unpack(data)
"""

"""

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = ('localhost', 10000)
sock.bind(server_address)
sock.listen(1)

# connection, client_address = sock.accept()
#
# data = connection.recv(16)
# connection.sendall(data)
# connection.close()

conn, addr = sock.accept()
with conn:
    printmsg('Connected by' + addr)
    while True:
        data = conn.recv(1024)
        printmsg('sending' + data)
        if not data: break
        conn.sendall(data)


# import struct
# values = (1, 'ab', 2.7)
# packer = struct.Struct('I 2s f')
# packed_data = packer.pack(*values)
"""
