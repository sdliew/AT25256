#include <Arduino.h>
/*--------------------*/ 
/* Command Definition */ 
/*--------------------*/ 
 
#define AT25_WREN_CMD           0x06        /* Set Write Enable Latch */ 
#define AT25_WRDI_CMD           0x04        /* Reset Write Enable Latch */ 
#define AT25_RDSR_CMD           0x05        /* Read Status Register */ 
#define AT25_WRSR_CMD           0x01        /* Write Status Register */ 
#define AT25_READ_CMD           0x03        /* Read Data from Memory Array */ 
#define AT25_WRITE_CMD          0x02        /* Write Data to Memory Array */ 
 
#define AT25_STATUS             0x00        /* Status Register */ 
#define AT25_STATUS_MASK_READY  0x01        /* Status Register ready/busy mask */ 
#define AT25_BUSY               0x1         /* RDY bit of SR = 0x1 */ 
#define AT25_READY              0x0         /* RDY bit of SR = 0x0 */ 
 
#define AT25_STATUS_MASK_WREN   0x02        /* Status Register WREN mask */ 
#define AT25_WREN               0x2         /* WEN of SR = 0x1 */ 
 
#define SPICLOCK                13          //sck
#define DATAIN                  12          //MISO
#define DATAOUT                 11          //MOSI
#define WRITEPROTECT            10
#define SLAVESELECT              9          //ss
#define HOLD                     8

#define PAGESIZE  64

typedef uint8_t			u_char;		/**< 8-bit value */
typedef uint16_t                u_short;

class AT25256
{
  public:
  static void begin();
  void write_enable();
  u_char read_status_register();
  void write_status_register(u_char);
  void write_byte(u_short address, u_char);
  void write_page(u_short, u_char *);
  u_char read_byte(u_short, u_char);
  int read_page(u_short, u_char *);
  u_char SPI_transmit(u_char);
};
