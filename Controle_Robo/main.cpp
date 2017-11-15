#include <string.h>
#include <espressif/esp_common.h>
#include <esp/uart.h>
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <dhcpserver.h>
#include <lwip/opt.h>
#include <lwip/arch.h>
#include <lwip/api.h>

#define AP_SSID "NOMEDOWIFI"
#define AP_PSK "SENHADOWIFI" //pelo menos 8 caracteres

struct sdk_softap_config ap_config;

const int D1 = 5, D2 = 4, D3 = 0, D4 = 2;  //portas do node

//headers
static void telnetTask(void *pvParameters);
static void zero();
static void controle(char *c);

//main function
extern "C" void user_init(void)
{
      //gpio config
      gpio_enable(D1, GPIO_OUTPUT);
      gpio_enable(D2, GPIO_OUTPUT);
      gpio_enable(D3, GPIO_OUTPUT);
      gpio_enable(D4, GPIO_OUTPUT);

      //wifi config
      uart_set_baud(0, 115200); // inicializa a wifi
      printf("SDK version:%s\n", sdk_system_get_sdk_version()); //mostra a versão do sdk
      sdk_wifi_set_opmode(SOFTAP_MODE); // quem vai gerar a rede é o esp
      struct ip_info ap_ip; // cria uma estrutura para armazenar as configurações de ip
      IP4_ADDR(&ap_ip.ip, 192, 168, 0, 100); //determina o ip do esp
      IP4_ADDR(&ap_ip.gw, 0, 0, 0, 0);// adiciona o getway
      IP4_ADDR(&ap_ip.netmask, 255, 255, 0, 0);//adiciona a mascara de rede
      sdk_wifi_set_ip_info(1, &ap_ip);//configura a rede
      strcpy((char *)ap_config.ssid, AP_SSID);// nome da rede wifi gerada
      ap_config.ssid_hidden = 0;// indica se a rede será visível ou não
      ap_config.channel = 3;// canal de comunicação wifi
      ap_config.authmode = AUTH_WPA_WPA2_PSK; // modo de autenticação
      ap_config.ssid_len = strlen(AP_SSID); //tamanho do vetor de caracteres ssid
      strcpy((char *)ap_config.password, AP_PSK); //senha
      ap_config.max_connection = 3;  // número máximo de dispositivos que podem se conectar ao esp
      ap_config.beacon_interval = 100; //intervalo de roteamento
      sdk_wifi_softap_set_config(&ap_config);//efetua as configurações na wifi
      ip_addr_t first_client_ip; // cria uma estrutura para armazenar o ip
      IP4_ADDR(&first_client_ip, 192, 168, 0, 101);//obriga o primeiro endereço  de ip a ser o colocado
      dhcpserver_start(&first_client_ip, 4);//configura servidor dhcp
      xTaskCreate(telnetTask, "telnetTask", 512, NULL, 2, NULL); // cria uma task para comunicação tcp ip
}

static void telnetTask(void *pvParameters)
{
      struct netconn *conn, *newconn; // estrutura que armazena estado da comunicação
      err_t err; //verifica erro de conexão

      conn = netconn_new(NETCONN_TCP);//cria um novo identificador de conexão

      netconn_bind(conn, NULL, 4000);//associa a conexão à porta 4000

      netconn_listen(conn);//começa a escutar a conexão

      while (1)
      {
            err = netconn_accept(conn, &newconn); //identifica nova conexão
            /* Processa a nova conexão */
            if (err == ERR_OK)
            {
                    struct netbuf *buf; // criando um buffer para armazenar os dados recebidos via wifi
                    void *data; //Variável que contem os dados raw
                    u16_t len; // tamanho dos dados recebidos
                    while ((err = netconn_recv(newconn, &buf)) == ERR_OK)
                    {//entrando na rotina se algum dado for recebido
                          do
                          {
                                netbuf_data(buf,&data,&len);//lê os dados recebidos e coloca no buffer
                                printf("%s\n", (char *)data); //é aqui que vocês recebem o sinal do wifi e convertem em controle para o robô
                                //é aqui que vocês recebem o sinal do wifi e convertem em controle para o robô
                                controle((char *)data);
                                err = netconn_write(newconn, "hello world\0"/*data*/, 12/*len*/, NETCONN_COPY);//envia um dado via wifi
                          } while (netbuf_next(buf) >= 0);//enquanto tiver dados recebidos, continua a executar
                          netbuf_delete(buf);//apagando o buffer
                    }
                    netconn_close(newconn);//fechando a conexão
                    netconn_delete(newconn);//deletando a conexão
              }
       }
}

static void controle(char *c)
{
      switch(c[0])
      {
            case 'w':
                    zero();
                    gpio_write(D1, 1);
                    gpio_write(D2, 0);
                    gpio_write(D3, 0);
                    gpio_write(D4, 1);
                    break;
            case 'a':
                    zero();
                    gpio_write(D1, 0);
                    gpio_write(D2, 1);
                    gpio_write(D3, 0);
                    gpio_write(D4, 1);
                    break;
            case 's':
                    zero();
                    gpio_write(D1, 0);
                    gpio_write(D2, 1);
                    gpio_write(D3, 1);
                    gpio_write(D4, 0);
                    break;
            case 'd':
                    zero();
                    gpio_write(D1, 1);
                    gpio_write(D2, 0);
                    gpio_write(D3, 1);
                    gpio_write(D4, 0);
                    break;
            case 'q':
                    zero();
                    break;
            default:
                    zero();
                    break;
      }
}

static void zero()
{
      gpio_write(D1, 0);
      gpio_write(D2, 0);
      gpio_write(D3, 0);
      gpio_write(D4, 0);
      vTaskDelay(50 / portTICK_PERIOD_MS);
}
