import socket
import os
import json

def printHeader():
	os.system('cls')
	print ('Welcome to Milestone 4 Demo')
	return

def printMotor ( lefts, leftd, rights, rightd  ):
	print ('\n\nLeft RPM:', lefts )
	if (leftd != '0'):
		print ('\nLeft Direction: REVERSE' )
	else:
		print ('\nLeft Direction: FORWARD' )
	print ('\nRight RPM:', rights )
	if (rightd != '0'):
		print ('\nRight Direction: REVERSE' )
	else:
		print ('\nRight Direction: FORWARD')
	
def printLineSet ( li0, li1, li2, li3, li4, li5, li6, li7 ):
	print ('\n\nCurrent line sensor data:')
	print ('\n 0 1 2 3 4 5 6 7')
	print ('\n | | | | | | | |')
	print ('\n', li0, li1, li2, li3, li4, li5, li6, li7)
	
def printSequence (seqnum):
	print('\n\nLast Sequence Number: ', seqnum)
	
def printMessageType (type):
	print('\n\nThe last non-empty received message type was:', type)
	
def printData():
	printHeader()
	printSequence(seq)
	printMessageType(lmt)
	printMotor( spl, dil, spr, dir  )
	printLineSet(l0, l1, l2, l3, l4, l5, l6, l7)
	
	
host = ''
port = 4000
backlog = 5
size = 1024

typ = 'n'
lmt = 'n'
seq = 0
dil = 0
dir = 0
spl = 0
spr = 0
l0 = 0
l1 = 0
l2 = 0
l3 = 0
l4 = 0
l5 = 0
l6 = 0
l7 = 0

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
				j = json.loads(data)
				if (j['typ'] == 'm'):
					typ = j['typ']
					seq = j['seq']
					dil = j['dil']
					dir = j['dir']
					spl = j['spl']
					spr = j['spr']
					printData()
					
				if (j['typ'] == 'l'):
					typ = j['typ']
					seq = j['seq']
					l0 = j['li0']
					l1 = j['li1']
					l2 = j['li2']
					l3 = j['li3']
					l4 = j['li4']
					l5 = j['li5']
					l6 = j['li6']
					l7 = j['li7']
					printData()
					
				if (j['typ'] == 'n'):
					typ = j['typ']
					seq = j['seq']
					printData()
					
				if (typ != 'n'):
					lmt = typ
			except:
				pass
client.close()