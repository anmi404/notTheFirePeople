import socket

UDP_IP = ""
UDP_PORT = 5005
DATA_FILE = 'sensor_data.txt'
fp = open(DATA_FILE, 'a')  

sock = socket.socket(socket.AF_INET, # Internet 
			socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))
while True:
	data, addr = sock.recvfrom(1024) #buffer size
	print "received message:", data
	fp.write(data+'\n');
fp.close()
