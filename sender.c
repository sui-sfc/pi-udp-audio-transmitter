#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pulse/error.h>  /* pulseaudio */
#include <pulse/simple.h> /* pulseaudio */
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>


#define APP_NAME "pulseaudio_udp"
#define STREAM_NAME "play"
#define DATA_SIZE 1024

const int PortNumber = 60000;
const char *IPaddress = "192.168.0.29";

int main(int argc, char** argv) {
    int n,pa_errno, pa_result, written_bytes, sock_df;
    struct sockaddr_in addr;
    //UDPの設定
    sock_df = socket(AF_INET, SOCK_DGRAM, 0);
    //ソケット作成失敗
    if(sock_df < 0)
    {
        perror("Couldn't make a socket");
        return 1;
    }

    addr.sin_family = AF_INET; //IPv4
    addr.sin_port = htons(PortNumber); //port
    addr.sin_addr.s_addr = inet_addr(IPaddress); //server adress
    ssize_t send_status;


    //ALSA
    pa_sample_spec ss;
    ss.format = PA_SAMPLE_S16LE;
    ss.rate = 44100;
    ss.channels = 2;

    pa_simple *pa = pa_simple_new(NULL, APP_NAME, PA_STREAM_RECORD, NULL, STREAM_NAME, &ss, NULL, NULL, &pa_errno);
    if (pa == NULL) {
        fprintf(stderr, "ERROR: Failed to connect pulseaudio server: %s\n", pa_strerror(pa_errno));
        return 1;
    }
    char data[DATA_SIZE];
    while (1) {
        pa_result = pa_simple_read(pa, data, DATA_SIZE, &pa_errno);
        if (pa_result < 0) {
            fprintf(stderr, "ERROR: Failed to read data from pulseaudio: %s\n", pa_strerror(pa_errno));
            return 1;
        }
        send_status = sendto(sock_df, data , strlen(data) , 0,
                    (struct sockaddr *)&addr, sizeof(addr) );
        n = strlen(data);
        printf("%d\n", n);
        if(send_status < 0){
            perror("send error");
            return 1;
        }
    }

    pa_simple_free(pa);
    close(sock_df);
    return 0;
}
