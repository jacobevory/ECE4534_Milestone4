import socket
import os
import json
	
host = ''
port = 4000
backlog = 5
size = 1024
dataL = 0
dataR = 0

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((host, port))
s.listen(backlog)

print ('server started and listening')

while True:
	client, address = s.accept()
	while True:
		data = client.recv(size)
		if data:
			try:
				data = data.decode('ascii')
				print(data)
			except:
				pass
client.close()
