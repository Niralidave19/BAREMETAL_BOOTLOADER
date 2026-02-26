import serial
import time

length = 0
def compute_crc(data: int, framechkseq: int)-> int:
    """ Compute 1 byte checksum for the given data.
    :param data: The input data 24 bit (3 byte) long.
    :param framechkseq: The frame check sequence, which is a 1 byte long value and should be >= 0x80.
    :return: 32 byte checksumed data as an integer.
    """   
    # When data is zero
    if data == 0:
        return(framechkseq & 0x7f)
    # Initialize the data with padding to form a 32-bit integer
    data = (data << 7)
    # Find the first non-zero bit in the data
    cnt = 31
    while (data & (1 << cnt) == 0):
        cnt  -= 1
    # Initialize bit position
    bitpos = cnt - 7
    num = (data & (0xFF << bitpos)) >> bitpos
    rem = framechkseq
    while(num >= (1 << 7)):
        rem = num ^ framechkseq
        while(bitpos > 0):
            bitpos -= 1
            rem = (rem << 1) | ((data & (1 << bitpos)) >> bitpos)
            if (rem  >= (1 << 7)):
                break
        num = rem & 0xFF
    return(data | rem)


def check_crc(data: int, framechkseq: int) -> bool:
    """ Check if the CRC is valid for the given data.
    :param data: The input data 32 bit long.
    :param framechkseq: The frame check sequence, which is a 1 byte long value and should be >= 0x80.
    :return: True if the CRC is valid, False otherwise.
    """
    if data < framechkseq:
        return False
    # Find the first non-zero bit in the data
    cnt = 31
    while (data & (1 << cnt) == 0):
        cnt  -= 1
    # Initialize bit position
    bitpos = cnt - 7
    num = (data & (0xFF << bitpos)) >> bitpos
    rem = framechkseq
    while(num >= (1 << 7)):
        rem = num ^ framechkseq
        while(bitpos > 0):
            bitpos -= 1
            rem = (rem << 1) | ((data & (1 << bitpos)) >> bitpos)
            if (rem  >= (1 << 7)):
                break
        num = rem & 0xFF
    return(rem == 0)

def parsehex(file: str, framechkseq: int = 0xAA) -> list:
    """ Parse a hex file and return the data as a list of integers"""

    with open(file, 'r') as f:
        lines = f.readlines()

    lines = lines[1:-2]
    array = []

    for line in lines:
        # Remove ':XXXXXXXX' first 9 characters - : bytecount, address, type also remove Checksum and \n
        line = line[9:-3]
        # Pick 2 characters at a time and form a byte
        for i in range(0, len(line)-1, 2):
            array.append(int('0x'+line[i:i+2], 16))
        
    return array
def append_crc(array: list, framechkseq: int = 0xAA)-> list:
    """ Append CRC to the data array.
    :param array: The input data array.
    :param framechkseq: The frame check sequence, which is a 1 byte long value and should be >= 0x80."""
    global length
    # Make the array length a multiple of 3
    length = len(array)
    if length % 3 == 2:
        array.append(0xFF)
    elif length % 3 == 1:
        array.append(0xFF)
        array.append(0xFF)
    length = len(array)
    # THIS IS THE LENGTH OF FLASH CONTENT


    crc_array = []
    for i in range(0, length, 3):
        # Take 3 bytes at a time
        data = ((array[i+2] << 16) | (array[i+1] << 8) | (array[i]))
        data_crc = compute_crc(data, framechkseq)
        print('Data: ', bin(data))
        print('CRC Data', bin(data_crc))
        print('Vaidation : ', check_crc(data_crc, framechkseq),end= ' ')
        print('Actual data : ', bin(data_crc>>7))
        print()
        crc_array.append(data_crc)

    return crc_array

############################################################################
j=0
flash_data = (parsehex('stm32f446re.hex'))
'''
if length % 3 == 2:
    flash_data.append(0xFF)
elif length % 3 == 1:
    flash_data.append(0xFF)
    flash_data.append(0xFF)'''

flash_send = append_crc(flash_data,0b10101010)

ser = serial.Serial(port='COM3', baudrate=9600)
print("Requesting for flash 0x3")
ser.write(bytes([0x3]))
response = ord(ser.read(1))
#response = 0x1
count = 0
if(response == 0x1):
    #ACK received - send number of records and number of bytes
    print("Server acknowledging the request")
    #sending number of records and size
    print("Client sending size of flash data")
    print(length.to_bytes(2,'big'))
    ser.write(length.to_bytes(2,'big'))
    #ack for sector erase
    response = ord(ser.read(1))
    if(response == 0x1):
        print("received an ACK for sector erase")
        for i in flash_send:
            x1 = bytes([((i&0xff000000)>>24)])
            x2 = bytes([((i&0xff0000)>>16)])
            x3 = bytes([((i&0xff00)>>8)])
            x4 = bytes([((i&0xff))])
            ser.write(x1)
            ser.write(x2)
            ser.write(x3)
            ser.write(x4)
            count+=1
            response = ord(ser.read(1))
            print(hex(i>>7))
            #print("Sent data",count)

        '''
        for i in range(0, len(flash_data), 4):
            ser.write(bytes([flash_data[i]]))
            ser.write(bytes([flash_data[i+1]]))
            ser.write(bytes([flash_data[i+2]]))
            #ser.write(bytes[((i&0xff000000)>>24)])
            #ser.write(bytes[((i&0xff0000)>>16)])
            #ser.write(bytes[((i&0xff00)>>8)])
            #ser.write(bytes[((i&0xff))])
            #ser.write(i&0xff)
            response = ord(ser.read(1))
            print("Sent data")
            if(response == 0x1):
                continue
            elif(response == 0xF):
                break'''
print("done",count)





