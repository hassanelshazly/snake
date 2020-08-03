import socket
import threading


def player1Sync():
    global player1
    global player2
    while True:
        try:
            data = player1.recv(1).decode()
            if not data:  # player disconnected, Ending Game
                print("player disconnected, ending game")
                exit()
            if data == "h":
                exit()
            player2.send(data.encode())
            print("player 1 send:" + data)

        except socket.error:
            print("Sockets error", flush=True)
            break

def player2Sync():
    global player1
    global player2
    while True:
        try:
            data = player2.recv(1).decode()
            if not data:  # player disconnected, Ending Game
                print("player disconnected, ending game")
                exit()
            if data == "h":
                exit()
            
            player1.send(data.encode())
            print("player 2 send:" + data)

        except socket.error:
            print("Sockets error", flush=True)
            break

ip = "127.0.0.1"
port = 9999
mysocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # SOCK_STREAM = TCP/IP --- AF_INET = IPV4
mysocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
mysocket.bind( (ip,port) )
mysocket.listen(2)
print("Server configuration successful (IP: "+str(ip)+" | Port: "+str(port)+")\n")

print("Waiting for player 1 to connect ...")
player1, addr1 = mysocket.accept()
print ( addr1 )
print("Player 1 connected successfully!\n ")
print("waiting for player 2 to connect ...")
player2, addr2 = mysocket.accept()
print (addr2 )
if player1 == player2 :
    print ("not good")
print("Player 2 connected successfully! \n")

player1.send(str("s").encode())
player2.send(str("v").encode())
print("Sent game start to both players")


p2 = threading.Thread(target=player1Sync)
p1 = threading.Thread(target=player2Sync)
# p1.daemon = True
p1.start()

# p2.daemon = True
p2.start()
print("Started direction sync threads for both players")