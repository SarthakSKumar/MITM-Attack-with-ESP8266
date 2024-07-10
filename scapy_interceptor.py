from scapy.all import *


def packet_handler(packet):
    if packet.haslayer(IP) and packet.haslayer(TCP) and packet.haslayer(Raw):
        ip_packet = packet.getlayer(IP)
        tcp_packet = packet.getlayer(TCP)
        http_payload = bytes(packet.getlayer(Raw).load)

        if ip_packet.dst == "192.168.250.98" and tcp_packet.dport == 8000:
            if b"POST /data" in http_payload:
                print("\nIntercepted payload:")
                try:
                    print(http_payload.decode())
                except UnicodeDecodeError:
                    print("Payload contains non-UTF-8 characters")

                del packet[IP].chksum
                del packet[TCP].chksum

                send(packet, verbose=0, iface=iface_name)
                print("Packet intercepted and sent!\n")


iface_name = "Wi-Fi"

try:
    conf.use_pcap = True
    sniff(iface=iface_name, prn=packet_handler,
          filter="tcp and port 8000", store=0)
except KeyboardInterrupt:
    print("\nPacket capture stopped.")
