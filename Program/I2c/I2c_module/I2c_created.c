/*type[I2C_NAME_SIZE] – chip type, to initialize i2c_client.name
flags                             – to initialize i2c_client.flags
addr                               – stored in i2c_client.addr
platform_data             – stored in i2c_client.dev.platform_data
archdata                       – copied into i2c_client.dev.archdata
of_node                         – pointer to OpenFirmware device node
fwnode                           – device node supplied by the platform firmware
irq                                 – stored in i2c_client.irq

*/









struct i2c_board_info {
  char type[I2C_NAME_SIZE];
  unsigned short flags;
  unsigned short addr;
  void * platform_data;
  struct dev_archdata * archdata;
  struct device_node * of_node;
  struct fwnode_handle * fwnode;
  int irq;
};
