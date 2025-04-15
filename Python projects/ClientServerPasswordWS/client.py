import os
import asyncio
import sys

os.chdir('myfiles')
IP, DPORT = 'localhost', 8080

# Helper function that converts integer into 8 hexadecimal digits
# Assumption: integer fits in 8 hexadecimal digits
def to_hex(number):
    # Verify our assumption: error is printed and program exists if assumption is violated
    assert number <= 0xffffffff, "Number too large"
    return "{:08x}".format(number)

async def receive_long_message(reader):
    # First we receive the length of the message: this should be 8 total hexadecimal digits!
    # Note: `socket.MSG_WAITALL` is just to make sure the data is received in this case.
    data_length_hex = await reader.readexactly(8)

    # Then we convert it from hex to integer format that we can work with
    data_length = int(data_length_hex, 16)
    full_data = await reader.readexactly(data_length)
    return full_data.decode()

# TODO: Implement me for Part 2!
async def send_long_message(writer, data):
    # TODO: Send the length of the message: this should be 8 total hexadecimal digits
    #       This means that ffffffff hex -> 4294967295 dec
    #       is the maximum message length that we can send with this method!
    #       hint: you may use the helper function `to_hex`. Don't forget to encode before sending!
    #print(data)
    writer.write(to_hex(len(data)).encode())
    writer.write(data.encode())
    await writer.drain()

async def send_file(writer, filename):
    if os.path.isfile(filename):
        with open(filename, "rb") as file:
            file_body = file.read()
        str_file_body = file_body.decode("utf-8")
        await send_long_message(writer, f"put {filename}")
        await send_long_message(writer, str_file_body)
    else:
        #needed because before it was not returning to the while loop
        raise ValueError("Invalid filename.")
        

#client login
async def login(reader, writer):
    # Get the password to send from the server for login
    for attempts in range(3):
        password = input("Enter the password: ")
        # Send the password to the server
        await send_long_message(writer, password)
        # Receive a response from the server
        server_message = await receive_long_message(reader)
        if "welcome" in server_message.lower():
            print(server_message)
            intro = await receive_long_message(reader)
            print(intro)
            return True
        else:
            print(server_message)
    return False

async def handle_commands(reader, writer):
    while True:
        command = input("Enter command: ")
        if command == "close":
            writer.close()
            await writer.wait_closed()
            sys.exit()
        elif command == "list":
            await send_long_message(writer, command)
            ack = await receive_long_message(reader)
            files = await receive_long_message(reader)
            print(ack)
            print("Files on server:\n" + files)
        elif command.startswith("put "):
            try:
                await send_file(writer, command[4:])
                error = await receive_long_message(reader)
                print(error)
            except ValueError as e:                                 #after the error still contiues on the while loops and does not get stuck
                print(f"Error: {e}") 
                continue  
        elif command.startswith("get "):
            await send_long_message(writer, command)
            ack = await receive_long_message(reader)
            print(ack)
            server_file = await receive_long_message(reader)
            if server_file.startswith("NAK: "):                         #checks for an error message
                print(server_file)
                continue
            elif not os.path.exists(command[4:]):
                with open(command[4:], "wb") as file:
                    file.write(server_file.encode())
            else:
                print("The file already exists")
            error = await receive_long_message(reader)
            print(error)
        elif command.startswith("remove "):
            await send_long_message(writer, command)
            ack = await receive_long_message(reader)
            print(ack)
        else:
            print("No command found")

async def connect():
    while True:  # Persistent loop for reconnection
        try:
            reader, writer = await asyncio.open_connection(IP, DPORT)
            if await login(reader, writer):
                await handle_commands(reader, writer)
        except Exception as e:
            print(f"An error occurred: {e}")  # Added to print exceptions

async def main():
    await connect()

if __name__ == "__main__":
    asyncio.run(main())
