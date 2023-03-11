from socket import *
import threading

clientSock = socket(AF_INET, SOCK_STREAM)

def while_msg_send():
    while 1:
        msg = str(input('검색할 내용을 입력하세요: '))
        clientSock.send(msg.encode('utf-8'))
        msg = clientSock.recv(10000)
        if msg != None:
            msg = msg.decode('utf-8')
        print(msg)
        print('---------------------------------------------------')


while 1:
    try:
        clientSock.connect(('127.0.0.1', 8080))
        msg = clientSock.recv(10000)
        if msg != None:
            msg = msg.decode('utf-8')
        print(msg)
        break
    except:
        print('[CLIENT] 서버와 연결하지 못했습니다.')
    

t2 = threading.Thread(target = while_msg_send)
t2.start()