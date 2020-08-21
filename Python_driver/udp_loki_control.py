import socket, time

lokiIP      = "192.168.10.218"
lokiPort    = 8888
bufferSize  = 1024

udpLokiServer = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
udpLokiServer.bind(('',lokiPort))

dataTosend = ['{"Car":"Forward","Speed":"100"}','{"Car":"Backward"}','{"Car":"Left"}','{"Car":"Right"}','{"Car":"Stop"}']

for idx,val in enumerate(dataTosend):
    valToSend = str.encode(val)
    udpLokiServer.sendto(valToSend,(lokiIP,lokiPort))
    time.sleep(5)


