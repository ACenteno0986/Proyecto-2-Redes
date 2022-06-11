from email.mime import base
from flask import Flask, request
import socket
import base64

app= Flask(__name__)

serverAddressPort = ("8.8.8.8", 53)
bufferSize = 1024

@app.route('/api/dns_resolver/', methods=['POST'])
def post():
    print("Se genera un post")
    decoded = base64.b64decode(request.get_data())
    #print(decoded.hex())
    print(request.content_type)
    

    #f= open("log.txt","wb")
    #f.write(request.get_data())
    #f.flush()
    #f.close()

    try:
        UDPClientSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        print("Se inicia el socket")
        UDPClientSocket.sendto(decoded, serverAddressPort)
        print("Informacion enviada al server")
        msgFromServer = UDPClientSocket.recvfrom(bufferSize)
        print("Recibido del servidor")
        msg = "Message from Server {}".format(msgFromServer[0])
        print(msg) 
    finally:
        UDPClientSocket.close()
    #return msgFromServer

if __name__ == '__main__':
    print("Hola")
    app.run(host='0.0.0.0', port=443)