import socket, time, json

lokiIP      = "192.168.10.218"
lokiPort    = 8888
bufferSize  = 1024
lokiRcvPort =8887

udpLokiServer = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
udpLokiRcvPort = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
udpLokiServer.bind(('',lokiPort))
udpLokiRcvPort.bind(('',lokiRcvPort))

dataTosend = ['{"Car":"Forward","Speed":"100"}','{"Car":"Backward"}','{"Car":"Left"}','{"Car":"Right"}','{"Car":"Stop"}']

for idx,val in enumerate(dataTosend):
    valToSend = str.encode(val)
    udpLokiServer.sendto(valToSend,(lokiIP,lokiPort))
    recieved = ''
    tempData =  ''
    # while recieved !='\n':
    #     recieved, ip = udpLokiServer.recvfrom(1024)
    #     tempData = tempData + recieved.decode('utf-8')
    #     # print(recieved.decode('utf-8'))
    # # json_obj = json.dumps(tempData.decode('utf-8'))
    # # print (tempData)
    #     # print ('got data distance :',json_obj.get('Distance'))
    #     # print ('got data digital :',json_obj['digital'])
    # print('got data:', tempData)
    # print ('finished reading')
    time.sleep(1)


