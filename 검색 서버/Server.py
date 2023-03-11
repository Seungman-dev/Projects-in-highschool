#추가할 것: 여러 클라이언트에서 동시접속할 수 있게, 다른 ip에서 접속할 수 있게, 모듈화


from socket import *
import threading

import FileSearch

def while_msg_recv(client):
    while 1:
        msg = client.recv(1024)
        if msg != None:
            msg = msg.decode('utf-8')
            print(f"검색 키워드: [{msg}]")
            result = FileSearch.article_find(msg)
            print(f"결과 {len(result)}글자 전송")
            client.send(result.encode('utf-8'))
            
# def while_msg_recv(client):
#     print(1)
#     while 1:
        
#         msg = client.recv(1024)
#         if msg != None:
#             msg = msg.decode('utf-8')
#             print(f"검색 키워드: [{msg}]")
#             result = article_find(msg)
#             print(f"결과 {len(result)}글자 전송")
#             client.send(result.encode('utf-8'))


serverSocket = socket(AF_INET, SOCK_STREAM)

serverSocket.bind(('127.0.0.1', 8080))
serverSocket.listen()

t = []
index = 0

def accepting():
    global index
    global t
    print('[SERVER] 서버 시작')
    while 1:
        t.append(serverSocket.accept())
        print(f"[SERVER] {t[index][1][1]}클라이언트와 연결되었습니다.")
        t[index][0].send("[CLIENT] 서버와 연결되었습니다.".encode('utf-8'))
        t1 = threading.Thread(target = while_msg_recv, args = (t[index][0],))
        t1.start()
        index += 1

a = threading.Thread(target = accepting)
a.start()


# serverSocket.accept() -> ( 소켓, ('127.0.0.1', 포트) )
# connectionSocket, clientAddr = serverSocket.accept() #ckuebtAddr = ('127.0.0.1', 5144(포트))
# print("[SERVER] 클라이언트와 연결되었습니다.")
# print(clientAddr)
# connectionSocket.send("[CLIENT] 서버와 연결되었습니다.".encode('utf-8'))



# t2 = threading.Thread(target = while_msg_recv)
# t2.start()


#---


